#include <io.h>

#include <stdio.h>

static struct Complex change_complex_form(struct Complex complex);

void
clear_input() { while(getchar() != '\n'); }

void
wait_user_reaction() {
    printf("Press any key to continue...\n");
    clear_input();
}

void 
print_rw_message(char *operation_result) {
    printf("---------------------------------------\n ");
    printf(operation_result);
    printf("\n---------------------------------------\n");
    wait_user_reaction();
}