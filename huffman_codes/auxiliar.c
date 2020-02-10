#include "auxiliar.h"

void *pont_para_void(unsigned char item){
    unsigned char *pont = (unsigned char*) malloc(sizeof(unsigned char));
    *pont = item;    

    return (void*) pont;
}
node_lista *cria_lista_invertida(node_lista *head, node_lista *fim, void *byte){
    node_lista *novo_byte=(node_lista*)malloc(sizeof(node_lista));

    if(head==NULL){
        head=novo_byte;
        novo_byte->previous=NULL;
    } else {
        fim->next=novo_byte;
        novo_byte->previous=fim;
    }
    novo_byte->byte_comp=byte;
    novo_byte->next=NULL;
    return novo_byte; 
}

void binario(int num){
   int bin[8]; 
   int aux;
   for (aux = 7; aux >= 0; aux--)
   {
      if (num % 2 == 0)
         bin[aux] = 0;
      else
         bin[aux] = 1;
      num = num / 2;
   }

   for (aux = 0; aux < 8; aux++)
       printf("%d", bin[aux]);

   printf(" ");
} 

void enqueue(queue *fila, void *byte, long long int f, node_arvore *left, node_arvore *right){ 
    node_arvore *new_node=(node_arvore*)malloc(sizeof(node_arvore));
    new_node->freq=f;
    new_node->byte=byte;
    new_node->left=left;
    new_node->right=right;
    if(fila->head==NULL || f <= fila->head->freq){ 
        new_node->next =fila->head; 
        fila->head=new_node; 
    }
    else{ 
        node_arvore *current=fila->head; 
        while((current->next !=NULL) && (current->next->freq < f)){ 
            current=current->next; 
        }
        new_node->next=current->next; 
        current->next=new_node;
    }
}

int eh_folha(node_arvore *head){
    if(head->left == NULL && head->right == NULL) return 1;
    else return 0;
}

unsigned char conteudo(void *item){
    return (*((unsigned char*)item));
}