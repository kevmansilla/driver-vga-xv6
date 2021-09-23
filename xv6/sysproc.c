#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
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
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
//tiene que ser parecidas a las anteriror (despues borrar comentario)
int
sys_modeswitch(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  return selec_mode(n);
}

int
sys_plotpixel(void)
{
  int a, b, c;
  if(argint(0, &a) < 0 || argint(1, &b) < 0 || argint(2, &c) < 0)
    return -1;
  return plotpixel(a, b, c);
}

int
sys_plotrectangle(void)
{
  int x1, x2, y1, y2, color;
  if((argint(0, &x1) < 0) || (argint(1, &y1) < 0) || (argint(2, &x2) < 0) || (argint(3, &y2) < 0) || (argint(4, &color) < 0)){
    return -1;
  }
  return plotrectangle(x1, y1, x2, y2, color);
}

int
sys_plotcircle(void)
{
  int x1, x2, y1, color;
  if((argint(0, &x1) < 0) || (argint(1, &y1) < 0) || (argint(2, &x2) < 0) || (argint(3, &color) < 0)){
    return -1;
  }
  return plotcircle(x1, x2, y1, color);
}
