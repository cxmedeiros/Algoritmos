#include <bits/stdc++.h>

using namespace std;

int p[33];
int l,m,q;
int cont = 0, itens=0;

void search(int i, int sum) {

    if(l == i)
        return;
    
    if(sum + p[i] <= q) {
        if(++itens >= m)
            cont++;
        search(i+1, sum+p[i]);
        itens--;
    }
    
    search(i+1, sum);

}

int main()
{

    int t;
    cin >> t;
    for(int c = 0; c < t; c++) {
       
        cin >> l;
        

        for(int i = 0; i < l; i++)
            cin >> p[i];  
        
        cin >> m >> q;
        if(m == 0) cont++;

        search(0, 0);
        printf("caso %d: %d\n", c, cont);

        cont = 0;
        itens=0;
    }

    return 0;
}