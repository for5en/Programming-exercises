(* ********************* *)
(* UWAGA! *)
(* Sam interpreter i resztę pliku (z wyjątkiem typu value) można dowolnie modyfikować. *)
(* Liczy się to, zeby funkcja eval_spreadsheet zwracała poprawną wartość! *)
(* ********************* *)

open Ast

let parse (s : string) : expr =
  Parser.main Lexer.read (Lexing.from_string s)

module M = Map.Make(String)

type env = value M.t

and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of ident * expr * env
  | VRecClosure of ident * ident * expr * env

let rec show_value v =
  match v with
  | VInt n -> string_of_int n
  | VBool v -> string_of_bool v
  | VUnit -> "()"
  | VPair (v1,v2) -> "(" ^ show_value v1 ^ ", " ^ show_value v2 ^ ")"
  | VClosure _ | VRecClosure _ -> "<fun>"

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

let rec eval_env (env : env) (e : expr) : value =
  match e with
  | Int i -> VInt i
  | Bool b -> VBool b
  | Binop (op, e1, e2) ->
      eval_op op (eval_env env e1) (eval_env env e2)
  | If (b, t, e) ->
      (match eval_env env b with
        | VBool true -> eval_env env t
        | VBool false -> eval_env env e
        | _ -> failwith "type error")
  | Var x ->
     (match M.find_opt x env with
       | Some v -> v
       | None -> failwith "unknown var")
  | Let (x, e1, e2) ->
      eval_env (M.add x (eval_env env e1) env) e2
  | Pair (e1, e2) -> VPair (eval_env env e1, eval_env env e2)
  | Unit -> VUnit
  | Fst e ->
      (match eval_env env e with
        | VPair (v1, _) -> v1
        | _ -> failwith "Type error")
  | Snd e ->
      (match eval_env env e with
        | VPair (_, v2) -> v2
        | _ -> failwith "Type error")
  | Match (_e1, _x, _y, _e2) ->
      failwith "Not implemented"
  | IsPair e ->
      (match eval_env env e with
        | VPair _ -> VBool true
        | _ -> VBool false)
  | Fun (x, e) -> VClosure (x, e, env)
  | Funrec (f, x, e) -> VRecClosure (f, x, e, env)
  | App (e1, e2) ->
      let v1 = eval_env env e1 in
      let v2 = eval_env env e2 in
      (match v1 with
        | VClosure (x, body, clo_env) ->
            eval_env (M.add x v2 clo_env) body
        | VRecClosure (f, x, body, clo_env) as c ->
            eval_env (clo_env |> M.add x v2 |> M.add f c) body
        | _ -> failwith "not a function")
  | Cell (_row, _col) ->
      failwith "???"

      

let eval_spreadsheet (s : expr list list) : value list list option =
  let odp =
  let rows = List.length s in
  let cols = if rows = 0 then 0 else List.length (List.hd s) in
  let memo = Array.make_matrix rows cols None in
  let is_visited i j visited : bool =
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
  | Cell (i, j) -> eval_cell env i j visited

  and 
  
  eval_cell env i j visited : value option =
    if i < 0 || j < 0 || i >= rows || j >= cols then None
    else if is_visited i j visited then None
    else
      match memo.(i).(j) with
      | Some v -> Some v
      | None -> 
        let expr = List.nth (List.nth s i) j in
        match eval_expr env ((i,j)::visited) expr with
        | None -> None
        | Some v -> 
          memo.(i).(j) <- Some v;
          Some v

  in

  let rec eval_row i j acc row =
    match row with
    | [] -> Some (List.rev acc)
    | _ :: tl ->
      match eval_cell M.empty i j [] with
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
    | None -> failwith "Error: circular dependency")


let ex1 = [["10";"50"];["0 - {1,1}";"{0,0} + {0,1}"]]
let ex2 = [["funrec fib n -> if n <= 1 then n else fib (n - 1) + fib (n - 2)";"0"];
["{0,0} 1";"1"];
["{0,0} 2";"{0,1} + {1,1}"];
["{0,0} 3";"{1,1} + {2,1}"];
["{0,0} 4";"{2,1} + {3,1}"];
["{0,0} 5";"{3,1} + {4,1}"];
["{0,0} 6";"{4,1} + {5,1}"]]
let ex3 = [["{1,0} + 3"];
["{2,0} * 10"];
["{0,0} - 17"]]


let parse_and_eval_spreadsheet (s : string list list) : string list list option =
  let es = List.map (List.map parse) s in
  let vs = eval_spreadsheet es in
  Option.map (List.map (List.map show_value)) vs



