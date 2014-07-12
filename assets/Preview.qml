import bb.cascades 1.2

Page {
    attachedObjects: [
        TextStyleDefinition {
            id: myStyle
            base: SystemDefaults.TextStyles.BodyText
            rules: [
                FontFaceRule {
                    source: "asset:///consola.ttf"
                    fontFamily: "ConsolaFont"            
                }
            ]
            fontFamily: "ConsolaFont, consola"
        }
    ]
    Container {
        Container {
            id: webViews
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
        }
        Container {
            id: hexViews
            TextArea {
                id: hexArea
                textStyle.base: myStyle.style
                text: "00 01 02 03 04 D5 06 D7 08 09 10 11 12 13 14 15 00 1D 18 19 20 21 22 2E 24 25 26 2D 28 29 30 EE 32 33 34 3C C6 D7 38 39 40 41 42 D3 44 45 46 47 48 49 50"
                //text: getNavPane.hextext
                preferredWidth: 766.0
                preferredHeight: 1139
                textFit.maxFontSizeValue: 2.0

            }
            TextArea {
                id: hexAsciiArea
                textStyle.base: myStyle.style
                text: getNavPane.hexascii
                textFit.maxFontSizeValue: 7 
                preferredWidth: 766.0
                preferredHeight: 1139
                visible: false
            }
        }
        

    }
    
    actions: [
        ActionItem {
            title: "Web View"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                hexViews.visible = false
                webViews.visible = true
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
            onTriggered: {
                hexViews.visible = true
                webViews.visible = false
                if (hexArea.visible == true ){
                    hexArea.visible = false
                    hexAsciiArea.visible = true
                } else {
                    hexArea.visible = true
                    hexAsciiArea.visible = false
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