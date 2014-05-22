import bb.cascades 1.2

Page {
    Container {
        
    }
    
    paneProperties: NavigationPaneProperties {
        backButton: ActionItem {
            title: "Parent dir"
            onTriggered: { 
                _app.gotoParentDir()
                root.pop(); 
            }
        }
    }
}
