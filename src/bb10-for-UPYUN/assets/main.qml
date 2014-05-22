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
import bb.cascades.pickers 1.0
import bb.system 1.0

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
    
    function listdir()
    {
        var file_items = _app.listDir() 
        
        model_data.clear()
        
        model_data.append(file_items)
        
        if(_app.pwd() === "/")
            to_parent_dir.enabled = false 
        else 
        	to_parent_dir.enabled = true
    }
    
    Page 
    {
           
        onCreationCompleted: {   
        	   login.open()
        }
        
        titleBar: TitleBar {
            title: "Upyun Cloud"
            acceptAction: ActionItem {
                id: to_parent_dir
                imageSource: "asset:///action_icons/ic_to_top.png"
                onTriggered: {
                    _app.gotoParentDir()
                    listdir()
                }
            }
        }
        
        Container {
            ListView {
                dataModel: ArrayDataModel {
                    id: model_data
                }
                
                function removeDir(dir_name)
                {
                    _app.removeDir(dir_name)
                }
                function removeFile(file_name)
                {
                    _app.removeFile(file_name)
                }
                function listdir()
                {
                    root.listdir()
                }
                
                accessibility.name: "TODO: Add property content"
                
                onTriggered: {
                    var chosenItem = dataModel.data(indexPath); 
                    if(chosenItem.size === "")
                    {
                    	_app.cd(chosenItem.name)
                    	listdir()

                    }
                }
                
                listItemComponents: [
                    ListItemComponent {
                        StandardListItem {
                            id: file_list_item
                            accessibility.description: ""
                            imageSource: ListItemData.type === "F" ?
                            "asset:///images/folder.png":"asset:///images/documents.png"
                            title: ListItemData.name
                            status: ListItemData.size
                            description: ListItemData.date 
                            accessibility.name: "TODO: Add property content"
                            
                            contextActions: [
                                ActionSet {
                                    title: ListItemData.name
                                    ActionItem {
                                        title: "Remove"
                                        onTriggered: {
                                            if(ListItemData.size === "")
                                            {
                                                file_list_item.ListItem.view.removeDir(ListItemData.name)    
                                            }
                                            else
                                            {
                                                file_list_item.ListItem.view.removeFile(ListItemData.name)
                                            }
                                            
                                            file_list_item.ListItem.view.listdir()
                                        }
                                        imageSource: "asset:///action_icons/ic_delete.png"
                                    }
                                
                                }
                            ]

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
                    file_picker.open()
                    
                }
                imageSource: "asset:///action_icons/ic_add_entry.png"
            },
            ActionItem {
                title: "Add folder"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    add_folder_prompt.exec()

                }
                imageSource: "asset:///action_icons/ic_add_folder.png"
            }
            
        ]

    }
    attachedObjects: [
        ComponentDefinition {
            id: dir;
            source: "main.qml"
        },
        SystemToast {
            id: toast
        },
        SystemDialog {
            id: dialog
        },
        FilePicker {
            id: file_picker
                    
            title: qsTr ("Select the upload file:")
            
            onFileSelected: {
                var selectf = selectedFiles[0]
                if(selectf === "")
                	return;
                
                if(_app.uploadFile(selectf))
                {
                    toast.body = "Upload file succeed!"                    
                    toast.show()
                    
                    listdir()
                }
            }
        },
        SystemPrompt{
            id: add_folder_prompt
            
            onFinished: {
                var dir_name = inputFieldTextEntry()	
                if (value === SystemUiResult.ConfirmButtonSelection)
                {
                    if (_app.makeDir(dir_name)) {
                        toast.body = "Make dir succeed!"
                        
                        toast.show()
                        
                        listdir()
                    
                    }                        
                }        	               
            }
            title: "Make dir"
            body: "Input remote dir name: "
        },
        Login {
            id: login
            onClosed: {  
                listdir()                                
            }
        }
    ]
    onPopTransitionEnded: {
        page.destroy();
    }
}
