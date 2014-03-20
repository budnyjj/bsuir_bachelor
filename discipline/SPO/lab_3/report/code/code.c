#include <stdio.h>
#include <windows.h>

int **
create_array(int N, int M)
/* Create NxM array in heap */
/* Return pointer to allocated memory, 
   if succeed, NULL otherwise */
{
  int i;
  const int uiFlags = 0;
  int ** a;

  a = (int **)GlobalAlloc(uiFlags, sizeof(int *) * N);
  if (a)
    {
      for (i = 0; i < N; i++)
	{
	  a[i] = (int *)GlobalAlloc(uiFlags, sizeof(int) * M);
	  if (!(a[i]))
	    {
	      for (i = i-1; i >=0; i--)
		GlobalFree(a[i]);	    
	      GlobalFree(a);
	      return NULL;
	    }
	}
      return a;
    }
  else
    return NULL;
}

void
print_array(int ** array, int N, int M)
/* Display array size and content */
{
  int i, j;
  puts("=== ARRAY DIMENSIONS ===");
  printf("N: %i; M: %i\n", N, M);
  puts("==== ARRAY CONTENTS ====");
  for (i = 0; i < N; i++)
    {
      for (j = 0; j < M; j++)
	{
	  printf("%d ", array[i][j]);
	}
      printf("\n");
    }
  puts("========================");
}

int
array_get_min(int ** array, int N, int M)
/* Display array size and content */
{
  int i, j, min = array[0][0];
  for (i = 0; i < N; i++)
    {
      for (j = 0; j < M; j++)
	{
	  if (array[i][j] < min)
	    min = array[i][j];
	}
    }
  return min;
}

void
destroy_array(int ** array, int N, int M)
/* Free array's allocated memory */
{
  int i;
  for (i = 0; i < N; i++)
    {
      GlobalFree(array[i]);
    }

  GlobalFree(array);
  array = NULL;
}

static void
clear_input()
{
  while (getchar() != '\n');
}

static void
print_usage()
{
  const char * usage_msg =
    "Press \'s\' to start calculations, \'q\' to exit";
  puts(usage_msg);
}

static int
get_dimension(int * dest)
/* Get array dimension from user input */
/* Return 1 if correct, 0 otherwise */
{
  if (!scanf("%i", dest) || (*dest <= 0)) 
    return 0;
  return 1;
}

int
get_options(struct io_opts * dest_opts)
/* Get user input from interactive console interface */
/* Return 0 if need to exit */
{
  char choice;
  print_usage();

  while (1)
    {
      scanf("%c", &choice);
      clear_input();
      switch (choice)
	{
	case 's':
	case 'S':
	  {
	    int N, M;

	    puts("Input first dimension size:");
	    while (!get_dimension(&N))
	      {
		puts("Size of dimension must be greater than zero");	     
		clear_input();
	      }
	    dest_opts->N = N;
	    clear_input();

	    puts("Input second dimension size:");
	    while (!get_dimension(&M))
	      {
		puts("Size of dimension must be greater than zero");	     
		clear_input();
	      }
	    dest_opts->M = M;
	    clear_input();

	    return 1;
	  }
	case 'q':
	case 'Q':
	  return 0;
	default:
	  {
	    print_usage();
	    break;
	  }
	}
    }
}

static int
get_value(int i, int j)
/* Get [i,j] array value from user input */
{
  int val = 0;
  printf("Input A[%d][%d]\n", i, j);

  while (!scanf("%i", &val))
    {
      puts("Incorrect input!");
      clear_input();
    }
    clear_input();

    return val;
}


void 
get_array_contents(int ** dest_array, int N, int M) 
/* Fill array with user input */
{
  int i, j;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      {
	dest_array[i][j] = get_value(i, j);
      }
}

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
