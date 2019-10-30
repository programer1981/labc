#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]){

    void *libmy;  // хандлер внешней библиотеки
    int (*libmyfunc)(int x,int y);

    libmy = dlopen("./libmyfunc.so",RTLD_LAZY);
    if (!libmy){
        fprintf(stderr,"dlopen() error: %s\n", dlerror());
        return 1;
    };

    //загружаем из библиотеки требуемую процедуру
    libmyfunc = dlsym(libmy,argv[1]);    
    int value1=8;
    int value2=4;
    //выводим результат работы процедуры
    printf("%d\n",(*libmyfunc)(value1,value2));

};