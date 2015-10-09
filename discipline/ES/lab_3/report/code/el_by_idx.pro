 domains
      li=integer*

 predicates
     nondeterm work
     nondeterm member(li, integer, integer)
     nondeterm isEmpty(li)

 clauses
     work :-
         write("Input list:"), nl, readterm(li, L),
         isEmpty(L), readchar(_).
     
     member([_|_], 0, R) :-
         write("Element with index 0 doesn't exist"), R = 0.
     
     member([], _, R) :-
         write("Element doesn't exist"), R = 0.
     
     member([X | Y],1,R) :-
         R = X, write("Memder=", R).
     
     member([X | Y],Z,R):-
         Z1 = Z-1, member(Y,Z1,R).
     
     isEmpty([]):-
             write("List is empty"), nl,
             write("Input list:"), nl,
             readterm(li, L), isEmpty(L).
     
     isEmpty([X|Y]):-
             write("Input index of element:"), readint(N),
             member([X|Y], N, M).

 goal
     work.
