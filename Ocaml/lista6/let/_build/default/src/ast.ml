type bop =
  (* arithmetic *)
  | Add | Sub | Mult | Div
  (* logic *)
  | And | Or
  (* comparison *)
  | Eq | Leq

type ident = string

type expr = 
  | Int   of int
  | Pair  of expr * expr
  | Fst   of expr
  | Snd   of expr
  | Binop of bop * expr * expr
  | Bool  of bool
  | If    of expr * expr * expr
  | Let   of ident * expr * expr
  | Var   of ident
  | UnitExpr
  (*  | For  of ident * expr * expr * expr  -  zmienna po ktorej sie iterujemy, od, do, wyrazenie  *)
  (*  | Integral of ident * expr * expr * expr  -  zmienna po ktorej calkujemy, od, do, wyrazenie(funkcja)  *)