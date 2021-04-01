type _Model;
[@bs.module "flexlayout-react"][@bs.val]
external model:_Model = "Model";
[@bs.send]
external fromJson:(_Model,Js.t({..}))=>_Model = "fromJson";