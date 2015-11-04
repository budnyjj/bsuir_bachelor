 auto_eval_from_variant(1, 0.1).
 auto_eval_from_variant(2, 0.5).
 auto_eval_from_variant(3, 0.9).

 road_eval_from_variant(1, 0.3).
 road_eval_from_variant(2, 0.5).
 road_eval_from_variant(3, 0.7).

 driver_eval_from_variant(1, 0.3).
 driver_eval_from_variant(2, 0.5).
 driver_eval_from_variant(3, 1.0).

 print_menu([], _).
 print_menu([Name|NamesTail], [Handler|HandlersTail]) :-
     format("~s~N", [Name]),
     Handler,
     print_menu(NamesTail, HandlersTail).

 get_expert_preference(Variant) :-
     format("1. BAD~N2. NORMAL~N3. GOOD~N~n", []),
     format("Your choose: ", []),
     read_integer(Variant),
     check_variant(Variant).

 check_variant(Variant) :-
     variant_is_not_valid(Variant), !,
     format("=== ERROR ===============================~N", []),
     format(" Bad variant! Try again.~N", []),
     format("=========================================~N", []),
     fail.
 check_variant(_).

 variant_is_not_valid(Variant) :-
     Variant < 1; Variant > 3.

 check_weights(X, Y, Z) :-
     weights_are_not_valid(X, Y, Z), !,
     format("=== ERROR ========================================================~N", []),
     format(" Weight sum is not equal 1.0 or elements are not valid! Try again.~N", []),
     format("==================================================================~N", []),
     fail.
 check_weights(_, _, _).

 weights_are_not_valid(X, Y, Z) :-
     X < 0; Y < 0; Z < 0;
     X > 1; Y > 1; Z > 1;
     X + Y + Z =\= 1.

 loop.
 loop :- loop.

 run :-
     loop,
     print_menu(["Please, give us information about AUTO.",
                 "Please, give us information about ROAD.",
                 "Please, give us information about DRIVER."],
                [get_expert_preference(AutoChosenVariant),
                 get_expert_preference(RoadChosenVariant),
                 get_expert_preference(DriverChosenVariant)]),
     
     auto_eval_from_variant(AutoChosenVariant, AutoEval),
     road_eval_from_variant(RoadChosenVariant, RoadEval),
     driver_eval_from_variant(DriverChosenVariant, DriverEval),

     print_menu(["Please, input WEIGHT coefficient for AUTO parameter:",
                 "Please, input WEIGHT coefficient for ROAD parameter:",
                 "Please, input WEIGHT coefficient for DRIVER parameter:"],
                [read_number(AutoWeight),
                 read_number(RoadWeight),
                 read_number(DriverWeight)]),

     check_weights(AutoWeight, RoadWeight, DriverWeight),

     Speed is 90 * (AutoEval * AutoWeight + RoadEval * RoadWeight + DriverEval * DriverWeight),

     format("=== RESULT ================~N", []),
     format(" Suggested speed is: ~2f~N", [Speed]),
     format("===========================~N", []).