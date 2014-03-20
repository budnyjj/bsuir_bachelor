#ifndef _ARRAY_H_
#define _ARRAY_H_

int **
create_array(int, int);

void 
print_array(int **, int, int);

int
array_get_min(int **, int, int);

void
destroy_array(int **, int, int);

#endif
