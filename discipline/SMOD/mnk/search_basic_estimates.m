function basic_estimates = search_basic_estimates(x, y, init_params)
    % search solution of nonlinear equations system
    % (a, alpha) based on proposed (x[1:2], y[1:2]) values
    % specified params in form (start_a, start_alpha)
    basic_estimates = fsolve(@target_function, init_params);
    function f = target_function(params) 
    % target function. x(1), x(2) and y(1), y(2) are parameters
        a = params(1);
        alpha = params(2);
        f = [a.*exp(-alpha.*x(1))-y(1);a.*exp(-alpha.*x(2))-y(2)];
    end
end