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

let eval = eval_env M.empty

let rec print_expr ?(indent=0) (e : expr) : unit =
  let pad () = print_string (String.make indent ' ') in
  match e with
  | Int n -> pad (); Printf.printf "Int(%d)\n" n
  | Bool b -> pad (); Printf.printf "Bool(%b)\n" b
  | Unit -> pad (); Printf.printf "Unit\n"
  | Var x -> pad (); Printf.printf "Var(%s)\n" x
  | Binop (op, e1, e2) ->
      pad (); Printf.printf "Binop(%s)\n" (string_of_binop op);
      print_expr ~indent:(indent+2) e1;
      print_expr ~indent:(indent+2) e2
  | If (e1, e2, e3) ->
      pad (); print_endline "If";
      print_expr ~indent:(indent+2) e1;
      print_expr ~indent:(indent+2) e2;
      print_expr ~indent:(indent+2) e3
  | Let (x, e1, e2) ->
      pad (); Printf.printf "Let(%s)\n" x;
      print_expr ~indent:(indent+2) e1;
      print_expr ~indent:(indent+2) e2
  | Fun (x, e1) ->
      pad (); Printf.printf "Fun(%s)\n" x;
      print_expr ~indent:(indent+2) e1
  | Funrec (f, x, e1) ->
      pad (); Printf.printf "Funrec(%s, %s)\n" f x;
      print_expr ~indent:(indent+2) e1
  | App (e1, e2) ->
      pad (); print_endline "App";
      print_expr ~indent:(indent+2) e1;
      print_expr ~indent:(indent+2) e2
  | Pair (e1, e2) ->
      pad (); print_endline "Pair";
      print_expr ~indent:(indent+2) e1;
      print_expr ~indent:(indent+2) e2
  | Fst e1 ->
      pad (); print_endline "Fst";
      print_expr ~indent:(indent+2) e1
  | Snd e1 ->
      pad (); print_endline "Snd";
      print_expr ~indent:(indent+2) e1
  | IsPair e1 ->
      pad (); print_endline "IsPair";
      print_expr ~indent:(indent+2) e1
  | Match (e1, x1, x2, e2) ->
      pad (); Printf.printf "Match(%s, %s)\n" x1 x2;
      print_expr ~indent:(indent+2) e1;
      print_expr ~indent:(indent+2) e2

and string_of_binop op =
  match op with
  | Add -> "+"
  | Sub -> "-"
  | Mult -> "*"
  | Div -> "/"
  | And -> "&&"
  | Or -> "||"
  | Eq -> "="
  | Neq -> "<>"
  | Leq -> "<="
  | Lt -> "<"
  | Gt -> ">"
  | Geq -> ">="


let rename_expr (e : expr) : expr =
  (* Funkcja do generowania nowej unikalnej nazwy zmiennej *)
  let new_var (l : int) : string =
    "#" ^ (string_of_int l)
  in

  (* Funkcja rekurencyjna do przekształcania wyrażeń z nowymi zmiennymi *)
  let rec rename (e : expr) (env : ident M.t) (counter : int) : expr * ident M.t * int =
    (match e with
    | Int _ | Bool _ | Unit -> (e, env, counter)
    | Var x ->
        (match M.find_opt x env with
        | Some new_x -> (Var new_x, env, counter)
        | None -> (e, env, counter))  (* zmienna nie została zmapowana, więc jest wolna *)
    | Binop (op, e1, e2) ->
        let (e1', env1, counter1) = rename e1 env counter in
        let (e2', env2, counter2) = rename e2 env1 counter1 in
        (Binop(op, e1', e2'), env2, counter2)
    | If (e1, e2, e3) ->
        let (e1', env1, counter1) = rename e1 env counter in
        let (e2', env2, counter2) = rename e2 env1 counter1 in
        let (e3', env3, counter3) = rename e3 env2 counter2 in
        (If(e1',e2',e3'), env3, counter3)
    | Let (x, e1, e2) ->
        let new_x = new_var counter in
        let env' = M.add x new_x env in
        let (e1', env1, counter1) = rename e1 env' (counter + 1) in
        let (e2', env2, counter2) = rename e2 env1 counter1 in
        (Let(new_x, e1', e2'), env2, counter2)
    | Pair (e1, e2) ->
      let (e1', env1, counter1) = rename e1 env counter in
      let (e2', env2, counter2) = rename e2 env1 counter1 in
      (Pair(e1', e2'), env2, counter2)
    | Fst e -> 
      let (e1', env1, counter1) = rename e env counter in
      (Fst e1', env1, counter1)
    | Snd e -> 
      let (e1', env1, counter1) = rename e env counter in
      (Snd e1', env1, counter1)
    | IsPair e -> 
      let (e1', env1, counter1) = rename e env counter in
      (IsPair e1', env1, counter1)
    | Fun (x, e) ->
        (* Generowanie nowej nazwy dla zmiennej funkcji *)
        let new_x = new_var counter in
        (* Dodajemy nową nazwę zmiennej do środowiska *)
        let env' = M.add x new_x env in
        let (e1', env1, counter1) = rename e env' (counter+1) in
        (Fun(new_x, e1'), env1, counter1)
    | Funrec (f, x, e) ->
        (* Generowanie nowych nazw dla funkcji rekurencyjnej i zmiennej *)
        let new_f = new_var counter in
        let new_x = new_var (counter+1) in
        let env' = M.add f new_f (M.add x new_x env) in
        let (e1', env1, counter1) = rename e env' (counter+2) in
        (Funrec(new_f,new_x,e1'), env1, counter1)
    | App (e1, e2) ->
      let (e1', env1, counter1) = rename e1 env counter in
      let (e2', env2, counter2) = rename e2 env1 counter1 in
      (App(e1', e2'), env2, counter2)
    | Match (e1, x1, x2, e2) ->
      let (e1', env1, counter1) = rename e1 env counter in
      let new_x1 = new_var counter1 in
      let new_x2 = new_var (counter1 + 1) in
      let env2 = M.add x1 new_x1 (M.add x2 new_x2 env1) in
      let (e2', env3, counter2) = rename e2 env2 (counter1 + 2) in
      (Match (e1', new_x1, new_x2, e2'), env3, counter2))
  in
  let (e', _, _) = rename e M.empty 0 in e'



let interp (s : string) : value =
  eval (parse s)

let rename_test (s : string) : value =
  eval (rename_expr (parse s))
