#include <stdio.h>
#include <stdlib.h>
#include "records.h"
#include "instructions.h"

char variable[16], digit[10];
char exprsym[] = {'+', '-', '%', '*'};
char psym[] = {'#'};
char sym;
FILE* f;
VarRecord* vr;
char nc = EOF;
machine* mach;

void init() {
    int i;
    for (i = 0; i < 16; i++) {
        variable[i] = 'a' + i;
    }
    for (i = 0; i < 10; i++) {
        digit[i] = '0' + i;
    }
    vr = newrecord();
    mach = newmachine();
}

typedef enum BOOL {
    FALSE,
    TRUE
} BOOL;

void error(char* err) {
    fprintf(stderr, "%s\n", err);
}

void next();
char peek();

void badchar() {
    error("Invalid character");
}

void loadFile(char* fp) {
    f = fopen(fp, "r");
    nc = fgetc(f);
}

void next() {
    sym = nc;
    printf("NC %c\n", sym);
    nc = fgetc(f);
}

char peek() {
    return nc;
}

void runFile() {
    char c;
    while ((c = fgetc(f)) != EOF) {
        printf("%c\n", c);
    }
}

void finish() {
    fclose(f);
}

BOOL stmtlist();
BOOL morestmts();
BOOL variablec(char);
BOOL digitc(char);
Var* expr();
BOOL assign();
BOOL print();
BOOL stmt();
BOOL program();

BOOL contains(char* arr, int len, char v) {
    int i;
    for (i = 0; i < len; i++) {
        if (arr[i] == v) return TRUE;
    }
    return FALSE;
}

BOOL variablec(char sym) {
    return contains(variable, 16, sym);
}

BOOL digitc(char d) {
    return contains(digit, 10, d);
}

Var* expr() {
    // printf("EXPR\n");
    next();
    printf("SYM %c\n", sym);
    if (variablec(sym) == TRUE) {
        return findvar(vr, sym);
    }
    else if (digitc(sym) == TRUE) {
        Var* reg = newreg(vr, sym-'0');
        insertreg(vr, reg);
        addop(mach, loadI(reg->val, reg->reg));
        return reg;
    }
    else if (contains(exprsym, 4, sym) == TRUE) {
        char operation = sym;
        Var* reg = newreg(vr, 0);
        Var* ex1 = expr();
        Var* ex2 = expr();
        printf("EX1 %d, EX2 %d\n", ex1->val, ex2->val);
        opc* op = NULL;
        switch(operation) {
            case '+':
                op = opadd(0, 0, reg->reg);
                reg->val = ex1->val + ex2->val;
                break;
            case '-':
                op = opsub(0, 0, reg->reg);
                reg->val = ex1->val + ex2->val;
                break;
            case '%':
                op = opdiv(0, 0, reg->reg);
                reg->val = ex1->val / ex2->val;
                break;
            case '*':
                op = opmul(0, 0, reg->reg);
                reg->val = ex1->val * ex2->val;
                break;
        }
        insertreg(vr, reg);
        printf("REG %d has value %d, %c %d %d\n",
                    reg->reg, reg->val, operation, ex1->val, ex2->val);
        fflush(stdout);
        int r1 = ex1->reg;
        int r2 = ex2->reg;
        if (ex1->var != 0) { // must be loaded to register from memory
            addop(mach, loadAI(0, ex1->reg, vr->nc)); // loading into register
            r1 = vr->nc;
            vr->nc++; // advance available registers
        }
        if (ex2->var != 0) {
            addop(mach, loadAI(0, ex2->reg, vr->nc));
            r2 = vr->nc;
            vr->nc++;
        }
        op->in1 = r1; op->in2 = r2;
        addop(mach, op);
        return reg;
    }
    error("Invalid operation");
    return NULL;
}

BOOL assign() {
    printf("ASSIGN\n");
    next();
    if (variablec(sym) == TRUE) {
        char vname = sym;
        next();
        if (sym == '=') {
            Var* v = expr(); // expression that the new register shall hold
            Var* modvar = findvar(vr, vname);
            if (modvar != NULL) {
                modvar->val = v->val;
                return TRUE;
            } else {
                Var* newvar = newureg(vr, vname, v->val);
                printf("New register %d with varname %c value %d\n",
                            newvar->reg, newvar->var, newvar->val);
                addop(mach, loadI(v->val, v->reg));
                addop(mach, storeAI(v->reg, 0, newvar->reg));
                insertreg(vr, newvar);
                return TRUE;
            }
        } else {
            error("Invalid character");
        }
    } else {
        error("Invalid character");
    }
    return FALSE;
}

BOOL print() {
    printf("PRINT\n");
    next();
    if (sym == '#') {
        next();
        if (variablec(sym) == TRUE) {
            Var* var = findvar(vr, sym);
            addop(mach, opprint(0, var->reg));
            return TRUE;
        } else error("Invalid character");
    } else error("Invalid character");
    return FALSE;
}

BOOL stmt() {
    printf("STMT\n");
    if (peek() == '#') return print();
    if (variablec(peek()) == TRUE) return assign();
    return FALSE;
}

BOOL morestmts() {
    printf("MSTMTS\n");
    next();
    if (sym == ';') {
        if (peek() == EOF) return TRUE;
        return stmtlist();
    } else if (sym == EOF || sym == '.') return TRUE;
    return FALSE;
}

BOOL stmtlist() {
    printf("STMTL\n");
    BOOL s = stmt();
    BOOL m = morestmts();
    return s && m;
}

BOOL program() {
    printf("PROG\n");
    return stmtlist();
}

int main(int argc, char** argv) {
    loadFile(argv[1]);
    init();
    printf("%d\n", program());
    printmachine(mach);
}
