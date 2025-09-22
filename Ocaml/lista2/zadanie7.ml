let rec is_sorted xs = 
  match xs with
  | [] -> true
  | [_] -> true
  | first :: second :: tail ->
    if first <= second && is_sorted (second :: tail) then true
    else false