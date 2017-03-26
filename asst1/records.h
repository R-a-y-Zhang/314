#ifndef __RECORDS_H
#define __RECORDS_H

// keeps track of declared variables

typedef struct Var {
    int reg; // register id (r<id>)
    char var; // register alias (used only for userspace variables)
    int val; // value in register
    char usable;
    struct Var* next;
} Var;

typedef struct VarRecord {
    Var* root;
    int ureg, sreg;
    char nc;
} VarRecord;

VarRecord* newrecord();
Var* newreg(VarRecord* vr, int val);
Var* newureg(VarRecord* vr, char name, int val);
void insertreg(VarRecord* vr, Var* v);
int modifyreg(VarRecord* vr, int reg, int nv);
Var* findreg(VarRecord* vr, int reg);
Var* findvar(VarRecord* vr, char var);
void deletereg(VarRecord* vr, int reg);
void clearrecord(VarRecord* vr);
void printrecord(VarRecord* vr);

#endif
