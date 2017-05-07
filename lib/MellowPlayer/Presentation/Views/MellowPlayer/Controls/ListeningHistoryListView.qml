import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import MellowPlayer 3.0

Item {
    ListView {
        id: listView

        property var collapsedSections: { return {} }

        signal sectionCollapsedChanged(var sectionName, var sectionIsCollapsed)

        anchors.fill: parent
        clip: true
        spacing: 0
        model: listeningHistory.model
        delegate: ListeningHistoryEntryDelegate { width: listView.width; }
        section.criteria: ViewSection.FullString
        section.delegate: ListeningHistorySectionDelegate { width: listView.width; }
        section.property: "dateCategory"

        add: Transition {
            SequentialAnimation {
                NumberAnimation { properties: "x"; duration: 0; from: 0; to: 950 }
                PauseAnimation { duration: 250; }
                NumberAnimation { properties: "x"; duration: 300; from: 950; to: 0 }
            }
        }
        displaced: Transition {
           NumberAnimation { properties: "x, y"; duration: 300 }
        }

        ScrollBar.vertical: ScrollBar {
           parent: listView.parent
           anchors.top: listView.top
           anchors.left: listView.right
           anchors.bottom: listView.bottom
           anchors.margins: 2
           active: hovered
           hoverEnabled: true
        }
    }
}

