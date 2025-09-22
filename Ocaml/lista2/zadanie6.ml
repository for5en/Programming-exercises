let rec suffixes xs =
  match xs with
  | [] -> [[]]
  | head :: tail -> xs :: suffixes tail 
