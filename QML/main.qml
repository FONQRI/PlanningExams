import QtQuick 2.7
import QtQuick.Controls 2.0
import "Create"

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: qsTr("Plan")

    MainListPage {
        anchors.fill: parent
    }
}
