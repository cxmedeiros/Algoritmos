#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct node{

    int val;
    node *left;
    node *right;
    int height;

};

struct bst{
    node *root;
};


//criando nós para a árvore dada
node* Create_new_node (int val){

    node* newNode = new node ();
    newNode->val = val;
    newNode->right = newNode->left = NULL;

    return newNode;
}

//inserir elementos em bst
node* insert(node* root, int val){

    if (root == NULL){
        root = Create_new_node(val);
        return root;
    } else {
        if (val <= root->val){
            root->left = insert(root->left, val);
        }
        if (val > root->val){
            root->right = insert(root->right, val);
        }
    }
    return root;
}

// ver qual é a maior subárvore
int bigger(int a, int b){
    if (a >= b){
        return a;
    } else {
        return b;
    }
}

//calcular a altura
int height(node *node){

    if (node==NULL){
        return 0;
    }else{
        return 1 + bigger(height(node->left), height(node->right));
    }
}

//calcula o fator de balanço de cada subárvore
int balance_factor(node *root){
    int height_l=0, height_r=0;
    
    //se a raiz for vazia ou forem folhas
    if (root == NULL || (root->left == NULL && root->right == NULL)){
        return 1;

    }else {
        height_l = height(root->left);
        height_r = height(root->right);

        if((height_l - height_r) <= 1 && (balance_factor(root->left)==1) && (balance_factor(root->right)==1)){
            return 1;
        }
    }
    return 0;
}

//rodar pra esquerda
node* rotate_left(node* root, int *count_left){

    node* temp, *temp_left;
    temp = root->right;
    temp_left = temp->left;
    temp->left = root;
    root->right=temp_left;

    (*count_left)++;
    return temp;

}

//rodar pra direita
node* rotate_right(node* root, int *count_right){

    node* temp, *temp_right;
    temp = root->left;
    temp_right = temp->right;
    temp->right = root;
    root->left=temp_right;

    (*count_right)++;
    return temp;

}

//deixar tudo para o lado esquerdo
node* part_1(node *root, int *count_left){

    if(root->left == NULL && root->right == NULL){
        return root;

    } else if (root->right != NULL){
        root = rotate_left(root, count_left);
        root = part_1 (root, count_left);

    } else if (root->left != NULL){
        root->left = part_1(root->left, count_left);
    }

    return root;
}

//girar para a direita
node* right(node *new_root, node *old_root, int *count_right){

    while(new_root->val != old_root->val){
        new_root = rotate_right(new_root, count_right);
    }
    return new_root;
}

//girar para a esquerda
node* left(node *new_root, node *old_root, int *count_left){

    while(new_root->val != old_root->val){
        new_root = rotate_left(new_root, count_left);
    }
    return new_root;
}

//girar até deixar a primeira arvore igual a segunda
node *part_2(node *new_root, node *old_root, bool flag, int *count_left, int *count_right){
    if (flag){
        new_root = right(new_root, old_root, count_right);
    } else {
        new_root = left(new_root, old_root, count_left);
    } 
    if (new_root->left != NULL){
        new_root->left = part_2(new_root->left, old_root->left, true, count_left, count_right);
    }
    if (new_root->right != NULL){
        new_root->right = part_2(new_root->right, old_root->right, false, count_left, count_right);
    }
    return new_root;
}

//printar em pós-ordem
void print_posorder(node *no, int tam, int *count){

    if (no != NULL){

        print_posorder(no->left, tam, count);
        print_posorder(no->right, tam, count);

        cout << no->val;

        if (*count != tam-1){
            cout << " ";
        }
        (*count)++;
    }
}


int main (){

    int tam, num, i=0, k=0, count_left=0, count_right=0, count=0;

    /*bst bst_1;
    bst_1.root=NULL;
    bst bst_2;
    bst_2.root=NULL;
    */
    //string command = "command";

    while (cin >> tam){
    
    bst bst_1;
    bst_1.root=NULL;
    bst bst_2;
    bst_2.root=NULL;

    while (i < tam){

        cin >> num;
        bst_1.root = insert(bst_1.root, num); 
        i++;
    }

    while (k < tam){

        cin >> num;
        bst_2.root = insert(bst_2.root, num); 
        k++;

    }

    bst_1.root = part_1(bst_1.root, &count_left);
    bst_1.root = part_2(bst_1.root, bst_2.root, true, &count_left, &count_right);

    cout << count_left << " " << count_right << endl;
    
    print_posorder(bst_2.root, tam, &count);
    cout << endl;

    // falta a parte da arvore
    if (balance_factor(bst_2.root)==0){
        cout << "false" << endl;
    } else {
        cout << "true" << endl;
    }

    count_left=0;
    count_right=0;
    count=0;
    i=0;
    k=0;

    cout << endl;

    }
    return 0;
}
