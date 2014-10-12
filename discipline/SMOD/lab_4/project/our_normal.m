function y = our_normal(a, R)

c_11 = R(1,1).^0.25;
c_12 = 0;
c_21 = (R(1,2)/sqrt(R(1,1)*R(2,2)))/c_11;
c_22 = sqrt(sqrt(R(2,2)) - c_21.^2);

C = [c_11, c_12;
     c_21, c_22];

t = [normrnd(0,1); normrnd(0, 1)];

y = C*t + a;