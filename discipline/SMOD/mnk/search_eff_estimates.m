function eff_estimates = search_eff_estimates(basic_estimates, Q, y, f, num_iter)
    eff_estimates = basic_estimates.';
    Q_t = Q.';
    f_t = f.';
    y_t = y.';
    for i = 1:num_iter
        eff_estimates = eff_estimates + inv(Q_t*Q)*Q_t*(y_t - f_t);
    end
end