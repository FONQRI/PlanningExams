import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

ItemDelegate {
    id: control
    spacing: 6
    property bool expand: expandButton.checked

    property alias rel1Text: rel1Label.text
    property alias rel2Text: rel2Label.text

    signal requestMenu(int x, int y)

    contentItem: RowLayout {
        spacing: control.spacing/2

        Column {
            id: column
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
                clip: true
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
            visible: rel1Text || rel2Text
        }

        RoundButton {
            text: "⋮"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: requestMenu(x+control.leftPadding+control.x+width/2,
                                   y+control.y+control.topPadding+height/2)
        }
    }

    Rectangle {
        color: "black"
        height: 1
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
