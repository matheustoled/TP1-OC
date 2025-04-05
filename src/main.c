#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
argc -> argument count (numero de argumentos recebidos)
argv -> argument vector (array com cada um dos argumentos, todos como string)
*/

int tipoSaida(int argc, char *argv[]){
    if (argc != 2 && argc != 4) {
        printf("Entrada inválida.\n");
        printf("  %s entrada.asm               (modo terminal)\n", argv[0]);
        printf("  %s entrada.asm -o saida.txt  (modo arquivo)\n", argv[0]);
        return 1;
    }

    char *arquivo_entrada = argv[1];
    FILE *entrada = fopen(arquivo_entrada, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", arquivo_entrada);
        return 1;
    }

    FILE *saida = NULL;
    int modo_operacao = 1; // saída pelo terminal

    if (argc == 4) {
        if (strcmp(argv[2], "-o") != 0) {
            printf("Erro: parâmetro desconhecido '%s'. Use -o para indicar o arquivo de saída.\n", argv[2]);
            fclose(entrada);
            return 1;
        }
        saida = fopen(argv[3], "w");
        if (saida == NULL) {
            printf("Erro ao criar o arquivo de saída: %s\n", argv[3]);
            fclose(entrada);
            return 1;
        }
        modo_operacao = 0; // saida por arquivo
    }

    char linha[55];

    while (fgets(linha, sizeof(linha), entrada)) {
        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n') {
            linha[len - 1] = '\0';
        }
        if (modo_operacao) {
            printf("Linha lida: %s\n", linha);
        } else {
            // teste -> fprintf(stderr, "Escrevendo no arquivo: %s\n", linha);
            fprintf(saida, "%s\n", linha);
        }
    }

    fclose(entrada);
    if (saida != NULL) fclose(saida);

    return 0;
}

int main(int argc, char *argv[]) {

    tipoSaida(argc, argv);

    return 0;
}
