import QtQuick 2.8
import QtQuick.Controls 2.1
import Qt.labs.settings 1.0
import QtQuick.Layouts 1.3

Page {
	id: page

	Settings {
		property alias confirmed: page.confirmed
	}

	property bool confirmed: false

	footer: RowLayout {
		spacing: 0
		Button {
			text: "Confirm"
			visible: !confirmed
			Layout.fillWidth: true

			onClicked: {
				confirmed = true
                programmer.paint()
                planManager.databseToModel()
			}
		}

		Button {
			text: "Clear"
			Layout.fillWidth: true

			onClicked: {
				confirmed = false
                planManager.clear()
			}
		}
	}

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

	ColorDialog {
		id: cd
	}

	ListView {
		id: listview
        model: planModel
		anchors.fill: parent
		clip: true

		delegate: MainDelegate {
			text: textRole
			width: parent.width
			rel1Text: rel1Role
			rel2Text: rel2Role
			currentColor: colorRole

			onRequestMenu: {
				menu.x = x-listview.contentX-menu.width
				menu.y = y-listview.contentY
                menu.current_Index = index
				menu.name = textRole
				menu.color = colorRole
				menu.id = idRole
                menu.rel1 = planManager.searchModel(rel1Role)
                menu.rel2 = planManager.searchModel(rel2Role)
				menu.open()
			}
		}

		ViewButton {
			text: "+"
			onClicked: aid.open()
		}

		Menu {
			id: menu
            property int current_Index: -1
			property string name
			property int rel1
			property int rel2
			property int color
			property int id

			MenuItem {
				text: "Edit"
				onClicked: {
					aid.edit = true
                    aid.currrentIndex = menu.current_Index
					aid.setValues(menu.name, menu.rel1, menu.rel2)
					aid.open()
				}
			}

			MenuItem {
				text: "Remove"
                onClicked: planManager.removeItem(menu.current_Index)
			}

			MenuItem {
				visible: confirmed
				text: "Choose Color"
				onClicked: {
					cd.currentID = menu.id
					cd.currentColor = menu.color
                    cd.current_Index = menu.current_Index
					cd.open()
				}
			}
		}
	}
}
