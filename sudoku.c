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
  int i,j,k,l,m,p;
  for(i=0;i<9;i++) {
    for(j=0;j<9;j++) {
      if(n->sudo[i][j]==0) continue;
      for(k=0;k<9;k++) {
          if(n->sudo[i][j]==n->sudo[i][k]) {
            if(j!=k) return 0;
          }
          if(n->sudo[i][j]==n->sudo[k][j]) {
            if(i!=k) return 0;
          }
      }
      k=(i/3)*3+j/3;
      for(p=0;p<9;p++){
        l=3*(k/3) + (p/3);
        m=3*(k%3) + (p%3);
        if(n->sudo[i][j]==n->sudo[l][m]) {
          if(i!=l && j!=m) return 0;
        }
      }
    }
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
          n->sudo[i][j]=0;
          return lista;
        }
      }
    }
    return lista;
}


int is_final(Node* n){
  int i,j;
  for(i=0;i<9;i++) {
    for(j=0;j<9;j++) {
      if(n->sudo[i][j]==0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Node *n; 
  Node *adj;
  Stack *S=createStack();
  push(S,initial);
  while(!is_empty(S)) {
    n=top(S); 
    pop(S);
    if(is_final(n)) {
      return n;
    }else continue;
    List* l=get_adj_nodes(n);
    adj=first(l);
    while(adj) {
      push(S, adj);
      adj=next(l);
    }
    free(n);
  }
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