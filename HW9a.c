#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXQLEN  10

int que[MAXQLEN];
int topq = 0;
int numq = 0;
int z;

void prhelp() 
{  
  printf("Command Data\n");
  printf("\tCommand:\n");
  printf("\t\ti[nput] or e[nqueue] Data\n");
  printf("\t\to[utput] or d[equeue]\n");
  printf("\t\tl[ist]\n");
  printf("\t\tb[ye]\n");
}

char *findcmd(char *cp)
{
  while ((*cp == ' ' || *cp == '\t') && *cp) cp++;

  return cp;
}

char *finddata(char *cp)
{
  while(!(('0' <= *cp && *cp <= '9') || *cp == '+' || *cp =='-')) cp++;

  if (*cp == '\n' || *cp == '\0') return NULL;

  return cp;
}

void enq(int x)
{
   if(numq < MAXQLEN ){
     que[(topq+numq)%MAXQLEN]=x;
    numq++;
    
  }else{
     printf("overflow\n");
    
  }
}

int deq()
{
  
  if(numq > 0){
    z = que[(topq++ % MAXQLEN)];
    numq --;
    return z;
  }else{
    printf("empty\n");
    return 10000;
  }
}
int listq()
{
  int x=0;
  printf("list\n");
  printf("topq = %d  , numq = %d\n", topq, numq);

 /*  printf("que[x] = %d", que[topq]); */
/*   printf("que[x] = %d", que[topq+numq-1]); */
  for(x=topq;x!=(topq+numq);x++){
  
  printf("%d\n",que[x]);
  }
}

int main()
{
  char buf[256];
  char *cp;
  char *cmd;
  char *datap;
  int  data;
  int  endflag;
 


  prhelp();
  endflag = 0;

  do {
    if ((cp = fgets(buf, sizeof(buf), stdin)) == NULL) break;

    cmd = findcmd(cp);
    if ((datap = finddata(cmd)) != NULL) {
      data = atoi(datap);
    }
    
    
    switch(*cmd) {
    case 'i':
    case 'e':
      enq(data);
      break;
    case 'd':
    case 'o':
      data = deq();
      printf("%d\n", data);
      break;
    case 'l':
      listq();
      break;
    case 'b':
      endflag = 1;
      break;
    default:
      prhelp();
    }
  }while (!endflag);
}

  
