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
  // Recorre el sudoku buscando un 0
  // y valida que no se repitan números en las filas, columnas y submatrices
  // de 3x3
  // y retorna 1 si es válido o 0 si no lo es


    int i,j;
  // define row, col y box como arreglos de 10 elementos
    // para almacenar los números del 1 al 9
    // y un elemento adicional para el 0
    // inicializa los arreglos en 0
    int row[10], col[10], box[10];
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            row[j]=0;
            col[j]=0;
            box[j]=0;
        }
        for(j=0;j<9;j++){
            // si n->sudo[i][j] es diferente de 0
            // verifica si ya existe en la fila
            if(n->sudo[i][j]!=0){
                if(row[n->sudo[i][j]]==1)
                    return 0;
                row[n->sudo[i][j]]=1;
            }
            if(n->sudo[j][i]!=0){
                if(col[n->sudo[j][i]]==1)
                    return 0;
                col[n->sudo[j][i]]=1;
            }
            if(n->sudo[(i/3)*3+(j/3)][(i%3)*3+(j%3)]!=0){
                if(box[n->sudo[(i/3)*3+(j/3)][(i%3)*3+(j%3)]]==1)
                    return 0;
                box[n->sudo[(i/3)*3+(j/3)][(i%3)*3+(j%3)]]=1;
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
                    if(is_valid(new)){
                        pushBack(list, new);
                    }
                }
            }
        }
    }
    return list;
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