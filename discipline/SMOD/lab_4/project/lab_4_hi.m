num = 500
k = 5

our_values = [];

hold on
grid on

matlab_values = []

for i=1:num 
    our_values(i, 1) = our_hi(k);
    our_values(i, 2) = our_hi(k);
    %plot(our_values(i,1), our_values(i,2), '.r', 'MarkerFaceColor','r')
    
    matlab_values(i,1) = chi2rnd(k);
    matlab_values(i,2) = chi2rnd(k);
    plot(matlab_values(i,1), matlab_values(i,2), '.', 'MarkerFaceColor', 'b')
end
hold off