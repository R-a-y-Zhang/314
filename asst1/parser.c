#include <stdio.h>
#include <stdlib.h>

char variable[16], digit[10];
char exprsym[] = {'+', '-', '%', '*'};
char psym[] = {'#'};
char sym;
FILE* f;
char nc = '\0';

void initconsts() {
    int i;
    for (i = 0; i < 16; i++) {
        variable[i] = 'a' + i;
    }
    for (i = 0; i < 10; i++) {
        variable[i] = '0' + i;
    }
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
}

void next() {
    sym = nc;
    printf("%c\n", sym);
    if (feof(f)) nc = '\0';
    else nc = fgetc(f);
}

char peek() {
    return nc;
}

void finish() {
    fclose(f);
}

BOOL stmtlist();
BOOL morestmts();
BOOL contains(char* arr, int len, char v) {
    int i;
    for (i = 0; i < len; i++) {
        if (arr[i] == v) return TRUE;
    }
    return FALSE;
}

BOOL variablec(char sym) {
    printf("VARS\n");
    return contains(variable, 16, sym);
}

BOOL digitc(char d) {
    printf("DIGITS\n");
    return contains(digit, 10, d);
}

BOOL expr() {
    printf("EXPR\n");
    next();
    if (variablec(sym) == TRUE) { return TRUE; }
    else if (digitc(sym) == TRUE) { return TRUE; }
    else if (contains(exprsym, 4, sym) == TRUE) {
        if ((expr() == TRUE) && (expr() == TRUE)) return TRUE;
    }
    return FALSE;
}

BOOL assign() {
    printf("ASSIGN\n");
    next();
    if (variablec(sym) == TRUE) {
        next();
        if (sym == '=') {
            next();
            if (expr() == TRUE) { return TRUE; }
            else return FALSE;
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

BOOL print() {
    printf("PRINT\n");
    next();
    if (sym == '#') {
        next();
        if (variablec(sym) == TRUE) { return TRUE; }
        else return FALSE;
    } else return FALSE;
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
        if (peek() == '\0') return TRUE;
        return stmtlist();
    } else if (sym == '\0') return TRUE;
    return FALSE;
}

BOOL stmtlist() {
    printf("STMTL\n");
    return stmt() && morestmts();
}

BOOL program() {
    printf("PROG\n");
    return stmtlist();
}

int main(int argc, char** argv) {
    loadFile(argv[1]);
    initconsts();
    printf("%d\n", program());
}
