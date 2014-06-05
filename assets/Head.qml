import bb.cascades 1.2

Page {
    Container {
        Header {
            title: "Full Header of QNetworkRequest::"
        }
//        Container {
//            layout: StackLayout {
//                orientation: LayoutOrientation.LeftToRight
//
//            }
//            Label {
//                text: "HttpStatusCodeAttribute:"
//           } 
//           Label {
//               text: "204"
//           }
//           
//        }
//        Divider {
//            
//        }
        
        TextArea {
            text: getNavPane.headertext
            preferredWidth: 766.0
            preferredHeight: 1139
            editable: false
        }

    }
}
