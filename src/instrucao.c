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
        printf("Instrucao R desconhecida: %s\n", instrucao);
    }
}
// Formato I -> addi, andi, ori, lb, lh, lw
void preencherInstrucaoI(InstrucaoFormatoI *instrucaoI, char *linha) {
    instrucaoI->formato = I;
    strcpy(instrucaoI->opcode, "0010011");

    char *palavra = strtok(linha, " ,");
    if (palavra == NULL) return;

    char instrucao[10];
    strcpy(instrucao, palavra);

    char *rd_str = strtok(NULL, " ,");
    char *rs1_str = strtok(NULL, " ,");
    char *imm_str = strtok(NULL, " ,");

    if (rd_str == NULL || rs1_str == NULL || imm_str == NULL) return;

    int rd = atoi(rd_str + 1);
    int rs1 = atoi(rs1_str + 1);
    int imediato = atoi(imm_str);  // direto

    strcpy(instrucaoI->rd, decimalParaBinario(rd, 5));
    strcpy(instrucaoI->rs1, decimalParaBinario(rs1, 5));
    strcpy(instrucaoI->imm, decimalParaBinario(imediato, 12));

    if (strcmp(instrucao, "addi") == 0) {
        strcpy(instrucaoI->funct3, "000");
    } else if (strcmp(instrucao, "andi") == 0) {
        strcpy(instrucaoI->funct3, "111");
    } else if (strcmp(instrucao, "ori") == 0) {
        strcpy(instrucaoI->funct3, "110");
    } else if (strcmp(instrucao, "lb") == 0) {
        strcpy(instrucaoI->funct3, "000");
    } else if (strcmp(instrucao, "lh") == 0) {
        strcpy(instrucaoI->funct3, "001");
    } else if (strcmp(instrucao, "lw") == 0) {
        strcpy(instrucaoI->funct3, "010");
    } else {
        printf("Instrucao I desconhecida: %s\n", instrucao);
    }
}

// Formato S -> sb, sh, sw
void preencherInstrucaoS(InstrucaoFormatoS *instrucaoS, char *linha) {
    instrucaoS->formato = S;
    strcpy(instrucaoS->opcode, "0100011");

    char *palavra = strtok(linha, " ,");
    if (palavra == NULL) return;

    char instrucao[10];
    strcpy(instrucao, palavra);

    char *rs2_str = strtok(NULL, " ,");
    char *offset_base = strtok(NULL, " ,");

    if (!rs2_str || !offset_base) return;

    char *offset_str = strtok(offset_base, "(");
    char *rs1_str = strtok(NULL, ")");

    if (!offset_str || !rs1_str) return;

    int rs1 = atoi(rs1_str + 1);
    int rs2 = atoi(rs2_str + 1);
    int imm = atoi(offset_str);

    strcpy(instrucaoS->rs1, decimalParaBinario(rs1, 5));
    strcpy(instrucaoS->rs2, decimalParaBinario(rs2, 5));
    char *imm_bin = decimalParaBinario(imm, 12);

    strncpy(instrucaoS->imm1, imm_bin, 7);  // 11:5
    strncpy(instrucaoS->imm2, imm_bin + 7, 5); // 4:0
    instrucaoS->imm1[7] = '\0';
    instrucaoS->imm2[5] = '\0';
    free(imm_bin);

    if (strcmp(instrucao, "sb") == 0) {
        strcpy(instrucaoS->funct3, "000");
    } else if (strcmp(instrucao, "sh") == 0) {
        strcpy(instrucaoS->funct3, "001");
    } else if (strcmp(instrucao, "sw") == 0) {
        strcpy(instrucaoS->funct3, "010");
    } else {
        printf("Instrucao S desconhecida: %s\n", instrucao);
    }
}

// Formato B -> beq, bne
void preencherInstrucaoB(InstrucaoFormatoB *instrucaoB, char *linha) {
    instrucaoB->formato = B;
    strcpy(instrucaoB->opcode, "1100011");

    char *palavra = strtok(linha, " ,");
    if (palavra == NULL) return;

    char instrucao[10];
    strcpy(instrucao, palavra);

    char *rs1_str = strtok(NULL, " ,");
    char *rs2_str = strtok(NULL, " ,");
    char *offset_str = strtok(NULL, " ,");

    if (!rs1_str || !rs2_str || !offset_str) return;

    int rs1 = atoi(rs1_str + 1);
    int rs2 = atoi(rs2_str + 1);
    int offset = atoi(offset_str);

    char *offset_bin = decimalParaBinario(offset, 13); // B usa 13 bits no total

    instrucaoB->imm1[0] = offset_bin[0];

    strncpy(instrucaoB->imm2, offset_bin + 1, 6); // bits 4:1
    instrucaoB->imm2[6] = '\0';

    strcpy(instrucaoB->rs1, decimalParaBinario(rs1, 5));
    strcpy(instrucaoB->rs2, decimalParaBinario(rs2, 5));

    strncpy(instrucaoB->imm3, offset_bin + 7, 4);       // bits 4:1
    instrucaoB->imm3[4] = '\0';

    instrucaoB->imm4[0] = offset_bin[11];               // bit 11
    instrucaoB->imm4[1] = '\0';

    free(offset_bin);
    
    // B format:
    // imm[12|10:5] | rs2 | rs1 | funct3 | imm[4:1|11]

    if (strcmp(instrucao, "beq") == 0) {
        strcpy(instrucaoB->funct3, "000");
    } else if (strcmp(instrucao, "bne") == 0) {
        strcpy(instrucaoB->funct3, "001");
    } else {
        printf("Instrucao B desconhecida: %s\n", instrucao);
    }
}

// teste imprimir
// void imprimirInstrucaoR(InstrucaoFormatoR *instrucao) {
//     printf("Formato: %s\n", 
//         instrucao->formato == R ? "R" :
//         instrucao->formato == I ? "I" :
//         instrucao->formato == S ? "S" : "B");

//     printf("funct7: %s\n", instrucao->funct7);
//     printf("rs2   : %s\n", instrucao->rs2);
//     printf("rs1   : %s\n", instrucao->rs1);
//     printf("funct3: %s\n", instrucao->funct3);
//     printf("rd    : %s\n", instrucao->rd);
//     printf("opcode: %s\n", instrucao->opcode);
// }

char* gerarInstrucaoBinariaR(InstrucaoFormatoR *instrucao) {
    // printf("Iniciando traducao da instrucao R\n");
    char *instrucaoFinal = (char*) malloc(33 * sizeof(char)); // 32 bits + '\0'

    if (instrucaoFinal == NULL) {
        printf("Erro de alocacao de memoria\n");
        return NULL;
    }

    // Concatena os campos na ordem correta
    strcpy(instrucaoFinal, instrucao->funct7);
    strcat(instrucaoFinal, instrucao->rs2);
    strcat(instrucaoFinal, instrucao->rs1);
    strcat(instrucaoFinal, instrucao->funct3);
    strcat(instrucaoFinal, instrucao->rd);
    strcat(instrucaoFinal, instrucao->opcode);

    return instrucaoFinal;
}

char* gerarInstrucaoBinariaI(InstrucaoFormatoI *instrucao) {
    // printf("Iniciando traducao da instrucao I\n");
    char *instrucaoFinal = (char*) malloc(33 * sizeof(char)); // 32 bits + '\0'

    if (instrucaoFinal == NULL) {
        printf("Erro de alocacao de memoria\n");
        return NULL;
    }

    // Concatena os campos na ordem: imm | rs1 | funct3 | rd | opcode
    strcpy(instrucaoFinal, instrucao->imm);     // 12 bits
    strcat(instrucaoFinal, instrucao->rs1);     // 5 bits
    strcat(instrucaoFinal, instrucao->funct3);  // 3 bits
    strcat(instrucaoFinal, instrucao->rd);      // 5 bits
    strcat(instrucaoFinal, instrucao->opcode);  // 7 bits

    return instrucaoFinal;
}

char* gerarInstrucaoBinariaS(InstrucaoFormatoS *instrucao) {
    // printf("Iniciando traducao da instrucao S\n");
    char *instrucaoFinal = (char*) malloc(33 * sizeof(char));
    if (!instrucaoFinal) return NULL;

    strcpy(instrucaoFinal, instrucao->imm1);
    strcat(instrucaoFinal, instrucao->rs2);
    strcat(instrucaoFinal, instrucao->rs1);
    strcat(instrucaoFinal, instrucao->funct3);
    strcat(instrucaoFinal, instrucao->imm2);
    strcat(instrucaoFinal, instrucao->opcode);

    return instrucaoFinal;
}

char* gerarInstrucaoBinariaB(InstrucaoFormatoB *instrucao) {
    // printf("Iniciando traducao da instrucao B\n");
    char *instrucaoFinal = (char*) malloc(33 * sizeof(char));
    if (!instrucaoFinal) return NULL;

    strcpy(instrucaoFinal, instrucao->imm1);     // bit 12
    strcat(instrucaoFinal, instrucao->imm2);     // bits 10:5
    strcat(instrucaoFinal, instrucao->rs2);      
    strcat(instrucaoFinal, instrucao->rs1);      
    strcat(instrucaoFinal, instrucao->funct3);   
    strcat(instrucaoFinal, instrucao->imm3);     // bits 4:1
    strcat(instrucaoFinal, instrucao->imm4);     // bit 11
    strcat(instrucaoFinal, instrucao->opcode);   

    return instrucaoFinal;
}

void imprimirInstrucaoBionaria(FormatoInstrucao formato, void *instrucao){
    char *binario = NULL;

    switch (formato) {
        case R:
            binario = gerarInstrucaoBinariaR((InstrucaoFormatoR*)instrucao);
            break;
        case I:
            binario = gerarInstrucaoBinariaI((InstrucaoFormatoI*)instrucao);
            break;
        case S:
            binario = gerarInstrucaoBinariaS((InstrucaoFormatoS*)instrucao);
            break;
        case B:
            binario = gerarInstrucaoBinariaB((InstrucaoFormatoB*)instrucao);
            break;
        default:
            printf("Formato de instrucao desconhecido.\n");
            return;
    }

    if (binario != NULL) {
        printf("Instrucao em binario: %s\n", binario);
        free(binario);
    }
}