#include <stdio.h>

int main () {
    int a=0, b=0, multi=0;

    scanf("%d %d", &a, &b);

    if (b<0){
        for(int c=0; c<-(b); c++){
            multi+=a;
        }
        multi=-(multi);
        printf("%d\n", multi);

    }else if  (a<0 && b<0){
        for(int c=0; c<(b*-1); c++){
            multi+=a;
        }
        multi=-(multi);
        printf("%d\n", multi);

    }else{
        for(int c=0; c<b; c++){
            multi+=a;
        }
        printf("%d\n", multi);
    }
    return 0;
}
