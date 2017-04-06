import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

ItemDelegate {
    id: control
    spacing: 6
    property bool expand: expandButton.checked

    property alias rel1Text: rel1Label.text
    property alias rel2Text: rel2Label.text

    contentItem: RowLayout {
        spacing: control.spacing/2

        Column {
            id: column
            clip: true
            Layout.fillWidth: true
            spacing: control.spacing

            Label {
                id: topLabel
                text: control.text
                width: parent.width
                elide: Text.ElideRight // TODO elide left
                font.pointSize: control.font.pointSize+2
            }

            Column {
                width: parent.width
                spacing: control.spacing/2
                height: expand ? implicitHeight:0
                Behavior on height { NumberAnimation { easing.type: Easing.OutQuad } }

                Label {
                    id: rel1Label
                    visible: text
                    width: parent.width
                    elide: Text.ElideRight // TODO elide left
                }

                Label {
                    id: rel2Label
                    visible: text
                    width: parent.width
                    elide: Text.ElideRight // TODO elide left
                }
            }
        }

        RoundButton {
            id: expandButton
            text: "\u2304"
            checkable: true
            visible: rel1Text && rel2Text
        }

        RoundButton {
            text: "⋮"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
