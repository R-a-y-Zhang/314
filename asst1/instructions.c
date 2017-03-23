#include <stdlib.h>

// load
opc load(int v, int out) {
    opc op = {.ins LOAD, .val v, .in1 -1, .in2 -1, .offset 0, .out out};
    return op;
}

opc loadAI(int v, int in, int offset, int out) {
    opc op = {.ins LOADAI, .val v, .in1 in, .in2 -1, .offset offset, .out out};
    return op;
}

opc loadI(int v, int in, int out, int offset) {
    opc op = {.ins LOADI, .val v, .in1 in, .in2 -1, .offset offset, .out out};
    return op;
}

opc add(int in1, int in2, int out) {
    opc op = {.ins ADD, .val 0, .in1 in1, .in2 in2, .offset 0, .out out};
    return op;
}

opc sub(int in1, int in2, int out) {
    opc op = {.ins SUB, .val 0, .in1 in1, .in2 in2, .offset 0, .out out};
    return op;
}

opc mul(int in1, int in2, int out) {
    opc op = {.ins MUL, .val 0, .in1 in1, .in2 in2, .offset 0, .out out};
    return op;
}

opc div(int in1, int in2, int out) {
    opc op = {.ins DIV, .val 0, .in1 in1, .in2 in2, .offset 0, .out out};
    return op;
}

opc print(int in, int offset) {
    opc op = {.ins PRINT, .val 0, .in1 in, .in2 -1, .offset offset, .out -1};
    return op;
}
