#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned char asterisco = '*';
typedef struct queue queue;
typedef struct node_arvore node_arvore;
typedef struct hash hash;
typedef struct node_lista node_lista; 
int pre=0;
struct queue
{
	node_arvore *head;
};
struct node_arvore 
{
	unsigned char  byte;
	long long int freq; 
	node_arvore *next;
	node_arvore *left; 
	node_arvore *right;
};
struct node_lista
{
    int bit;
    unsigned char byte_comp;
    node_lista *next;
    node_lista *previous;
}; 
struct hash
{
    unsigned short compactado[256];
    unsigned short profundidade[256];
    node_lista *head_hash[256];
};
node_lista *cria_lista_invertida(node_lista *head, node_lista *fim, unsigned char byte){
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
int contando(node_arvore *head, int tamanho_da_arvore){ 
    if(head!=NULL){
        if((head->byte=='*'&&head->left==NULL&&head->right==NULL) || head->byte==92){ //eh folha
            tamanho_da_arvore++;
        }
        tamanho_da_arvore++;
        tamanho_da_arvore=contando(head->left, tamanho_da_arvore);
        tamanho_da_arvore=contando(head->right, tamanho_da_arvore);
    }
    return tamanho_da_arvore;
}
void para_arvores(node_arvore *head){ 
    if(head!=NULL){
        //printf("%c", head->byte);
        para_arvores(head->left);
        para_arvores(head->right);
    }
}
void escreve_arvore(node_arvore *head, FILE *salvar){
    unsigned char barra= 92;
    if(head!=NULL){
        if(head->byte==92){
            fwrite(&barra, sizeof(unsigned char), 1, salvar);
        }
        else if(head->byte=='*' && head->left==NULL && head->right==NULL){
            fwrite(&barra, sizeof(unsigned char), 1, salvar);
        }
        fwrite(&head->byte, sizeof(char), 1, salvar);
        escreve_arvore(head->left, salvar);
        escreve_arvore(head->right, salvar);
    }
}
void enqueue(queue *fila, unsigned char byte, long long int f, node_arvore *left, node_arvore *right){
    node_arvore *new_node=(node_arvore*)malloc(sizeof(node_arvore));
    new_node-> freq=f;
    new_node->byte=byte;
    new_node->left=left;
    new_node->right=right;
    if(fila->head==NULL || f <= fila->head->freq){
        new_node->next =fila->head;
        fila->head=new_node; 
    }
    else{ 
        node_arvore *current=fila->head; 
        while((current->next !=NULL) && (current->next->freq < f)){ 
            current=current->next;
        }
        new_node->next=current->next;
        current->next=new_node;
    }
}
void ler_arquivo_original(FILE *pont, queue *fila){
    unsigned char byte;
    long long int frequencia[256]; 
    long long int total=0;
    int i;
    fila->head=NULL;
    for(i=0;i<256;i++){
        frequencia[i]=0; 
    }
    i=0;
    while(fscanf(pont,"%c", &byte)!=EOF){ 
        frequencia[byte]++;
    }
    for(i=0;i<256;i++){
        if(frequencia[i]!=0){
                enqueue(fila, i, frequencia[i], NULL, NULL);
        }
    }
    if(fila->head==NULL){
        printf("ERRO NA FORMAÇÃO DA FILA!\n");
    }
    node_arvore *aux=fila->head;

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
    fila->head=aux2->next; 
    enqueue(fila,'*', (aux->freq)+(aux2->freq), aux, aux2);
    criar_primeira_arvore(fila);
}
void dicionario(node_arvore *head, hash *new_hash, unsigned short byte, int profundidade) {
    if(head!=NULL) {
        if (head->left==NULL && head->right==NULL) {
            new_hash->compactado[head->byte] = byte;
            new_hash->profundidade[head->byte]=profundidade;
        }
        profundidade++;
        byte = byte << 1;
        dicionario(head->left, new_hash, byte, profundidade);
        byte++;
        dicionario(head->right, new_hash, byte, profundidade);
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
    printf("TAMANHO DA ARVORE: %d\n", tamanho_da_arvore);
    escreve_arvore(cabeca_arvore, salvar);
    while(head != NULL)
    {
        fwrite(&head->byte_comp, sizeof(char), 1, salvar);
        head = head->next;
    }
    fclose(salvar);
}
unsigned char empurrando(unsigned char output, unsigned char aux){
    output = output << 1;
    return output | aux;
}
void compactar(hash *new_hash, char arquivo[], node_arvore *cabeca_arvore, int tamanho_da_arvore){
    unsigned char input, output=0, aux;
    node_lista *head=NULL, *fim=NULL;
    int bits, posicao=0; 
    FILE *pont2=fopen(arquivo, "rb");
    while(fscanf(pont2,"%c", &input)!=EOF){
        bits= new_hash->profundidade[input] - 1;
        while(bits>=0){
            if(posicao==8){
                fim=cria_lista_invertida(head,fim,output);
                if(head==NULL){
                    head = fim;
                }              
                posicao=0;
                output=0;
            }
            aux = new_hash->compactado[input] >> bits;
            output=empurrando(output, aux);
            posicao++;
            bits--;
        }
    }
        int lixo=8-posicao;
        output=output<<lixo;
        fim=cria_lista_invertida(head,fim,output);
        if(head==NULL){
            head = fim;
        }
    escreve(head, cabeca_arvore, arquivo, tamanho_da_arvore, lixo);
    fclose(pont2);
}
void converte_original_para_compactado(node_arvore *head, char arquivo[]){
    hash *new_hash = (hash*)malloc(sizeof(hash));
    int i;
    for(i=0;i<256;i++){
        new_hash->head_hash[i]=NULL;
        new_hash->profundidade[i]=0;
    }
    node_lista *ajuda=NULL;
    node_lista *fim=NULL;
    node_arvore *aux=head;
    node_arvore *aux2=head;
    int tamanho_da_arvore;
    tamanho_da_arvore=contando(aux2,0);
    dicionario(aux, new_hash,0, 0);
    for(i=0;i<256;i++){
        if(new_hash->profundidade[i]){
        }
    }
    compactar(new_hash, arquivo, head, tamanho_da_arvore);
}
node_arvore *cria_arv_pre(unsigned char arv[], int tam_arvore, node_arvore *head_descomp){ //tirar o tam_arvore
    node_arvore *novo_no = (node_arvore*)malloc(sizeof(node_arvore));
    if(head_descomp==NULL){
        head_descomp = novo_no;
    }
    if(arv[pre]==asterisco){
        novo_no->byte = asterisco;
        novo_no->left = NULL;
        novo_no->right = NULL;
        pre++;
        novo_no->left = cria_arv_pre(arv, tam_arvore, head_descomp);
        novo_no->right = cria_arv_pre(arv, tam_arvore, head_descomp);
    }
    else if(arv[pre]==92){
        pre++;
        novo_no->byte = arv[pre];
        novo_no->left = NULL;
        novo_no->right = NULL;
        pre++;
    }
    else{
        novo_no->byte = arv[pre];
        novo_no->left = NULL;
        novo_no->right = NULL;
        pre++;
    }
    return novo_no;
} 
void descompactar(node_arvore *head_arv, node_lista *head_list, node_lista *fim_list, int descartar, FILE *pont, char arquivo[]){
    int i=7, folha=0;
    unsigned char bit;
    int tamanho =strlen(arquivo);
    char descompactado[tamanho-5];
    int j;
    for(j=0; j<tamanho-5;j++){
        descompactado[j]=arquivo[j];
    }
    descompactado[j] = '\0';
    FILE *descomp=fopen(descompactado, "wb");
    node_arvore *aux=head_arv;
    while(head_list!=NULL){
        i=7;
        if(head_list==fim_list){ 
            while(i>=descartar){
                if(folha==1){
                    folha=0;
                    aux=head_arv;
                }
                bit=head_list->byte_comp >> i;
                printf("'%d' ", bit);

                if(bit%2 != 0){ 
                    aux=aux->right;
                    if(aux->left==NULL && aux->right==NULL){
                        folha=1;
                        fwrite(&aux->byte,sizeof(unsigned char), 1, descomp);
                    }
                }else{ 
                    aux=aux->left;
                    if(aux->left==NULL && aux->right==NULL){
                        folha=1;
                        fwrite(&aux->byte,sizeof(unsigned char), 1, descomp);
                    }
                }
                i--;
            }
        }
        else{
            while(i>=0){
                if(folha==1){
                    folha=0;
                    aux=head_arv;
                }
                bit=head_list->byte_comp >> i;
                if(bit%2 != 0){ 
                    aux=aux->right;
                    if(aux->left==NULL && aux->right==NULL){
                        folha=1;
                        fwrite(&aux->byte,sizeof(unsigned char), 1, descomp);
                    }
                }else{ 
                    aux=aux->left;
                    if(aux->left==NULL && aux->right==NULL){
                        folha=1;
                        fwrite(&aux->byte,sizeof(unsigned char), 1, descomp);
                    }
                }
                i--;
            }
        }
        
        head_list=head_list->next;
    }
    fclose(descomp);
}
void lendo_cabecalho(FILE *pont, char arquivo[]){
    unsigned char cabecalho1, cabecalho2;
    short int descartar, tam_arvore;
    int i=31, j;
    fscanf(pont,"%c", &cabecalho1);
    printf("aqui");
    fscanf(pont,"%c", &cabecalho2);
    descartar = cabecalho1 >> 5;
    printf("descartar %d\n", descartar);
    cabecalho1=cabecalho1<<3;
    cabecalho1=cabecalho1>>3;
    tam_arvore = ((cabecalho1)*pow(2,8)) + (cabecalho2);
    unsigned char arv[tam_arvore];
    for(j=0; j<tam_arvore; j++){
        fscanf(pont,"%c", &arv[j]);    
    }
    printf("TAMANHO DA ARVORE: %d\n", tam_arvore);
    node_arvore *head_descomp=NULL;
    head_descomp = cria_arv_pre(arv, tam_arvore, head_descomp);  
    node_arvore *aff=head_descomp;
    unsigned char lendo;
    node_lista *arq_comp=NULL, *fim_comp=NULL;
    while(fscanf(pont,"%c", &lendo)!= EOF){
        fim_comp=cria_lista_invertida(arq_comp,fim_comp,lendo);
        if(arq_comp==NULL){
            arq_comp=fim_comp;
        }
    }
    descompactar(head_descomp, arq_comp, fim_comp, descartar, pont, arquivo);
}

void main(){
    char arquivo[100];
    unsigned char bytes;
    printf("Insira o nome do arquivo:\n");
    scanf("%[^\n]s", arquivo);
    FILE *pont=fopen(arquivo, "rb"); 
    if(pont == NULL)
    {
        printf("Esse arquivo não existe!\n");
        exit(1); 
    }
    printf("Digite:\n");
    printf("1. Compactar arquivo\n2. Descompactar arquivo\n3. Sair\n");
    int opcao;
    scanf("%d", &opcao);
    if(opcao==1){
        queue *fila=(queue*)malloc(sizeof(queue));
        ler_arquivo_original(pont, fila);
        criar_primeira_arvore(fila);
        fclose(pont);
        converte_original_para_compactado(fila->head, arquivo);
        printf("Arquivo compactado!\n");
    }
    else if(opcao==2){
        lendo_cabecalho(pont, arquivo);
        fclose(pont);
        printf("Arquivo descompactado!\n");
    }
    else{
        exit(1);
    }
}