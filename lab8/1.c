#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h>
#include <unistd.h>

struct client
{
  long mtype;			/* тип сообщения, должен быть > О */
  char mtext[10];		/* данные */
};

struct server
{
  long mtype;			/* тип сообщения, должен быть > О */
  char mtext[10];		/* имя  */
  float math;
};

int
main (int argc, char **argv)
{
  int pid[argc];
  FILE *fp;
  int s;
  int k = 0;
  int r = 0;
  int m = 0;
  double t = 0;
  struct client client_buf;
  struct server server_buf;
  //     printf("1");
  int i, n, stat, status;
        int id = msgget (1, 0600 | IPC_CREAT);
        for (i = 1; i < argc; i++)
    {
      strcpy (client_buf.mtext, argv[i]);
      client_buf.mtype = 1;
      msgsnd (id, &client_buf, sizeof (client_buf) - sizeof (long),
	      IPC_NOWAIT);
    }

  for (i = 1; i < argc; i++)
    {
      pid[i] = fork ();
      srand (getpid ());
      if (-1 == pid[i])
	{
	  perror ("fork");	/* произошла ошибка */
	  exit (1);		/*выход из родительского процесса */
	  /* процесс-потомок закрывает доступный для чтения конец канала 0 */

	}
      else if (0 == pid[i])
	{
      client_buf.mtype = 1;
      strcpy (client_buf.mtext, argv[i]);
      msgsnd (i, &client_buf, sizeof (client_buf) - sizeof (long),
          IPC_NOWAIT);

	  printf
	    (" CHILD: Это процесс-потомок СТАРТ!\n");
	  msgrcv (id, &client_buf, sizeof (client_buf) - sizeof (long), 1,
		  IPC_NOWAIT);
	  printf ("%s\n", client_buf.mtext);

	  r = 0;
	  k = 0;
	  if ((fp = fopen (client_buf.mtext, "r")) == NULL)
	    {
	      printf ("Не удалось открыть файл");
	    }
	  while ((fscanf (fp, "%d", &s) != EOF))
	    {
	      if (!fp)
		break;		//чтобы не делал лишнего
	      k += 1;
	    }
	  int *c = (int *) malloc (k * sizeof (int));	//должен быть динамическим
	  //перематываем файл для повторногfpя
	  rewind (fp);
	  for (i = 0; i < k; i++)
	    {
	      fscanf (fp, "%d", &c[i]);
	      //printf("c[%d]=%d\n  ",i,c[i]);
	      r = r + c[i];
	      //printf("%d\n",r);
	    }
	  t = (float) r / k;
	  printf ("%f", t);
	  printf
	    (" CHILD: Это %d процесс-потомок ВЫХОД!\n",
	     i);
	  server_buf.mtype = 2;
	  strcpy (server_buf.mtext, client_buf.mtext);
	  server_buf.math = t;
	  printf ("%f\n", server_buf.math);
	  msgsnd (id, &server_buf, sizeof (server_buf) - sizeof (long), IPC_NOWAIT);

	  printf (" CHILD: Это процесс-потомок EXIT!\n");
	  free (c);
	  fclose (fp);
	  exit (1);
	}
    }
  printf (" CHILD: Это процесс-родитель старт!\n");
  for (i = 1; i < argc; i++)
    {
      status = waitpid (pid[i], &stat, 0);
      if (pid[i] == status)
	{
	  printf ("процесс-потомок result=%d\n",
		  WEXITSTATUS (stat));

	  msgrcv (id, &server_buf, sizeof (server_buf) - sizeof (long), 2,
		  IPC_NOWAIT);

	  printf ("%f\n", server_buf.math);
	}
    }
    for (i = 1; i < argc; i++)
    {
	msgctl (id, IPC_RMID, NULL);
    }
  return 0;
}
