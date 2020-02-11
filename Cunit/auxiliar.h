#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef AUXILIAR_H
#define AUXILIAR_H

typedef struct queue queue;
typedef struct node_arvore node_arvore;
typedef struct fake_hash fake_hash;
typedef struct node_lista node_lista;


struct node_arvore // estrutura onde alocamos o nó para a criação da fila e logo em seguida para a árvore
{
	void *byte;
	long long int freq; // a frequencia em lld, pois em casos de foto e videos a frequencias do caracteres será bem grande
	node_arvore *next;
	node_arvore *left; // ponteiro para esquerda para a criação da arvore
	node_arvore *right; // ponteiro para a direita para a criação da arvore

};

struct node_lista
{
    int bit;
    void *byte_comp;
    node_lista *next;
    node_lista *previous;
}; 

struct fake_hash
{
    unsigned short compactado[256];
    unsigned short profundidade[256];
};

struct queue
{
	node_arvore *head;
};

node_lista *cria_lista_invertida(node_lista *head, node_lista *fim, void *byte);

void binario(int num);

#endif