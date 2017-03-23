#include <stdlib.h>
#include "records.h"

VarRecord* newrecord() {
    VarRecord* r = (VarRecord*)malloc(sizeof(VarRecord));
    r->root = NULL;
    return r;
}

Var* newvar(char c, int cv) {
    Var* v = (Var*)malloc(sizeof(Var));
    v->v = c;
    v->cv = cv;
    v->next = NULL;
    return v;
}

void insertvar(VarRecord* vr, Var* v) {
    if (!vr->root) { vr->root = v; }
    else {
        Var* p = vr->root;
        while (p->next) { p = p->next; }
        p->next = v;
    }
}

char modifyvar(VarRecord* vr, char c, int nv) {
    Var* v = vr->root;
    while (v) {
        if (v->v == c) {
            v->cv = nv;
            return c;
        }
        v = v->next;
    }
    return 0;
}

int getvar(VarRecord* vr, char c) {
    Var* v = vr->root;
    while (v) {
        if (v->v == c) { return v->cv; }
        v = v->next;
    }
    return -1;
}

char findvar(VarRecord* vr, char c) {
    Var* v = vr->root;
    while (v) {
        if (v->v = c) { return c; }
        v = v->next;
    }
    return 0;
}

void clearrecord(VarRecord* vr) {
    Var* p = vr->root;
    Var* n = p->next;
    while (p) {
        free(p);
        p = n;
        if (n) { n = n->next; }
    }
    free(vr);
}
