function X1 = regr_2(X2, A, R)

X1 = zeros(size(X2));

for i = 1:numel(X1)
    X1(i) = A(1) + R(1, 2) / R(1, 1).*(X2(i) - A(2));
end