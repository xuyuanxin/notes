#include "sa_dbg.h"

int ut_log_main();
int main_cmd(void);

int dbg_flag = 1;

int main()
{
    sa_dbgp("aaa %d\n",1);
    sa_dbgp("ssssssssssssssss\n");

	ut_log_main();

    (void)main_cmd();
    return 0;
}

