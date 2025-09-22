let product xs =
  match xs with
  | [] -> 1
  | _ -> List.fold_left (fun acc x -> acc * x) 1 xs;;

product [4;2;5;1;2;5;];;