#include <stdio.h>

#include <io.h>
#include <array.h>

int main()
{
  struct io_opts options;
  while (get_options(&options))
    {
      int ** a;
      int min = 0;

      if (a = create_array(options.N, options.M))
	{
	  get_array_contents(a, options.N, options.M);

	  print_array(a, options.N, options.M);
      
	  min = array_get_min(a, options.N, options.M);
	  printf("Min value: %d\n", min);

	  destroy_array(a, options.N, options.M);
	}
      else
	{
	  puts("Error of memory allocation!");
	}
    }
  return 0;
}
