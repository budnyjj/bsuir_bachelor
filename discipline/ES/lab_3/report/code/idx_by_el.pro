 domains
     li=integer*

 predicates
     nondeterm work
     nondeterm member(integer, li, integer)
     nondeterm isEmpty(li)

 clauses
     work :-
         write("Input list:"), nl, readterm(li, L),
         isEmpty(L),
         readchar(_).

     member(X, [X|_], I) :-
         write("Index of list = ", I).

     member(X, [_|Y], I) :-
         I1 = I + 1, member(X, Y, I1).

     member(_,[],_) :-
         write("Element doesn't exist in list").

     isEmpty([]) :-
            write("List is empty"), nl,
            write("Input list:"), nl,
            readterm(li, L),
            isEmpty(L).

     isEmpty([R|M]) :-
            write("Input element:"), readint(E),
            member(E, [R|M], 1).

 goal
     work.
