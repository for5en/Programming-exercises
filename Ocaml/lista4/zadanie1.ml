module type DICT = 
    sig
        type ('a , 'b) dict
        val empty : ('a , 'b) dict
        val insert : 'a -> 'b -> ('a , 'b) dict -> ('a , 'b) dict
        val remove : 'a -> ('a , 'b) dict -> ('a , 'b) dict
        val find_opt : 'a -> ('a , 'b) dict -> 'b option
        val find : 'a -> ('a , 'b) dict -> 'b
        val to_list : ('a , 'b) dict -> ('a * 'b) list
end

module ListDict : DICT = 
    struct
        type ('a, 'b) dict = ('a * 'b) list

        let empty = []

        let rec insert key value dict =
            match dict with
            | [] -> [(key, value)]
            | (a, b) :: tail -> 
                if a = key then (a, value) :: tail
                else (a, b) :: (insert key value tail)
        
        let rec remove key dict = 
            match dict with
            | [] -> []
            | (a, b) :: tail ->
                if a = key then tail
                else (a, b) :: (remove key tail)

        let rec find_opt key dict =
            match dict with
            | [] -> None
            | (a, b) :: tail ->
                if a = key then Some b
                else find_opt key tail

        let rec find key dict = 
            match dict with
            | [] -> failwith "KeyNotFound"
            | (a, b) :: tail ->
                if a = key then b
                else find key tail

        let to_list dict = dict
            
end