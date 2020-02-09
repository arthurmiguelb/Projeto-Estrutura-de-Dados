

void main(){
    char arquivo[100];
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