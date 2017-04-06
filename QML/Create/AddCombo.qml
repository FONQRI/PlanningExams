import QtQuick 2.0
import QtQuick.Controls 2.1

ComboBox {
    id: control


    delegate: ItemDelegate {
        width: control.popup.width
        text: textRole
        font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
        highlighted: control.highlightedIndex == index
        hoverEnabled: control.hoverEnabled
    }
}
