import bb.cascades 1.2
import bb.system 1.2

Page {
    attachedObjects: [
        TextStyleDefinition {
            id: myStyle
            base: SystemDefaults.TextStyles.BodyText
            rules: [
                FontFaceRule {
                    source: "asset:///Lekton-Bold.ttf"
                    fontFamily: "ConsolaFont"            
                }
            ]
            fontFamily: "ConsolaFont, consola"
        },
        SystemToast {
            id: copyToast
        }
    ]
    Container {
        SegmentedControl {
            id: segcontrol
            Option {
                id: websegcontrol
                text: "WEB"
                value: 1
                
            }
            Option {
                id: textsegcontrol
                text: "TEXT"
                value: 2
            }
            Option {
                id: hexsegcontrol
                text: "HEX"
                value: 3
            }
            Option {
                id: asciisegcontrol
                text: "ASCII"
                value: 4
            }
            onSelectedOptionChanged: {
//                if (selectedOption == websegcontrol){
//                    webViews.visible = true
//                    hexViews.visible = false
//                } 
//                else {
//                    webViews.visible = false
//                    hexViews.visible = true
//                }
                var value = segcontrol.selectedIndex
                textArea.visible = false
                webView.visible = false
                hexArea.visible = false
                hexAsciiArea.visible = false
                
                switch (value) {
                    case 0:
                        webView.visible = true
                        webView.html = getNavPane.webviewGet.html
                        break;
                    case 1:
                        textArea.visible = true
                        break;
                    case 2:
                        hexArea.visible = true
                        break;
                    case 3:
                        hexAsciiArea.visible = true
                        break;
                }
                
            }
        }
        Container {
            id: webViews
            TextArea {
                id: textArea
                text: getNavPane.webviewGet.html
                preferredWidth: 766.0
                preferredHeight: 1139
                editable: false
                textFormat: TextFormat.Plain
                onVisibleChanged: {
                    if(textArea.visible)
                    {
                        enableButtons()
                    }
                }
            
            }
            WebView {
                id: webView
                preferredWidth: 766.0
                preferredHeight: 1139
                //visible: true
                settings.defaultTextCodecName: "UTF-16"
                onVisibleChanged: {
                    if(webView.visible)
                    {
                        disableButtons()
                    }
                }
            }
        }
        Container {
            id: hexViews
            TextArea {
                id: hexArea
                textStyle.base: myStyle.style
                //text: "00 01 02 03 04 D5 06 D7 08 09 10 11 12 13 14 15 00 1D 18 19 20 21 22 2E 24 25 26 2D 28 29 30 EE 32 33 34 3C C6 D7 38 39 40 41 42 D3 44 45 46 47 48 49 50"
                text: getNavPane.hextext
                preferredWidth: 766.0
                preferredHeight: 1139
                //textStyle.fontSize: FontSize.XLarge
                textFit.maxFontSizeValue: 2.0
                editable: false
                onVisibleChanged: {
                    if(hexArea.visible)
                    {
                        enableButtons()
                    }
                }
            }
            TextArea {
                id: hexAsciiArea
                textStyle.base: myStyle.style
                text: getNavPane.hexascii
                textFit.maxFontSizeValue: 7 
                preferredWidth: 766.0
                preferredHeight: 1139
                editable: false
                onVisibleChanged: {
                    if(hexAsciiArea.visible)
                    {
                        enableButtons()
                    }
                }
            }
        }
        

    }
    actions: [
        ActionItem {
            id: copybutton
            ActionBar.placement: ActionBarPlacement.OnBar
            title: "Copy as text"
            
            onTriggered: {
                if (_applicationui.clipboardCopy(returningText()))
                {
                    copyToast.body = "Text Now In Clipboard"
                    copyToast.show()
                } else {
                    
                }
                
            }
            
        },
        InvokeActionItem {
            id: sharebutton
            ActionBar.placement: ActionBarPlacement.OnBar
            query {
                mimeType: "text/plain"
                invokeActionId: "bb.action.SHARE"
            }
            onTriggered: {
                data = returningText()
            }
            title: "Share Current Tab"
        }
    ]
    
    paneProperties: NavigationPaneProperties {
        backButton: ActionItem {
            onTriggered: {
                getNavPane.pop();
            }
        }
        
    
    }
    onCreationCompleted: {
        textArea.visible = false
        webView.visible = false
        hexArea.visible = false
        hexAsciiArea.visible = false
        webView.visible = true ;
        webView.html = getNavPane.webviewGet.html ;
        copybutton.enabled = false
        sharebutton.enabled = false
        
        
    }
    function returningText() {
        var data;
        switch (segcontrol.selectedIndex) {
            case 0:
                break;
            case 1:
                data = getNavPane.webviewGet.html
                break;
            case 2:
                data = getNavPane.hextext
                break;
            case 3:
                data = getNavPane.hexascii 
                break;
        }
        return data
    }
    function enableButtons()
    {
        copybutton.enabled = true
        sharebutton.enabled = true
    }
    function disableButtons() {
        copybutton.enabled = false
        sharebutton.enabled = false
    } 
}