  %%%%% main file %%%%%
  [X1, X2] = meshgrid(-1:.2:5, -1:.2:5);

  A = [1, 10];
  B = [1, 1];

  Z = gamma_rasp(X1, X2, A, B);

  hold on
  grid on

  contour(X1, X2, Z)
  % mesh(X1, X2, Z)
  hold off

  %%%%% function %%%%%

  function f = gamma_rasp(X1, X2, A, B)

  f = zeros(size(X1));

  for i = 1:size(X1,1)
     for j = 1:size(X1,2)
         if ((X1(i,j) > 0) && (X2(i,j) > 0))
             c_1 = gamma(A(1)) * (B(1) ^ A(1));
             c_2 = gamma(A(2)) * (B(2) ^ A(2));
             part_1 = (X1(i,j)^(A(1)-1))*exp(-X1(i,j)/B(1)) / c_1;
             part_2 = (X2(i,j)^(A(2)-1))*exp(-X2(i,j)/B(2)) / c_2;
             f(i,j) = part_1 * part_2;
         end
     end
  end
