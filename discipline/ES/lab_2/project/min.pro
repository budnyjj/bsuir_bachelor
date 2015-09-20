#!/usr/bin/gprolog --consult-file

min(0,B,C,Acc,Ret) :-
  Ret is Acc.

min(A,0,C,Acc,Ret) :-
  Ret is Acc.

min(A,B,0,Acc,Ret) :-
  Ret is Acc.
  
min(A,B,C,Acc,Ret) :-
  A1 is A-1,
  B1 is B-1,
  C1 is C-1,
  Acc1 is Acc+1,
  min(A1,B1,C1,Acc1,Ret).

min(A,B,C) :-
  min(A,B,C,0,Ret),
  format("Min is: ~w~N", [Ret]).

min(1,1,1).
