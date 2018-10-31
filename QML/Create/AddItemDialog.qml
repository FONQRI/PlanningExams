import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Popup {
	id: popup
	dim: true
	spacing: 8
	width: parent.width*3/4
	height: implicitHeight
	x: (parent.width-width)/2
	y: (parent.height-height)/2

	property bool edit: false
	property int currrentIndex: -1

	onClosed: {
		nameField.clear()
		combo1.currentIndex = 0
		combo2.currentIndex = 0
		check1.checked = false
		check2.checked = false
		edit = false
		currrentIndex = -1
	}

	function setValues(name, r1, r2) {
		nameField.text = name
		combo1.currentIndex = r1<0 ? 0:r1
		combo2.currentIndex = r2<0 ? 0:r2
		check1.checked = (r1>=0)
		check2.checked = (r2>=0)
	}

	contentItem: Column {
		spacing: popup.spacing

		Label {
			visible: edit
			font.pointSize: popup.font.pointSize+3
			text: edit ? "Editing":""
			width: parent.width
		}

		TextField {
			id: nameField
			width: parent.width
			placeholderText: "Name"
		}

		Column {
			width: parent.width
			spacing: popup.spacing/2

			Label {
				width: parent.width
				elide: Text.ElideRight // TODO elide left
				text: "Select the first relation\nSelected: "+
					  (!check1.checked ? "None":combo1.displayText)
			}

			RowLayout {
				width: parent.width

				CheckBox {
					id: check1
					enabled: combo1.count
				}

				ComboBox {
					id: combo1
                    model: planModel
					textRole: "textRole"
					width: parent.width
					Layout.fillWidth: true
					enabled: check1.checked
				}
			}
		}

		Column {
			width: parent.width
			spacing: popup.spacing/2

			Label {
				width: parent.width
				elide: Text.ElideRight // TODO elide left
				text: "Select the first relation\nSelected: "+
					  (!check2.checked ? "None":combo2.displayText)
			}

			RowLayout {
				width: parent.width

				CheckBox {
					id: check2
					enabled: combo2.count
				}

				ComboBox {
					id: combo2
                    model: planModel
					textRole: "textRole"
					width: parent.width
					Layout.fillWidth: true
					enabled: check2.checked
				}
			}
		}

		RowLayout {
			width: parent.width
			spacing: popup.spacing/2

			Button {
				text: "Cancel"
				Layout.fillWidth: true
				onClicked: popup.close()
			}

			Button {
				text: "OK"
				Layout.fillWidth: true

				onClicked: {
					if (edit)
                        planManager.editItem(popup.currrentIndex, nameField.text,
											 check1.checked ? combo1.currentIndex:-1,
															  check2.checked ? combo2.currentIndex:-1)
					else
                        planManager.addItem(nameField.text,
											check1.checked ? combo1.currentIndex:-1,
															 check2.checked ? combo2.currentIndex:-1)

					popup.close()
				}
			}
		}
	}
}
