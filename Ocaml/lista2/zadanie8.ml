let select xs =
  match xs with
  | [] -> (neg_infinity,[])
  | [a] -> (a,[])
  | xs ->
    let rec find_min xs mn = 
      match xs with
      | [] -> mn
      | head :: tail ->
        if head < mn then find_min tail head
        else find_min tail mn

      in
      let min_el = find_min xs (List.hd xs)

        in
        let rec rest xs = 
          match xs with
          | [] -> []
          | head :: tail ->
            if head = min_el then tail
            else rest tail
          in
          (min_el,rest xs)


let rec select_sort xs = 
  match xs with
  | [] -> []
  | xs ->
    let (mn,rest) = select xs in 
    mn :: (select_sort rest)