#!/usr/bin/gprolog --consult-file

is_growing([_]).
is_growing([A|Y]) :-
    Y = [B|_],
    cmp(A, B),
    is_growing(Y).

cmp(A, B) :-
    format("cmp: A: ~w, B: ~w~N", [A, B]),
    A < B.

task :-
    format("Please, input list in form [int, int, ...].~N", []),
    read(X),
    is_growing(X).
