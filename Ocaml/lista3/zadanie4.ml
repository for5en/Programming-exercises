open Printf

let empty_set xs =
  match xs with
  | [] -> true
  | xs -> false

let singleton a = [a;]

let rec in_set a xs = 
  match xs with
  | [] -> false
  | head :: tail ->
    if head = a then true
    else in_set a tail

let union s t = 
  let rec build_xminusy xs ys = 
    match xs with
    | [] -> []
    | head :: tail ->
      if (in_set head ys) then build_xminusy tail ys
      else head :: (build_xminusy tail ys)
  in s @ build_xminusy t s;;

  let intersect s t = 
    let rec build_xxy xs ys = 
      match xs with
      | [] -> []
      | head :: tail ->
        if (in_set head ys) then head :: (build_xxy tail ys)
        else build_xxy tail ys
    in build_xxy t s;;

let lista = union [1;2;3;4;5;6;] [4;5;6;7;8;9;10]
let lista = intersect [1;2;3;4;5;6;] [4;5;6;7;8;9;10]