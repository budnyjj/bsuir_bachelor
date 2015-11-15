#!/usr/bin/gprolog --consult-file

dynamic([preference/2, value/2, weight/2]).

% Conversion mapping
preference_to_value(auto, 1, 0.1).
preference_to_value(auto, 2, 0.5).
preference_to_value(auto, 3, 0.9).

preference_to_value(road, 1, 0.3).
preference_to_value(road, 2, 0.5).
preference_to_value(road, 3, 0.7).

preference_to_value(driver, 1, 0.3).
preference_to_value(driver, 2, 0.5).
preference_to_value(driver, 3, 1.0).

% infinite loop
loop.
loop :- loop.

% remove all facts from db
cleanup :-
    retractall(preference(_, _)),
    retractall(value(_, _)),
    retractall(weight(_, _)).

% Executes handlers form handler list
exec([Handler|HandlersTail]) :-
    Handler,
    !,
    exec(HandlersTail).
exec([]).

get_preference(Key, Prompt) :-
    loop,
    format("~s~N", [Prompt]),
    format("1. BAD~N2. NORMAL~N3. GOOD~N~n", []),
    format("Your preference: ", []),
    read_integer(Pref),
    check_preference(Pref),
    asserta(preference(Key, Pref)).

check_preference(Pref) :-
    Pref >= 1, Pref =< 3.
check_preference(_) :-
    format("=== ERROR ===============================~N", []),
    format(" Incorrect preference value! Try again...~N", []),
    format("=========================================~N", []),
    fail.

preference_to_value(Key) :-
    preference(Key, Pref),
    preference_to_value(Key, Pref, Val),
    asserta(value(Key, Val)).

get_weight(Key, Prompt) :-
    loop,
    format("~s~N", [Prompt]),
    format("Your value: ", []),
    read_number(Weight),
    check_weight(Weight),
    asserta(weight(Key, Weight)).

check_weight(Weight) :-
    Weight >= 0, Weight =< 1.
check_weight(_) :-
    format("=== ERROR ===============================~N", []),
    format(" Incorrect weight value! Try again...~N",     []),
    format("=========================================~N", []),
    fail.

% Checks, if sum of weights is equal to 1
is_full_group_weight(Keys) :-
    is_full_group_weight(Keys, 0).
is_full_group_weight([Key|KeysTail], Weights) :-
    weight(Key, Weight),
    is_full_group_weight(KeysTail, Weights + Weight).
is_full_group_weight([], Weights) :-
    Weights =:= 1.
is_full_group_weight([], Weights) :-
    Weights =\= 1,
    format("=== ERROR ===============================~N", []),
    format(" Weight sum is: ~2f != 1. Exit.~N",           [Weights]),
    format("=========================================~N", []),
    fail.

calc_speed(Keys, MaxSpeed, Speed) :-
    calc_speed(Keys, MaxSpeed, 0, Speed).
calc_speed([Key|KeysTail], MaxSpeed, AccSpeed, Speed) :-
    value(Key, Value),
    weight(Key, Weight),
    calc_speed(KeysTail, MaxSpeed, AccSpeed + MaxSpeed * Value * Weight, Speed).
calc_speed([], _, AccSpeed, AccSpeed).

print_speed(Speed) :-
    format("=== RESULT ================~N", []),
    format(" Suggested speed is: ~2f~N",    [Speed]),
    format("===========================~N", []).

run :-
    cleanup,

    exec([get_preference(auto,   "Please, give us information about AUTO."),
          get_preference(road,   "Please, give us information about ROAD."),
          get_preference(driver, "Please, give us information about DRIVER.")]),

    exec([preference_to_value(auto),
          preference_to_value(road),
          preference_to_value(driver)]),

    exec([get_weight(auto,   "Please, input weight coefficient for AUTO parameter:"),
          get_weight(road,   "Please, input weight coefficient for ROAD parameter:"),
          get_weight(driver, "Please, input weight coefficient for DRIVER parameter:")]),

    is_full_group_weight([auto, road, driver]),

    calc_speed([auto, road, driver], 90, Speed),
    print_speed(Speed).
