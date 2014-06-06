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
            title: "Web View"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                if (textArea.visible == true) {
                    textArea.visible = false ;
                    webView.visible = true ;
                    webView.html = getNavPane.webviewGet.html ;
                    //webView.html = textArea.text ;
                    title = "Text View"
                } else {
                    textArea.visible = true ;
                    webView.visible = false ;
                    title = "Web View"
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