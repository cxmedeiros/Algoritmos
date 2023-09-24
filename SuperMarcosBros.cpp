#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//coordenadas das plataformas
struct xy_points{
    int x, y;
};

//id, posiçao e moeda das plataformas
struct points{
    int id;
    xy_points pos;
    int coins;
};

//aresta com pai, filho e seu peso (peso da aresta)
struct edge{
    int son;
    int father;
    int weight;
};

//para achar os caminhos
struct return_way{
    vector <int> way;
    int has_way;
};

vector <points> plataform (0); //vetor das plataformas
vector <edge> sons[10000];

//calcular a distancia entre duas plataformas
int distance(xy_points a, xy_points b){
    return (int) pow(b.x - a.x, 2) + pow(b.y - a.y, 2);
}

//calcular os pesos das arestas
int calculate_weight(points a, points b){
    if(b.coins == 0) {
        return (int) distance(a.pos, b.pos);
    } else {
        int neg = (int) distance(a.pos, b.pos);

        return -neg;
    }
}

//add uma plataforma
void add_point(int id, int x, int y){
    points aux;
    aux.id = id;
    aux.pos.x = x;
    aux.pos.y = y;
    aux.coins = 0;
    plataform.push_back(aux);
}

//add as moedas
void add_coins(int id, int coins){
    plataform[id].coins = coins;
}

//add filho/aresta/plataforma
string add_plataform(int id_father, int id_son, string auxx, int i){
    edge aux;

    aux.weight = calculate_weight(plataform[id_father], plataform[id_son]);
    aux.father=id_father;
    aux.son=id_son;

    sons[id_father][i] = aux;

    return auxx;
}

//pq nem todos os nós tem a mesma quantidade de aresta
void resize_son(int id, int n){
    sons[id].resize(n);
}

return_way find_showerst_way(int source, int destination){
    
    vector <int> way (0);//caminho
    vector <int> dist (plataform.size(), INT_MAX);//tamaho infinito da aresta
    vector <int> previous (plataform.size(), -1);//o precedente do nó é -1 

    vector <int> node = vector <int> (plataform.size(), 0); // guardar a quantidade de plataformas
    int has_way = 1;
    dist[source] = 0;

    for (int i = 0; i < plataform.size() - 1; i++){
        for (int j = 0; j < plataform.size(); j++){
            for (int k = 0; k < sons[j].size(); k++){
                if(dist[j] != INT_MAX){
                    int a = sons[j][k].father;
                    int b = sons[j][k].son;

                    int weight = sons[j][k].weight;

                    bool less = dist[a] + weight < dist[b];
                    bool equal = dist[a] + weight == dist[b];

                    bool compare_nodes = node[a] + 1 < node[b];
                    bool nodes_equal = node[a] + 1 == node[b];

                    bool lexic = a < previous[b];

                    if(less || (equal && compare_nodes) || (equal && nodes_equal && lexic)){
                        dist[b] =  dist[a] + weight;
                        previous[b] = a;
                        node[b] = node[a] + 1;
                    }
                }
            }
        }
    }

    int current = destination;
    int count = 0;

    return_way true_or_false;

    if (has_way){
        while(current != -1 && count < (plataform.size() * 10)){
            way.push_back(current);
            current = previous[current];
            count++;
        }
        if(count == (plataform.size() * 10)){
            has_way = 0;
        }
        reverse(way.begin(), way.end());
        way.push_back(destination);
        true_or_false.way = way;   
    }
    true_or_false.has_way = has_way;
    return true_or_false;
}

int main(){

    int cases=0, i=0, pointss=0, x=0, y=0, n_coin=0, n=0, plat=0, n_plat=0, skp=0;

    string aux;
    string command;

    cin >> cases;//casos testes

    while (i < cases){

        plataform.clear();
        for(int b=0; b < 10000 ; b++){
            sons[b].clear();
        }
        
        cin >> pointss;//quantidade de plataformas/pontos em um caso

        for(int i=0; i < pointss; i++){

            cin >> x >> y;//coordenadas x e y desses pontos

            add_point(i, x, y);
        }

        cin >> n_coin;//quantidades de plataformas com moedas

        if(n_coin > 0){
            for(int i=0; i < n_coin; i++){
                cin >> n;//numero dessas plataformas
                add_coins(n,1);
            }
        }

        for(int i=0; i < pointss - 1; i++){
            cin >> n_plat; //quantidade de plataformas alcançáveis com um salto
            resize_son(i, n_plat);
            for(int a=0; a < n_plat; a++){
                cin >> plat;//número dessas plataformas
                aux = add_plataform(i, plat, aux, a);

            }
        }

        return_way way = find_showerst_way(0, pointss - 1);
        if(way.has_way){
            int sum=0;
            for(int i=0; i < way.way.size() - 1; i++){
                sum += calculate_weight(plataform[way.way[i]], plataform[way.way[i + 1]]);
            }
            cout << sum << " ";
            for(int i=0; i < way.way.size() - 1; i++){
                 cout << way.way[i];
                if(i != way.way.size() -2){
                    cout << " ";
                }
            }
            cout << endl;
        } else {
            cout << "LOOP" << endl;
        }
        cin >> skp;
        i++;

    }
    return 0;
}
