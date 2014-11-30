function q = quality(f, x, y)
    q = 0;
    for i = 1:numel(x)
        q = q + (f(x(i)) - y(i)).^2;
    end
    q = sqrt(q);
end