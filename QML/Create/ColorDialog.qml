import QtQuick 2.8
import QtQuick.Controls 2.1

Popup {
    id: popup
    modal: true
    x: (parent.width-width)/2
    y: (parent.height-height)/2

    width: parent.width*3/4
    height: parent.height/2

    onOpened: rep.model = PlanManager.getAvailableColors(id)

    property int planIndex
    property int currentColor
    property int currentID

    contentItem: Page {
        Flickable {
            anchors.fill: parent
            contentHeight: grid.implicitHeight

            Grid {
                id: grid
                width: parent.width
                spacing: 10

                Repeater {
                    id: rep

                    delegate: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 40
                        antialiasing: true
                        radius: width
                        border.color: "black"
                        color: "transparent"

                        Label {
                            anchors.fill: parent
                            text: currentColor == -1 ? "?":currentColor
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }
        }

        footer: Button {
            text: "+"
            width: parent.width
        }
    }
}
