let alpha_num = 3;;
let alpha_denom = 4;;
let alpha = (float_of_int alpha_num) /. (float_of_int alpha_denom);;

type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree;;
type 'a sgtree = { tree : 'a tree; size : int; max_size: int };;

let test_tree = 
  Node(
    Node(
      Node(Leaf, 1, Node(Leaf, 2, Leaf)),  (* lewy podwęzeł 1 *)
      3,                                   (* korzeń 3 *)
      Node(Leaf, 4, Leaf)                  (* prawy podwęzeł 4 *)
    ),
    5,                                      (* korzeń 5 *)
    Node(
      Node(Leaf, 6, Leaf),                  (* lewy podwęzeł 6 *)
      7,                                    (* korzeń 7 *)
      Leaf                                  (* brak prawego podwęzła *)
    )
  )
;;

let alpha_height (n : int) : int = 
    int_of_float( floor (log (float_of_int n) /. log ((float_of_int alpha_denom) /. (float_of_int alpha_num))))
;;

let rec to_list (t : 'a tree) xs = 
  match t with
  | Leaf -> xs
  | Node (l, v, r) -> 
      to_list l (v :: to_list r xs)
  (* zrobic bardziej optymalnie bez @ *)
;;

let rec take ls n =
  match ls with
  | [] -> []
  | h :: tail ->
    if n <= 0 then [] 
    else h :: (take tail (n-1))

let rec drop ls n =
  match ls with
  | [] -> []
  | h :: tail ->
    if n<=0 then ls
    else drop tail (n-1)


let rebuild_balanced (t : 'a tree) : 'a tree =
  let rec build ls =
  match ls with
  | [] -> Leaf
  | lst ->
    let len = List.length lst in
    let mid = len / 2 in
    let left = take ls mid in
    let right = drop ls mid in
    (match right with
    | [] -> Leaf
    | h :: tail -> Node(build left, h, build tail))
  in build (to_list t [])
;;

let empty : 'a sgtree =
  {tree = Leaf; size = 0; max_size = 0}
;;

let find (x : 'a) (sgt : 'a sgtree) : bool =
  let rec recfind (t : 'a tree) : bool =
    match t with
    | Leaf -> false
    | Node(l,v,r) -> 
      if x < v then recfind l
      else if v < x then recfind r
      else true
  in recfind sgt.tree
;;

let rec size (t : 'a tree) : int =
  match t with 
  | Leaf -> 0
  | Node(l,v,r) ->
    size(l) + size(r) + 1
;;

let isok sst ssl : bool = 
  (float_of_int ssl) <= alpha *. (float_of_int sst) && (float_of_int (sst - ssl - 1)) <= alpha *. (float_of_int sst)

let insert (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  if find x sgt then sgt
  else
    let rec recins (t : 'a tree) : 'a tree * int=
      match t with
      | Leaf -> (Node(Leaf, x, Leaf), 1)
      | Node(l,v,r) ->
        if x < v then 
          let (newl, lsize) = recins l in
          let rsize = size r in
          if (isok (rsize+lsize+1) lsize) then (Node(newl, v, r), rsize+lsize+1)
          else (rebuild_balanced (Node(newl, v, r)), rsize+lsize+1)
        else
          let (newr, rsize) = recins r in
          let lsize = size l in
          if (isok (lsize+rsize+1) lsize) then (Node(l, v, newr), rsize+lsize+1)
          else (rebuild_balanced (Node(l, v, newr)), rsize+lsize+1)
    in 
    let (ntree, _) = recins sgt.tree in
    let nsize = sgt.size + 1 in
    let nmax_size = if nsize > sgt.max_size then nsize else sgt.max_size in
    {tree = ntree; max_size = nmax_size; size = nsize}
;;

let remove (x : 'a) (sgt : 'a sgtree) : 'a sgtree =
  if not (find x sgt) then sgt
  else
    let rec recrem (t : 'a tree) (y : 'a) : 'a tree =
      match t with
      | Leaf -> Leaf
      | Node(l, v, r) ->
        if y < v then Node(recrem l y, v, r)
        else if v < y then Node(l, v, recrem r y)
        else 
          (
          match (l, r) with
          | (Leaf, Leaf) -> Leaf
          | (Leaf, _) ->  r
          | (_, Leaf) -> l
          | (_, _) ->
            let rec find_min t =
              match t with
              | Leaf -> failwith "Empty tree"
              | Node (Leaf, v, _) -> v
              | Node (l, _, _) -> find_min l
            in
            let mn = find_min r in
            Node(l, mn, recrem r mn)
          )
    in 
    let ntree = recrem sgt.tree x in
    let nsize = sgt.size - 1 in
    if (float_of_int nsize) < ((float_of_int sgt.max_size) *. alpha) then {tree = rebuild_balanced ntree; size = nsize; max_size = nsize}
    else {tree = ntree; size = nsize; max_size = sgt.max_size}

    
  let rbtest = rebuild_balanced test_tree
  let test_sgt = {tree = rebuild_balanced test_tree; size = 7; max_size = 7}
  let sgtest = ((insert 10 (insert 9 (insert 8 test_sgt))))
