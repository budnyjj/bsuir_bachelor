dynamic([iteration/1, etalon_number/1, weights/4]).

etalon(1, 0.7, 0.6, 0.6, "yes").
etalon(2, 0.7, 0.4, 0.8, "no").
etalon(3, 0.3, 0.5, 1.0, "no").
etalon(4, 0.9, 0.8, 0.6, "yes").
etalon(5, 0.4, 0.7, 0.8, "yes").
etalon(6, 0.7, 0.9, 0.6, "yes").
etalon(7, 0.2, 0.6, 0.7, "no").
etalon(8, 0.6, 0.7, 0.8, "yes").
etalon(9, 0.4, 0.4, 0.6, "no").
etalon(10, 0.7, 1.0, 0.6, "yes").

cleanup :-
    retractall(iteration(_)),
    retractall(etalon_number(_)),
    retractall(weight(_, _)).

loop :- update_iteration_number.
loop :- loop.

update_iteration_number :-
    iteration(I),
    I < 1000,
    New_I is I + 1,
    format("Iteration #~0f~N", [New_I]),
    retractall(iteration(_)),
    asserta(iteration(New_I)).

update_etalon_number :-
    etalon_number(E),
    E < 11,
    New_E is E + 1,
    format("Etalon number #~0f~N", [New_E]),
    retractall(etalon_number(_)),
    asserta(etalon_number(etalon_number)).

init :-
    asserta(iteration(0)),
    asserta(etalon_number(1)),
    asserta(weights(3, 2, 2, 2)).
    
teach :-
    loop,
    weights(A0, A1, A2, A3),
    etalon_number(E),
    etalon(E, X1, X2, X3, S),
    Y = A0 + X1 * A1 + X2 * A2 + X3 * A3,
    check(S, Y, A0, X1, X2, X3),

    format("Point: [A1:~1f, A2:~1f, A3:~1f] [X1:~1f, X2:~1f, X3:~1f]~N", [A1, A2, A3, X1, X2, X3]).


check("yes", Y, _, _, _, _):- Y > 0, update_etalon_number, !.
check("yes", Y, A0, X1, X2, X3) :-
    weights(_, A1, A2, A3),
    
    A1_new = A1 + X1,
    A2_new = A2 + X2,
    A3_new = A3 + X3,

    retractall(etalon_number(_)),
    retractall(weights(_,_,_,_)),
    asserta(etalon_number(1)),
    asserta(weights(A1_new, A2_new, A3_new, A0)),
    !, fail.

check("no", Y, _, _, _, _):- Y < 0, update_etalon_number, !.
check("no", Y, A0, X1, X2, X3) :-
    weights(_, A1, A2, A3),

    A1_new = A1 - X1,
    A2_new = A2 - X2,
    A3_new = A3 - X3,

    retractall(etalon_number(_)),
    retractall(weights(_,_,_,_)),
    asserta(etalon_number(1)),
    asserta(weights(A1_new, A2_new, A3_new, A0)),
    !, fail.

run :-
    cleanup,
    init,
    teach.
