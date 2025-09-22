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


module MakeListDict (Ord : Map.OrderedType) : KDICT with type key = Ord.t  = 
  struct
    type key = Ord.t
    type 'a dict = (key * 'a) list

    let empty = []

    let rec insert key value dict =
        match dict with
        | [] -> [(key, value)]
        | (a, b) :: tail -> 
          if Ord.compare a key = 0 then (key, value) :: tail
          else (a, b) :: (insert key value dict)
          
    
    let rec remove key dict = 
        match dict with
        | [] -> []
        | (a, b) :: tail ->
            if Ord.compare a key = 0 then tail
            else (a, b) :: (remove key tail)

    let rec find_opt key dict =
        match dict with
        | [] -> None
        | (a, b) :: tail ->
            if Ord.compare a key = 0 then Some b
            else find_opt key tail

    let rec find key dict = 
        match dict with
        | [] -> failwith "KeyNotFound"
        | (a, b) :: tail ->
            if Ord.compare a key = 0 then b
            else find key tail

    let to_list dict = dict
end

module CharOrderedType : Map.OrderedType with type t = char = 
  struct
    type t = char
    let compare a b =
      if a < b then -1
      else if a > b then 1
      else 0
end

module CharListDict = MakeListDict(CharOrderedType)
