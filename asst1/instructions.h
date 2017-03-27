#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

typedef enum INS {
    LOADI,
    LOADAI,
    STOREAI,
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

opc* loadI(int v, int out);
opc* loadAI(int in, int offset, int out);
opc* storeAI(int in, int out, int offset);
opc* opadd(int in1, int in2, int out);
opc* opsub(int in1, int in2, int out);
opc* opmul(int in1, int in2, int out);
opc* opdiv(int in1, int in2, int out);
opc* opprint(int in, int offset);

typedef struct op {
    opc* oper;
    struct op* prev;
    struct op* next;
} op;

typedef struct machine {
    op* root;
} machine;

machine* newmachine();
op* newop(opc* o);
void addop(machine* mach, opc* o);
void clean(machine* mach);
void printmachine(machine* mach);

#endif
