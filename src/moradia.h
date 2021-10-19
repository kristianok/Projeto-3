#ifndef MORADOR_H
#define MORADOR_H

typedef void* Moradia;

#include "pessoa.h"
#include "locacao.h"
#include "quadra.h"

/*
    Este modulo contem toda a implementacao referente ao TAD Moradia/Moradores
*/

//Aloca a memoria e inicializa o TAD moradia
Moradia criarMoradia(char* cep, char face, double num, char* compl, Pessoa pessoa, Locacao locacao);

//Retorna a posicao de uma moradia de acordo com sua quadra
double* getCoordenadaMoradia(Quadra quadra, Moradia m);

//Retorna a face de uma moradia
char getFace(Moradia m);

//Retorna o cep de uma moradia
char* getCepMoradia(Moradia m);

//Retorna o complemento de uma moradia
char* getComplemento(Moradia m);

//Retorna o numero de uma moradia
double getNumero(Moradia m);

//Retorna a pessoa que reside na moradia
Pessoa getPessoa(Moradia m);

//Determina uma pessoa como moradora de uma moradia
void setPessoa(Moradia m, Pessoa p);

//Retorna o contrato de locacao relacionado a moradia
Locacao getLocacao(Moradia m);

//Desaloca a memoria utilizada pelo TAD moradia
Moradia freeMoradia(Moradia m);

//Determina um contrato de locacao para uma moradia
void setLocacao(Moradia m, Locacao loc);

#endif