import bb.cascades 1.2

Page {
    Container {
        TextArea {
            id: textArea
            text: getNavPane.previewtext
            preferredWidth: 766.0
            preferredHeight: 1139
            editable: false
            textFormat: TextFormat.Plain

        }
    
    }
    
    actions: [
        ActionItem {
        title: qsTr("RAW / HTML")
        ActionBar.placement: ActionBarPlacement.OnBar
        onTriggered: {
            if (textArea.textFormat == TextFormat.Html) { 
                textArea.textFormat = TextFormat.Plain 
            } else {textArea.textFormat = TextFormat.Html}
        }
    },
        ActionItem {
            title: "Edit"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                if (textArea.editable == false) { 
                    textArea.editable = true 
                } else {textArea.editable = false} 
            }
        }
        ]

    paneProperties: NavigationPaneProperties {
        backButton: ActionItem {
            onTriggered: {
                getNavPane.pop();
            }
        }
    
    }
}