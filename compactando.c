
void enqueue(queue *fila, unsigned char byte, long long int f, node_arvore *left, node_arvore *right){ 
    node_arvore *new_node=(node_arvore*)malloc(sizeof(node_arvore));
    new_node->freq=f;
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

void contando(node_arvore *head){ 
    if(head!=NULL){
        if((head->byte=='*'&&head->left==NULL&&head->right==NULL) || head->byte==92){ //eh folha
            tamanho_da_arvore++;
        }
        tamanho_da_arvore++;
        contando(head->left);
        contando(head->right);
    }
}
void dicionario(node_arvore *head, hash *new_hash, unsigned short byte, int profundidade) {
    if(head!=NULL) {
        if(head->left==NULL && head->right==NULL) { //eh folha
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
unsigned char empurrando(unsigned char output, unsigned char aux){
    output = output << 1;
    return output | aux;
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
void escreve(node_lista *head, node_arvore *cabeca_arvore, char arquivo[]){
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
        fwrite(&head->byte_comp, sizeof(char), 1, salvar);
        head = head->next;
    }
    fclose(salvar);
}
void compactar(hash *new_hash, char arquivo[], node_arvore *cabeca_arvore){
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
    lixo=8-posicao;
    output=output<<lixo;
    fim=cria_lista_invertida(head,fim,output);
    if(head==NULL){
        head = fim;
    }
    escreve(head, cabeca_arvore, arquivo);
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
    contando(aux2);
    dicionario(aux, new_hash,0, 0);
    compactar(new_hash, arquivo, head);
}