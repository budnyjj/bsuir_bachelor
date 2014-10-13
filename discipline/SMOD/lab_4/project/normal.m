function y = normal(X1, X2, A, R)

r_12 = R(1,2)/sqrt(R(1,1).*R(2,2));

phi = zeros(size(X1,1), size(X2,1));

c_1 = (1-r_12).^2;
for i = 1:size(X1,1)
    for j = 1:size(X1,2)
        part_1 = ((X1(i,j) - A(1)).^2)/R(1,1);
        part_2 = 2.*r_12.*(X1(i,j) - A(1)).*(X2(i,j) - A(2))/sqrt(R(1,1).*R(2,2));
        part_3 = ((X2(i,j) - A(2)).^2)/R(2,2);
        
        phi(i,j) = (part_1 - part_2 + part_3)./c_1;
    end
end

y = zeros(size(X1,1), size(X1,2));

c_2 = 1./(2*pi*sqrt(R(1,1).*R(2,2).*(1-r_12.^2)));
for i = 1:size(X1,1)
       for j = 1:size(X1, 2)
            y(i,j) = c_2*exp(-0.5*phi(i,j));
       end
end