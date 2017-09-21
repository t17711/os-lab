# os-lab projects
1. system calls
  - file read using access, read, open, write
  - error check using perror, errno
  - read command line arg for file neame
2. process management using fork
  - use watpid to waid child process
3. system calls
   - use excel to run linux command
   - fork process that runs the system call since process ends after call finishes
   - run date to get system date
   - run ls with args
   - execute other process
   - also executor is infinite loop that executes args
4. fork with concurent file access
  - test read file from multiple file by forking process
  - we can see that the read happens in different order each time
5. fork with semaphore for access
  - fork process that edits file based on order using semaphore
6. Ciggrate Smoker problem using semaphore and pthread
  - implement Ciggrate Smoker problemusing pthread 
    - uses pthread_mutex_init, pthread_create, pthread_join, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
  - fork and semaphorep
