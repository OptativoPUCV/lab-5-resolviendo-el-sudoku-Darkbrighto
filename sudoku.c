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

/*
**¿Cómo recorrer las submatrices de 3x3?**
El siguiente código se puede usar para recorrer los elementos de una sumbatriz k (por ejemplo k=4):

    int k=4,p; 
    for(p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        printf("%d ",nodo->sudo[i][j]);
        if(p%3 == 2) printf("\n");
    }
*/

int is_valid(Node* n){
    int i,j,k;
    // Verifica filas
    for(i=0;i<9;i++){
        int row[10]={0};
        for(j=0;j<9;j++){
            if(n->sudo[i][j]!=0){
                if(row[n->sudo[i][j]]==1){
                    return 0;
                }
                row[n->sudo[i][j]]=1;
            }
        }
    }

    // Verifica columnas
    for(i=0;i<9;i++){
        int col[10]={0};
        for(j=0;j<9;j++){
            if(n->sudo[j][i]!=0){
                if(col[n->sudo[j][i]]==1){
                    return 0;
                }
                col[n->sudo[j][i]]=1;
            }
        }
    }

    // Verifica submatrices de 3x3
    for(k=0;k<9;k++){
        int sub[10]={0};
        for(int p=0;p<9;p++){
            int i=3*(k/3) + (p/3) ;
            int j=3*(k%3) + (p%3) ;
            if(n->sudo[i][j]!=0){
                if(sub[n->sudo[i][j]]==1){
                    return 0;
                }
                sub[n->sudo[i][j]]=1;
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
    List* list = createList();
    Node* new;
    int i, j;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {
                    new = copy(n);
                    new->sudo[i][j] = k;
                    if (is_valid(new)) {
                        pushBack(list, new);
                    }
                }
                // detener la función tras procesar la primera celda vacía
                return list;
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

/*
5.Implemente la función Node* DFS(Node* n, int* cont). Esta función realiza una búsqueda en profundidad a partir del nodo n. El algoritmo es el siguiente:

1. Cree un stack S (pila) e inserte el nodo.
2. Mientras el stack S no se encuentre vacío:

   a) Saque y elimine el primer nodo de S.
   
   b) Verifique si corresponde a un estado final, si es así retorne el nodo.
   
   c) Obtenga la lista de nodos adyacentes al nodo.
   
   d) Agregue los nodos de la lista (uno por uno) al stack S.
   
   e) Libere la memoria usada por el nodo.
   
3. Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.

Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.
*/
Node* DFS(Node* initial, int* cont){
    List* stack = createList();
    pushBack(stack, initial);
    Node* current;

    while (!is_empty(stack)) {
        current = front(stack);
        popFront(stack);
        (*cont)++;

        if (is_final(current)) {
            clean(stack);
            return current;
        }

        List* adj_nodes = get_adj_nodes(current);
        Node* node;
        while (!is_empty(adj_nodes)) {
            node = front(adj_nodes);
            popFront(adj_nodes);
            pushBack(stack, node);
        }
        clean(adj_nodes);
        free(current);
    }

    clean(stack);
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