#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

typedef enum INS {
    LOAD,
    LOADAI,
    LOADI,
    ADD,
    SUB,
    MUL,
    DIV,
    PRINT
} INS;

typedef struct opc {
    INS ins;
    int val;
    int in1, in2;
    int offset;
    int out;
} opc;

opc load(int v, int out);
opc loadAI(int v, int in, int offset, int out);
opc loadI(int v, int in, int out, int offset);
opc add(int in1, int in2, int out);
opc sub(int in1, int in2, int out);
opc mul(int in1, int in2, int out);
opc div(int in1, int in2, int out);
opc print(int in, int offset);

#endif
