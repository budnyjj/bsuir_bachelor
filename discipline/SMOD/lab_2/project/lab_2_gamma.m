[X1, X2] = meshgrid(0:.2:5, 0:.2:5);

A = [1, 1];
B = [2, 1];
 
Z = gamma_rasp(X1, X2, A, B);

hold on

contour(X1, X2, Z)
% mesh(X1, X2, Z)
hold off
