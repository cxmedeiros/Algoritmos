#include <iostream>
#include <algorithm>

using namespace std;

struct hosp
{
    int ID;
    int cases;
};

int tam = 0;
int sizee=1000000;

void bubble_up(hosp *pandemic, int tam)
{
    int aux = tam;

    while (aux > 0 && pandemic[aux].cases >= pandemic[(aux - 1) / 2].cases)
    {
        if (pandemic[aux].cases != pandemic[(aux - 1) / 2].cases)
        {
            swap(pandemic[aux], pandemic[(aux - 1) / 2]); 
        }else
        {
            if (pandemic[aux].ID > pandemic[(aux - 1) / 2].ID)
            {
                swap(pandemic[aux], pandemic[(aux - 1) / 2]);
            }
        }
        aux = (aux - 1) / 2;
    }
}

void heapify(hosp *pandemic, int tam, int i)
{

    if (tam != 1)
    {

        int largest = i;
        int l = (2 * i) + 1;
        int r = (2 * i) + 2;

        if (l < tam && pandemic[l].cases >= pandemic[largest].cases)
        {
            if (pandemic[l].cases != pandemic[largest].cases)
            {
                largest = l;
            }
            else
            {
                if (pandemic[l].ID > pandemic[largest].ID)
                {
                    largest = l;
                }
            }
        }
        if (r < tam && pandemic[r].cases >= pandemic[largest].cases)
        {
            if (pandemic[r].cases != pandemic[largest].cases)
            {
                largest = r;
            }
            else
            {
                if (pandemic[r].ID > pandemic[largest].ID)
                {
                    largest = r;
                }
            }
        }
        if (largest != i)
        {

            swap(pandemic[i], pandemic[largest]);
            heapify(pandemic, tam, largest);
        }
    }
}

//inserir elem
void insert(hosp *pandemic, int cases, int id)
{
    if(tam == sizee){
        hosp *aux = new hosp[sizee*2];
        for (int i=0; i<tam; i++){
            aux[i]=pandemic[i];
        }
        pandemic = aux;
        sizee = sizee*2;
    }
    if (tam == 0)
    {
        pandemic[tam].cases = cases;
        pandemic[tam].ID = id;

        tam += 1;
    }
    else
    {
        pandemic[tam].cases = cases;
        pandemic[tam].ID = id;

        tam += 1;

        bubble_up(pandemic, (tam)-1);
    }
}

//deletar elem
void deleteRoot(hosp *pandemic, int num)
{
    int index;

    for (int i = 0; i < tam; i++)
    {
        if (num == pandemic[i].ID)
        {
            index = i;
            i = tam;
        }
    }

    swap(pandemic[index], pandemic[tam - 1]);
    tam -= 1;

    heapify(pandemic, tam, index);
}

//printar o vetor
void printArray(hosp *pandemic, int tam)

{
    for (int i = 0; i < tam; ++i)
    {
        cout << pandemic[i].cases << " " << pandemic[i].ID << "/";
    }

    cout << "\n";
}

//add casos
void in(hosp *pandemic, int h, int c)
{

    int index;

    for (int i = 0; i < tam; i++)
    {
        if (pandemic[i].ID == h)
        {
            pandemic[i].cases += c;
            index = i;
            i = tam;
        }
    }

    bubble_up(pandemic, index);
}

//diminuir casos
void out(hosp *pandemic, int h, int c)
{

    int index;

    for (int i = 0; i < tam; i++)
    {
        if (pandemic[i].ID == h && pandemic[i].cases > 0)
        {
            pandemic[i].cases -= c;
            if (pandemic[i].cases < 0)
            {
                pandemic[i].cases = 0;
            }
            index = i;
            i = tam;
        }
    }

    heapify(pandemic, tam, index);
}

//distribuir os recursos
hosp *pay_2(hosp *pandemic, int *res){

    while(*res!=0 && pandemic[0].cases>0){
        out(pandemic, pandemic[0].ID, 1);
        (*res)--;
    }
    return pandemic;
}

int main()
{
    int total, cases, H, C, sum = 0, R;

    string command;

    cin >> total;

    hosp *pandemic = new hosp[sizee];

    for (int i = 0; i < total; i++)
    {

        cin >> cases;

        insert(pandemic, cases, i);
    }

    while (command != "END")
    {

        cin >> command;

        if (command == "P"){
            printArray(pandemic, tam);
        }
        if (command == "NEW")
        {
            cin >> H >> C;
            insert(pandemic, C, H);
            cout << pandemic[0].ID << " ";
            cout << pandemic[0].cases << "\n";

        }
        if (command == "DEL")
        {
            cin >> H;
            deleteRoot(pandemic, H);

            if (tam <= 0)
            {
                cout << "-1 -1" << endl;
            }
            else
            {
                cout << pandemic[0].ID << " ";
                cout << pandemic[0].cases << "\n";
                
            }
        }
        if (command == "IN")
        {
            cin >> H >> C;

            in(pandemic, H, C);

            for (int i = 0; i < tam; i++)
            {
                if (pandemic[i].ID == H)
                {
                    cout << pandemic[i].cases << endl;
                    i = tam;
                }
            }
        }
        if (command == "OUT")
        {
            cin >> H >> C;
            out(pandemic, H, C);

            for (int i = 0; i < tam; i++)
            {
                if (pandemic[i].ID == H)
                {
                    cout << pandemic[i].cases << endl;
                }
            }
        }
        if (command == "PAY")
        {
            cin >> R;
            int aux = R;
            pandemic = pay_2(pandemic, &R);
            cout << aux - R << endl;
            R = 0;
            
        }
    }
    for (int i = 0; i < tam; i++)
    {
        sum += pandemic[i].cases;
    }
    cout << sum << "\n";

    return 0;
}