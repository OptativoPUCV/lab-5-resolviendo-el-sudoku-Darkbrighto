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
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
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


/*
2.Cree la función **int is_valid(Node * n)**, para validar si un estado/nodo es válido (cumple con las restricciones del problema). Debe validar que:

- No se repitan números en las filas
- No se repitan números en las columnas
- No se repitan números en las submatrices de 3x3

Si el estado es válido la función retorna 1, si no lo es retorna 0.
*/

int is_valid(Node* n){
  // 1. Verifica si el nodo es válido
    int i,j,k;
    // Se crean matrices para verificar si hay repetidos
    // en filas, columnas y submatrices
    int row[9][10]={0};
    int col[9][10]={0};
    int box[3][3][10]={0};
    // Se recorren las filas y columnas
    // y se verifica si hay repetidos
    // uso del doble for para recorrer filas y columnas
    // y un tercer for para recorrer los números
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j]!=0){
                k=n->sudo[i][j];
                if(row[i][k] || col[j][k] || box[i/3][j/3][k]){
                    return 0;
                }
                row[i][k]=1;
                col[j][k]=1;
                box[i/3][j/3][k]=1;
            }
        }
    }
    return 1;
}



/*
1.Cree una función que a partir de un nodo genere una **lista con los nodos adyacentes**:

    List* get_adj_nodes(Node* n){
      List* list=createList();
      return list;
    }
    }
*/

/*

List* createList();
void clean(List* list);
int is_empty(List* list);
void* front(List* list);
void* first(List* list);
void* next(List* list);
void* last(List* list);
void* prev(List* list);
void popFront(List* list);
void popBack(List* list);
void pushFront(List* list, void* data);
void pushBack(List* list, void* data);
void pushCurrent(List* list, void* data);
void popCurrent(List* list);
int get_size();

*/

// 3.Modifique la función *get_adj_nodes* para que sólo los nodos válidos sean retornados (use la función *is_valid*).

List* get_adj_nodes(Node* n){
    List* list=createList();
    Node* new;
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j]==0){
                for(int k=1;k<=9;k++){
                    new=copy(n);
                    new->sudo[i][j]=k;
                    // Verifica si el nuevo nodo es válido
                    // y lo agrega a la lista
                    if(is_valid(new)){
                        pushBack(list, new);
                    }
                }
            }
        }
    }
    return list;
}

/*
4.Implemente la función **int is_final(Node * n)**. Esta función retorna 1 si el nodo corresponde a un nodo final 
(es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.
*/
int is_final(Node* n){
    // Verifica si el nodo es final
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j]==0){
                return 0;
            }
        }
    }
    return 1;
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