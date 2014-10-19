% input data
x = [0, 110, 195, 410, 540];
y = [33, 24, 20, 13, 12];

appr_x = [min(x):10:max(x)]

% init parameter values
init_params = [0, 0]

% basic_estimates(1) -- a_0
% basic_estimates(2) -- alpha_0
basic_estimates = search_basic_estimates(x(1:2), y(1:2), init_params);
a_0 = basic_estimates(1);
alpha_0 = basic_estimates(2);

q_1 = arrayfun(@(vals) diff_f_by_a(vals, a_0, alpha_0), x);
q_2 = arrayfun(@(vals) diff_f_by_alpha(vals, a_0, alpha_0), x);

% target function
appr_f = arrayfun(@(vals) f(vals, a_0, alpha_0), x);

% transposed version of Q
Q = [q_1; q_2].';

eff_estimates = search_eff_estimates(basic_estimates, Q, y, appr_f, 1);
a = eff_estimates(1)
alpha = eff_estimates(2)

% appr function
% hold on
% plot(x, y, '.k')
% plot(appr_x, arrayfun(@(vals) f(vals, a_0, alpha_0), appr_x), 'b-')
% plot(appr_x, arrayfun(@(vals) f(vals, a, alpha), appr_x), 'r-')
% hold off

% eff_estimates by iteration
num_iter = 100
eff_estimates_per_iter = [];
for i = 1:num_iter
    eff_estimates_per_iter = [eff_estimates_per_iter search_eff_estimates(basic_estimates, Q, y, appr_f, i)];
end

% eff_a
plot(1:num_iter, eff_estimates_per_iter(1,:), 'b-')
% eff_alpha
plot(1:num_iter, eff_estimates_per_iter(2,:), 'r-')