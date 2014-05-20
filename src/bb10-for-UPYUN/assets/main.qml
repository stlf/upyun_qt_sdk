/*
 * Copyright (c) 2011-2014 stlf@live.cn.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2

NavigationPane {
    id: root
    property string bucket
    property string operator
    property string pass
    
    Menu.definition: MenuDefinition {
        // Add any remaining actions
        actions: [
            ActionItem {
                title: "Sign in"
                onTriggered: {
                    _app.signin()
                }
            }           
            ,
            ActionItem {
                title: "Login out"
                onTriggered: {
                    login.open()
                }
            }
            
        ]
    }
    Page {
           
        onCreationCompleted: {
            
        	login.open()
        }
        
        titleBar: TitleBar {
            title: "Upyun Cloud"
        }
        
        Container {
            ListView {
                dataModel: ArrayDataModel {
                    id: model_data
                }
                
                accessibility.name: "TODO: Add property content"
                
                listItemComponents: [
                    ListItemComponent {
                        StandardListItem {
                            accessibility.description: ""
                            imageSource: "asset:///action_icons/ic_entry.png"
                            title: ListItemData.name
                            status: ListItemData.size
                            description: ListItemData.date
                            accessibility.name: "TODO: Add property content"

                        }

                    }
                ]
            }
            
        }

        actions: [
            ActionItem {
                title: "Upoad file"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {

                }
                imageSource: "asset:///action_icons/ic_add_entry.png"
            },
            ActionItem {
                title: "Add folder"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {

                }
                imageSource: "asset:///action_icons/ic_add_folder.png"
            }
            
        ]

    }
    attachedObjects: [
        Login {
            id: login
            onClosed: {  
                var file_items = _app.listDir() 
                
                model_data.clear()
                
                model_data.append(file_items)
                
                // only for test:
                for(var i = 0; i !== file_items.length; ++i)
                {
                    for (var prop in file_items[i]) {
                        var _js = {"nihao":"hehe"}
                        console.log("Object item:", prop, "=", file_items[i][prop], _js.nihao)
                    }         
                }
                
            }
        },
        ComponentDefinition {
            id: itemPageDefinition
            source: "ItemPage.qml"
        }
    ]
    onPopTransitionEnded: {
        page.destroy();
    }
}
