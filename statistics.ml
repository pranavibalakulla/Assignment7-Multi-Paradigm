(* Calculate the mean *)
let calculate_mean numbers =
  let sum = List.fold_left ( + ) 0 numbers in
  float_of_int sum /. float_of_int (List.length numbers)

(* Calculate the median *)
let calculate_median numbers =
  let sorted = List.sort compare numbers in
  let length = List.length sorted in

  if length mod 2 = 1 then
    float_of_int (List.nth sorted (length / 2))
  else
    let left = List.nth sorted (length / 2 - 1) in
    let right = List.nth sorted (length / 2) in
    (float_of_int left +. float_of_int right) /. 2.0

(* Calculate the mode *)
let calculate_mode numbers =
  let count_occurrences value =
    List.fold_left
      (fun count number ->
        if number = value then count + 1 else count)
      0
      numbers
  in

  let unique_numbers =
    List.sort_uniq compare numbers
  in

  List.fold_left
    (fun current_mode number ->
      if count_occurrences number >
         count_occurrences current_mode
      then number
      else current_mode)
    (List.hd unique_numbers)
    unique_numbers

let numbers = [4; 2; 7; 2; 9; 4; 2; 5; 7; 2]

let mean = calculate_mean numbers
let median = calculate_median numbers
let mode = calculate_mode numbers

let () =
  print_endline "Multi-Paradigm Statistics Program - OCaml";
  print_endline "-----------------------------------------";

  print_string "Numbers: ";

  List.iter
    (fun number -> Printf.printf "%d " number)
    numbers;

  print_endline "";
  print_endline "";

  Printf.printf "Mean: %.2f\n" mean;
  Printf.printf "Median: %.2f\n" median;
  Printf.printf "Mode: %d\n" mode