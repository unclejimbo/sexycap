import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Sexycap"

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

    Rectangle {
        id: rectangle1
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        ColumnLayout {
            spacing: 5
            anchors.horizontalCenter: parent.horizontalCenter

            RowLayout {
                width: 800
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: false
                Layout.fillWidth: false
                spacing: 15
                Button {
                    id: capbtn
                    text: "Caputure!"
                    Layout.fillHeight: false
                    enabled: true
                    onClicked: function() {
                        if (pcap.captureStart(device.currentIndex,
                                              mixedMode.checked))
                            console.log("capture sucess!")
                    }
                }

                Button {
                    id: stopbtn
                    text: qsTr("Stop!")
                    enabled: false
                }

                Row {
                    id: row1
                    width: 200
                    height: 400
                    Layout.fillHeight: true
                    spacing: 5

                    Label {
                        text: "Select An Interface"
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    ComboBox {
                        id: device
                        width: 100
                        anchors.verticalCenter: parent.verticalCenter
                        clip: false
                        model: pcap.devices()
                        textRole: "description"
                    }
                }
                CheckBox {
                    id: mixedMode
                    text: "Mixed Mode"
                    Layout.fillHeight: false
                    checked: true
                }

                Row {
                    id: row2
                    width: 200
                    height: 400
                    Layout.fillHeight: true
                    spacing: 5

                    Label {
                        text: qsTr("Filter")
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    TextField {
                        id: filter
                        width: 200
                        anchors.verticalCenter: parent.verticalCenter
                        placeholderText: qsTr("Packet Filter")
                    }
                }
            }

            SplitView {
                height: 550
                Layout.fillHeight: true
                Layout.rowSpan: 1
                clip: false
                orientation: Qt.Vertical
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                TableView {
                    id: tabv
                    model: pcap.packetModel
                    width: 800
                    height: 250
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    TableViewColumn{ role: "no"; title: "No"; width: 20 }
                    TableViewColumn{ role: "time"; title: "Time"; width: 100 }
                    TableViewColumn{ role: "len"; title: "Length"; width: 80}
                    TableViewColumn{ role: "src"; title: "Source"; width: 150 }
                    TableViewColumn{ role: "dst"; title: "Destination"; width: 150 }
                    TableViewColumn{ role: "describe"; title: "Desctiption"; width: 300 }
                    onCurrentRowChanged: full_text.update_text(tabv.currentRow)
                }

                Text {
                    id: full_text
                    visible: true
                    text: ""
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 10

                    function update_text(row_index) {
                        var str = pcap.displaySelected(row_index);
                        full_text.text = str;
                    }
                }

            }
        }
    }
}
