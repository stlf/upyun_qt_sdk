import bb.cascades 1.2

Sheet {
    id: loginsheet
    Page {
        titleBar: TitleBar {
            title: "Login upyun bucket"
            acceptAction: ActionItem {
                title: "Login"
                onTriggered: {                    
                    if(_app.login(bucket.text,operator.text,pass.text))
                    	loginsheet.close()
                }

            }

        }
        Container {
            Label {
                text: "Bucket:"
            }
            TextField {
                id: bucket
                text: "stlf-first-bucket"
            }
            
            Label {
                text: "Operator:"
            }
            TextField {
                id: operator
                text: "test"
            }
            
            Label {
                text: "Operator password:"
            }
            TextField {
                id: pass
                inputMode: TextFieldInputMode.Password

            }

        }
    }
}