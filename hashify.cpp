#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct music {

    int key;
    string name;
    int time;
    int reproduction;

};

void init_playlist(int tam, music *playlist){

    for (int i=0; i < tam; i++){
        playlist[i].key=-1;
        playlist[i].name=" ";
        playlist[i].reproduction=-1;
        playlist[i].time=-1;
        
    }
}

int key(music *playlist){

    int keyy, val;

    int n = (playlist->name).size();

    playlist->key=0;
    keyy=playlist->key;

    for(int i =0; i<n; i++){

        val= (playlist->name[i]*i);
        keyy= keyy + val;
    }
    
    return keyy;
}

int hashfunction(int keyy, int tam){
    return keyy % tam;
}

void add_playlist(int *total, music *playlist, int tam, music *song){

    int k = key(song);
    song->key = k;

    int index = hashfunction(k, tam);
    int i = 0,pos=0, aux; 

    aux = index % tam;
    for(i=0; i<tam; i++){

        if (playlist[aux].name == " "){
            playlist[aux] = *song;
            i=tam;

        } else {
            pos++;
            aux=(index+pos)%tam;
            if(aux>=tam){
                aux=0;
                pos=0;
            }
            
        }
    }
    cout << playlist[aux].name << " " << aux << endl;

    (*total)++;
}

void add_rehashing(music *playlist, music song, int tam){

    int index = hashfunction(song.key, tam);

    int i = 0,pos=0, aux; 

    aux = index % tam;
    for(i=0; i<tam; i++){

        if (playlist[aux].name == " "){
            playlist[aux] = song;
            i=tam;

        } else {
            pos++;
            aux=(index+pos)%tam;
            if(aux>=tam){
                aux=0;
                pos=0;
            }
            
        }
    }
   
}

music *rehashing(music *playlist, int *tam){
    
    int temp = *tam;
    *tam=(*tam*2)+1;
    music *aux = new music[*tam];
    init_playlist(*tam, aux);

    int i=0;
    while (i<temp) {
        if(playlist[i].name != " "){
            add_rehashing(aux, playlist[i], *tam);
        }
        i++;
    }
    delete [] playlist;
   
    return aux;
}

void play(music *playlist, int tam, string name){

    music *nova = new music;
    nova->name = name; nova->reproduction = 0; 

    int k = key(nova);

    int index = hashfunction(k, tam);
    int i = 0,pos=0, aux; 

    aux = index % tam;
    for(i=0; i<tam; i++){
     
        if (playlist[aux].name == name){
            playlist[aux].reproduction += playlist[aux].time;
            i=tam;

        } else {
            pos++;
            aux=(index+pos)%tam;
            if(aux>=tam){
                aux=0;
                pos=0;
            }
            
        }
    }
    cout << playlist[aux].name << " " << playlist[aux].reproduction << endl;
}

void time(music *playlist, int tam, string name){

    music *nova = new music;
    nova->name = name;

    int k = key(nova);

    int index = hashfunction(k, tam);
    int i = 0,pos=0, aux; 

    aux = index % tam;
    for(i=0; i<tam; i++){
        
        if (playlist[aux].name == name){
            i=tam;
        } else {
            pos++;
            aux=(index+pos)%tam;
            if(aux>=tam){
                aux=0;
                pos=0;
            }
            
        }
    }
    cout << playlist[aux].name << " " << playlist[aux].reproduction << endl;
}

int main(){

    int tam, total=0, duraction, size, pos;

    string name;

    string command = "mila";

    cin >> tam;

    music *playlist= new music[tam];

    init_playlist (tam, playlist);

    music song;

    while(command != "END"){
        cin >> command;

        if (command == "ADD"){
    
            cin >> song.name >> song.time;

            add_playlist(&total,playlist,tam,&song);

            if(tam%2 == 0){
                if(total >= (int) tam*0.5){
                    playlist = rehashing(playlist, &tam);
                }
            }
            else{
                if(total > (int) tam*0.5){
                    playlist = rehashing(playlist, &tam);
                }
            } 
           
        } 
        else if (command == "PLAY"){

            cin >> song.name;
            play(playlist, tam, song.name);

        } 
        else if (command == "TIME"){

            cin >> song.name;
            time(playlist, tam, song.name);
        }
    }
    return 0;
}