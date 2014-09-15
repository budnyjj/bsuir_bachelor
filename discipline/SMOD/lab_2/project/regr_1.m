function X2 = regr_1(X1, A, R)

X2 = zeros(size(X1));

for i = 1:numel(X2)
    X2(i) = A(2) + R(1, 2) / R(1, 1).*(X1(i) - A(1));
end
