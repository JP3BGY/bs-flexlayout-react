type _Model;
[@bs.module "flexlayout-react"][@bs.val]
external model:_Model = "Model";
[@bs.send]
external rawFromJson:(_Model,Js.t({..}))=>_Model = "fromJson";
let fromJson = (a) => rawFromJson(model,a)