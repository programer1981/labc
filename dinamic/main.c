#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]){

    void *libmy;  // хандлер внешней библиотеки
    double (*libmyfanc)(int x,int y);

    libmy = dlopen("libmyfanc.so",RTLD_LAZY);
    if (!libmy){
        fprintf(stderr,"dlopen() error: %s\n", dlerror());
        return 1;
    };

    //загружаем из библиотеки требуемую процедуру
    libmyfanc = dlsym(libmy,argv[1]);    
    int value1=8;
    int value2=4;
    //выводим результат работы процедуры
    printf("%s(%d) = %d\n",argv[1],value1,value2,(*libmyfanc)(value1,value2));

    dlclose(libmyfanc);
};