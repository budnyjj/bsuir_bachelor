  domains
     li=integer*

predicates
  nondeterm work
  nondeterm member(integer,li,integer)

clauses
  work:-
      write("Input list:"), nl,
      readterm(li,L),
      write("Input element:"),
      readint(E),
      member(E,L,1),
      readchar(_).
      
   member(_,[],_):-
   write("Element doesn't exit in list "),
   readchar(_).
   
   member(X,[X |_],I):-
   write("Index of list = ",I).
   
   member(X,[_ | Y],I):-
     I1 = I + 1, 
     member(X,Y,I1).

goal
	work.
