#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct b_arv b_arv;
typedef struct lista lista;
struct b_arv{
	int value;
	b_arv *left;
	b_arv *right;
};
struct lista{
	int value;
	lista *next;
};
//Creates the new tree nodes.
b_arv* create_new_node(int value){
	b_arv *new_node = (b_arv *) malloc(sizeof(b_arv ));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->value = value;
	return new_node;
}
//Build the tree randomly.
b_arv* construct(b_arv *no, int num){
	if(no == NULL){
		no = create_new_node(num); 
	}
	else if(num < no->value){
		if(no->left != NULL)
			construct(no->left, num);
		else
			no->left = create_new_node(num);
	}
	else{
		if(no->right != NULL)
			construct(no->right, num);
		else
			no->right = create_new_node(num);
	}
	return no;
}
//Maps the tree to the desired node;
void map(b_arv *no, int num, int *resul){
	if(no == NULL){
		printf("O elemento não existe na arvore");
	}
	else{

		if(num == no->value){
			printf("Existe o elemento\n");
			*resul += 1;
		}
		else if(num < no->value){
			*resul += 1;
			map(no->left, num, resul);
		}
		else if(num > no->value){
			*resul +=1;
			map(no->right, num, resul);
		}
	}
}
//Handles the tree search.
void busca_arv(b_arv *no, int num, FILE *pont)
{
	int resul = 0;
	map(no, num, &resul);
	printf("num = %d\ncounter = %d\n\n", num, resul);
	fprintf(pont, "%d,%d\n", num, resul);
	//printf("comp: %d\n\n", x);
}
void print(b_arv *no)
{
	if(no != NULL){
		printf("%d ", no->value);
		print(no->left);
		print(no->right);
	}
}
//Build the list randomly.
lista* construct_list(lista *list, int value)
{
	lista *new_node = (lista *) malloc(sizeof(lista ));
	new_node->value = value;
	new_node->next = list;
	return new_node;
}
//Handles the list search.
void busca_list(lista *list, int item, FILE *pont2)
{
	lista *aux = list;
	int comp=0, i=0;
	while(aux != NULL){
		comp++;
		if(aux->value == item){
			i=1;
			break;
		}
		aux=aux->next;
	}
	printf("item: %d\n", item);
	printf("comp: %d\n\n", comp);
	fprintf(pont2, "%d,%d\n", item, comp);		
	// if(i) printf("O elemento existe na lista\ncomp: %d\n", comp);
	// else printf("O elemento nao existe na lista\ncomp: %d\n", comp);
}
void printlist(lista *list){

	while(list != NULL){
		printf("%d\n", list->value);
		list = list->next;
	}
}
int main()
{
	b_arv *no = NULL;
	lista *list = NULL;
	FILE *pont = fopen("abb.csv", "a+");
	FILE *pont2 = fopen("lista.csv", "a+");
	int x,i;
	srand((unsigned) time(NULL));
	for(i = 0; i < 50000; i++){
		x = 0 + ( rand() % 10000 );
		no = construct(no, x);
		list = construct_list(list, x);
	}
	for(i =0; i< 50000;i++){
		x = 0 + ( rand() % 10000 );
		busca_arv(no, x, pont);
		busca_list(list, x, pont2);
	}
	fclose(pont);
	fclose(pont2);
	return 0;
}
