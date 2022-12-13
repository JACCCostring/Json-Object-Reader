import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Window {
    id: mainWindow
    width: Screen.width - 50
    height: Screen.height - 70
    x: 20
    visible: true
    title: qsTr("Object Reader")
    color: "transparent"
    Rectangle{ //for making gradient color effect
        width: mainWindow.width
        height: mainWindow.height
        radius: 25
        gradient: Gradient{
            GradientStop{ position: 0.5; color: "#4d0026" }
            GradientStop{ position: 1.0; color: "#33001a" }
        }
    }

    flags: Qt.FramelessWindowHint

    //    mouse area
    MouseArea{
        //if mouse x,y is in frame top border then show frame again
        hoverEnabled: true
        width: mainWindow.width
        height: 100

        onEntered: {
            btnCloseMainWindow._active = true
            animCloseBtn.running = true
        }
        onExited: {
            btnCloseMainWindow._active = false
            animCloseBtnDissapear.running = true
        }
    }

    property int rectModelWidth: 200
    property int rectModelHeight: 200
    property real menuOpacity: 1.0
    property int statTotalElements: 0
    property int statCurrentElement: 0

    ScrollView{
        id: scrollViewRect
        x: 5
        y: 100
        clip: true

        width: mainWindow.width - 50
        height: mainWindow.height - 100

        Grid{
            id: gridForModel
            spacing: 4

            Repeater{
                id: modelDataVisual
                anchors.fill: parent

                delegate: Image{
                    id: rectModel
                    width: rectModelWidth
                    height: rectModelHeight
                    source: "qrc:/icons/json-miniature.png"
                    fillMode: Image.PreserveAspectFit

                    property int _id: FileReader.getID()[index]
                    property string name: FileReader.getName()[index]
                    property string country: FileReader.getCountry()[index]

                    opacity: menuOpacity //same as the main menu
                    scale: 0.5

                    MouseArea{
                        hoverEnabled: true
                        anchors.fill: parent
                        onEntered: { cursorShape = Qt.PointingHandCursor; parent.scale = 1 }
                        onExited: parent.scale = 0.5
                        onClicked: {
                            textDetails.text = "ID: " + modelDataVisual.itemAt(index)._id + "\n" +
                                    "Name: " + modelDataVisual.itemAt(index).name + "\n"+
                                    "Country: " + modelDataVisual.itemAt(index).country

                            miniatureDetail.visible = true
                            miniatureDetail.opacity = 1
                            statCurrentElement = index
                            animRecDetailsShow.running = animRecDetailsShow.running ? false : true
                        }
                    } //end of MouseArea
                } //end of image
            } //end of model
        } //end of grid for model
    } //end of ScrollView

    //rectangle for json object details
    Rectangle {
        id: miniatureDetail
        color: "pink"
        opacity: 0.7
        width: 200
        height: 200
        x: 0
        y: 300

        radius: 50
        visible: false

        Text{
            id: textDetails
            text: qsTr("details")
            font.pixelSize: 11
            color: "#400080"
            clip: true
            width: 190
            height: 200
            x: 5
            y: 70
            font.bold: true
        }

        CustomButton{
            _label: "X"
            _color: "lightblue"
            onButtonClicked: { animRecDetailsHide.running = true }
        }
    }

    //close button for closing window
    CustomButton{
        id: btnCloseMainWindow

        y: 50
        x: mainWindow.width / 2

        _label: ""
        //        _colorLabel: "white"
        _opacity: 0
        _color: "transparent"
        //    _active: false
        Image {
            id: name
            anchors.centerIn: parent
            width: parent.width + 40
            height: parent.height

            source: "qrc:/icons/button-lighter.png"
        }
        onButtonClicked: mainWindow.close()
    }

    //custom menu
    CustomMenu{
        id: mainMenu
        _height: mainWindow.height
        opacity: menuOpacity
        x: -170 //to produce hiden effect

        gradient: Gradient{
            GradientStop{ position: 0.0; color: "#404040" }
            GradientStop{ position: 0.33; color: "#400080" }
            GradientStop{ position: 1.0; color: "#e60073" }
        }

        //    icon
        Image {
            id: notchIcon

            width: 32
            height: 32

            property int clickCounted: 0

            anchors.bottom: parent.bottom
            anchors.right: parent.right

            source: "qrc:/icons/menu-notch.png"
            fillMode: Image.PreserveAspectFit
            scale: 0.8

            MouseArea{
                hoverEnabled: true
                anchors.fill: notchIcon
                onEntered: { cursorShape = Qt.PointingHandCursor; notchIcon.scale = 1.0 }
                onExited: notchIcon.scale = 0.8
                onClicked: {
                    notchIcon.clickCounted++

                    if(notchIcon.clickCounted === 2){
                        animDragMenuIn.running = true;
                        notchIcon.clickCounted = 0
                        sizeSquare.visible = false
                        opacityMenuSlider.visible = false
                        statistics.visible = false
                        currentStatistics.visible = false
                        loadJsonBtn.visible = false
                    }

                    else {
                        animDragMenuOut.running = true;
                        sizeSquare.visible = true
                        opacityMenuSlider.visible = true
                        statistics.visible = true
                        currentStatistics.visible = true
                        loadJsonBtn.visible = true
                    }
                }
            }
        }

        //    column layout
        ColumnLayout{
            anchors.centerIn: mainMenu
            spacing: 50

            //total stats text
            Text {
                id: statistics
                text: qsTr("Total Elements: ")
                color: "#9fff80"
                font.pixelSize: 16
                font.bold: true
                visible: false

                Text {
                    text: qsTr("%1").arg(statTotalElements)
                    color: "yellow"
                    font.pixelSize: 16
                    anchors.left: statistics.right
                }
            }
            // current stats text
            Text {
                id: currentStatistics
                text: qsTr("Current Element: ")
                color: "#9fff80"
                font.pixelSize: 16
                font.bold: true
                visible: false

                Text {
                    text: qsTr("%1").arg(statCurrentElement)
                    color: "yellow"
                    font.pixelSize: 16
                    anchors.left: currentStatistics.right
                }
            }
            //load json button
            CustomButton{
                id: loadJsonBtn
                _label: "       load json"
                _color: "transparent"
                _colorLabel: "yellow"
                visible: false

                Image {
                    width: 32
                    height: 32
                    source: "qrc:/icons/jsonfile.png"
                    fillMode: Image.PreserveAspectFit
                }

                onButtonClicked: loadJSONFile.open()
            }

            //            size miniatures
            Slider{
                id: sizeSquare
                from: 20
                to: 200
                value: 200
                visible: false

                handle: Rectangle{
                    width: 16;
                    height: 16;
                    color: sizeSquare.value > 0.5 ? "#400080" : "#e60073"
                    x: sizeSquare.leftPadding + sizeSquare.visualPosition * (sizeSquare.availableWidth - width)
                    y: sizeSquare.availableHeight - 2
                    radius: 100
                }
                onValueChanged: {
                    rectModelWidth = sizeSquare.value
                    rectModelHeight = sizeSquare.value
                }
            }
            //opacity slider
            Slider{
                id: opacityMenuSlider
                from: 0.3
                to: 1.0
                value: 1.0
                visible: false
                handle: Rectangle{
                    width: 16;
                    height: 16;
                    color: opacityMenuSlider.value > 0.5 ? "#400080" : "#e60073"
                    x: opacityMenuSlider.leftPadding + opacityMenuSlider.visualPosition * (opacityMenuSlider.availableWidth - width)
                    y: opacityMenuSlider.availableHeight - 2
                    radius: 100
                }
                onValueChanged: menuOpacity = opacityMenuSlider.value
            }

        } //end of Layout

    } //end of CustomMenu

    //fileDialog for opening json file
    FileDialog{
        id: loadJSONFile
        title: "select a JSON file"
        folder: shortcuts.documents
        onAccepted:{
            FileReader.openFile(loadJSONFile.fileUrl)
            gridForModel.columns = mainWindow.width / rectModelWidth - 1
            gridForModel.rows = FileReader.getModelDataSize()
            modelDataVisual.model = FileReader.getModelDataSize()
            statTotalElements = FileReader.getModelDataSize() - 1
        }

    }
    //animation menu main window close button

    NumberAnimation {
        id: animCloseBtn
        target: btnCloseMainWindow
        property: "opacity"
        from: 0
        to: 1
        duration: 700
        easing.type: Easing.InOutQuad
    }

    //same but to dissapear close button
    NumberAnimation {
        id: animCloseBtnDissapear
        target: btnCloseMainWindow
        property: "opacity"
        from: 1
        to: 0
        duration: 700
        easing.type: Easing.InOutQuad
    }

    //same but to drag menu out
    NumberAnimation {
        id: animDragMenuOut
        target: mainMenu
        property: "x"
        running: false
        from: -170
        to: 0
        duration: 700
        easing.type: Easing.InOutQuad
    }
    //same but to drag menu in
    NumberAnimation {
        id: animDragMenuIn
        target: mainMenu
        property: "x"
        running: false
        from: 0
        to: -170
        duration: 700
        easing.type: Easing.InOutQuad
    }
    //animation for Rectangle json object details show
    NumberAnimation {
        id: animRecDetailsShow
        target: miniatureDetail
        property: "x"
        duration: 500
        from: 0
        to: Screen.width - 250

        easing.type: Easing.InOutQuad
    }
    //animation for Rectangle json object details hide
    NumberAnimation {
        id: animRecDetailsHide
        target: miniatureDetail
        property: "opacity"
        duration: 1600
        from: 1.0
        to: 0.0

        easing.type: Easing.InOutQuad
    }
}
