import bb.cascades 1.2
import PostRequests 1.0
import bb.system 1.2

Page {
    attachedObjects: [
        SystemToast {
            id: notif
            body: "Text Copied!"
            
        }
    ]
    titleBar: TitleBar {
        title: "Bookmarks" 
    }
    Container {
        ListView {
            id: listview
            dataModel: _app.dataModel
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    StandardListItem {
                        
                        title: qsTr(ListItemData.name)
                        description: qsTr(ListItemData.link)
                        status: qsTr("GET")

                    }
                }
            ]
            onTriggered: {
                var selectedItem = dataModel.data(indexPath);
                textField.text = selectedItem.name
                console.debug("this:")
                console.debug(indexPath)
                console.debug(selectedItem.name)
            }
            contextActions: [
                ActionSet {
                    DeleteActionItem {
                        onTriggered: {
                            
                            console.debug("this:")
                            console.debug(listview.selected())
                            var selectedItem = listview.dataModel.data(listview.selected())
                            textField.text = selectedItem.name + " Deleted"
                            _app.deleteObject(listview.selected())
                        
                        }
                    }
                    ActionItem {
                        title: "Copy"
                        imageSource: "asset:///images/ic_copy.png"
                        onTriggered: {
                            var selectedItem = listview.dataModel.data(listview.selected())
                            //_app.useLink(listview.selected())
                            //listDataModel.useLink(listview.selected())
                            tabbedPane.getcommand = selectedItem.link
                            //tabbedPane.gettitlebar = selectedItem.name
                            tabbedPane.activeTab = getTab
                            notif.show()
                        }
                    }
                }
            ]
        }
        TextField {
            id: textField
            visible: false
        }
    }
}
