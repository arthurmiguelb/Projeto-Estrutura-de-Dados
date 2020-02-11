#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "auxiliar.h"

void teste_pont_para_void(){
    unsigned char *pont = (unsigned char*) malloc(sizeof(unsigned char));
    int item=90;
    *pont = item;  

    CU_ASSERT(pont!=NULL);
    CU_ASSERT_EQUAL(conteudo(pont),90);
    
    void *aux=pont_para_void(90);

    CU_ASSERT_EQUAL(conteudo(pont),conteudo(aux));
}

void teste_enqueue(){ 
    node_arvore *new_node=(node_arvore*)malloc(sizeof(node_arvore));
    new_node->freq=15;
    new_node->byte=pont_para_void('*');
    new_node->left=NULL;
    new_node->right=NULL;

    queue *test = (queue*)malloc(sizeof(queue));
    test->head=NULL;
    enqueue(test,pont_para_void('*'), 15, NULL, NULL);

    CU_ASSERT(new_node!=NULL);
    
    
    CU_ASSERT_EQUAL(new_node->freq, 15);
    CU_ASSERT_EQUAL(conteudo(new_node->byte),'*');
    CU_ASSERT(new_node->left==NULL);
    CU_ASSERT(new_node->right==NULL);
    CU_ASSERT_EQUAL(new_node->freq, test->head->freq);
    CU_ASSERT_EQUAL(conteudo(new_node->byte), conteudo(test->head->byte));
}

void teste_cria_lista_invertida(){
    node_lista *novo_byte=(node_lista*)malloc(sizeof(node_lista));
    novo_byte->byte_comp=pont_para_void('*');
    novo_byte->next=NULL;
    novo_byte->previous=NULL;

    CU_ASSERT(novo_byte!=NULL);
    CU_ASSERT_EQUAL(conteudo(novo_byte->byte_comp),'*');
    CU_ASSERT(novo_byte->previous==NULL);
    CU_ASSERT(novo_byte->next==NULL);

    node_lista *teste_head=NULL;
    node_lista *teste_fim=NULL;
    CU_ASSERT_PTR_EQUAL(teste_head,teste_fim);
    teste_fim = cria_lista_invertida(teste_head, teste_fim,pont_para_void('*'));
    CU_ASSERT_EQUAL(conteudo(novo_byte->byte_comp),conteudo(teste_fim->byte_comp));
    CU_ASSERT(teste_fim->next==NULL);
    CU_ASSERT(teste_fim->previous==NULL);
    CU_ASSERT_PTR_EQUAL(teste_fim->next,teste_fim->previous);
    
}

void teste_eh_folha(){
    node_arvore *head=(node_arvore*)malloc(sizeof(node_arvore));
    head->byte=pont_para_void(10);
    head->left=NULL;
    head->right=NULL;

    CU_ASSERT(head!=NULL);
    CU_ASSERT_EQUAL(conteudo(head->byte),10);
    CU_ASSERT(head->right==NULL);
    CU_ASSERT(head->left==NULL);

    int teste = eh_folha(head);
    CU_ASSERT_EQUAL(teste,1);
}

void teste_conteudo(){
    void *item = (char*)malloc(sizeof(char));
    item=pont_para_void('X');

    CU_ASSERT(item!=NULL);
    CU_ASSERT_EQUAL(conteudo(item),'X');
}

int main()
{
	// Registro no CUnit
    srand(time(NULL));
    CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

   // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
   // Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL

	//CU_basic_set_mode(CU_BRM_VERBOSE);

	// Add a suite to the registry

	pSuite = CU_add_suite("TEST", 0, 0);

	// Always check if add was successful

	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Add the test to the suite

	if (NULL == CU_add_test(pSuite, "test - 1", teste_enqueue)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "test - 2", teste_cria_lista_invertida)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "test - 3", teste_pont_para_void)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
    if (NULL == CU_add_test(pSuite, "test - 4", teste_conteudo)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
    if (NULL == CU_add_test(pSuite, "test - 5", teste_eh_folha)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// Run the tests and show the run summary
	CU_basic_run_tests();
    CU_cleanup_registry();
	return CU_get_error();
}
