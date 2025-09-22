type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree;;

let rec flat_append t xs =
  match t with
  | Leaf -> xs
  | Node(l, v, r) -> flat_append l (v :: flat_append r xs);;

let t =
  Node  ( Node  (Leaf, 2 , Leaf),
          5,
          Node  ( Node (Leaf, 6, Leaf),
                  8,
                  Node (Leaf, 9, Leaf)
                )
          );;

flatten = flat_append t [];;