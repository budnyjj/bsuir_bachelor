#!/usr/bin/gprolog --consult-file

menu :-
    loop,
    format("Please, select value from list:~N", []),
    format("1. First option~N", []),
    format("2. Exit~N", []),
    read_number(Option),
    check(Option).

loop.
loop :-
    loop.

check(1) :-
    format("You've selected the first option.~N", []).

check(2) :-
    format("Exit.~N", []).

check(Option) :-
    format("Please, input 1 or 2 to select desired menu option.~N", []),
    fail.

