#include <stdlib.h>
#include "records.h"

VarRecord* newrecord() {
    VarRecord* r = (VarRecord*)malloc(sizeof(VarRecord));
    r->ureg = 0;
    r->sreg = 26;
    r->nc = 'a';
    r->root = NULL;
    return r;
}

Var* newreg(VarRecord* vr, int val) {
    Var* var = (Var*)malloc(sizeof(Var));
    var->val = val;
    var->reg = vr->sreg;
    vr->sreg++;
    var->nc = 0;
    var->next = NULL;
    return var;
}

Var* newureg(VarRecord* vr, char name, int val) {
    Var* var = (Var*)malloc(sizeof(Var));
    var->val = val;
    var->reg = vr->ureg;
    vr->ureg++;
    var->nc = name;
    var->next = NULL;
    return var;
}

void insertreg(VarRecord* vr, Var* v) {
    if (vr->root == NULL) { vr->root = v; }
    else {
        Var* p = vr->root;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = v;
    }
}

int modifyreg(VarRecord* vr, int reg, int nv) {
    Var* v = vr->root;
    while (v != NULL) {
        if (v->reg == reg) {
            v->val = nv;
            return reg;
        }
        v = v->next;
    }
    return -1;
}

Var* findreg(VarRecord* vr, int reg) {
    Var* v = vr->root;
    while (v != NULL) {
        if (v->reg == reg) {
            return v;
        }
        v = v->next;
    }
    return NULL;
}

Var* findvar(VarRecord* vr, char var) {
    Var* v = vr->root;
    while (v != NULL) {
        if (v->nc == var) {
            return v;
        }
        v = v->next;
    }
    return NULL;
}

void deletereg(VarRecord* vr, int reg) {

}

void clearrecord(VarRecord* vr) {

}
