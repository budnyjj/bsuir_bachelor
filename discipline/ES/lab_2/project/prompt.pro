prompt :-
    loop(3),
    format("Please, enter password: ", []),
    read(Password),
    Password is "abc",
    format("Password: ~w", [Password]).

loop(N).
loop(N) :-
    loop(N).
