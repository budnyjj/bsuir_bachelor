  %%%%% main file %%%%%

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

  %%%%% function %%%%%

  function y = our_normal(a, sigma)

  alpha_1 = unifrnd(0, 1);
  alpha_2 = unifrnd(0, 1);
  c = 2 * pi;
  r = sqrt(-2 * log(alpha_1));
  phi = c / alpha_2;
  y = a + sigma * r * cos(phi);
