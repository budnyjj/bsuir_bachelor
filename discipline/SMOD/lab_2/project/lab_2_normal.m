[X1, X2] = meshgrid(-5:.2:5, -5:.2:5);

A1 = [-2, 0];
A2 = [2, 0];

R1 = [2, 0.5;
     0.5, 1];

R2 = [1, 0.5;
      0.5, 3];
 
Z1 = normal(X1, X2, A1, R1);
Z2 = normal(X1, X2, A2, R2);

% mesh(X1, X2, Z)

hold on
% contour(X1, X2, Z1, 4)
% plot(X1(1,:), regr_1(X1(1,:), A1, R1), 'k.-')
% plot(regr_2(X2(:,1), A1, R1), X2(:,1), 'k.-')

%contour(X1, X2, Z2, 4)
%plot(X1(1,:), regr_1(X1(1,:), A2, R2), 'k.-')
%plot(regr_2(X2(:,1), A2, R2), X2(:,1), 'k.-')

contour(X1, X2, Z1)
contour(X1, X2, Z2)
% mesh(X1, X2, Z1)
% mesh(X1, X2, Z2)
hold off
