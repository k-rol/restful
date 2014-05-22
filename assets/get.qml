import bb.cascades 1.2
import GetRequest 1.0

Page {
    attachedObjects: [
        Get {
            id: get
            
            onGetReceived: {
                responseAre.text = response
            }
        }
    ]
        
    
    titleBar: TitleBar {
        title: "Get"
    } 
    Container {
        TextField {
            id: commandtxt
            hintText: "Enter GET string"

        }
        Button {
            text: "Send"
            onClicked: {
                get.send(commandtxt.text)
            }

        }
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
        ScrollView {
            TextArea {
                id: responseAre
                hintText: "Get Response will be here"
                maximumLength: 500
                maxHeight: 400.0
                maxWidth: 750.0
                minHeight: 550.0
                minWidth: 700.0
                textFormat: TextFormat.Html

            }

        }

    }
}
