open Model;
open TabNode;
open I18nLabel;
open TabSetNode;
open BorderNode;
open Action;
open Union;
open Uncurry;
open Fmap;

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
    ~factory: (._TabNode) => React.element,
    ~font: font=?,
    ~fontFamily: string=?,
    ~iconFactory: (._TabNode) => option(React.element)=?,
    ~titleFactory: (._TabNode) => option(React.element)=?,
    ~closeIcon: React.element=?,
    ~icons: _IIcons=?,
    ~onAction: (._Action)=>option(_Action)=?,
    ~onRenderTab: (.
      _TabNode,
      tabRenderValues  
    )=>unit=?,
    ~onRenderTabSet: (.
      TsnorBdn.t,
      tabSetRenderValues  
    )=>unit=?,
    ~onModelChange: (._Model)=>unit=?,
    ~classNameMapper: (.string)=>string=?,
    ~i18nMapper:(._I18nLabel,option(string))=>option(string)=?,
    ~supportsPopout: option(bool)=?,
    ~popoutURL: option(string)=?
  )=>React.element = "Layout";
};
[@react.component]
let make = (
  ~model,
  ~factory,
  ~font=?,
  ~fontFamily=?,
  ~iconFactory=?,
  ~titleFactory=?,
  ~closeIcon=?,
  ~icons=?,
  ~onAction=?,
  ~onRenderTabSet=?,
  ~onModelChange=?,
  ~classNameMapper=?,
  ~i18nMapper=?,
  ~supportsPopout=?,
  ~popoutURL=?
)=>{
  let rawFactory = uncurry1(factory);
  let rawIconFactory = iconFactory >>| uncurry1;
  let rawTitleFactory = titleFactory >>| uncurry1;
  let rawOnAction = onAction >>| uncurry1;
  let rawOnRenderTabSet = switch onRenderTabSet {
  | None => None;
  | Some(g) => Some((. rawJs,y)=>{
    let cases=TsnorBdn.classify(rawJs);
    let x=switch cases {
    | TsnorBdn.S(x) => `tsn(x);
    | TsnorBdn.T(x) => `bdn(x);
    };
    g(x,y);
  });
  };
  let rawOnModelChange = onModelChange >>| uncurry1;
  let rawClassNameMapper = classNameMapper >>| uncurry1;
  let rawI18nMapper = i18nMapper >>| uncurry2;
  <LayoutJs 
    model={model}
    factory={rawFactory} 
    font=?{font} 
    fontFamily=?{fontFamily}
    iconFactory=?{rawIconFactory}
    titleFactory=?{rawTitleFactory}
    closeIcon=?{closeIcon}
    icons=?{icons}
    onAction=?{rawOnAction}
    onRenderTabSet=?{rawOnRenderTabSet}
    onModelChange=?{rawOnModelChange}
    classNameMapper=?{rawClassNameMapper}
    i18nMapper=?{rawI18nMapper}
    supportsPopout=?{supportsPopout}
    popoutURL=?{popoutURL}
  />;
}