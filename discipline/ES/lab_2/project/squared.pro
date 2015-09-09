square(0, 0, Ret) :-
    Ret is 0.

square(0, Acc, Ret) :-
    Ret is Acc.

square(N, Acc, Ret) :-
    N1 is N - 1,
    square(N1, Acc, X),
    Ret is X + 2*N - 1.

square(N) :-
    square(N, 0, Ret),
    format("Square of ~w: ~w~N", [N, Ret]).
