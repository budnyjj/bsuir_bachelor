function y = our_normal(x, a, sigma)

y = zeros(size(x));

for i = 1:numel(x)
    alpha_1 = unifrnd(0, 1)
    alpha_2 = unifrnd(0, 1)
    c = 2 * pi
    r = sqrt(-2 * log(alpha_1))
    phi = c / alpha_2
    y(i) = a + sigma * r * cos(phi)
end