
(* The type of tokens. *)

type token = 
  | WITH
  | UNIT
  | TIMES
  | THEN
  | SND
  | SEMIC
  | RPAREN
  | RBRACK
  | PLUS
  | OR
  | MINUS
  | MATCH
  | LPAREN
  | LET
  | LEQ
  | LBRACK
  | INT of (int)
  | IN
  | IF
  | IDENT of (string)
  | FST
  | FOLD
  | EQ
  | EOF
  | ELSE
  | DIV
  | COMMA
  | BOOL of (bool)
  | ARR
  | ANDTXT
  | AND

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val main: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.expr)
