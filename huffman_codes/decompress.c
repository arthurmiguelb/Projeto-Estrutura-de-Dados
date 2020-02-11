#include "decompress.h"


int pre=0;

void descompactar(node_arvore *head_arv, node_lista *head_list, node_lista *fim_list, int descartar, FILE *pont, char arquivo[]){
    int i=7, folha=0, j;
    unsigned char bit, aux_byte;
    int tamanho =strlen(arquivo);
    char descompactado[tamanho-5];

    for(j=0; j<tamanho-5;j++){
        descompactado[j]=arquivo[j];
    }
    descompactado[j] = '\0';

    FILE *descomp=fopen(descompactado, "wb");

    node_arvore *aux=head_arv;
    while(head_list!=NULL){
        i=7;
        int limite;

        if(head_list==fim_list){
            limite=descartar;
        }else{
            limite=0;
        }
        
        while(i>=limite){
            if(folha==1){
                folha=0;
                aux=head_arv;
            }
            
            bit=(conteudo(head_list->byte_comp)) >> i;

            if(bit%2 != 0){ 
                aux=aux->right;
                if(eh_folha(aux)){
                    folha=1;
                    aux_byte = (conteudo(aux->byte));
                    fwrite(&aux_byte,sizeof(unsigned char), 1, descomp);
                }
            }else{ 
                aux=aux->left;
                if(eh_folha(aux)){
                    folha=1;
                    aux_byte = (conteudo(aux->byte));
                    fwrite(&aux_byte,sizeof(unsigned char), 1, descomp);
                }
            }
            i--;
        }
        
        head_list=head_list->next;
    }
    fclose(descomp);
}
node_arvore *cria_arv_pre(unsigned char arv[], int tam_arvore, node_arvore *head_descomp){
    node_arvore *novo_no = (node_arvore*)malloc(sizeof(node_arvore));
    if(head_descomp==NULL){
        head_descomp = novo_no;
    }
    if(arv[pre]=='*'){ 
        novo_no->byte = pont_para_void('*');
        novo_no->left = NULL;
        novo_no->right = NULL;
        pre++;
        novo_no->left = cria_arv_pre(arv, tam_arvore, head_descomp);
        novo_no->right = cria_arv_pre(arv, tam_arvore, head_descomp);
    }
    else{
        if(arv[pre]==92) pre++;
        novo_no->byte = pont_para_void(arv[pre]);
        novo_no->left = NULL;
        novo_no->right = NULL;
        pre++;
    }
    return novo_no;
} 
void lendo_cabecalho(FILE *pont, char arquivo[]){
    unsigned char cabecalho1, cabecalho2;
    short int descartar, tam_arvore;
    int j;

    fscanf(pont,"%c", &cabecalho1);
    fscanf(pont,"%c", &cabecalho2);


    descartar = cabecalho1 >> 5;
    cabecalho1=cabecalho1<<3;
    cabecalho1=cabecalho1>>3;

    tam_arvore = ((cabecalho1)*pow(2,8)) + (cabecalho2);

    unsigned char arv[tam_arvore];

    for(j=0; j<tam_arvore; j++){
        fscanf(pont,"%c", &arv[j]);
    }
    
    node_arvore *head_descomp=NULL;
    head_descomp = cria_arv_pre(arv, tam_arvore, head_descomp);  

    unsigned char lendo;

    node_lista *arq_comp=NULL, *fim_comp=NULL;

    while(fscanf(pont,"%c", &lendo)!= EOF){
        fim_comp=cria_lista_invertida(arq_comp,fim_comp,pont_para_void(lendo));
        if(arq_comp==NULL){
            arq_comp=fim_comp;
        }
    }
    descompactar(head_descomp, arq_comp, fim_comp, descartar, pont, arquivo);
}