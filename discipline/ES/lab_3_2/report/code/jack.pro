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
 s([has_prop(dog, old),
    has_prop(dog, without-tail)]).
 %% 6
 s([who(cow), did(kick), who(dog)]).
 s([has_prop(cow, hornless)]).
 %% 7
 s([who(lady), do(milk), who(cow)]).
 s([has_prop(lady, old),
    has_prop(lady, hoary),
    has_prop(lady, strict)]).
 %% 8
 s([who(cowboy), do(scold), who(lady)]).
 s([who(lady), do(scold), who(cowboy)]).
 s([has_prop(cowboy, lazy),
    has_prop(cowboy, fat)]).
 %% 9
 s([who(two-roosters), do(wake), who(cowboy)]).
