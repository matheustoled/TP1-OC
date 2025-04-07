#ifndef INSTRUCAO_H_
#define INSTRUCAO_H_

typedef enum FormatoInstrucao {
    R,
    I,
    S,
    B
} FormatoInstrucao;

// Formato R -> add, sub, and, or, xor, sll, srl
typedef struct InstucaoFormatoR {
    FormatoInstrucao formato;
    char funct7[8];
    char rs2[6];
    char rs1[6];
    char funct3[4];
    char rd[6];
    char opcode[8];
} InstrucaoFormatoR;

// Formato I -> addi, andi, ori, lb, lh, lw
typedef struct InstucaoFormatoI {
    FormatoInstrucao formato;
    char imm[13];
    char rs1[6];
    char funct3[4];
    char rd[6];
    char opcode[8];
} InstrucaoFormatoI;

// Formato S -> sb, sh, sw
typedef struct InstucaoFormatoS {
    FormatoInstrucao formato;
    char imm1[8];
    char rs2[6];
    char rs1[6];
    char funct3[4];
    char imm2[6];
    char opcode[8];
} InstrucaoFormatoS;

// Formato B -> beq, bne
typedef struct InstucaoFormatoB {
    FormatoInstrucao formato;
    char imm1[2];
    char imm2[7];
    char rs2[6];
    char rs1[6];
    char funct3[4];
    char imm3[5];
    char imm4[2];
    char opcode[8];
} InstrucaoFormatoB;

char *decimalParaBinario(int numero, int bits);

void preencherInstrucaoR(InstrucaoFormatoR *instrucaoR, char *linha);
void preencherInstrucaoI(InstrucaoFormatoI *instrucaoI, char *linha);
void preencherInstrucaoS(InstrucaoFormatoS *instrucaoS, char *linha);
void preencherInstrucaoB(InstrucaoFormatoB *instrucaoB, char *linha);

char *gerarInstrucaoBinariaR(InstrucaoFormatoR *instrucao);
char *gerarInstrucaoBinariaI(InstrucaoFormatoI *instrucao);
char *gerarInstrucaoBinariaS(InstrucaoFormatoS *instrucao);
char *gerarInstrucaoBinariaB(InstrucaoFormatoB *instrucao);

void imprimirInstrucaoBionaria1(FormatoInstrucao formato, void *instrucao);
void imprimirInstrucaoBionaria2(FormatoInstrucao formato, void *instrucao, FILE *saida);

#endif
