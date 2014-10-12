function y = our_hi(k)

y = 0;

for i = 1:k
    y = y + normrnd(0, 1).^2;
end
