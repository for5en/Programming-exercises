let matrix_id = (1,0,0,1)

let matrix_mult (a,b,c,d) (x,y,z,w) = 
  ((a*x+b*z),(a*y+b*w),(c*x+d*z),(c*y+d*w))

let rec matrix_expt (a,b,c,d) k =
  if k = 0 then matrix_id
  else if k mod 2 = 1 then
    matrix_mult (matrix_expt (matrix_mult (a,b,c,d) (a,b,c,d)) (k/2)) (a,b,c,d)
  else
    matrix_expt (matrix_mult (a,b,c,d) (a,b,c,d)) (k/2)

let fib_fast n =
  let (a,b,c,d) = matrix_expt (1,1,1,0) n in b
  