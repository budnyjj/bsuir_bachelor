#!/usr/bin/gprolog --consult-file

dynamic([a/2, teach_speed/2]).

%% teach_db([[[0.7, 0.6, 0.6], y],
%%           [[0.7, 0.4, 0.8], n],
%%           [[0.3, 0.5, 1.0], n],
%%           [[0.9, 0.8, 0.6], y],
%%           [[0.4, 0.7, 0.8], y],
%%           [[0.7, 0.9, 0.6], y],
%%           [[0.2, 0.6, 0.7], n],
%%           [[0.6, 0.7, 0.8], y],
%%           [[0.4, 0.4, 0.6], n],
%%           [[0.7, 1.0, 0.6], y]]).

% main teach clause
teach(TSpeedA0, TSpeedAi, MaxIter) :-
    teach(TSpeedA0, TSpeedAi, 1, MaxIter).

% initializes iteration counter
teach(TSpeedA0, TSpeedAi, InitIter, MaxIter) :-
    teach(TSpeedA0, TSpeedAi, InitIter, InitIter, MaxIter).

%
% Recursive teach clauses
%

% stop
teach(TSpeedA0, TSpeedAi, InitIter, CurIter, MaxIter) :-
    CurIter >= MaxIter,
    format("Number of iterations exceeded (~d).~n", [MaxIter]).

% starts teach process
% tracks current iteration number
teach(TSpeedA0, TSpeedAi, InitIter, CurIter, MaxIter) :-
    teach_db(TDb),
    teach_proc(TDb, TSpeedA0, TSpeedAi),
    format("Number of iterations: ~d of ~d.~n", [CurIter, MaxIter]).

% increments iteration number
teach(TSpeedA0, TSpeedAi, InitIter, CurIter, MaxIter) :-
    teach(TSpeedA0, TSpeedAi, InitIter, CurIter+1, MaxIter).

%
% Teach process definition
%

% stop
teach_proc([], _, _) :-
    format("teach_proc: success.~n~n", []).

% worker
teach_proc([[Values, TeachResult]|RestDb], TSpeedA0, TSpeedAi) :-
    format("teach_proc: Values = ", []),
    format_float(Values),
    format("TeachResult = ~w; TSpeedA0 = ~2f; TSpeedAi = ~2f.~n",
           [TeachResult, TSpeedA0, TSpeedAi]),
    % get coefficients from db
    a(InitA0, InitAi),
    test(InitA0, InitAi, Values, TestResult),
    % modify A0 in-place
    mod_cfs(TestResult, TeachResult, Values, InitA0+TSpeedA0, InitAi),
    teach_proc(RestDb, TSpeedA0, TSpeedAi).

% gets perceptron's "opinion"
test(A0, Ai, Values, Result) :-
	poly_sum(Ai, Values, A0, Estimate),
	positive(Estimate, Result),
    format("test: A0 = ~2f; Ai = ", [A0]),
    format_float(Ai),
    format("Values = ", []),
    format_float(Values),
    format("Estimate = ~3f -> ~w.~n", [Estimate, Result]).

% positive case: nothing to do
mod_cfs(Result, Result, Values, InitA0, InitAi) :-
    format("mod_cfs: correct result. nothing to do.~n", []).

% negative case: TestResult = y, TeachResult = n
mod_cfs(y, n, Values, InitA0, InitAi) :-
    teach_speed(TeachSpeedA0, TeachSpeedAi),
    ModA0 is InitA0 + TeachSpeedA0,
    vec_sum(-TeachSpeedAi, Values, InitAi, ModAi),
    % replace coefficients with modified ones
    retract(a(_, _)),
    asserta(a(ModA0, ModAi)),
    format("mod_cfs: ModA0 = ~2f, ModAi = ", [ModA0]),
    format_float(ModAi),
    format("y =/= n -> fail.~n~n", []),
    fail.

% negative case: TestResult = n, TeachResult = y
mod_cfs(n, y, Values, InitA0, InitAi, InitA0, ModAi) :-
    teach_speed(TeachSpeedA0, TeachSpeedAi),
    ModA0 is InitA0 + TeachSpeedA0,
    vec_sum(TeachSpeedAi, Values, InitAi, ModAi),
    % replace coefficients with modified ones
    retract(a(_, _)),
    asserta(a(ModA0, ModAi)),
    format("mod_cfs: ModA0 = ~2f, ModAi = ", [ModA0]),
    format_float(ModAi),
    format("n =/= y -> fail.~n~n", []),
    fail.

% ResEstimate = sum(A_i * Value_i)
poly_sum([], [], ResEstimate, ResEstimate).
poly_sum([Ai|RestAi], [Value|RestValues], AccEstimate, ResEstimate) :-
    poly_sum(RestAi, RestValues, AccEstimate + Ai * Value, ResEstimate).

positive(Value, y) :- Value > 0.
positive(Value, n) :- Value =< 0.

% ResAi = [Ai + Factor*Value|...]
vec_sum(Factor, Values, InitAi, ResAi) :-
    vec_sum(Factor, Values, InitAi, [], ModAi),
    reverse(ModAi, ResAi).
vec_sum(Factor, [Value|RestValues], [Ai|RestAi], AccAi, ModAi) :-
    vec_sum(Factor, RestValues, RestAi, [Ai + Factor*Value|AccAi], ModAi).
vec_sum(_, [], [], ModAi, ModAi).

%
% Utilities
%

% print list of float values
format_float([]) :-
    format(" ", []).
format_float([Float|RestFloats]) :-
    format("~2f,", [Float]),
    format_float(RestFloats).

cleanup_db :-
    retractall(a(_, _)),
    retractall(iter(_, _)).

setup_db :-
    asserta(a(-3, [2, 2, 2])),
    asserta(iter(1, 100)),
    asserta(teach_speed(0, 0.01)).

run :-
    cleanup_db,
    setup_db,
	teach(0, 0.2, 100),
    a(A0, Ai),
    format("Result: A0 = ~2f; Ai = ", [A0]),
    format_float(Ai).
