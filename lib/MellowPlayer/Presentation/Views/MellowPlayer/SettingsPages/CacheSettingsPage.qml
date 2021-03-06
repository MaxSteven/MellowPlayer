import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

Item {
    clip: true

    ColumnLayout {
        anchors.fill: parent
        clip: true
        spacing: 0

        ToolButton{
            highlighted: true
            hoverEnabled: true
            text: qsTr("Clear cookies")
            onClicked: {
                paneRestart.state = "visible"
                _cookies.clear();
            }

            Layout.fillWidth: true
        }

        Rectangle {
            color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
            height: 1
            Layout.fillWidth: true
        }

        ToolButton {
            highlighted: true
            hoverEnabled: true
            text: qsTr("Clear cache")
            onClicked: {
                paneRestart.state = "visible"
                _cache.clear();
            }

            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
        }
    }


    Pane {
        id: paneRestart

        clip: true
        width: parent.width

        Material.background: _theme.primary
        Material.elevation: 8
        Material.foreground: _theme.primaryForeground
        Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

        RowLayout {
            id: rowLayout
            anchors.fill: parent
            spacing: 8

            Label {
                text: MaterialIcons.icon_info
                font {
                    family: MaterialIcons.family
                    pixelSize: 32
                }
            }

            Label {
                text: qsTr("You need to restart MellowPlayer for the change to be applied.")
                font.pixelSize: 16
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                highlighted: true
                text: qsTr("Restart now")
                onClicked: _app.restart()
            }
        }

        state: "hidden"
        states: [
            State {
                name: "hidden"

                PropertyChanges { target: paneRestart; y: parent.height }
            },
            State {
                name: "visible"

                PropertyChanges { target: paneRestart; y: parent.height - paneRestart.implicitHeight }
            }
        ]
        transitions: Transition {
            from: "hidden"
            to: "visible"

            PropertyAnimation { properties: "y" }
        }
    }
}
