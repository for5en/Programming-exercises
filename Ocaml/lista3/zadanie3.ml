let build_list f n =
  let rec blst f n k =
    if n > k then []
    else [f k] @ blst f n (k+1)
  in blst f n 0;;

let negatives n = build_list (fun x -> -x) n
let reciprocals n = build_list (fun x -> 1/x) n
let evens n = build_list (fun x -> 2*x) n

let identityM n =
  build_list (fun x -> build_list (fun y -> if x = y then 1 else 0) n) n 