#include <stdlib.h>
#include <stdio.h>
#include "instructions.h"

opc* newopc(INS v) {
    opc* op = (opc*)calloc(1, sizeof(opc));
    op->ins = v;
    op->in1 = -1;
    op->in2 = -1;
    op->out = -1;
    return op;
}

opc* loadI(int v, int out) {
    opc* op = newopc(LOADI);
    op->val = v;
    op->out = out;
    return op;
}

opc* loadAI(int in, int offset, int out) {
    opc* op = newopc(LOADAI);
    op->in1 = in;
    op->offset = offset;
    op->out = out;
    return op;
}

opc* storeAI(int in, int out, int offset) {
    opc* op = newopc(STOREAI);
    op->in1 = in;
    op->out = out;
    op->offset = offset;
    return op;
}

opc* opadd(int in1, int in2, int out) {
    opc* op = newopc(ADD);
    op->in1 = in1;
    op->in2 = in2;
    op->out = out;
    return op;
}

opc* opsub(int in1, int in2, int out) {
    opc* op = newopc(SUB);
    op->in1 = in1;
    op->in2 = in2;
    op->out = out;
    return op;
}

opc* opmul(int in1, int in2, int out) {
    opc* op = newopc(MUL);
    op->in1 = in1;
    op->in2 = in2;
    op->out = out;
    return op;
}

opc* opdiv(int in1, int in2, int out) {
    opc* op = newopc(DIV);
    op->in1 = in1;
    op->in2 = in2;
    op->out = out;
    return op;
}

opc* opprint(int in, int offset) {
    opc* op = newopc(PRINT);
    op->in1 = in;
    op->offset = offset;
    return op;
}

machine* newmachine() {
    return (machine*)calloc(1, sizeof(machine));
}

op* newop(opc* oper) {
    op* op_ = (op*)calloc(1, sizeof(op));
    op_->oper = oper;
    return op_;
}

void addop(machine* mach, opc* o) {
    op* new_op = newop(o);
    if (mach->root == NULL) { mach->root = new_op; }
    else {
        op* p = mach->root;
        while (p->next) {
            p = p->next;
        }
        p->next = new_op;
        new_op->prev = p;
    }
}

void clean(machine* mach) {
    op* n0 = mach->root;
    while (n0) {
        op* n1 = NULL;
        if (n0->next) { n1 = n0->next; }
        free(n0->oper);
        free(n0);
        n0 = n1;
    }
    free(mach);
}

void printmachine(machine* mach) {
    char* insts[] = {"LOADI", "LOADAI", "STOREAI", "ADD", "SUB", "MUL", "DIV", "PRINT"};
    op* operator = mach->root;
    while (operator) {
        opc* o = operator->oper;
        switch (o->ins) {
            case LOADI:
                printf("LOADI %d -> r%d\n", o->val, o->out);
                break;
            case LOADAI:
                printf("LOADAI %d, %d -> %d\n", o->in1, o->offset, o->out);
                break;
            case STOREAI:
                printf("STOREAI %d -> %d, %d\n", o->in1, o->out, o->offset);
                break;
            case PRINT:
                printf("PRINT %d, %d\n", o->in1, o->offset);
                break;
            case ADD:
                printf("ADD ");
                break;
            case SUB:
                printf("SUB ");
                break;
            case MUL:
                printf("MUL ");
                break;
            case DIV:
                printf("DIV ");
                break;
        }
        if ((o->ins == ADD) || (o->ins == SUB) || (o->ins == MUL) || (o->ins == DIV)) {
            printf("%d, %d -> %d\n", o->in1, o->in2, o->out);
        }
        operator = operator->next;
    }
}
