#include <stdlib.h>

opc* newopc(INS v) {
    opc* op = (opc*)calloc(1, sizeof(opc));
    op->ins = v;
    op->in1 = -1;
    op->in2 = -1;
    op->out = -1;
    return op;
}

opc* loadI(int v, int in) {
    opc* op = newopc(LOAD);
    op->val = v;
    op->in1 = in;
    return op;
}

opc* loadAI(int in, int offset, int out) {
    opc* op = newopc(LOADAI);
    op->in1 = in;
    op->offset = offset;
    op->out = out;
    return op;
}

opc* storeAI(int v, int in, int out, int offset) {
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

void addop(machine* mach, op* o) {
    if (mach->root == NULL) { mach->root = o; }
    else {
        op* p = mach->root;
        while (p->next) {
            p = p->next;
        }
        p->next = o;
        o->prev = p;
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
