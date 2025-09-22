let rec mem x xs =
  match xs with
  | [] -> false
  | head :: tail ->
    if head = x then true
    else mem x tail