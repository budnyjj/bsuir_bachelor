#ifndef _IO_
#define _IO_

#define MAX_DIMENSION_SIZE 1000

struct io_opts
{
  int N;
  int M;
};

int
get_options(struct io_opts *);

void 
get_array_contents(int **, int, int);

#endif
