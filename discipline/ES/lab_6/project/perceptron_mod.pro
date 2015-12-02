teach_dict(1, [0.7, 0.6, 0.6], y).
teach_dict(2, [0.7, 0.4, 0.8], n).
teach_dict(3, [0.3, 0.5, 1.0], n).
teach_dict(4, [0.9, 0.8, 0.6], y).
teach_dict(5, [0.4, 0.7, 0.8], y).
teach_dict(6, [0.7, 0.9, 0.6], y).
teach_dict(7, [0.2, 0.6, 0.7], n).
teach_dict(8, [0.6, 0.7, 0.8], y).
teach_dict(9, [0.4, 0.4, 0.6], n).
teach_dict(10, [0.7, 1.0, 0.6], y).

%loop.
%loop :- loop.

next(0, 1).
next(Iter, Iter+1).

teach(InitWeights, W0, Cf, ModWeights) :-
	teach_iter(0, InitWeights, W0, Cf, ModIter, ModWeights).

teach_iter(InitIter, InitWeights, W0, Cf, ModIter, ModWeights)
	teach_dict(Idx, TeachValues, TeachResult),
	ask(InitWeights, Values, W0, Result),
	update_weights(Result, Values, InitWeights, ModWeights),
	next(InitIter, NextIter),
	teach_iter(NextIter, ModWeights, W0, Cf, ModIter, ModWeights).

ask(Weights, Values, W0, Result) :-
	ask(Weight, Values, 0, Estimate),
	positive(Estimate - W0, Result).

ask([], [], _, _).
ask([Weight|RestWeights], [Value|RestValues], 
	InitEstimate, InitEstimate + Weight * Value).
	
positive(Estimate, y) :-
	Estimate > 0.
positive(Estimate, n).

update_weights(_, [], [], Cf, []).
update_weights(y, [Value|RValues], [InitWeight|RInitWeights], Cf, [ModWeight|RModWeights]).
	update_weights(y, RValues, RInitWeights, Cf, RModWeights),
	ModWeight is InitWeight + Cf * Value.
update_weights(n, [Value|RValues], [InitWeight|RInitWeights], Cf, [ModWeight|RModWeights]).
	update_weights(n, RValues, RInitWeights, Cf, RModWeights),
	ModWeight is InitWeight - Cf * Value.

run :-
	init_weights(InitWeights),
	teach([2, 2, 2], -3, 0.5,  Weights).