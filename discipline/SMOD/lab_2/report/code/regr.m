  %%%%% main file %%%%%

  [X1, X2] = meshgrid(-5:.2:5, -5:.2:5);

  A1 = [0, 0];
  A2 = [2, 0];

  R1 = [5, 0.3;
       0.3, 1];

  R2 = [1, 0.5;
        0.5, 3];

  Z1 = normal(X1, X2, A1, R1);
  Z2 = normal(X1, X2, A2, R2);

  hold on
  grid on
  contour(X1, X2, Z1, 4)
  plot(X1(1,:), regr_1(X1(1,:), A1, R1), 'k.-')
  plot(regr_2(X2(:,1), A1, R1), X2(:,1), 'k.-')

  %contour(X1, X2, Z2, 4)
  %plot(X1(1,:), regr_1(X1(1,:), A2, R2), 'k.-')
  %plot(regr_2(X2(:,1), A2, R2), X2(:,1), 'k.-')

  hold off

  %%%%% function #1 %%%%%

  function X2 = regr_1(X1, A, R)

  X2 = zeros(size(X1));

  for i = 1:numel(X2)
      X2(i) = A(2) + R(1, 2) / R(2, 2).*(X1(i) - A(1));
  end

  %%%%% function #2 %%%%%

  function X1 = regr_2(X2, A, R)

  X1 = zeros(size(X2));

  for i = 1:numel(X1)
      X1(i) = A(1) + R(1, 2) / R(1, 1).*(X2(i) - A(2));
  end
