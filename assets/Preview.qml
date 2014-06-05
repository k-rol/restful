import bb.cascades 1.2

Page {
    Container {
        TextArea {
            id: textArea
            text: getNavPane.webviewGet.html
            preferredWidth: 766.0
            preferredHeight: 1139
            editable: false
            textFormat: TextFormat.Plain
            visible: true

        }
        WebView {
            id: webView
            preferredWidth: 766.0
            preferredHeight: 1139
            visible: false
            settings.defaultTextCodecName: "UTF-16"

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
        },
        ActionItem {
            title: "WebView"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                if (textArea.visible == true) {
                    textArea.visible = false ;
                    webView.visible = true ;
                    webView.html = getNavPane.webviewGet.html ;
                } else {
                    textArea.visible = true ;
                    webView.visible = false ;
                }
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