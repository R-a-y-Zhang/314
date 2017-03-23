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

void init() {
    int i;
    for (i = 0; i < 16; i++) {
        variable[i] = 'a' + i;
    }
    for (i = 0; i < 10; i++) {
        digit[i] = '0' + i;
    }
    vr = newrecord();
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
BOOL expr();
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
    if (variablec(sym) == TRUE) {
        return findvar(sym);
    }
    else if (digitc(sym) == TRUE) {
        Var* reg = newreg(sym-'0');
        insertreg(reg);
        return reg;
    }
    else if (contains(exprsym, 4, sym) == TRUE) {
        Var* reg = newreg(0);
        switch(sym) {
            case '+':
                reg->val = expr()->val + expr()->val;
                break;
            case '-':
                reg->val = expr()->val - expr()->val;
                break;
            case '%':
                reg->val = expr()->val / expr()->val;
                break;
            case '*':
                reg->val = expr()->val * expr()->val;
                break;
        }
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
            int v = expr();
            if (findvar(vr, vname) == vname) {
                modifyvar(vr, v);
                return TRUE;
            } else {
                insertvar(vr, newvar(vname, v));
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
            printf("%d\n", getvar(vr, sym));
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
}
