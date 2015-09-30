 cmp(X, Y, Y) :-
     Y < X, !.
 
 cmp(X, Y, X) :-
     Y >= X, !.
 
 find_min([H], H).
 
 find_min([H|T], Min):-
     find_min(T, Ret),
     cmp(Ret, H, Min).
 
 run:-
     format("Input list in form [int, int, ...].~N", []),
     read(X),
     find_min(X, Min),
     format("Min element of the list is: ~w~N", [Min]).
