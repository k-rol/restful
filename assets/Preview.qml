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
            visible: false

        }
        WebView {
            id: webView
            preferredWidth: 766.0
            preferredHeight: 1139
            visible: false
            settings.defaultTextCodecName: "UTF-16"

        }
        TextArea {
            id: hexArea
            //text: "00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15"
            text: getNavPane.hextext
            textFit.maxFontSizeValue: 7 
            preferredWidth: 766.0
            preferredHeight: 1139
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
        },
        ActionItem {
            title: "Hex View"
            ActionBar.placement: ActionBarPlacement.OnBar
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