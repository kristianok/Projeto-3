#include "moradia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mor {
    char face,cep[25],compl[25];
    double num;
    Pessoa pessoa;
    Locacao locacao;
};

typedef struct mor *moradia;

Moradia criarMoradia(char* cep, char face, double num, char* compl, Pessoa pessoa, Locacao locacao){
    moradia mora = (moradia) malloc(sizeof(struct mor));
    strcpy(mora->cep,cep);
    mora->face = face;
    mora->num = num;
    strcpy(mora->compl,compl);
    mora->locacao = locacao;
    mora->pessoa = pessoa;
    return mora;
}

double* getCoordenadaMoradia(Quadra quadra, Moradia m){
    moradia mor = (moradia) m;
    if(m == NULL || quadra == NULL){
        return NULL;
    }
    double* coordenada = (double*) malloc(sizeof(double)*2);
    if(mor->face == 'S'){
        coordenada[0] = getX(quadra) + mor->num;
        coordenada[1] = getY(quadra);
    }
    else if(mor->face == 'N'){
        coordenada[0] = getX(quadra) + mor->num;
        coordenada[1] = getY(quadra) + getH(quadra);
    }
    else if(mor->face == 'O'){
        coordenada[0] = getX(quadra) + getW(quadra);
        coordenada[1] = getY(quadra)+ mor->num;
    }
    else{
        coordenada[0] = getX(quadra);
        coordenada[1] = getY(quadra)+ mor->num; 
    }
    return coordenada;
}

char getFace(Moradia m){
    moradia mo = (moradia) m;
    return mo->face;
}

char* getCepMoradia(Moradia m){
    moradia mo = (moradia) m;
    return mo->cep;
}

char* getComplemento(Moradia m){
    moradia mo = (moradia) m;
    return mo->compl;
}

double getNumero(Moradia m){
    moradia mo = (moradia) m;
    return mo->num;
}

Pessoa getPessoa(Moradia m){
    moradia mo = (moradia) m;
    return mo->pessoa;
}

void setPessoa(Moradia m, Pessoa p){
    moradia mo = (moradia) m;
    mo->pessoa = p;
}

Locacao getLocacao(Moradia m){
    moradia mo = (moradia) m;
    return mo->locacao;
}

void setLocacao(Moradia m, Locacao loc){
    moradia mo = (moradia) m;
    mo->locacao = loc;
}

Moradia freeMoradia(Moradia m){
    moradia mo = (moradia) m;
    free(mo);
}

