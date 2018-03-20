import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Window {
    id: window
    visible: true
    width: 640
    height: 280
    title: qsTr("Hello World")

    Button {
        id: button
        width: 200
        height: 60
        text: qsTr("打开")
        opacity: 0.8
        font.pointSize: 30
        anchors.topMargin: 30
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            if (button.text == "打开")
            {
                MainModel.openDevices()
                text2.text = "12"
                button.text = "关闭"
            }
            else{
                MainModel.closeDevices()
                button.text = "打开"
            }
        }
    }

    Label {
        id: label
        text: qsTr("距离：")
        font.pointSize: 30
        fontSizeMode: Text.Fit
        anchors.horizontalCenterOffset: -100
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: text1
        text: MainModel.value
        renderType: Text.NativeRendering
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 100
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
    }

    Label {
        id: label1
        text: qsTr("XX：")
        font.pointSize: 30
        fontSizeMode: Text.Fit
        anchors.horizontalCenterOffset: -100
        anchors.verticalCenterOffset: 50
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: text2
        text: ""
        renderType: Text.NativeRendering
        anchors.verticalCenterOffset: 50
        anchors.horizontalCenterOffset: 100
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
    }
}
