#!/usr/bin/gprolog --consult-file

% 'abc def' -> [abc, def]
extract_words(Atoms, ResWords) :-
    extract_words(Atoms, [], RevWords),
    reverse(RevWords, ResWords).

% worker
extract_words(Atoms, AccWords, ResWords) :-
    sub_atom(Atoms, Before, Length, After, ' '),
    TailLength is Length + After,
    HeadLength is Before + Length,
    sub_atom(Atoms, 0, Before, TailLength, Word),
    sub_atom(Atoms, HeadLength, After, 0, RestAtoms),
    extract_words(RestAtoms, [Word|AccWords], ResWords).

% stop
extract_words(Atom, AccWords, [Atom|AccWords]).



run :-
    read_atom(Sentence),
    extract_words(Sentence, Words),
    format("~w", [Words]).
