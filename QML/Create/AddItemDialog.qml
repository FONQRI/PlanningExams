import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Popup {
    id: popup
    dim: true
    spacing: 8
    height: implicitHeight
    x: (parent.width-width)/2
    y: (parent.height-height)/2

    contentItem: Column {
        spacing: popup.spacing

        TextField {
            id: nameField
            placeholderText: "Name"
        }

        Column {
            width: parent.width
            spacing: popup.spacing/2

            Label {
                text: "Select the first relation"
            }

            AddCombo {
                id: combo1
                model: PlanModel
                width: parent.width
            }
        }

        Column {
            width: parent.width
            spacing: popup.spacing/2

            Label {
                text: "Select the second relation"
            }

            ComboBox {
                id: combo2
                model: PlanModel
                width: parent.width
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
                    popup.close()
                    PlanManager.addItem(nameField.text, combo1.currentIndex, combo2.currentIndex)
                }
            }
        }
    }
}
