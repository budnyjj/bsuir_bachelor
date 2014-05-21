#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#ifndef __IO__
#define __IO__

void DLL_API clear_input();
void DLL_API wait_user_reaction();

void DLL_API print_rw_message(char *operation_result);

#endif