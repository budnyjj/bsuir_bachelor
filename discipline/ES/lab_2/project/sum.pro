#!/usr/bin/gprolog --consult-file

sum(0, Ret) :-
    Ret is 0.

sum(1, Ret) :-
	Ret is 1.

sum(N, Ret) :-
    N1 is N - 1,
    sum(N1,X),
    Ret is X + N.

sum(0) :-
    sum(0, Ret),
    format("Sum up to 0: ~w~N", [Ret]).

sum(N) :-
    sum(N, Ret),
    format("Sum up to ~w: ~w~N", [N, Ret]).
