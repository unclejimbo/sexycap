import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Hello World"

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Open"
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: "Exit"
                onTriggered: Qt.quit();
            }
        }
    }

    TabView {
        anchors.fill: parent

        Tab {
            title: "Welcome"
            Rectangle {
                anchors.fill: parent

                RowLayout {
                    anchors.horizontalCenter: parent.horizontalCenter
                    Label {
                        text: "Please select an interface"
                    }
                    ComboBox {
                        width: 500
                        model: deviceModel
                        textRole: "name"
                    }
                }
            }
        }

        Tab {
            title: "Capture"
            Label {
                text: "Capturing"
                anchors.centerIn: parent
            }
        }
    }
}
