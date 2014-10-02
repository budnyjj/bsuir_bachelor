function y = our_normal(a, sigma)

alpha_1 = unifrnd(0, 1);
alpha_2 = unifrnd(0, 1);
c = 2 * pi;
r = sqrt(-2 * log(alpha_1));
phi = c / alpha_2;
y = a + sigma * r * cos(phi);
