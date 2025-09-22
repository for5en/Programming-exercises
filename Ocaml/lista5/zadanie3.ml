let parens_ok s = 
  let list_of_string s = String.to_seq s |> List.of_seq in
  let rec parens_ok_rec s o z =
    match s with
    | [] -> true
    | head :: tail ->
      if head = '(' then parens_ok_rec tail (o+1) z
      else if (z+1) > o then false
      else parens_ok_rec tail o (z+1)
  in parens_ok_rec (list_of_string s) 0 0
