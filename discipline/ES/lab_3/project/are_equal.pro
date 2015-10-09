#!/usr/bin/gprolog --consult-file

cmp(X, Y) :-
    X > Y.

cmp_list([], []).
cmp_list([H1|T1], [H2|T2]) :-
    H1 =:= H2,
    cmp_list(T1, T2).

split(H, [A|X], [A|Y], Z) :-
    cmp(A, H),
    split(H, X, Y, Z).

split(H, [A|X], Y, [A|Z]) :-
    \+(cmp(A, H)),
    split(H, X, Y, Z).

split(_, [], [], []).

quick_sort(L, X) :-
    quick_sort(L, X, []).

quick_sort([], X, X).
quick_sort([H|T], S, X) :-
    split(H, T, A, B),
    quick_sort(A, S, [H|Y]),
    quick_sort(B, Y, X).

are_equal(L1, L2) :-
    quick_sort(L1, L1_s),
    quick_sort(L2, L2_s),
    cmp_list(L1_s, L2_s).
