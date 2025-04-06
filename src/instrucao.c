#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/instrucao.h"

char* decimalParaBinario(int numero, int bits) {
    char *binario = (char*) malloc((bits + 1) * sizeof(char)); // +1 pro '\0'

    if (binario == NULL) {
        return NULL; // erro de alocação
    }

    for (int i = bits - 1; i >= 0; i--) {
        binario[bits - 1 - i] = ((numero >> i) & 1) ? '1' : '0';
    }

    binario[bits] = '\0'; // termina a string

    return binario;
}

// Formato R -> add, sub, and, or, xor, sll, srl
void preencherInstrucaoR(InstrucaoFormatoR *instrucaoR, char *linha) {

    instrucaoR->formato = R;
    strcpy(instrucaoR->opcode, "0110011");

    char *palavra = strtok(linha, " ,");  // Instrução
    if (palavra == NULL) return;

    // Guardamos a instrução (add, sub, etc)
    char instrucao[10];
    strcpy(instrucao, palavra);

    // Lemos os registradores
    char *rd_str = strtok(NULL, " ,");
    char *rs1_str = strtok(NULL, " ,");
    char *rs2_str = strtok(NULL, " ,");

    if (rd_str == NULL || rs1_str == NULL || rs2_str == NULL) return;

    // Remove o 'x' e converte para inteiro
    int rd = atoi(rd_str + 1);
    int rs1 = atoi(rs1_str + 1);
    int rs2 = atoi(rs2_str + 1);

    // Converte para binário de 5 bits e armazena nos campos
    strcpy(instrucaoR->rd, decimalParaBinario(rd, 5));
    strcpy(instrucaoR->rs1, decimalParaBinario(rs1, 5));
    strcpy(instrucaoR->rs2, decimalParaBinario(rs2, 5));

    // Define funct3 e funct7 dependendo da instrução
    if (strcmp(instrucao, "add") == 0) {
        strcpy(instrucaoR->funct3, "000");
        strcpy(instrucaoR->funct7, "0000000");
    } else if (strcmp(instrucao, "sub") == 0) {
        strcpy(instrucaoR->funct3, "000");
        strcpy(instrucaoR->funct7, "0100000");
    } else if (strcmp(instrucao, "and") == 0) {
        strcpy(instrucaoR->funct3, "111");
        strcpy(instrucaoR->funct7, "0000000");
    } else if (strcmp(instrucao, "or") == 0) {
        strcpy(instrucaoR->funct3, "110");
        strcpy(instrucaoR->funct7, "0000000");
    } else if (strcmp(instrucao, "xor") == 0) {
        strcpy(instrucaoR->funct3, "100");
        strcpy(instrucaoR->funct7, "0000000");
    } else if (strcmp(instrucao, "sll") == 0) {
        strcpy(instrucaoR->funct3, "001");
        strcpy(instrucaoR->funct7, "0000000");
    } else if (strcmp(instrucao, "srl") == 0) {
        strcpy(instrucaoR->funct3, "101");
        strcpy(instrucaoR->funct7, "0000000");
    } else {
        printf("Instrução R desconhecida: %s\n", instrucao);
    }
}
// Formato I -> addi, andi, ori, lb, lh, lw
void preencherInstrucaoI(InstrucaoFormatoI *instrucaoI, char *linha) {
    while (linha != NULL) {
        printf("Palavra: %s\n", linha);
        linha = strtok(NULL, " /t");
    }
}

// Formato S -> sb, sh, sw
void preencherInstrucaoS(InstrucaoFormatoS *instrucaoS, char *linha) {
    while (linha != NULL) {
        printf("Palavra: %s\n", linha);
        linha = strtok(NULL, " /t");
    }
}

// Formato B -> beq, bne
void preencherInstrucaoB(InstrucaoFormatoB *instrucaoB, char *linha) {
    while (linha != NULL) {
        printf("Palavra: %s\n", linha);
        linha = strtok(NULL, " /t");
    }
}

void imprimirInstrucaoR(InstrucaoFormatoR *instrucao) {
    printf("Formato: %s\n", 
        instrucao->formato == R ? "R" :
        instrucao->formato == I ? "I" :
        instrucao->formato == S ? "S" : "B");

    printf("funct7: %s\n", instrucao->funct7);
    printf("rs2   : %s\n", instrucao->rs2);
    printf("rs1   : %s\n", instrucao->rs1);
    printf("funct3: %s\n", instrucao->funct3);
    printf("rd    : %s\n", instrucao->rd);
    printf("opcode: %s\n", instrucao->opcode);
}