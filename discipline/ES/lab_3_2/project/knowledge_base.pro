contains(_, []):- fail.

contains(what(X),  [what(X)|_]):- !.
contains(who(X),   [who(X)|_]):- !.
contains(doing(X), [doing(X)|_]):- !.

contains(X, [_|Tail]):-
    contains(X, Tail).

sentence(1, [who(europe),   doing("is"),    what(continent)]).
sentence(2, [who(belarus),  doing("is in"), what(europe)]).
sentence(3, [who(mogilev),  doing("is in"), what(belarus)]).
sentence(4, [who(minsk),    doing("is in"), what(belarus)]).
sentence(5, [who(minsk),    doing("is"),    what(capital)]).

ask :-
    sentence(_, Sentence),
    contains(who(Objects), Sentence),
    contains(doing("is"), Sentence),
    contains(what(capital), Sentence),
    format("Object is ~w~N", [Objects]).
