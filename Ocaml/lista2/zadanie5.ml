let rec maximum xs =
  match xs with
  | [] -> neg_infinity
  | head :: tail ->
    if head < maximum tail then maximum tail
    else head