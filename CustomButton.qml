import QtQuick 2.0

Rectangle {
    property int _radius: 25
    property bool _visible: true
    property bool _active: true
    property int _opacity: 1
    property string _label: "new button"
    property string _color: "grey"
    property string _colorLabel: "black"

    signal buttonClicked

    width: labelButton.contentWidth + 15
    height: labelButton.contentHeight + 10

    radius: _radius
    opacity: _opacity
    visible: _visible
    color: _color

    Text {
        id: labelButton
        anchors.centerIn: parent
        color: _colorLabel
        text: qsTr("%1").arg(_label)
    }

    MouseArea{
    hoverEnabled: true
    anchors.fill: parent
    //emitting signals acording to produced event
    onClicked: buttonClicked()
    onEntered: cursorShape = Qt.PointingHandCursor
    onPressed: _opacity = 0.8
    onReleased: _opacity = 1.0
    }

}
