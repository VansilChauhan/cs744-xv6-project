#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// LAB-3 ----------------------------------------------

int sys_worldpeace(void)
{
  // function definition in sysproc.c
  cprintf("Systems are vital to world peace !!\n");
  return 0;
}

int sys_numberofprocesses(void)
{
  // function definition in sysproc.c
  return numberofprocesses();
}

int sys_spawn(void)
{
  // function definition in sysproc.c
  int n, *pids;
  // take arguments
  if (argint(0, &n) < 0 || argptr(1, (void *)&pids, n * sizeof(*pids)) < 0)
  {
    return -1;
  }
  return spawn(n, pids);
}

int sys_getvasize(void)
{
  // function definition in sysproc.c
  int pid;
  // take arguments
  if (argint(0, &pid) < 0)
  {
    return -1;
  }
  return getvasize(pid);
}

int sys_va_to_pa(void)
{
  // function definition in sysproc.c
  int virtual_addr;
  // take arguments
  if (argint(0, &virtual_addr) < 0)
  {
    return -1;
  }
  return va_to_pa((uint)virtual_addr);
}

int sys_get_pgtb_size(void)
{
  // function definition in sysproc.c
  return get_pgtb_size();
}

int sys_get_usr_pgtb_size(void)
{
  // function definition in sysproc.c
  return get_usr_pgtb_size();
}

int sys_get_kernel_pgtb_size(void)
{
  // function definition in sysproc.c
  return get_kernel_pgtb_size();
}

int sys_getpasize(void)
{
  // function definition in sysproc.c
  int pid;
  // take arguments
  if (argint(0, &pid) < 0)
  {
    return -1;
  }

  return getpasize(pid);
}

int sys_mmap(void)
{
  // function definition in sysproc.c
  int size;
  // take arguments
  if (argint(0, &size) < 0)
  {
    return 0;
  }
  int addr = myproc()->sz;
  if (grow(size) < 0)
  {
    return 0;
  }
  return addr;
}

int sys_get_sibling(void)
{
  return get_sibling();
}

int sys_whatsthestatus(void)
{
  int pid;
  if (argint(0, &pid) < 0)
  {
    return 0;
  }
  return whatsthestatus(pid);
}
