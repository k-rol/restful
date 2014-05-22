import bb.cascades 1.2
import QBookmarks 1.0

Page {
    titleBar: TitleBar {
        title: "Bookmarks" 
    }
    Container {

        ListView {
            dataModel: _app.dataModel
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    StandardListItem {
                        
                        title: qsTr("%1 %2").arg(ListItemData.firstName).arg(ListItemData.lastName)
                        description: qsTr("Unique Key: %1").arg(ListItemData.customerID)
                        
                        contextActions: [
                            ActionSet {
                                title: "Link"
                                ActionItem {
                                    title: "Delete"
                                    onTriggered: {

                                        console.debug("this:")
                                        console.debug(seindexPath)
                                        
                                    }
                                }
                            }
                        ]
                    }
                }
            ]
            onTriggered: {
                var selectedItem = dataModel.data(indexPath);
                textField.text = selectedItem.firstName
                console.debug("this:")
                console.debug(indexPath)
                console.debug(selectedItem.firstName)
            }
        }
        TextField {
            id: textField

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
