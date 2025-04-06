#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/instrucao.h"

/*
argc -> argument count (numero de argumentos recebidos)
argv -> argument vector (array com cada um dos argumentos, todos como string)
*/

void definirTipoInstrucao(char *linha){
    char *lista_instrucoes_r[] = {"add", "sub", "and", "or", "xor", "sll", "srl"};
    char *lista_instrucoes_i[] = {"addi", "andi", "ori", "lb", "lh", "lw"};
    char *lista_instrucoes_s[] = {"sb", "sh", "sw"};
    char *lista_instrucoes_b[] = {"beq", "bne"};

    // Minhas instrucoes -> char *lista_isntrucoes_tp[] = {"lb", "sb", "add", "and", "ori", "sll", "bne"};

    // Fazemos uma cópia da linha porque strtok modifica a string original
    char linha_copia[55];
    strcpy(linha_copia, linha);

    // Pegamos a primeira palavra (instrução)
    char *palavra = strtok(linha_copia, " ");
    if (palavra == NULL) return;

    // Guardamos a instrução original em uma string separada
    char instrucao_original[10];
    strcpy(instrucao_original, palavra);

    for (int i = 0; i<7; i++) {
        if (strcmp(instrucao_original, lista_instrucoes_r[i]) == 0) {
            InstrucaoFormatoR instrucaoR;
            preencherInstrucaoR(&instrucaoR, linha);
            // printf("Instrucao R definida\n");
            imprimirInstrucaoBionaria(instrucaoR.formato, &instrucaoR);
        }
    }
    for (int i = 0; i<6; i++) {
        if (strcmp(instrucao_original, lista_instrucoes_i[i]) == 0) {
            InstrucaoFormatoI instrucaoI;
            preencherInstrucaoI(&instrucaoI, linha);
            // printf("Instrucao I definida\n");
            imprimirInstrucaoBionaria(instrucaoI.formato, &instrucaoI);
        }
    }
    for (int i = 0; i<3; i++) {
        if (strcmp(instrucao_original, lista_instrucoes_s[i]) == 0) {
            InstrucaoFormatoS instrucaoS;
            preencherInstrucaoS(&instrucaoS, linha);
            // printf("Instrucao S definida\n");
            imprimirInstrucaoBionaria(instrucaoS.formato, &instrucaoS);
        }
    }
    for (int i = 0; i<2; i++) {
        if (strcmp(instrucao_original, lista_instrucoes_b[i]) == 0) {
            InstrucaoFormatoB instrucaoB;
            preencherInstrucaoB(&instrucaoB, linha);
            // printf("Instrucao B definida\n");
            imprimirInstrucaoBionaria(instrucaoB.formato, &instrucaoB);
        }
    }
}

int tipoSaida(int argc, char *argv[]) {

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
            definirTipoInstrucao(linha);
        } else {
            // teste -> fprintf(stderr, "Escrevendo no arquivo: %s\n", linha);
            fprintf(saida, "%s\n", linha);
        }
    }

    // ImprimirLista(&lista);

    fclose(entrada);
    if (saida != NULL) fclose(saida);

    return 0;
}

int main(int argc, char *argv[]) {

    tipoSaida(argc, argv);

    return 0;
}
