import bb.cascades 1.2
import GetRequest 1.0
import QBookmarks 1.0
import PostRequests 1.0

NavigationPane {
    id: getNavPane
    property alias webviewGet: webviewshare
    property variant previewtext
    property string headertext
    property string statuscode
    property string length
    property string hextext
    Page {    

        titleBar: TitleBar {
            id: titelBar
            title: tabbedPane.gettitlebar
        } 
        Container {
            attachedObjects: [
                Getter {
                    id: get
                    
                    onGetReceived: {
                        //responseArea.text = response
                        webviewshare.html = response
                        responseArea.text = webviewshare.html
                        //testwebview.html = response
                        headertext = toSendRawHeader
                        statuscode = toSendhttpStatusCode
                        length = toSendContentLength
                        labelStatusCode.visible = true
                        labelLength.visible = true
                        console.debug(response)
                        //hexArea
                        hextext = hexCode;
                    }
                }
            ]
            DropDown {
                id: dropdownservice
                title: "REST Service"
                onSelectedIndexChanged: {
                    console.log("SelectedIndex was changed to " + selectedIndex);
                }
                Option {
                    text: "GET"
                    description: "Send a GET request"
                    selected: true
                }
                Option {
                    text: "POST"
                    description: "Send a POST request"
                }
            }
            Label {
                id: labelcommandtxt
                text: tabbedPane.getcommand
                visible: false
                onTextChanged: {
                    commandtxt.text = text
                }
            }
            TextField {
                id: commandtxt
                //text: tabbedPane.getcommand //"http://www.mocky.io/v2/537d6220386c77eb08e97e1d"
                hintText: "Enter GET string"
                
                onTextChanged: {
                    
                    saveButton.text = "Save"
                    //console.debug(tabbedPane.activeTab != bookmarksTab);
                    //titelBar.title = "GETe"
                    //if (tabbedPane.activeTab != bookmarksTab){
                    //    titelBar.title = "GETe"
                    //}
                
                }
                input.submitKey: SubmitKey.Send
                inputMode: TextFieldInputMode.Url
                input {
                    onSubmitted: {
                        get.send(commandtxt.text)
                    }
                    
                }
            }
            TextArea {
                hintText: "Body"
                visible: false;
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
                leftPadding: 19.0
                rightPadding: 19.0
                horizontalAlignment: HorizontalAlignment.Center
                Button {
                    text: "Head"
                    onClicked: {
                        var page = headerDefinition.createObject()
                        getNavPane.push(page)
                    }
                }
                Button {
                    text: "Body"
                    onClicked: {
                        //previewtext = responseArea.text
                    	var page = previewDefinition.createObject()
                    	getNavPane.push(page)
                    }
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                horizontalAlignment: HorizontalAlignment.Center
                Label {
                    id: labelStatusCode
                    text: "Status code: " + statuscode
                    visible: false
                }
                Label {
                    text: "\t"
                }
                Label {
                    id: labelLength
                    text: "Length: " + length
                    visible: false
                }
            }

            TextArea {
                id: responseArea
                hintText: "Get Response will be here"
                maximumLength: 50000
                maxHeight: 400.0
                maxWidth: 750.0
                minHeight: 550.0
                minWidth: 700.0
                textFormat: TextFormat.Plain
                editable: false
                scrollMode: TextAreaScrollMode.Elastic
                           
            }
        
        
        
        }
        attachedObjects: [
            ComponentDefinition {
                id: previewDefinition
                source: "Preview.qml"
            },
            ComponentDefinition {
                id: headerDefinition
                source: "Head.qml"
            },
            WebView {
                id: webviewshare
                
            }
        ]
    }//Page
    onPopTransitionEnded: {
        page.destroy();
    }
}
