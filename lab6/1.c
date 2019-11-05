#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i, pid[argc], status, stat;
    FILE *fp;
int s;
int k=0;
int r=0;
int m=0;
double t=0;
    for (i = 1; i < argc; i++) {

        // запускаем дочерний процесс 
        pid[i] = fork();
        srand(getpid());
        if (-1 == pid[i]) {
            perror("fork"); /* произошла ошибка */
            exit(1); /*выход из родительского процесса*/
        } else if (0 == pid[i]) {
            printf(" CHILD: Это %d процесс-потомок СТАРТ!\n", i);
            r=0;
            k=0;
            if ((fp = fopen(argv[i], "r")) == NULL)
               {
                   printf("Не удалось открыть файл");
               }              

            while ((fscanf(fp, "%d",&s)!=EOF))
        {   if(!fp) break;    //чтобы не делал лишнего
        k+=1;
        }
int *c = (int*) malloc(k*sizeof(int));  //должен быть динамическим
    //перематываем файл для повторногfpя
rewind(fp);
for(i=0;i<k;i++)
{
    fscanf(fp, "%d",&c[i]);
  //printf("c[%d]=%d\n  ",i,c[i]);
    r=r+c[i];
  //printf("%d\n",r);
}
            t=(float)r/k;
            printf("%f",t);
            printf(" CHILD: Это %d процесс-потомок ВЫХОД!\n", i);
            free(c);
            fclose(fp);
            exit(1);
             /* выход из процесс-потомока */
        }
    }
    // если выполняется родительский процесс
    printf("PARENT: Это процесс-родитель!\n");
    // ожидание окончания выполнения всех запущенных процессов
    for (i = 1; i < argc; i++) {
        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
            printf("процесс-потомок %d done\n", WEXITSTATUS(stat));
        }
    }
    return 0;
}