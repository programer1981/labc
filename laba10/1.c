#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
struct DATA
{
  char a[10];
  float h;
};

void *square_of_triangle(struct DATA *arg);

int main (int argc, char *argv[])
{
  int result;
  pthread_t threads[5];
  struct DATA data[5];
  void *status[5];

  for (int i = 1; i < argc; i++)
    {
      strcpy(data[i].a,argv[i]);
      result =pthread_create (&threads[i], NULL, (void *)square_of_triangle, &data[i]);
      if (result != 0)
	{
	  perror ("Creating the first thread");
	  return EXIT_FAILURE;
	}
    }

  for (int i = 1; i < argc; i++)
    {
      result = pthread_join (threads[i], &status[i]);
      if (result != 0)
	{
	  perror ("Joining the first thread");
	  return EXIT_FAILURE;
	}
      else
	{
	  printf ("square[%s]=%f\n", data[i].a, *((float *) status[i]));
	}
      free (status[i]);
  }

  printf ("Done..\n");
  return EXIT_SUCCESS;
}

void *square_of_triangle(struct DATA *arg)
{
  printf ("square=%s\n", arg->a);
  FILE *pf;
  int k,r,s;
 if ((pf = fopen(arg->a, "r")) == NULL)
               {
                   printf("Не удалось открыть файл");
               }  
while ((fscanf(pf, "%d",&s)!=EOF))
        {   if(!pf) break;    //чтобы не делал лишнего
        k+=1;
        }
int *c = (int*) malloc(k*sizeof(int));  //должен быть динамическим
    //перематываем файл для повторногfpя
rewind(pf);
for(int i=0;i<k;i++)
{
    fscanf(pf, "%d",&c[i]);
  //printf("c[%d]=%d\n  ",i,c[i]);
    r=r+c[i];
  //printf("%d\n",r);
}
      float *ps = (float*)malloc(sizeof(float)); 
  *ps =(float) r/k;
  sleep(1);
  printf("square=%f\n", *ps);
    fclose(pf);
  pthread_exit((void*)ps);
}
