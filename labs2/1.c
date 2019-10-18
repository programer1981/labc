#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>		/* для mtrace */
#include <string.h>
#define MAX_LEN 1024		/* максимальная длина строки */
int Swap = 0;
int count = 0;
char **
readMas (int count)
{
  char buffer[MAX_LEN];
  char **mas;			//указатель на массив указателей на строки
  mas = (char **) malloc (sizeof (char *) * count);	// выделяем память для массива указателей/
  for (int i = 0; i < count; i++)
    {
      scanf ("%s", buffer);	// читаем строку в буфер
      mas[i] = (char *) malloc (sizeof (char) * strlen (buffer));	//выделяем память для строки
      strcpy (mas[i], buffer);	//копируем строку из буфера в массив указателей
    }
  return mas;
}

void
printMas (char **mas, int count)
{
  for (int i = 0; i < count; i++)
    {
      printf ("%ld\n", strlen (mas[i]));
    }
}

void
freeMas (char **mas, int count)
{
  for (int i = 0; i < count; i++)
    {
      free (mas[i]);		// освобождаем память для отдельной строки
    }
  free (mas);			// освобождаем памать для массива указателей на строки
}

int
sort (char **mas, int count)
{
  for (int i = count - 1; i >= 0; i--)
    {
      for (int j = 0; j < i; j++)
	{

	  if (strlen (mas[j]) > strlen (mas[j + 1]))
	    {
	      char *temp = mas[j];
	      mas[j] = mas[j + 1];
	      mas[j + 1] = temp;
	      Swap = Swap + 1;
	    }
	}
    }
}

int
main (int argc, char **argv)
{
  scanf ("%d\n", &count);
  char **mas = NULL;
  //указатель на массив указателей на строки
  //  printf("%d\n",count );
  mas = readMas (count);
  sort (mas, count);
  printMas (mas, count);
  freeMas (mas, count);
  printf ("a=%d", Swap);
}
