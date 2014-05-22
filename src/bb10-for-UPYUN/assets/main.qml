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

TabbedPane{
    showTabsOnActionBar: false 
    Tab {
        
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
                
                cur_dir.text = _app.pwd()
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
                            root.listdir()
                        }
                    }
                }
                
                Container {
                    Label {
                        id: cur_dir
                    }
                    
                    ListView {
                        dataModel: ArrayDataModel {
                            id: model_data
                        }
                        
                        function  remove_comfirm(name)
                        {
                            dialog.title = "Comfirm"
                            dialog.body = "Remove " + name + " ?"
                            dialog.exec()
                            
                            if (dialog.result === SystemUiResult.CancelButtonSelection)
                                return false 
                            return true  
                        }
                        
                        function removeDir(dir_name)
                        {
                            if(remove_comfirm(dir_name))
                                _app.removeDir(dir_name)
                            root.listdir()
                        }
                        function removeFile(file_name)
                        {
                            if(remove_comfirm(file_name))
                                _app.removeFile(file_name)
                            root.listdir()
                        }
                        function listdir()
                        {
                            root.listdir()
                        }
                        function save(name)
                        {
                            if(_app.downloadFile(name))
                            {
                                toast.body = "Down load file: " + name + " succeed!"
                                toast.show()
                            }
                        }
                        
                        accessibility.name: "TODO: Add property content"
                        
                        onTriggered: {
                            var chosenItem = dataModel.data(indexPath); 
                            if(chosenItem.size === "")
                            {
                                _app.cd(chosenItem.name)
                                root.listdir()
                            
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
                                            actions: [ 
                                                ActionItem {
                                                    title: "Save"
                                                    onTriggered: {
                                                        file_list_item.ListItem.view.save(ListItemData.name)
                                                    }
                                                    imageSource: "asset:///action_icons/ic_save_as.png"
                                                }, 
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
                                            ]
                                        
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
                    },
                    ActionItem {
                        title: "Refresh"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {
                            root.listdir()
                        }
                        imageSource: "asset:///action_icons/ic_reload.png"
                    
                    },
                    ActionItem {
                        title: "Login out"
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {
                            login.open()
                        }
                    
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
                        if(mode === FilePickerMode.Saver)
                        {
                        }
                        else 
                        {
                            if(_app.uploadFile(selectf))
                            {
                                toast.body = "Upload file succeed!"                    
                                toast.show()
                                
                                listdir()
                            }
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
                                
                                root.listdir()
                            
                            }                        
                        }        	               
            }
            title: "Make dir"
            body: "Input remote dir name: "
        },
        Login {
            id: login
            onClosed: {  
            	root.listdir()                                
            }
        }
    ]
    onPopTransitionEnded: {
        page.destroy();
    }
}
}
Tab {
    Page {
        Container {
            ImageView {
                imageSource: "asset:///images/upyun_logo.jpg"
            }
            Label {
                text: "App author: stlf(stlf@live.cn)"
            }
        
        }
    }    
}
}
