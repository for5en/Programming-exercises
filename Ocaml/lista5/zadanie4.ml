let parens_ok s = 
  let list_of_string s = String.to_seq s |> List.of_seq in
  let rec parens_ok_rec stos s =
    match s with
    | [] -> true
    | head :: tail ->
      if head = '(' then
        parens_ok_rec (head :: stos) tail
      else if head = '[' then
        parens_ok_rec (head :: stos) tail
      else if head = '{' then
        parens_ok_rec (head :: stos) tail
      else if head = ')' then
        match stos with
        | [] -> false
        | h :: t ->
          if h = '(' then parens_ok_rec t tail
          else false
      else if head = ']' then
        match stos with
        | [] -> false
        | h :: t ->
          if h = '[' then parens_ok_rec t tail
          else false
      else if head = '}' then
        match stos with
        | [] -> false
        | h :: t ->
          if h = '{' then parens_ok_rec t tail
          else false
      else false
  in parens_ok_rec [] (list_of_string s);;
      
let res = parens_ok "((([][)]))";;

(* dziala to w ten sposob ze idac po tablicy naszych nawiasow trzymamy stos na ktory wrzucamy kolejno otwarcia nawiasow,
a jesli natrafimy na nawias zamykajacy to zeby nawiasowanie bylo poprawne to ostatnio otworzony nawias musi byc tego samego
typu jesli jest to usuwamy ten otwierajacy ze stosu, bo wlasnie go zamykamy i idziemy dalej, a jesli jest zly to zwracamy false *)
