#include "auxiliar.h"
void *pont_para_void(unsigned char item)
{
    unsigned char *pointer = (unsigned char*) malloc(sizeof(unsigned char));
    *pointer = item;    
    return (void*) pointer;
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