/*

---->½©ËÀ(zombie)½ø³Ì
If a process terminates, and that process has children in the zombie state, the parent process ID of all the zombie children 
is set to 1 (the init process), which will inherit the children and clean them up (i.e., init will wait for them, which removes the zombie). 


