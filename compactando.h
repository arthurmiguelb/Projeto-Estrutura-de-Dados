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

void enqueue(queue *fila, unsigned char byte, long long int f, node_arvore *left, node_arvore *right)

void ler_arquivo_original(FILE *pont, queue *fila)

void criar_primeira_arvore(queue *fila)

void contando(node_arvore *head)

void dicionario(node_arvore *head, hash *new_hash, unsigned short byte, int profundidade)

node_lista *cria_lista_invertida(node_lista *head, node_lista *fim, unsigned char byte)

unsigned char empurrando(unsigned char output, unsigned char aux)

void escreve_arvore(node_arvore *head, FILE *salvar)

void escreve(node_lista *head, node_arvore *cabeca_arvore, char arquivo[])

void compactar(hash *new_hash, char arquivo[], node_arvore *cabeca_arvore)

void converte_original_para_compactado(node_arvore *head, char arquivo[])