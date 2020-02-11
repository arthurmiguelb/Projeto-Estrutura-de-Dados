#include "compress.h"


void ler_arquivo_original(FILE *pont, queue *fila){
    unsigned char byte;
    long long int frequencia[256]; 
    int i;
    fila->head=NULL;
    for(i=0;i<256;i++){
        frequencia[i]=0; 
    }

    while(fscanf(pont,"%c", &byte)!=EOF){ 
        frequencia[byte]++; 
    }
    for(i=0;i<256;i++){
        if(frequencia[i]!=0){
            enqueue(fila, pont_para_void(i), frequencia[i], NULL, NULL);
        }
    } 
    if(fila->head==NULL){
        printf("ERRO NA FORMAÇÃO DA FILA!\n");
    }
}

void criar_primeira_arvore(queue *fila){
    node_arvore *aux=fila->head;
    node_arvore *aux2=aux->next; 
    if(aux==NULL){
        printf("A FILA ESTA VAZIA\n");
        return;
    }
    if(aux2==NULL){ 
        return;
    }
    node_arvore *dequeued=aux;
    node_arvore *dequeued2=aux2;
    fila->head=aux2->next; 
    enqueue(fila,pont_para_void('*'), (aux->freq)+(aux2->freq), aux, aux2);
    dequeued->next=NULL;
    dequeued2->next=NULL;
    criar_primeira_arvore(fila);
}
int contando(node_arvore *head, int tamanho_da_arvore){ 
    if(head!=NULL){
        if((conteudo(head->byte)==92) || (conteudo(head->byte)) =='*'&& (eh_folha(head))  ){
            tamanho_da_arvore++;
        }
        tamanho_da_arvore++;
        tamanho_da_arvore=contando(head->left, tamanho_da_arvore);
        tamanho_da_arvore=contando(head->right, tamanho_da_arvore);
    }
    return tamanho_da_arvore;
}
void dicionario(node_arvore *head, array_comp *new_array_comp, unsigned short byte, int profundidade) {
    if(head!=NULL) {
        if(eh_folha(head)) {
            new_array_comp->compactado[(conteudo(head->byte))] = byte;
            new_array_comp->profundidade[(conteudo(head->byte))]=profundidade;
        }
        profundidade++;
        byte = byte << 1;
        dicionario(head->left, new_array_comp, byte, profundidade);
        byte++;
        dicionario(head->right, new_array_comp, byte, profundidade);
    }
}
unsigned char empurrando(unsigned char output, unsigned char aux){
    output = output << 1;
    return output | aux;
}
void escreve_arvore(node_arvore *head, FILE *salvar){
    unsigned char barra= 92;
    if(head!=NULL){
        if(conteudo(head->byte)==barra){
            fwrite(&barra, sizeof(unsigned char), 1, salvar);
        }
        else if(conteudo(head->byte) =='*' && eh_folha(head)){
            fwrite(&barra, sizeof(unsigned char), 1, salvar);
        }
        unsigned char aux_byte = (conteudo(head->byte));
        fwrite(&aux_byte, sizeof(char), 1, salvar);
        escreve_arvore(head->left, salvar);
        escreve_arvore(head->right, salvar);
    }
}
void escreve(node_lista *head, node_arvore *cabeca_arvore, char arquivo[], int tamanho_da_arvore, int lixo){
    char compactado[100];
    strcpy(compactado,arquivo);
    strcat(compactado,".huff");
    FILE *salvar= fopen(compactado, "wb");
    unsigned char cabecalho1, cabecalho2, aux = 0;

    cabecalho1= lixo<<5;
    aux = tamanho_da_arvore >> 8;
    cabecalho1 = (cabecalho1 | aux);
    cabecalho2 = tamanho_da_arvore;

    fwrite(&cabecalho1, sizeof(unsigned char), 1, salvar);
    fwrite(&cabecalho2, sizeof(unsigned char), 1, salvar);


    escreve_arvore(cabeca_arvore, salvar);
    while(head != NULL)
    {
        unsigned char aux_bytecomp = (conteudo(head->byte_comp));
        fwrite(&aux_bytecomp, sizeof(char), 1, salvar);
        head = head->next;
    }
    fclose(salvar);
}
void compactar(array_comp *new_array_comp, char arquivo[], node_arvore *cabeca_arvore, int tamanho_da_arvore){
    unsigned char input, output=0, aux;
    node_lista *head=NULL, *fim=NULL;
    int bits, posicao=0;
    FILE *pont2=fopen(arquivo, "rb");

    while(fscanf(pont2,"%c", &input)!=EOF){
        bits= new_array_comp->profundidade[input] - 1;
        while(bits>=0){
            if(posicao==8){
                fim=cria_lista_invertida(head,fim,pont_para_void(output));
                if(head==NULL){
                    head = fim;
                }
                posicao=0;
                output=0;
            }
            aux = new_array_comp->compactado[input] >> bits;
            output=empurrando(output, aux);
            posicao++;
            bits--;
        }
    }
    int lixo=8-posicao;
    output=output<<lixo;
    fim=cria_lista_invertida(head,fim,pont_para_void(output));
    if(head==NULL){
        head = fim;
    }
    escreve(head, cabeca_arvore, arquivo, tamanho_da_arvore, lixo);
    fclose(pont2);

}
void converte_original_para_compactado(node_arvore *head, char arquivo[]){
    array_comp *new_array_comp = (array_comp*)malloc(sizeof(array_comp));
    int i;
    for(i=0;i<256;i++){
        new_array_comp->profundidade[i]=0;
    }
    node_arvore *aux=head;
    int tamanho_da_arvore;
    tamanho_da_arvore=contando(aux,0);
    aux=head;
    dicionario(aux, new_array_comp,0, 0);
    compactar(new_array_comp, arquivo, head, tamanho_da_arvore);
}