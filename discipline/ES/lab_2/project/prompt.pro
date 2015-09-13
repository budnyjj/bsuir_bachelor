#!/usr/bin/gprolog --consult-file

prompt :-
    loop(3),
    format("Please, enter password: ", []),
    read(Password),
    Password = abc,
    format("Password: ~w", [Password]).

loop(N) :-
    %% format("Loop #1: ~w~N", [N]),
    N > 0; fail.

loop(N) :-
    %% format("Loop #2: ~w~N", [N]),
    N > 0,
    loop(N - 1).

abc.
