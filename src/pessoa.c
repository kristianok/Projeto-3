#include "pessoa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct pes {
	char cpf[25], nome[25], sobrenome[50], nascimento[25], sexo;
    Moradia moradia;
};

typedef struct pes *pessoa;

Pessoa criarPessoa(char* cpf, char* nome, char* sobrenome, 
char* nascimento, char sexo, Moradia moradia){
    pessoa p = (pessoa) malloc(sizeof(struct pes));
    strcpy(p->cpf,cpf);
    strcpy(p->nome,nome);
    strcpy(p->sobrenome,sobrenome);
    strcpy(p->nascimento,nascimento);
    p->sexo = sexo;
    p->moradia = moradia;
    return p;
}

char* getCpf(Pessoa p){
    pessoa pe = (pessoa) p;
    return pe->cpf;
}

char* getNome(Pessoa p){
    pessoa pe = (pessoa) p;
    return pe->nome;
}

char* getSobrenome(Pessoa p){
    pessoa pe = (pessoa) p;
    return pe->sobrenome;
}

char* getNascimento(Pessoa p){
    pessoa pe = (pessoa) p;
    return pe->nascimento;
}

char getSexo(Pessoa p){
    pessoa pe = (pessoa) p;
    return pe->sexo;
}

Moradia getMoradia(Pessoa p){
    pessoa pe = (pessoa) p;
    return pe->moradia;
}

void setMoradia(Pessoa p, Moradia m){
    pessoa pe = (pessoa) p;
    pe->moradia = m;
}

void freePessoa(Pessoa p){
    pessoa pe = (pessoa) p;
    free(pe);
}

