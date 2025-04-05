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
    FormatoInstrucao formato = R;
    int funct7[7];
    int rs2[5];
    int rs1[5];
    int funct3[3];
    int rd[5];
    int opcode[7];
} InstrucaoFormatoR;

// Formato I -> addi, andi, ori, lb,  lh, lw
typedef struct InstucaoFormatoI {
    FormatoInstrucao formato = I;
    int imm[12];
    int rs1[5];
    int funct3[3];
    int rd[5];
    int opcode[7];
} InstrucaoFormatoI;

// Formato S -> sb, sh, sw
typedef struct InstucaoFormatoS {
    FormatoInstrucao formato = S;
    int imm1[7];
    int rs2[5];
    int rs1[5];
    int funct3[3];
    int imm2[5];
    int opcode[7];
} InstrucaoFormatoS;

// Formato B -> beq, bne
typedef struct InstucaoFormatoB {
    FormatoInstrucao formato = B;
    int imm1[1];
    int imm2[6];
    int rs2[5];
    int rs1[5];
    int funct3[3];
    int imm3[4];
    int imm5[1];
    int opcode[7];
} InstrucaoFormatoB;

#endif
