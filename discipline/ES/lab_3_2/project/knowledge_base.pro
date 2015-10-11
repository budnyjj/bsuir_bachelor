contains(_, []):- fail.

contains(noun(X),  [noun(X)|_]):- !.
contains(verb(X), [verb(X)|_]):- !.

contains(X, [_|Tail]):-
    contains(X, Tail).

sentence(1, [noun(europe),   verb("is"),    noun(continent)]).
sentence(2, [noun(belarus),  verb("is in"), noun(europe)]).
sentence(3, [noun(mogilev),  verb("is in"), noun(belarus)]).
sentence(4, [noun(minsk),    verb("is in"), noun(belarus)]).
sentence(5, [noun(minsk),    verb("is"),    noun(capital)]).

ask :-
    sentence(_, Sentence),
    contains(noun(Objects), Sentence),
    contains(verb("is"), Sentence),
    contains(noun(capital), Sentence),
    format("Object is ~w~N", [Objects]).
