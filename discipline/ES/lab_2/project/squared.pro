#!/usr/bin/gprolog --consult-file

square(0, Ret) :-
    Ret is 0.

square(0, Ret).

square(N, Ret) :-
    N1 is N - 1,
    square(N1, X),
    Ret is X + 2*N - 1.

square(N) :-
    square(N, Ret),
    format("Square of ~w: ~w~N", [N, Ret]).
