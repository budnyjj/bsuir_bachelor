 %
 % Extract words from input
 % 'abc def' -> [abc, def]
 %
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

 %
 % Sentence definition
 %
 sentence(S, NounBlock1, VerbBlock, NounBlock2) :-
     subj_block(S, NounBlock1, RestS1),
     act_block(RestS1, VerbBlock, RestS2),
     obj_block(RestS2, NounBlock2, []).

 %
 % subject block
 % 
 % without article
 subj_block(S, SubjBlock, ResRestS) :-
     subj_block(S, [], RevSubjBlock, ResRestS),
     reverse(RevSubjBlock, SubjBlock).

 % with article
 subj_block([Word|RestS], SubjBlock, ResRestS) :-
     art(Word),
     subj_block(RestS, [Word], RevSubjBlock, ResRestS),
     reverse(RevSubjBlock, SubjBlock).

 % catch all
 subj_block(S, _, _) :-
     format("subj_block: cannot parse sentence ~w.~n", [S]),
     !, fail.

 % adjs...
 subj_block([Word|RestS], AccSubjBlock, ResSubjBlock, ResRestS) :-
     adj(Word),
     subj_block(RestS, [Word|AccSubjBlock], ResSubjBlock, ResRestS).

 % noun
 subj_block([Word|RestS], AccSubjBlock, ResSubjBlock, ResRestS) :-
     noun(Word),
     stop_block(RestS, [Word|AccSubjBlock], ResSubjBlock, ResRestS).

 %
 % action block
 %
 act_block(S, ActBlock, RestS) :-
     act_block(S, [], RevActBlock, RestS),
     reverse(RevActBlock, ActBlock).

 % catch all
 act_block(S, _, _) :-
     format("act_block: cannot parse sentence ~w.~n", [S]),
     !, fail.

 % adverbs...
 act_block([Word|RestS], AccActBlock, ResActBlock, ResRestS) :-
     adv(Word),
     act_block(RestS, [Word|AccActBlock], ResActBlock, ResRestS).

 % verb
 act_block([Word|RestS], AccActBlock, ResActBlock, ResRestS) :-
     verb(Word),
     stop_block(RestS, [Word|AccActBlock], ResActBlock, ResRestS).

 %
 % object block
 %
 % without article
 obj_block(S, ObjBlock, ResRestS) :-
     obj_block(S, [], RevObjBlock, ResRestS),
     reverse(RevObjBlock, ObjBlock).

 % with article
 obj_block([Word|RestS], ObjBlock, ResRestS) :-
     art(Word),
     obj_block(RestS, [Word], RevObjBlock, ResRestS),
     reverse(RevObjBlock, ObjBlock).

 % with proposal
 obj_block([Word|RestS], ObjBlock, ResRestS) :-
     prp(Word),
     obj_block(RestS, [Word], RevObjBlock, ResRestS),
     reverse(RevObjBlock, ObjBlock).

 % with article and proposal
 obj_block([Word1,Word2|RestS], ObjBlock, ResRestS) :-
     prp(Word1), art(Word2),
     obj_block(RestS, [Word2,Word1], RevObjBlock, ResRestS),
     reverse(RevObjBlock, ObjBlock).

 % catch all
 obj_block(S, _, _) :-
     format("obj_block: cannot parse sentence ~w.~n", [S]),
     !, fail.

 % adjs...
 obj_block([Word|RestS], AccObjBlock, ResObjBlock, ResRestS) :-
     adj(Word),
     obj_block(RestS, [Word|AccObjBlock], ResObjBlock, ResRestS).

 % noun
 obj_block([Word|RestS], AccObjBlock, ResObjBlock, ResRestS) :-
     noun(Word),
     stop_block(RestS, [Word|AccObjBlock], ResObjBlock, ResRestS).

 %
 % stop block
 %
 stop_block(AccRestS, AccBlock, AccBlock, AccRestS).

 % nouns
 noun(cat). noun(mouse). noun(sofa). noun(yard).

 % adjectives
 adj(black). adj(clever). adj(lazy). adj(red). adj(scraggy). adj(violet).

 % verbs
 verb(lays). verb(mews). verb(runs). verb(wanton).

 % adverbs
 adv(silly). adv(stilly).

 % proposals
 prp(at). prp(in). prp(on).

 % articles
 art(a). art(the).

 %
 % Check for forbidden collocations
 %
 fbid_collocations([[violet, cat],
                    [red,    cat],
                    [violet, mouse],
                    [red,    mouse]]).

 check_collocations(Block) :-
     fbid_collocations(FbidCollocations),
     check_collocations(Block, FbidCollocations).

 % found invalid collocation
 check_collocations(Block, [FbidCollocation|_]) :-
     sublist(FbidCollocation, Block),
     format("Incorrect collocation: ~w in ~w.~n", [FbidCollocation, Block]).

 % continue search
 check_collocations(Block, [FbidCollocation|RestFbidCollocations]) :-
     check_collocations(Block, RestFbidCollocations).

 % stop
 check_collocations(Block, []).

 %
 % Main clause
 %
 run :-
     read_atom(Input),
     extract_words(Input, Sentence),
     format("~nSentence: ~w~n", [Sentence]),
     sentence(Sentence, SubjBlock, ActBlock, ObjBlock),
     format("Subject block: ~w~n", [SubjBlock]),
     format("Action block:  ~w~n", [ActBlock]),
     format("Object block:  ~w~n", [ObjBlock]),
     check_collocations(SubjBlock),
     check_collocations(ObjBlock).