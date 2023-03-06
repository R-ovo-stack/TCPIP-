#include <stdio.h>
#include <unistd.h>
#include <sched.h>

/**
 * 本程序用于理解fork()函数的作用以及特点
 * 
 * 父进程调用fork函数的同时复制出子进程，并分别得到fork函数的返回值。
 * 但复制前，父进程将全局变量gval增加到11，将局部变量lval的值增加到25，
 * 因此在这种状态下完成进程复制。复制完成后根据fork函数的返回类型区分父子进程。
 * 父进程将lval的值加1，但这不会影响子进程的lval值。
 * 同样，子进程将gval的值加1也不会影响到父进程的gval。
 * 因为fork函数调用后分成了完全不同的进程，只是二者共享同一代码而已。
*/
int gval = 10;
int main(int argc, char const *argv[])
{
    pid_t pid;
    int lval = 20;
    gval++, lval += 5;
    // gval = 11,lval = 25
    // 调用fork函数后,父子进程拥有完全独立的内存结构
    pid = fork();   // 成功返回0,失败返回-1
    if (pid == 0)
    {
        /* code */
        gval += 2,lval +=2;  // 子进程操作
    }
    else 
    {
        gval -=2,lval -=2;  // 父进程操作
    }
    
    if (pid == 0)
    {
        /* code */
        printf("Child Proc : [%d, %d] \n",gval,lval);   //  [13, 27] 
    }
    else
        printf("Parent Proc : [%d, %d] \n",gval,lval);    //  [9, 23] 
      

    return 0;
}
