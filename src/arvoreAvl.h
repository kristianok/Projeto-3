#ifndef ARVOREAVL_H
#define ARVOREAVL_H

typedef void* Item;
typedef void *ArvoreAvl;

#include "listaDup.h"
#include "stdio.h"
#include "quadra.h"

/*
    Este modulo contem toda a implementacao referente ao TAD Arvore Avl
    Contem as funcoes responsaveis pela organizacao desta estrutura de dados
*/


/*Retorna uma lista de todas as quadras em uma determinada regiao, realizando podas
por meio do xMax e xMin dos nos*/
Lista buscarRegiao(ArvoreAvl arvore, Lista encontrados, Quadra regiao, double x, double xMax);

//Cria um nodo da arvore avl
ArvoreAvl criarFolha(Item item, double x);

//Insere um nodo em uma arvore avl
ArvoreAvl inserirArvoreAvl(ArvoreAvl Avl,Item item, double x);

//Remove um item armazenado na arvore avl
ArvoreAvl removerArvoreAvl(ArvoreAvl arvore, int x, Item item);

//Realiza uma rotacao para a direita na arvore 
ArvoreAvl rotacionarDireita(ArvoreAvl No);

//Realiza uma rotacao para a esquerda na arvore 
ArvoreAvl rotacionarEsquerda(ArvoreAvl No);

//Retorna o maior valor entre dois
int maiorValor(int a, int b);

//Retorna a altura de um no na arvore
int getAlturaAvl(ArvoreAvl Arvore);

//Calcula o balanceamento de um no da arvore
int calcularBalanceamento(ArvoreAvl Avl);

//Busca o no com valor minimo de uma subarvore
ArvoreAvl minimoNoArvore(ArvoreAvl arvore);

//Retorna a subarvore direita de um no
ArvoreAvl getNoAvlDireito(ArvoreAvl ar);

//Retorna a subarvore esquerda de um no
ArvoreAvl getNoAvlEsquerdo(ArvoreAvl ar);

//Retorna um item armazenado em um no da arvore
ArvoreAvl getItemAvl(ArvoreAvl ar);

//Retorna a chave da arvore avl
double getXAvl(ArvoreAvl ar);

//Copia o conteudo do no2 para o no1
void copiarNo(ArvoreAvl no1, ArvoreAvl no2);

/*Determina o valor maximo de uma subarvore, visto que p eh o no pai
e f o no filho */
void determinarMinMax(ArvoreAvl p, ArvoreAvl f);

//Calcula novamente os valores minimos e maximos de um no e seus filhos
void retornarMinMax(ArvoreAvl ar);

//Realiza o processo de balanceamento da arvore avl
ArvoreAvl balancearArvoreAvl(ArvoreAvl a);

//Retorna o valor de x maximo de uma subarvore
double getXMax(ArvoreAvl ar);

//Retorna o valor de x minimo de uma subarvore
double getXMin(ArvoreAvl ar);

//Desaloca a memoria utilizada por um TAD arvore avl
ArvoreAvl freeArvoreAvl(ArvoreAvl arvore);

//Desenha uma arvore avl em um arquivo dots
void desenharArvoreAvl(ArvoreAvl arvore, const char *narq);

//Gera os dados a serem inseridos no arquivo dots
void gerarDadosDot(ArvoreAvl no, FILE *tf);

#endif