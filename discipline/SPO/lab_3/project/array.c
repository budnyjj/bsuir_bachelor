#include <array.h>
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
