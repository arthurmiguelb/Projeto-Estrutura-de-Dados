#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "auxiliar.h"

#ifndef DESCOMPACTANDO_H
#define DESCOMPACTANDO_H


void descompactar(node_arvore *head_arv, node_lista *head_list, node_lista *fim_list, int descartar, FILE *pont, char arquivo[]);

node_arvore *cria_arv_pre(unsigned char arv[], int tam_arvore, node_arvore *head_descomp);

void lendo_cabecalho(FILE *pont, char arquivo[]);

#endif