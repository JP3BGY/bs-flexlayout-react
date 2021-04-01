open Model;
open TabNode;
open I18nLabel;
open TabSetNode;
open BorderNode;
open Action;
open Union;

type _IIcons={
  close:option(React.element),
  popout:option(React.element),
  maximize:option(React.element),
  restore:option(React.element),
  more:option(React.element),
};
type font={
  size: option(string),
  family: option(string),
  style: option(string),
  weight: option(string),
};
type tabRenderValues = {
  leading:React.element,
  content:React.element,
  name:string,
  buttons:array(React.element),
};
type tabSetRenderValues = {
  headerContent:option(React.element),
  buttons: array(React.element),
};

module TsnorBdn = SorT ({
  type s = _TabSetNode;
  let s_typename = "tabset";
  type t = _BorderNode;
  let t_typename = "border";
});
module LayoutJs ={
  [@bs.module "flexlayout-react"][@react.component]
  external make: (
    ~model: _Model,
    ~factory: _TabNode => React.element,
    ~font: font=?,
    ~fontFamily: string=?,
    ~iconFactory: _TabNode => option(React.element)=?,
    ~titleFactory: _TabNode => option(React.element)=?,
    ~closeIcon: React.element=?,
    ~icons: _IIcons=?,
    ~onAction: _Action=>option(_Action)=?,
    ~onRenderTab: (
      _TabNode,
      tabRenderValues  
    )=>unit=?,
    ~onRenderTabSet: (
      TsnorBdn.t,
      tabSetRenderValues  
    )=>unit=?,
    ~onModelChange: (_Model)=>unit=?,
    ~classNameMapper: string=>string=?,
    ~i18nMapper:(_I18nLabel,option(string))=>option(string)=?,
    ~supportsPopout: option(bool)=?,
    ~popoutURL: option(string)=?
  )=>React.element = "Layout";
};
[@react.component]
let make = (
  ~model:_Model,
  ~factory:_TabNode => React.element,
  ~font:option(font)=?,
  ~fontFamily:option(string)=?,
  ~iconFactory:option(_TabNode => option(React.element))=?,
  ~titleFactory:option(_TabNode => option(React.element))=?,
  ~closeIcon:option(React.element)=?,
  ~icons:option(_IIcons)=?,
  ~onAction:option(_Action=>option(_Action))=?,
  ~onRenderTabSet:option(([`tsn(_TabSetNode)|`bdn(_BorderNode)],tabSetRenderValues)=>unit)=?,
  ~onModelChange:option(_Model=>unit)=?,
  ~classNameMapper:option(string=>string)=?,
  ~i18nMapper:option((_I18nLabel,option(string))=>option(string))=?,
  ~supportsPopout:option(bool)=?,
  ~popoutURL:option(string)=?
)=>{
  let f = switch onRenderTabSet {
  | None => None;
  | Some(g) => Some((rawJs,y)=>{
    let cases=TsnorBdn.classify(rawJs);
    let x=switch cases {
    | TsnorBdn.S(x) => `tsn(x);
    | TsnorBdn.T(x) => `bdn(x);
    };
    g(x,y);
  });
  };
  <LayoutJs 
    model={model}
    factory={factory} 
    font=?{font} 
    fontFamily=?{fontFamily}
    iconFactory=?{iconFactory}
    titleFactory=?{titleFactory}
    closeIcon=?{closeIcon}
    icons=?{icons}
    onAction=?{onAction}
    onRenderTabSet=?{f}
    onModelChange=?{onModelChange}
    classNameMapper=?{classNameMapper}
    i18nMapper=?{i18nMapper}
    supportsPopout=?{supportsPopout}
    popoutURL=?{popoutURL}
  />;
}