#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          fscanf (file, "%d", &n->sudo[i][j]);
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i,j,k;
  for(i=0;i<9;i++) {
    for(j=0;j<9;j++) {
      for(k=0;k<9;k++) {
          if(n->sudo[i][j]==n->sudo[i][k]) {
            if(j!=k) return 1;
          }
          if(n->sudo[i][j]==n->sudo[k][j]) {
            if(i!=k) return 1;
          }
      }
    }
  }
  int p; 
  k=4;
  for(p=0;p<9;p++){
    int i=3*(k/3) + (p/3) ;
    int j=3*(k%3) + (p%3) ;
    printf("%d ",n->sudo[i][j]);
    if(p%3 == 2) printf("\n");
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    int i,j,num;
    List* lista=createList();
    for(i=0;i<9;i++) {
      for(j=0;j<9;j++) {
        if(n->sudo[i][j]==0) {
          for(num=1;num<10;num++) {
            n->sudo[i][j]=num;
            if(is_valid(n)) {
              Node* nuevo=copy(n);
              pushBack(lista,nuevo);
            }
          }
          n->sudo[i][j]=num;
          return lista;
        }
      }
    }
    return lista;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/