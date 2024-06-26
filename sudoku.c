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

int is_valid(Node* n) //Funcion que valida si el sudoku es valido
{
   int i, j, k, cont;
   for (i = 0 ; i < 9 ; i++) //Filas
   {
      for (j = 0 ; j < 9 ; j++)//Columnas
      {
         if (n->sudo[i][j] != 0) //
         {
            cont = 0;
            for (k = 0 ; k < 9 ; k++)
            {
               if (n->sudo[i][j] == n->sudo[i][k])
               {
                  cont++;
               }
               if (cont > 1)
               {
                  return 0;
               }
            }
            cont = 0;
            for (k = 0 ; k < 9 ; k++)
            {
               if (n->sudo[i][j] == n->sudo[k][j]) 
               {
                  cont++;
               }
               if (cont > 1)
               {
                  return 0;
               }
            }
            cont = 0;
            for (k = 0 ; k < 9 ; k++)
            {
               if (n->sudo[i][j] == n->sudo[i/3*3 + k/3][j/3*3 + k%3]) 
               {
                  cont++;
               }
               if (cont > 1)
               {
                  return 0;
               }
            }
         }
      }
   }
   return 1;
}


List* get_adj_nodes(Node* n) //Funcion que obtiene los nodos adyacentes
{
   List* list = createList(); //Crea una lista vacia
   int i, j;
   for (i = 0 ; i < 9 ; i++) //Filas
   {
      for (j = 0 ; j < 9 ; j++) //Columnas
      {
         if (n->sudo[i][j] == 0) 
         {
            int k;
            for (k = 1 ; k <= 9 ; k++) 
            {
               Node* adj = copy(n);
               adj->sudo[i][j] = k;
               if (is_valid(adj))
               {
                  pushBack(list, adj); 
               }
            }
            return list;
         }
      }
   }
   return list;
}


int is_final(Node* n)
{
   int i, j;
   for (i = 0 ; i < 9 ; i++)
   {
      for (j = 0 ; j < 9 ; j++)
      {
         if (n->sudo[i][j] == 0)
         {
            return 0;
         }
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont) 
{
    Stack* S = createStack();
    push(S, initial);
    while (!is_empty(S)) 
    {
        Node* n = top(S);
        pop(S);
        if (is_final(n)) 
        {
           return n;
        }
        List* list = get_adj_nodes(n);
        Node* adj;
        while ((adj = first(list)) != NULL) 
        {
            push(S, adj);
            popFront(list);
        }
        if (cont != NULL) (*cont)++;
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