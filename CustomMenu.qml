import QtQuick 2.0

Rectangle {
    property int _width: 200
    property int _height: 400
    property int _radius: 25
    property bool _visible: true
    property bool _active: true
    property int _opacity: 1
    property string _color: "grey"

//    signal buttonEntered
//    signal buttonExited

    width: _width
    height: _height
    radius: _radius
    opacity: _opacity
    visible: _visible
    color: _color

    MouseArea{
    hoverEnabled: true
    anchors.fill: parent
    //emitting signals acording to produced event
//    onEntered: buttonEntered()
//    onExited: buttonExited()
    }
}
