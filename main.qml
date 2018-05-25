import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Window {
    id: window
    visible: true
    width: 800
    height: 280
    title: qsTr("BC_Tester")

    Button {
        id: button
        width: 120
        height: 40
        text: qsTr("打开")
        opacity: 0.8
        font.pointSize: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height * 0.35
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: parent.width * 0.35
        onClicked: {
            if (button.text == "打开")
            {
                MainModel.openDevices()
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
        text: qsTr("测量: ")
        font.bold: true
        font.pointSize: 100
        fontSizeMode: Text.Fit
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: parent.width * -0.25
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: text1
        text: MainModel.value
        font.bold: true
        renderType: Text.NativeRendering
        anchors.left: label.right
        anchors.verticalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 100   }
}
