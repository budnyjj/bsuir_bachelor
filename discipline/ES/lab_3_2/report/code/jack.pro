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
