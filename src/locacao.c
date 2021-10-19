#include "locacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct loc {
    char id[25], situacao[20];
    double area,valor;
    Moradia moradia;
};

typedef struct loc *locacao;

Locacao criarLocacao(char* id, double area, double valor, Moradia moradia){
    locacao loc = (locacao) malloc(sizeof(struct loc));
    strcpy(loc->id,id);
    loc->area=area;
    loc->valor=valor;
    loc->moradia=moradia;
    strcpy(loc->situacao,"disponivel");
    return loc;
}

void freeLocacao(Locacao Loc){
    locacao loc = (locacao) Loc;
    free(loc);
}

char* getId(Locacao l){
    locacao lo = (locacao) l;
    return lo->id;
}

double getArea(Locacao l){
    locacao lo = (locacao) l;
    return lo->area;
}

double getValor(Locacao l){
    locacao lo = (locacao) l;
    return lo->valor;
}

Moradia getMoradiaLocacao(Locacao l){
    locacao lo = (locacao) l;
    return lo->moradia;
}

void setMoradiaLocacao(Locacao l, Moradia m){
    locacao lo = (locacao) l;
    lo->moradia = m;
}

void setSituacao(Locacao l,char* situ){
    locacao lo = (locacao) l;
    strcpy(lo->situacao,situ);
}

char* getSituacao(Locacao l){
    locacao lo = (locacao) l;
    return lo->situacao;
}


