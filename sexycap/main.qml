import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 800
    height: 600
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

        // Welcom tab
        Tab {
            title: "Welcome"
            Rectangle {
                anchors.fill: parent

                ColumnLayout {
                    anchors.horizontalCenter: parent.horizontalCenter

                    RowLayout {
                        Label {
                            text: "Select An Interface"
                        }
                        ComboBox {
                            width: 500
                            model: deviceModel
                            textRole: "description"
                        }
                        CheckBox {
                            text: "Advanced"
                            checked: false
                            onCheckedChanged: function() {
                                if (checked == true)
                                    advanced.visible = true
                                else
                                    advanced.visible = false
                            }
                        }
                    }

                    RowLayout {
                        id: advanced
                        visible: false
                        CheckBox {
                            id: mixedMode
                            text: "Mixed Mode"
                            checked: true
                        }
                        Label {
                            text: "Time Out (ms):"
                        }
                        TextField {
                            id: timeOut
                            text: "1000"
                            validator: IntValidator {bottom: 0;}
                        }
                    }

                    RowLayout {
                        Button {
                            text: "Caputure!"
                        }
                    }
                }
            }
        }

        // Capture tab
        Tab {
            title: "Capture"

            Rectangle {
                anchors.fill: parent

                TableView {
                    anchors.fill: parent

                    TableViewColumn {
                        title: "No"
                        width: 50
                    }
                    TableViewColumn {
                        title: "Protocol"
                        width: 100
                    }
                }
            }
        }
    }
}
