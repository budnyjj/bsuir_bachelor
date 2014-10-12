num = 500
a = [0; 0]
R = [1, 0;
     0, 1]

our_values_x = []
our_values_y = []

hold on
grid on

matlab_values = mvnrnd(a, R, num)

for i=1:num 
    our_values = our_normal(a, R);
    our_values_x(i) = our_values(1);
    our_values_y(i) = our_values(2);
    %plot(our_values_x(i), our_values_y(i), '.r', 'MarkerFaceColor','r')
    plot(matlab_values(i,1), matlab_values(i,2), '.', 'MarkerFaceColor', 'b')
end
hold off