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

    contentItem: Column {
        spacing: popup.spacing

        TextField {
            id: nameField
            placeholderText: "Name"
            width: parent.width
        }

        Column {
            width: parent.width
            spacing: popup.spacing/2

            Label {
                width: parent.width
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
                    model: PlanModel
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
                text: "Select the first relation\nSelected: "+
                      (!check2.checked ? "None":combo2.displayText)
            }

            RowLayout {
                width: parent.width

                CheckBox {
                    id: check2
                    enabled: combo1.count
                }

                ComboBox {
                    id: combo2
                    model: PlanModel
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
                    popup.close()
                    PlanManager.addItem(nameField.text, check1.checked ? -1:combo1.currentIndex,
                                                                         check2.checked ? -1:combo2.currentIndex)
                }
            }
        }
    }
}
