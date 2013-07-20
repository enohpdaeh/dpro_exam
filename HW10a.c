#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct node{
    /* ノードの要素 */
  int data;
  struct node *next;
};




struct node *CreateNode()
{
    /* 新しいnodeにメモリを割り当て、その先頭アドレスを返す */
  struct node *np;

  np = (struct node *) malloc(sizeof(struct node));
  if (np == NULL){
    perror("malloc:");
    exit(-1);
}
  np->next = NULL;
  return np;
}
/* topは一番最初のnode */
struct node *AddNode(struct node *top, struct node *np)
{
  struct node *tp;

  if(top == NULL) return np;
  for(tp = top; tp->next; tp = tp ->next);
  tp ->next = np;

  return top;
    /* npをリストの最後に追加最初のnodeの先頭アドレスを返す */
}
struct node *InsertNode(struct node *top,struct node *np,int offset)
{
  int  i;
  //insert関連
  struct node *tp;
  struct node *tp_a;
  if(top == NULL)return np;
  for(tp = top,i=1;tp->next;tp=tp->next,i++){
    if(offset -1 == i){
      tp_a =tp->next;
      tp->next = np;
      np->next = tp_a;
    }
  }
  return top;
}
/* npは削除するnodeの先頭アドレス */
struct node *DeleteNode(struct node *top, struct node *np)
{
  struct node *tp;
  struct node *dp;

  if(top==np){
    tp = top->next;
    free(top);
    return tp;
  }
  for(tp = top; tp->next; tp = tp->next){
    if(tp->next == np){
      tp->next = np->next;
      free(np);
      return top;
    }
  }
  fprintf(stderr,"No node in list:%p\n",np);
  return top;
}
    /* npをリストから削除し、最初のnodeの先頭アドレスを返す*/
 

void PrintNodesData(struct node *top)
{
  struct node *tp;
    /* リストの中のすべてのnodeを表示 */
  for(tp = top; tp;tp = tp->next){
    printf("%d",tp->data);
  }
}

struct node *FindNode(struct node *top, int data)
{
    /* 特定のdataを持つnodeの先頭アドレスを返す */
  struct node *np;
  for(np = top; np; np = np->next){
    if(np->data == data)
      return np;
  }
  return NULL;
}


void prhelp() 
{  
  printf("Command Data\n");
  printf("\tCommand:\n");
  printf("\t\ta[dd] Data\n");
  printf("\t\td[elete] Data\n");
  printf("\t\ti[nsert] d\n");
  printf("\t\tl[ist]\n");
  printf("\t\tb[ye]\n");
}
char *findoffset(char *cp){
  while ((*cp == ' ' || *cp == '\t') && *cp) cp++;

  return cp;
}
char *findcmd(char *cp)
{
  while ((*cp == ' ' || *cp == '\t') && *cp) cp++;

  return cp;
}

char *finddata(char *cp)
{
  while(!(('0' <= *cp && *cp <= '9') || *cp == '+' || *cp == '-')) cp++;

  if (*cp == '\n' || *cp == '\0') return NULL;

  return cp;
}

int main()
{
  struct node *Top;
  struct node *np;
  char buf[256];
  char *cp;
  char *cmd;
  char *datap;
  char *offsetp;
  int offset;
  int  data;
  int  endflag;

  Top = NULL;
  prhelp();
  endflag = 0;

  do {
    if ((cp = fgets(buf, sizeof(buf), stdin)) == NULL) break;

    cmd = findcmd(cp);
    if ((datap = finddata(cmd)) != NULL) {
      data = atoi(datap);
    }
    if ((offsetp = finddata(cmd)) != NULL) {
      offset = atoi(offsetp);
    }
    
    
    
    switch(*cmd) {
    case 'a':
      np = CreateNode();
      np->data = data;
      Top = AddNode(Top, np);
      break;
    case 'd':
      if((np = FindNode(Top, data)) != NULL) {
	Top = DeleteNode(Top, np);
      } else {
	printf("No node in the list with data %d\n", data);
      }
      break;
    case 'i':
      np = CreateNode();
      np->data = data;
      Top = InsertNode(Top,np,offset);
      break;
    case 'l':
      PrintNodesData(Top);
      break;
    case 'b':
      endflag = 1;
      break;
    default:
      prhelp();
    }
  }while (!endflag);
  return 0;
}
