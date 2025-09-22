type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree;;

let rec insert_bst t x =
  match t with
  | Leaf -> Node (Leaf, x, Leaf)
  | Node(l, v, r) -> 
    if x < v then Node(r, v, insert_bst l x)
    else Node(l, v, insert_bst r x);;

let t =
  Node  ( Node  (Leaf, 2 , Leaf),
          5,
          Node  ( Node (Leaf, 6, Leaf),
                  8,
                  Node (Leaf, 9, Leaf)
                )
          );;

let t = insert_bst t 7;;
let t = insert_bst t 11;;
