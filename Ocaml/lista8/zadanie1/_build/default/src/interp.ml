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

let rec reify (v : value) : expr =
  match v with
  | VInt i -> Int i
  | VBool b -> Bool b
  | VUnit -> Unit
  | VPair (v1, v2) -> Pair (reify v1, reify v2)
  | VClosure (x, e, _) -> Fun (x, e)  (* Funkcje są traktowane jako wyrażenia! *)
  | VRecClosure (f, x, e, _) -> Funrec (f, x, e)

let rec cp_env (env : expr M.t) (e : expr) : expr = 
  match e with
  | Int _ -> e
  | Bool _ -> e
  | Unit -> e
  | Var x ->
      (match M.find_opt x env with
       | Some e' -> e'
       | None -> Var x)
  | Binop (op, e1, e2) ->
      let e1' = cp_env env e1 in
      let e2' = cp_env env e2 in
      (match e1', e2' with
       | Int v1, Int v2 ->
           (match op with
            | Add -> Int (v1 + v2)
            | Sub -> Int (v1 - v2)
            | Mult -> Int (v1 * v2)
            | Div -> Int (v1 / v2)
            | Leq -> Bool (v1 <= v2)
            | Lt  -> Bool (v1 < v2)
            | Geq -> Bool (v1 >= v2)
            | Gt  -> Bool (v1 > v2)
            | Eq  -> Bool (v1 = v2)
            | Neq -> Bool (v1 <> v2)
            | _ -> Binop (op, e1', e2'))
       | Bool v1, Bool v2 ->
           (match op with
            | And -> Bool (v1 && v2)
            | Or  -> Bool (v1 || v2)
            | Eq  -> Bool (v1 = v2)
            | Neq -> Bool (v1 <> v2)
            | _ -> Binop (op, e1', e2'))
       | _, _ -> Binop (op, e1', e2'))
  | If (e1, e2, e3) ->
      let e1' = cp_env env e1 in
      let e2' = cp_env env e2 in
      let e3' = cp_env env e3 in
      (match e1' with
       | Bool true -> e2'
       | Bool false -> e3'
       | _ -> If (e1', e2', e3'))
  | Let (x, e1, e2) ->
      let e1' = cp_env env e1 in
      (match e1' with
       | Int _ | Bool _ ->
           cp_env (M.add x e1' env) e2
       | _ ->
           Let (x, e1', cp_env (M.add x (Var x) env) e2))
  | Pair (e1, e2) ->
      Pair (cp_env env e1, cp_env env e2)
  | Fst e ->
      let e' = cp_env env e in
      (match e' with
       | Pair (e1, _) -> e1
       | _ -> Fst e')
  | Snd e ->
      let e' = cp_env env e in
      (match e' with
       | Pair (_, e2) -> e2
       | _ -> Snd e')
  | Match (e1, x, y, e2) ->
      let e1' = cp_env env e1 in
      (match e1' with
       | Pair (e1l, e1r) ->
           let env' = env |> M.add x e1l |> M.add y e1r in
           cp_env env' e2
       | _ -> Match (e1', x, y, cp_env env e2))
  | IsPair e ->
      let e' = cp_env env e in
      (match e' with
       | Pair _ -> Bool true
       | _ -> IsPair e')
  | Fun (x, e) -> Fun (x, cp_env env e)
  | Funrec (f, x, e) -> Funrec (f, x, cp_env env e)
  | App (e1, e2) -> App (cp_env env e1, cp_env env e2)

let eval = eval_env M.empty

let interp (s : string) : value =
  eval (parse s)
