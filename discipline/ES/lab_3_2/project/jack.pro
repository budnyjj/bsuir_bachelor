#!/usr/bin/gprolog --consult-file

m(_, []) :- fail.
m(X, [X|_]) :- !.
m(X, [_|T]) :-
    m(X, T).

%% 1
s([who(jack), did(build), what(house)]).

%% 2
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
%% need a better translation
s([is_a(lady, korovnitsa)]). 
s([has_prop(lady, old), has_prop(lady, hoary), has_prop(lady, strict)]).

%% 8
s([who(cowboy), do(scold), who(korovnitsa)]).
s([who(korovnitsa), do(scold), who(cowboy)]).
s([has_prop(cowboy, lazy)]).
s([has_prop(cowboy, fat)]).

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
%% s(S1), s(S2), s(S3), m(who(W), S1), m(how(H), S1), m(who(W), S2), m(has_prop(W, P), S3).
%%
%% H = by-the-collar
%% P = old
%% S1 = [who(dog),do(shake),who(cat),how(by-the-collar)]
%% S2 = [who(dog),do(shake),who(cat),how(by-the-collar)]
%% S3 = [has_prop(dog,old),has_prop(dog,without-tail)]
%% W = dog ? ;
%% 
%% H = by-the-collar
%% P = old
%% S1 = [who(dog),do(shake),who(cat),how(by-the-collar)]
%% S2 = [who(cow),did(kick),who(dog)]
%% S3 = [has_prop(dog,old),has_prop(dog,without-tail)]
%% W = dog ? ;
%%
%%
%% 3.
%% s(S1), s(S2), s(S3), m(who(korovnitsa), S1), m(do(D), S1), m(who(W), S1), m(who(W), S2), m(has_prop(W, fat), S3)
%%
%% D = scold
%% S1 = [who(cowboy),do(scold),who(korovnitsa)]
%% S2 = [who(cowboy),do(scold),who(korovnitsa)]
%% S3 = [has_prop(cowboy,fat)]
%% W = cowboy ? ;
%% 
%% D = scold
%% S1 = [who(cowboy),do(scold),who(korovnitsa)]
%% S2 = [who(korovnitsa),do(scold),who(cowboy)]
%% S3 = [has_prop(cowboy,fat)]
%% W = cowboy ? ;
%% 
%% D = scold
%% S1 = [who(cowboy),do(scold),who(korovnitsa)]
%% S2 = [who(two-roosters),do(wake),who(cowboy)]
%% S3 = [has_prop(cowboy,fat)]
%% W = cowboy ? ;
