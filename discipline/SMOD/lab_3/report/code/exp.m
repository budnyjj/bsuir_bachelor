  %%%%% main file %%%%%

  num = 20
  lambda = 10

  our_values = []
  hold on
  grid on
  for i=1:num
      our_values(i) = our_exp(lambda)
      plot(our_values(i), -0.2, '.r', 'MarkerFaceColor', 'r')
      plot(exprnd(lambda), 0.2, '.', 'MarkerFaceColor', 'b')
  end
  hold off

  min = min(our_values)
  max = max(our_values)
  mean = mean(our_values)
  std = std(our_values)
  skewness = skewness(our_values)
  kurtosis = kurtosis(our_values)

  %%%%% function %%%%%

  function y = our_exp(lambda)

  alpha = unifrnd(0, 1)
  y = -lambda * log(alpha)
