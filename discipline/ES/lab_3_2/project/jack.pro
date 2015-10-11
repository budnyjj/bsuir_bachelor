#!/usr/bin/gprolog --consult-file

m(_, []) :- fail.
m(X, [X|_]) :- !.
m(X, [_|T]) :-
    m(X, T).

%% 1
s([who(jack), did(build), what(house)]).

%% 2
s([what(lumber-room), do(keep), what(wheat)]).
s([what(lumber-room), has_prop(dark)]).

%% 3
s([who(titmouse), do(steal), what(wheat), how(often)]).
s([who(titmouse), is_a(bird)]).

%% 4
s([who(cat), do(catch), who(titmouse)]).
s([who(cat), do(fright), who(titmouse)]).

%% 5
s([who(dog), do(shake), who(cat), how(by-the-collar)]).
s([who(dog), has_prop(old)]).
s([who(dog), has_prop(without-tail)]).

%% 6
s([who(cow), did(kick), who(dog)]).
s([who(cow), has_prop(old)]).

%% 7
s([who(lady), do(milk), who(cow)]).
%% need a better translation
s([who(lady), is_a(korovnitsa)]). 
s([who(lady), has_prop(old)]).
s([who(lady), has_prop(hoary)]).
s([who(lady), has_prop(strict)]).

%% 8
s([who(cowboy), do(scold), who(korovnitsa)]).
s([who(korovnitsa), do(scold), who(cowboy)]).
s([who(cowboy), has_prop(lazy)]).
s([who(cowboy), has_prop(fat)]).

%% 9
s([who(two-roosters), do(wake), who(cowboy)]).

%% Questions:
%%
%% 1.
%%
%% s(S1), m(what(W1), S1), m(who(W2), S1).
%%
%% S1 = [who(jack),did(build),what(house)]
%% W1 = house
%% W2 = jack
%%
%%
%% 2.
%%
%% s(S1), s(S2), m(who(W), S1), m(how(H), S1), m(who(W), S2), m(has_prop(P), S2).
%%
%% H = by-the-collar
%% P = old
%% S1 = [who(dog),do(shake),who(cat),how(by-the-collar)]
%% S2 = [who(dog),has_prop(old)]
%% W = dog
%%
%% H = by-the-collar
%% P = without-tail
%% S1 = [who(dog),do(shake),who(cat),how(by-the-collar)]
%% S2 = [who(dog),has_prop(without-tail)]
%% W = dog
%%
%%
%% 3.
%%
%% s(S1), s(S2), m(who(korovnitsa), S1), m(do(D), S1), m(who(W), S1), m(who(W), S2), m(has_prop(fat), S2).
%% 
%% D = scold
%% S1 = [who(cowboy),do(scold),who(korovnitsa)]
%% S2 = [who(cowboy),has_prop(fat)]
%% W = cowboy
