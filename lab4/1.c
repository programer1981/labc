#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ch;
int i=0;
char m=' ';
int count=0;
char a[10];

int  read_string(char*st, FILE *fp,char ch){
ch=fgetc(fp);
printf("%d\n",ch );
return ch;
}

void write_string(char*st, FILE *fp1,char ch){
fputc(ch,fp1);
}

int main(int argc, char *argv[]){

  char *st = malloc(sizeof(char)*strlen(argv[1])+1);
  strcpy(st,argv[1]);
  char *p = strstr(argv[1],".");
  for(int i=0;i<strlen(st)-strlen(p);i++){
   printf("%c",st[i]);
   a[i]=st[i];
  }
strcat(a,".sh");
  FILE *fp;
  FILE *fp1;
  if((fp=fopen(argv[1], "r"))==NULL) {
    printf("Не удается открыть файл1.\n");
    exit(1);
  }
    if((fp1=fopen(a, "w"))==NULL) {
    printf("Не удается открыть файл2.\n");
    exit(1);
  }
do 
 {
  ch = read_string(argv[2],fp,ch);
  if (ch != EOF ){ 
  write_string(argv[3],fp1,ch);
    }  
 }while(ch!=EOF);

  if(fclose(fp)){ 
    printf("Ошибка при закрытии файла.\n");
    exit(1);
  }
  if(fclose(fp1)){
    printf("Ошибка при закрытии файла.\n");
    exit(1);
  }


   return 0;
}