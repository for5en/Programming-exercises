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

module MakeMapDict (Ord : Map.OrderedType) : KDICT with type key = Ord.t = 
  struct
    module M = Map.Make(Ord)

    type key = Ord.t
    type 'a dict = 'a M.t
    
    let empty = M.empty
    let insert key value dict = M.add key value dict
    let remove key dict = M.remove key dict
    let find_opt key dict = M.find_opt key dict
    let find key dict = M.find key dict
    let to_list dict = M.bindings dict
end

module CharOrderedType : Map.OrderedType with type t = char =
  struct
    type t = char
    let compare a b =
      if a < b then -1
      else if a > b then 1
      else 0
end


module CharMapDict = MakeMapDict(CharOrderedType)