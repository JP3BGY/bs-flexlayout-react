module type S_T ={
  type s;
  let s_typename:string;
  type t;
  let t_typename:string;
};
module SorT:(ST:S_T)=>{
  type t;
  let a: ST.s => t;
  let b: ST.t => t;
  type case =
    | S(ST.s)
    | T(ST.t);
  let classify: t => case;
} = (ST: S_T) => {
  [@unboxed]
  type t =
    | Any('a): t;
  type case =
    | S(ST.s)
    | T(ST.t);
  let a = (v: ST.s) => Any(v);
  let b = (v: ST.t) => Any(v);
  let classify = (Any (v): t) =>
    if ([%raw {|function (a,b) { return  a.TYPE===b;}|}](v,ST.s_typename)) {
      S(Obj.magic(v));
    } else {
      T(Obj.magic(v));
    };
};