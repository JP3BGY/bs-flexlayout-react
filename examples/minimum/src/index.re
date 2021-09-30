open BsFlexlayoutReact

let layoutJson = [%raw{|
  {
    global: {tabEnableClose:false},
    borders:[
    		{
	        "type": "border",
          "location":"bottom",
          "size": 100,
          "children": [
              {
              "type": "tab",
              "name": "four",
              "component": "text"
              }
            ]
        },
    		{
          "type": "border",
          "location":"left",
          "size": 100,
          "children": []
         }
    ],
    layout: {
        "type": "row",
        "weight": 100,
        "children": [
            {
                "type": "tabset",
                "weight": 50,
                "selected": 0,
                "children": [
                    {
                        "type": "tab",
                        "name": "One",
                        "component": "text"
                    }
                ]
            },
            {
                "type": "tabset",
                "weight": 50,
                "selected": 0,
                "children": [
                    {
                        "type": "tab",
                        "name": "Two",
                        "component": "text"
                    },
                    {
                        "type": "tab",
                        "name": "Three",
                        "component": "text"
                    }
                ]
            }
        ]
    }
  }
|}]

let opt2str = (s)=> switch (s) {
| Some(x) => x
| None => ""
}

let factory = (node) => if (BsFlexlayoutReact.TabNode.getComponent(node) == Some("text")){
  (<div className="panel">{React.string("Panel" ++ opt2str(BsFlexlayoutReact.TabNode.getName(node)))}</div>)
}else{
  React.string("")
}
switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<BsFlexlayoutReact.Layout 
                                    model={BsFlexlayoutReact.Model.fromJson(layoutJson)} 
                                    factory={factory} />,root)
| None => ()
}