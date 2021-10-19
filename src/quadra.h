#ifndef QUADRA_H
#define QUADRA_H

typedef void* Quadra;

#include "arvoreAvl.h"
#include "listaDup.h"

/*
    Este modulo contem toda a implementacao referente ao TAD quadra
    Contem as funcoes responsaveis pela manipulacao dos seus dados e de
    suas caracteristicas proprias 
*/

//Cria uma quadra 
Quadra criarQuadra(double espessura, char* corBorda, char* corCentro, 
char* id, double x, double y, double w, double h);

// Retorna os valores referentes ao parametro cep da quadra.
char* getCep(Quadra Qua);

// Retorna os valores referentes ao parametro x da quadra.
double getX(Quadra Qua);

// Retorna os valores referentes ao parametro y da quadra.
double getY(Quadra Qua);

// Retorna os valores referentes ao parametro w da quadra.
double getW(Quadra Qua);

// Retorna os valores referentes ao parametro h da quadra.
double getH(Quadra Qua);

// Retorna os valores referentes ao parametro cor de preenchimento da quadra.
char* getPreenchimento(Quadra Qua);

// Retorna os valores referentes ao parametro cor da borda da quadra.
char* getBorda(Quadra Qua);

// Define os valores referentes ao parametro cor da borda da quadra.
void setBorda(Quadra Qua, char* corB);

double getEspessura(Quadra Qua);

//Define os valores referentes ao parametro cor de preenchimento da quadra.
void setPreenchimento(Quadra Qua, char* corP);

//Desaloca um a memoria utilizada para uma quadra
void freeQuadra(Quadra Qua);

//Checa se a quadr2 esta dentro da quadr1
int checarInterior(Quadra Quad1, Quadra Quad2);

//Checa se o ponto esta dentro da quadr1
int checarPontoInterno(int x1, int y1, Quadra quad1);

//Retorna o centro de massa de uma quadra
double* centroQuadra(Quadra qua);

//Funcao especial que libera a memoria utilizada por uma arvore avl e suas quadras internas
ArvoreAvl liberarArvoreQuadras(ArvoreAvl quadras);

#endif
