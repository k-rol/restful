import bb.cascades 1.2
import PostRequests 1.0

Page {
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
                        title: "GET"
                        onTriggered: {
                            var selectedItem = listview.dataModel.data(listview.selected())
                            //_app.useLink(listview.selected())
                            //listDataModel.useLink(listview.selected())
                            tabbedPane.getcommand = selectedItem.link
                            //tabbedPane.gettitlebar = selectedItem.name
                            tabbedPane.activeTab = getTab
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
    actions: [
        ActionItem {
            title: "Delete"
            onTriggered: {
                //groupData.remove({
                //        number: "L",
                //        link: "description"
                //})
            }
        }
    ]
    
}
