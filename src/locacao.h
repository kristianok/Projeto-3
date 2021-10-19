#ifndef LOCACAO_H
#define LOCACAO_H

typedef void* Locacao;

#include "moradia.h"

/*
    Este modulo contem toda a implementacao referente ao TAD Contrato de Locacao
*/

//Aloca a memoria e inicializa o TAD locacao
Locacao criarLocacao(char* id, double area, double valor, Moradia moradia);

//Libera a memoria utilizada pelo TAD locacao
void freeLocacao(Locacao Loc);

//Retorna o id de uma locacao
char* getId(Locacao l);

//Retorna a area de uma locacao
double getArea(Locacao l);

//Retorna o valor de uma locacao
double getValor(Locacao l);

//Retorna a moradia relacionada a um contrato de locacao
Moradia getMoradiaLocacao(Locacao l);

//Determina a situacao de um contrato de locacao
void setSituacao(Locacao l,char* situ);

//Retorna a situacao de um contrato de locacao
char* getSituacao(Locacao l);

//Determina a moradia a qual determinada locacao esta relacionada
void setMoradiaLocacao(Locacao l, Moradia m);

#endif