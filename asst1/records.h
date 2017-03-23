#ifndef __RECORDS_H
#define __RECORDS_H

// keeps track of declared variables

typedef struct Var {
    char v;
    int cv;
    struct var* next;
} Var;

typedef struct VarRecord {
    Var* root;
    char nc;
} VarRecord;

VarRecord* newrecord();
Var* newvar(char c, int cv);
void insertvar(VarRecord* vr, Var* v);
char modifyvar(VarRecord* vr, char c, int nv);
int getvar(VarRecord* vr, char c);
char findvar(VarRecord* vr, char c);
void clearrecord(VarRecord* vr);

#endif
