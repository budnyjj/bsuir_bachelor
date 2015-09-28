 is_growing([_]) :- !.
 is_growing([A|Y]) :-
     Y = [B|_],
     cmp(A, B),
     is_growing(Y).
 
 cmp(A, B) :-
     A < B.
 
 task :-
     format("Input list in form [int, int, ...].~N", []),
     read(X),
     is_growing(X).
