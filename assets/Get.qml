import bb.cascades 1.2
import GetRequest 1.0
import QBookmarks 1.0
import PostRequests 1.0

Page {    
property string previewtext
    titleBar: TitleBar {
        id: titelBar
        title: tabbedPane.gettitlebar
        } 
    Container {
        attachedObjects: [
            Getter {
                id: get
                
                onGetReceived: {
                    responseAre.text = response
                }
            }
        ]
        TextField {
            id: commandtxt
            text: tabbedPane.getcommand //"http://www.mocky.io/v2/537d6220386c77eb08e97e1d"
            hintText: "Enter GET string"
            
            onTextChanged: {
                
                saveButton.text = "Save"
                //console.debug(tabbedPane.activeTab != bookmarksTab);
                //titelBar.title = "GETe"
                //if (tabbedPane.activeTab != bookmarksTab){
                //    titelBar.title = "GETe"
                //}
                
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
                    titelBar.title = "GET"
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
                onClicked: {
                 
                }
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
