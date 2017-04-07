import QtQuick 2.8
import QtQuick.Controls 2.1

Page {
    id: page

    header: ToolBar {
        id: topbar

        contentItem: Label {
            text: "The List"
            font.pointSize: topbar.font.pointSize+5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    AddItemDialog {
        id: aid
    }

    ListView {
        id: listview
        model: PlanModel
        anchors.fill: parent

        delegate: MainDelegate {
            text: textRole
            width: parent.width
            rel1Text: rel1Role
            rel2Text: rel2Role

            onRequestMenu: {
                menu.x = x-listview.contentX-menu.width
                menu.y = y-listview.contentY
                menu.currentIndex = index
                menu.name = textRole
                menu.rel1 = PlanManager.indexFromText(rel1Role)
                menu.rel2 = PlanManager.indexFromText(rel2Role)
                menu.open()
            }
        }

        ViewButton {
            text: "+"
            onClicked: aid.open()
        }

        Menu {
            id: menu
            property int currentIndex: -1
            property string name
            property int rel1
            property int rel2

            MenuItem {
                text: "Edit"
                onClicked: {
                    aid.edit = true
                    aid.currrentIndex = menu.currentIndex
                    aid.setValues(menu.name, menu.rel1, menu.rel2)
                    aid.open()
                }
            }

            MenuItem {
                text: "Remove"
                onClicked: PlanManager.removeItem(menu.currentIndex)
            }
        }
    }
}
