function dst_array = arrayfun(func, src_array)
    [rows cols] = size(src_array);
    dst_array = zeros(rows, cols);
    for i = 1:rows
        for j = 1:cols
            dst_array(i,j) = func(src_array(i,j));
        end
    end
end