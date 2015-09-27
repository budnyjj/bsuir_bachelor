domains
     li=integer*

predicates
	nondeterm work
	nondeterm member(li,integer,integer)
  
clauses
work:-
      write("Input list:"), nl,
      readterm(li,L),
      write("Input index of element:"),
      readint(N),
      member(L,N,M),
      nl,
      write("Memder=",M),
      readchar(_).
  
member([X | Y],1,R):- 
  	R=X.
  
member([X | Y],Z,R):-
	Z1=Z-1,
	member(Y,Z1,R).
     
goal
	work.

