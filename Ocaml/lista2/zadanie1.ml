let rec fib n =
  if n = 0 then 0
  else if n = 1 then 1
  else fib(n-1)+fib(n-2)

let fib_iter n =
  let rec pom n a b =
    if n = 0 then a
    else if n = 1 then b
    else pom (n-1) b (a+b)
  in pom n 0 1

  let() =
    print_endline (string_of_int (fib 20));
    print_endline (string_of_int (fib_iter 10))