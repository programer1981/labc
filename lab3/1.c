#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pash{
    char name[50];
    int long1;
    int stat;
    int cost;
};
typedef struct pash routes;
 
void readway(routes *st)
{
    printf("Введите Имя:");
    scanf("%s", st->name);
    printf("протяженность:");
    scanf("%d", &st->long1);
        printf("кол остановок:");
    scanf("%d", &st->stat);
        printf("Стоимость:");
    scanf("%d", &st->cost);
}
void out(routes *st)
{
    printf("Введите Имя: %s\n",st->name);
//    printf("протяженность:%d\n",st->long1);
  //  printf("кол остановок:%d\n",st->stat);
    //printf("Стоимость:%d\n",st->cost);
}
 
int main(int argc, char **argv){
    int count = 0;
    routes* buf = (routes*)malloc(sizeof(routes*));
    printf("Введите кол маршрутов");
    scanf("%d", &count);
    routes** st = (routes**)malloc(sizeof(routes*)*count);
    for (int i = 0; i < count ; i++){
        st[i] = (routes*) malloc (sizeof(routes));
        readway(st[i]);
    }
  for (int i = count - 1; i >= 0; i--)
    {
         printf("%s\n","Here1" );
        
      for (int j = 0; j < i; j++)
    {
         printf("%s\n","Here2" );

      if ((st[j]->cost) >  (st[j + 1]->cost))
        {
                strcpy(buf->name,st[j]->name);
                strcpy(st[j]->name,st[j+1]->name);
                strcpy(st[j+1]->name,buf->name);
                printf("%s\n","Here" );
        }
    }
    }
    for (int i = 0; i < count; i++)
    {
        out(st[i]);
        free(st[i]);
    }
    free(st);
    return 0;
}