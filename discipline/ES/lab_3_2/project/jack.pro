#!/usr/bin/gprolog --consult-file

m(_, []) :- !, fail.
m(X, [X|_]).
m(X, [_|T]) :-
    m(X, T).

%% 1
s([who(jack), did(build), what(house)]).

%% 2
s([what(house), do(contain), what(lumber-room)]).
s([what(lumber-room), do(keep), what(wheat)]).
s([has_prop(lumber-room, dark)]).

%% 3
s([who(titmouse), do(steal), what(wheat), how(often)]).
s([who(titmouse), is_a(bird)]).

%% 4
s([who(cat), do(catch), who(titmouse)]).
s([who(cat), do(fright), who(titmouse)]).

%% 5
s([who(dog), do(shake), who(cat), how(by-the-collar)]).
s([has_prop(dog, old), has_prop(dog, without-tail)]).

%% 6
s([who(cow), did(kick), who(dog)]).
s([has_prop(cow, hornless)]).

%% 7
s([who(lady), do(milk), who(cow)]).
s([has_prop(lady, old), has_prop(lady, hoary), has_prop(lady, strict)]).

%% 8
s([who(cowboy), do(scold), who(lady)]).
s([who(lady), do(scold), who(cowboy)]).
s([has_prop(cowboy, lazy)]).
s([has_prop(cowboy, fat)]).

%% 9
s([who(two-roosters), do(wake), who(cowboy)]).

%% Questions:
%%
%% 1. Где хранится пшеница в доме, который построил Джек?
q_1(X) :-
    s(S1), s(S2),
    m(what(house), S1),
    m(do(contain), S1),
    m(what(X), S1),
    m(what(X), S2),
    m(do(keep), S2),
    m(what(wheat), S2).
%% 2. Кто бранится с тем, кто доит корову?
q_2(X, Y) :-
    s(S1), s(S2),
    m(who(X), S1),
    m(do(scold), S1),
    m(who(Y), S1),
    m(who(Y), S2),
    m(do(milk), S2),
    m(who(cow), S2).
%% 3. Как пес треплет того, кто ловит синицу?
q_3(X, Y) :-
    s(S1), s(S2),
    m(who(dog), S1),
    m(do(shake), S1),
    m(who(Y), S1),
    m(how(X), S1),
    m(who(Y), S2),
    m(do(catch), S2),
    m(who(titmouse), S2).
%% Кто пугает того, кто ворует пшеницу?
q_4(X, Y) :-
    s(S1), s(S2),
    m(who(X), S1),
    m(do(fright), S1),
    m(who(Y), S1),
    m(who(Y), S2),
    m(do(steal), S2),
    m(what(wheat), S2).
%% Что хранится в доме [который построил Джек]?
q_5(X) :-
    s(S1), s(S2),
    m(what(house), S1),
    m(do(contain), S1),
    m(what(Y), S1),
    m(what(Y), S2),
    m(what(X), S2).
%% Кто треплет того, кто ловит синицу?
q_6(X, Y) :-
    s(S1), s(S2),
    m(who(X), S1),
    m(do(shake), S1),
    m(who(Y), S1),
    m(who(Y), S2),
    m(do(catch), S2),
    m(who(titmouse), S2).
%% Кто ворует то, что в темном чулане хранится?
q_7(X, Y) :-
    s(S1), s(S2),
    m(who(X), S1),
    m(do(steal), S1),
    m(what(Y), S1),
    m(what(lumber-room), S2),
    m(do(keep), S2),
    m(what(Y), S2).
