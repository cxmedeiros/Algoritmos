#include <stdio.h>

int main (){
    int num,b=0,c=1, aux;
    scanf("%d", &num);

    if (num==1){
        printf("0\n");
    }
    else if (num==2){
        printf("1\n");
    }

    else if(num>2){
        for (int a=2; a<num; a++){
            aux=b+c;
            b=c;
            c=aux;
        }
        printf("%d\n", aux);
    }
    return 0;
}