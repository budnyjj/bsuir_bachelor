 #!/usr/bin/gprolog --consult-file
 
 prompt :-
     loop(3),
     format("Please, enter password: ", []),
     read(Password),
     Password = abc,
     format("Password: ~w", [Password]).
 
 loop(N) :-
     N > 0; fail.
 
 loop(N) :-
     N > 0,
     loop(N - 1).
 
 abc.
