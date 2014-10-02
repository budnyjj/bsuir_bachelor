num = 20
a = 0
sigma = 10 

our_values = []
hold on
grid on
for i=1:num
    our_values(i) = our_normal(a, sigma)
    plot(our_values(i), -0.2, '.r', 'MarkerFaceColor','r')
    plot(normrnd(a, sigma), 0.2, '.', 'MarkerFaceColor', 'b')
end
hold off

min = min(our_values)
max = max(our_values)
mean = mean(our_values)
std = std(our_values)
skewness = skewness(our_values)
kurtosis = kurtosis(our_values)