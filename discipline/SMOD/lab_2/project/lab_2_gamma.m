[X1, X2] = meshgrid(-1:.2:5, -1:.2:5);

A = [1, 10];
B = [1, 1];

Z = gamma_rasp(X1, X2, A, B);

hold on
grid on

contour(X1, X2, Z)
% mesh(X1, X2, Z)
hold off
