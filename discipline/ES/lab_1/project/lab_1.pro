may_exist(X) :-
    X=0; X=1.

not_exist(X) :-
    X=0.

equation :-
    may_exist(P1),
    may_exist(P2),
    may_exist(P3),
    not_exist(P4),

    may_exist(C1),
    not_exist(C2),
    not_exist(C3),
    not_exist(C4),

    not_exist(M1),
    may_exist(M2),
    may_exist(M3),
    may_exist(M4),

    not_exist(H1),
    not_exist(H2),
    not_exist(H3),
    may_exist(H4),

    P1 + P2 + P3 + P4 =:= 1,
    C1 + C2 + C3 + C4 =:= 1,
    M1 + M2 + M3 + M4 =:= 1,
    H1 + H2 + H3 + H4 =:= 1,

    P1 + C1 + M1 + H1 =:= 1,
    P2 + C2 + M2 + H2 =:= 1,
    P3 + C3 + M3 + H3 =:= 1,
    P4 + C4 + M4 + H4 =:= 1,
    
    format("   P C M H~N", []),
    format("1: ~w ~w ~w ~w~N", [P1,C1,M1,H1]),
    format("2: ~w ~w ~w ~w~N", [P2,C2,M2,H2]),
    format("3: ~w ~w ~w ~w~N", [P3,C3,M3,H3]),
    format("4: ~w ~w ~w ~w~N", [P4,C4,M4,H4]).
