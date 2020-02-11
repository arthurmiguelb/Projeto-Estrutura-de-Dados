#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "auxiliar.h"


#ifndef COMPRESS_H
#define COMPRESS_H

void ler_arquivo_original(FILE *pont, queue *fila);

void criar_primeira_arvore(queue *fila);

int contando(node_arvore *head, int tamanho_da_arvore);

void dicionario(node_arvore *head, array_comp *new_array_comp, unsigned short byte, int profundidade);

unsigned char empurrando(unsigned char output, unsigned char aux);

void escreve(node_lista *head, node_arvore *cabeca_arvore, char arquivo[], int tamanho_da_arvore, int lixo);

void compactar(array_comp *new_array_comp, char arquivo[], node_arvore *cabeca_arvore, int tamanho_da_arvore);

void converte_original_para_compactado(node_arvore *head, char arquivo[]);

#endif