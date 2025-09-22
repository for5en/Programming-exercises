type bop = Add | Sub | Mult | Div | Pow
type sop = Log

type expr = 
    | Float of float
    | Binop of bop * expr * expr
    | Sinop of sop * expr
