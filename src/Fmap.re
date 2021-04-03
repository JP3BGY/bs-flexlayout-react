let (>>|) = (a,f)=>{
  switch a {
  | Some(x) => Some(f(x));
  | None => None
  };
}