#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct queue queue;
typedef struct node_arvore node_arvore;
typedef struct hash hash;
typedef struct node_lista node_lista;



struct queue
{
	node_arvore *head;
};

struct node_arvore // estrutura onde alocamos o nó para a criação da fila e logo em seguida para a árvore
{
	unsigned char  byte;
	long long int freq; // a frequencia em lld, pois em casos de foto e videos a frequencias do caracteres será bem grande
	node_arvore *next;
	node_arvore *left; // ponteiro para esquerda para a criação da arvore
	node_arvore *right; // ponteiro para a direita para a criação da arvore

};

struct node_lista
{
    int bit;
    unsigned char byte_comp;
    node_lista *next;
    node_lista *previous;
}; //tirar dps

struct hash
{
    unsigned short compactado[256];
    unsigned short profundidade[256];
    node_lista *head_hash[256]; //tirar dps
};


void descompactar(node_arvore *head_arv, node_lista *head_list, node_lista *fim_list, int descartar, FILE *pont, char arquivo[])

node_arvore *cria_arv_pre(unsigned char arv[], int tam_arvore, node_arvore *head_descomp)

node_lista *cria_lista_invertida(node_lista *head, node_lista *fim, unsigned char byte)

void lendo_cabecalho(FILE *pont, char arquivo[])