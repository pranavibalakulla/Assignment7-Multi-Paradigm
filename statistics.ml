(* statistics.ml
   Assignment 7: Multi-Paradigm Problem Solving - Functional approach (OCaml)

   Calculates the mean, median, and mode(s) of a list of integers using
   pure functions over immutable lists. There is no mutable state: no refs,
   no arrays that are modified, and no loops. Every result is built with
   higher-order list functions such as fold_left, map, and filter.

   Run: ocaml statistics.ml             (uses the sample dataset)
        ocaml statistics.ml 3 1 4 1 5   (uses the integers given on the command line) *)

(* Sample dataset used when no numbers are given on the command line. *)
let sample_data = [4; 2; 7; 2; 9; 4; 2; 5; 7; 2]

(* Mean: the sum (computed with fold_left) divided by the length.
   Returns None for an empty list instead of dividing by zero. *)
let calculate_mean = function
  | [] -> None
  | numbers ->
    let sum = List.fold_left ( + ) 0 numbers in
    Some (float_of_int sum /. float_of_int (List.length numbers))

(* Median: the middle value of a sorted copy of the list, or the average of
   the two middle values when the length is even. List.sort returns a new
   list, so the original is never changed. *)
let calculate_median = function
  | [] -> None
  | numbers ->
    let sorted = List.sort compare numbers in
    let length = List.length sorted in
    let upper = float_of_int (List.nth sorted (length / 2)) in
    if length mod 2 = 1 then Some upper
    else
      let lower = float_of_int (List.nth sorted (length / 2 - 1)) in
      Some ((lower +. upper) /. 2.0)

(* Frequencies: folds over the sorted list to build (value, count) pairs.
   Equal values are adjacent after sorting, so each one either extends the
   count at the head of the accumulator or starts a new pair. *)
let frequencies numbers =
  List.sort compare numbers
  |> List.fold_left
       (fun pairs number ->
          match pairs with
          | (value, count) :: rest when value = number -> (value, count + 1) :: rest
          | _ -> (number, 1) :: pairs)
       []
  |> List.rev

(* Mode: every value whose count equals the highest count, so ties are kept.
   Returns an empty list for an empty input. *)
let calculate_modes numbers =
  let counts = frequencies numbers in
  let highest = List.fold_left (fun best (_, count) -> max best count) 0 counts in
  counts
  |> List.filter (fun (_, count) -> count = highest)
  |> List.map fst

(* Converts command-line arguments to integers. Returns Error with the first
   invalid argument, or Ok with the list of numbers. *)
let parse_arguments arguments =
  match List.find_opt (fun arg -> int_of_string_opt arg = None) arguments with
  | Some bad -> Error (Printf.sprintf "Error: '%s' is not a valid integer." bad)
  | None -> Ok (List.map int_of_string arguments)

(* Uses the command-line numbers if any were given, otherwise the sample data. *)
let read_input () =
  match Array.to_list Sys.argv with
  | _ :: (_ :: _ as arguments) -> parse_arguments arguments
  | _ -> Ok sample_data

let format_option = function
  | Some value -> Printf.sprintf "%.2f" value
  | None -> "undefined (empty list)"

let format_numbers numbers = String.concat " " (List.map string_of_int numbers)

let format_modes numbers = String.concat ", " (List.map string_of_int numbers)

let () =
  match read_input () with
  | Error message ->
    prerr_endline message;
    exit 1
  | Ok numbers ->
    print_endline "Multi-Paradigm Statistics Program - OCaml";
    print_endline "-----------------------------------------";
    Printf.printf "Numbers: %s\n\n" (format_numbers numbers);
    Printf.printf "Mean: %s\n" (format_option (calculate_mean numbers));
    Printf.printf "Median: %s\n" (format_option (calculate_median numbers));
    Printf.printf "Mode: %s\n" (format_modes (calculate_modes numbers))
