%% It works
%% sum(A, B) :-
%%   C is A + B,
%%   format("Sum of ~w and ~w is ~w~N", [A,B,C]).

sum(0, 0, Ret) :-
    Ret is 0.

sum(0, Acc, Ret) :-
    Ret is Acc.

sum(N, Acc, Ret) :-
    Acc1 is Acc + N,
    N1 is N - 1,
    sum(N1,Acc1,Ret).

sum(0) :-
    sum(0, 0, Ret),
    format("Sum up to 0: ~w~N", [Ret]).

sum(N) :-
    sum(N, 0, Ret),
    format("Sum up to ~w: ~w~N", [N, Ret]).
