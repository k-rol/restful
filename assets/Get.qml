import bb.cascades 1.2
import GetRequest 1.0
import QBookmarks 1.0
import PostRequests 1.0

Page {    
    titleBar: TitleBar {
        title: "Get"
        } 
    Container {
        attachedObjects: [
            Getter {
                id: get
                
                onGetReceived: {
                    responseAre.text = response
                }
            },
            QBookmarks {
                onCopyGetLink: {
                    console.debug("!!!!! FUCK  !!!!!")
                }
            },
            PostRequests {
                id: postrequests
                onSignalToQml: {
                    console.debug("IT CAME AROUND HERE!")
                }
            }
        ]
        TextField {
            id: commandtxt
            text: "http://www.mocky.io/v2/537d6220386c77eb08e97e1d"
            hintText: "Enter GET string"
            onTextChanged: {
                saveButton.text = "Save"
            }
        
        }
        
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            
            }
            horizontalAlignment: HorizontalAlignment.Center

            bottomMargin: 10.0
            leftPadding: 19.0
            rightPadding: 19.0
            Button {
                text: "Send"
                onClicked: {
                    get.send(commandtxt.text)
                }
            
            }
            Button {
                text: "New"
                onClicked: {
                    commandtxt.text = "http://"
                    commandtxt.requestFocus()
                }
            }
            Button {
                id: saveButton
                text: "Save"
                onClicked: {
                    if (saveButton.text == "Save") {
                        saveButton.text = "Saved!"
                    }
                    _app.promptName("Save this request", commandtxt.text)
                }
            }
            Button {
                text: "signal"
                onClicked: {
                    //postrequests.tryIt()
                }
            }
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            
            }
            horizontalAlignment: HorizontalAlignment.Center
            Button {
                text: "Raw / Html" 
                onClicked: {
                    if (responseAre.textFormat == TextFormat.Html)
                    {
                        responseAre.textFormat = TextFormat.Plain
                    }
                    else {
                        responseAre.textFormat = TextFormat.Html
                    }
                }
            }
            Button {
                text: "Preview"
            }
        }
        TextArea {
            id: responseAre
            hintText: "Get Response will be here"
            maximumLength: 50000
            maxHeight: 400.0
            maxWidth: 750.0
            minHeight: 550.0
            minWidth: 700.0
            textFormat: TextFormat.Html
            editable: false
            scrollMode: TextAreaScrollMode.Elastic
        
        }
    
    
    
    }
}
