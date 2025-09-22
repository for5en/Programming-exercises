type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree;;

let rec fold_tree f b t =
  match t with
  | Leaf -> b
  | Node(l, v, r) -> f (fold_tree f b l) v (fold_tree f b r);;

let tree_product t = fold_tree (fun a b c -> a*b*c) 1 t;;
let tree_height t = fold_tree (fun a b c -> if c > a then c+1 else a+1) 0 t;;
let tree_flip t = fold_tree (fun l v r -> Node(r, v, l)) Leaf t;;

let max a b =
  if a > b then a else b;;
let min a b = a+b - max a b;;

let tree_span t = fold_tree (
  fun l v r -> (
      let (mn, _) = l in
      let (_, mx) = r in
      (min mn v, max mx v))) 
  (9999, 0) t;;

let flatten t = fold_tree (fun l v r -> (l @ [v] @ r)) [] t;;


let t =
  Node  ( Node  (Leaf, 2 , Leaf),
          5,
          Node  ( Node (Leaf, 6, Leaf),
                  8,
                  Node (Leaf, 9, Leaf)
                )
          );;

flatten t;;