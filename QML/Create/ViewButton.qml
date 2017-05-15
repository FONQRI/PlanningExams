import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

RoundButton {
	id: control
	implicitWidth: 75
	implicitHeight: 75
	x: endX
	y: endY

	property bool rightEdge: true

	state: "opened"

	Connections {
		target: control.parent

		onVerticalVelocityChanged: {
			if (control.parent.contentY <= 0 ||
					control.parent.contentY+control.parent.height
					>= control.parent.contentHeight)
				return

			if (control.parent.verticalVelocity > 0)
			{
				if (control.state == "opened")
					control.state = "closed"
			}
			else if (control.parent.verticalVelocity < 0)
			{
				if (control.state == "closed")
					control.state = "opened"
			}
		}
	}


	property real endX: rightEdge ? parent.width-width*3/2:width/2
	property real endY: parent.height-height*3/2

	states: [
		State {
			name: "opened"
			PropertyChanges { target: control; y: endY }
		},
		State {
			name: "closed"
			PropertyChanges { target: control; y: control.parent.height }
		}
	]

	transitions: [
		Transition {
			reversible: true
			from: "closed"
			to: "opened"

			NumberAnimation {
				property: "y"
				target: control
				duration: 200
			}
		}
	]
}
