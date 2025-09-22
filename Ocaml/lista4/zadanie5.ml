module type KDICT = 
  sig
    type key
    type 'a dict
    val empty : 'a dict
    val insert : key -> 'a -> 'a dict -> 'a dict
    val remove : key -> 'a dict -> 'a dict
    val find_opt : key -> 'a dict -> 'a option
    val find : key -> 'a dict -> 'a
    val to_list : 'a dict -> (key * 'a) list
end


module Freq (D : KDICT) = 
  struct
    let freq (xs : D.key list) : (D.key * int) list =
      let rec iter d arr = 
        match arr with
        | [] -> d 
        | x :: xs ->
          match D.find_opt x (iter d xs) with
          | None -> D.insert x 1 (iter d xs) 
          | Some y -> D.insert x y (iter d xs) 
      in D.to_list (iter D.empty xs)
end