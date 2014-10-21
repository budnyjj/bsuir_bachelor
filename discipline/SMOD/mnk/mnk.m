% input data
x = [0, 110, 195, 410, 540];
y = [33, 24, 20, 13, 12];

mean_x = [mean(x(1)), mean(x(2))];
mean_y = [mean(y(1)), mean(y(2))];

appr_x = [min(x):10:max(x)];

% init parameter values
init_params = [0, 0];

% basic_estimates(1) -- a_0
% basic_estimates(2) -- alpha_0
basic_estimates = search_basic_estimates(mean_x, mean_y, init_params);
a_0 = basic_estimates(1)
alpha_0 = basic_estimates(2)

% eff_estimates by iteration
num_iter = 10
eff_estimates_per_iter = [];

hold on
%plot(x, y, '.k')
%plot(appr_x, arrayfun(@(vals) f(vals, a_0, alpha_0), appr_x), 'b-')

for i = 1:num_iter
    cur_eff_estimates = search_eff_estimates(basic_estimates, x, y, @f, i);
    a = cur_eff_estimates(1);
    alpha = cur_eff_estimates(2);
    
    %plot(appr_x, arrayfun(@(vals) f(vals, a, alpha), appr_x), 'r-')
    eff_estimates_per_iter = [eff_estimates_per_iter cur_eff_estimates];
end

hold off

eff_estimates_per_iter()

% a per number of iterations
%plot(1:num_iter, eff_estimates_per_iter(1,:))

% alpha per number of iterations
%plot(1:num_iter, eff_estimates_per_iter(2,:))


 
hold off


% eff_a
%plot(1:num_iter, eff_estimates_per_iter(1,:), 'b-')
% eff_alpha
% plot(1:num_iter, eff_estimates_per_iter(2,:), 'r-')
