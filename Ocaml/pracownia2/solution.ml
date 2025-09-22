type bop =
  (* arithmetic *)
  | Add | Sub | Mult | Div
  (* logic *)
  | And | Or
  (* comparison *)
  | Eq | Neq | Leq | Lt | Geq | Gt

type ident = string

module M = Map.Make(String)

type expr =
  | Int    of int
  | Binop  of bop * expr * expr
  | Bool   of bool
  | If     of expr * expr * expr
  | Let    of ident * expr * expr
  | Var    of ident
  | Cell   of int * int
  | Unit
  | Pair   of expr * expr
  | Fst    of expr
  | Snd    of expr
  | Match  of expr * ident * ident * expr
  | IsPair of expr
  | Fun    of ident * expr
  | Funrec of ident * ident * expr
  | App    of expr * expr

type env = value M.t

and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env

  let eval_spreadsheet (s : expr list list) : value list list option =
    let odp =
    let rows = List.length s in
    let cols = if rows = 0 then 0 else List.length (List.hd s) in
    let memo = Array.make_matrix rows cols None in
    let rec is_visited i j visited : bool =
      List.exists (fun (r,c) -> r = i && c = j) visited
  
    in
  
    let eval_op (op : bop) (val1 : value) (val2 : value) : value =
      match op, val1, val2 with
      | Add,  VInt  v1, VInt  v2 -> VInt  (v1 + v2)
      | Sub,  VInt  v1, VInt  v2 -> VInt  (v1 - v2)
      | Mult, VInt  v1, VInt  v2 -> VInt  (v1 * v2)
      | Div,  VInt  v1, VInt  v2 -> VInt  (v1 / v2)
      | And,  VBool v1, VBool v2 -> VBool (v1 && v2)
      | Or,   VBool v1, VBool v2 -> VBool (v1 || v2)
      | Leq,  VInt  v1, VInt  v2 -> VBool (v1 <= v2)
      | Lt,   VInt  v1, VInt  v2 -> VBool (v1 < v2)
      | Gt,   VInt  v1, VInt  v2 -> VBool (v1 > v2)
      | Geq,  VInt  v1, VInt  v2 -> VBool (v1 >= v2)
      | Neq,  _,        _        -> VBool (val1 <> val2)
      | Eq,   _,        _        -> VBool (val1 = val2)
      | _,    _,        _        -> failwith "type error"
  
    in
  
    let rec eval_expr (env : env) (visited : (int * int) list) (e : expr) : value option  =
    match e with
    | Int i -> Some (VInt i)
    | Bool b -> Some (VBool b)
    | Binop (op, e1, e2) ->
      (match (eval_expr env visited e1), (eval_expr env visited e2) with
      | Some v1, Some v2 -> Some (eval_op op v1 v2)
      | _ -> None)
    | If (b, t, e) ->
        (match eval_expr env visited b with
          | Some VBool true -> eval_expr env visited t
          | Some VBool false -> eval_expr env visited e
          | _ -> failwith "type error")
    | Var x ->
       (match M.find_opt x env with
         | Some v -> Some v
         | None -> failwith "unknown var")
    | Let (x, e1, e2) ->
      (match eval_expr env visited e1 with
      | Some v -> eval_expr (M.add x v env) visited e2
      | None -> None)
    | Pair (e1, e2) -> 
      (match eval_expr env visited e1, eval_expr env visited e2 with
      | Some v1, Some v2 -> Some (VPair(v1,v2))
      | _ -> None)
    | Unit -> Some VUnit
    | Fst e ->
        (match eval_expr env visited e with
          | Some VPair (v1, _) -> Some v1
          | _ -> failwith "Type error")
    | Snd e ->
        (match eval_expr env visited e with
          | Some VPair (_, v2) -> Some v2
          | _ -> failwith "Type error")
    | Match (_e1, _x, _y, _e2) ->
        failwith "Not implemented"
    | IsPair e ->
        (match eval_expr env visited e with
          | Some VPair _ -> Some (VBool true)
          | _ -> Some (VBool false))
    | Fun (x, e) -> Some (VClosure (x, e, env))
    | Funrec (f, x, e) -> Some (VRecClosure (f, x, e, env))
    | App (e1, e2) ->
        let v1 = eval_expr env visited e1 in
        let v2 = eval_expr env visited e2 in
        (match v1 with
          | Some VClosure (x, body, clo_env) ->
            (match v2 with
            | Some v2' -> eval_expr (M.add x v2' clo_env) visited body
            | _ -> None)
          | Some VRecClosure (f, x, body, clo_env) as c ->
            (match v2,c with
            | Some v2', Some c' -> eval_expr (clo_env |> M.add x v2' |> M.add f c') visited body
            | _ -> None)
          | None -> None
          | _ -> failwith "not a function")
    | Cell (i, j) -> eval_cell i j visited
  
    and 
    
    eval_cell i j visited : value option =
      if i < 0 || j < 0 || i >= rows || j >= cols then None
      else if is_visited i j visited then None
      else
        match memo.(i).(j) with
        | Some v -> Some v
        | None -> 
          let expr = List.nth (List.nth s i) j in
          match eval_expr M.empty ((i,j)::visited) expr with
          | None -> None
          | Some v -> 
            memo.(i).(j) <- Some v;
            Some v
  
    in
  
    let rec eval_row i j acc row =
      match row with
      | [] -> Some (List.rev acc)
      | _ :: tl ->
        match eval_cell i j [] with
        | Some v -> eval_row i (j + 1) (v :: acc) tl
        | None -> None
  
    in
  
    let rec eval_all i acc sheet =
      match sheet with
      | [] -> Some (List.rev acc)
      | row :: tl ->
        match eval_row i 0 [] row with
        | Some row_vals -> eval_all (i + 1) (row_vals :: acc) tl
        | None -> None
  
    in
  
    eval_all 0 [] s in
    (match odp with
    | Some _ -> odp
    | None -> None)