{
open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let number = '-'? (digit+ | digit+'.'digit+ | '.'digit+)

rule read =
    parse
    | white { read lexbuf }
    | "*" { TIMES }
    | "+" { PLUS }
    | "-" { MINUS }
    | "/" { DIV }
    | "(" { LPAREN }
    | ")" { RPAREN }
    | "**" { POW }
    | "log" { LOG }
    | "e" { FLOAT ( 2.71828182845904523536028747135266249775724709369995 ) }
    | number { FLOAT ( float_of_string (Lexing.lexeme lexbuf)) }
    | eof { EOF }
