#ifndef _SVGFILE_H__INCLUDE
#define _SVGFILE_H__INCLUDE

typedef void *SvgFile;

#include "quadra.h"
#include "path.h"
#include <stdio.h>
#include "arvoreAvl.h"
#include "listaDup.h"
#include "locacao.h"
#include "tabelaEspalhamento.h"
#include "moradia.h"

/*
    Este módulo prove operacoes para a criação de arquivos no formato svg. Um novo arquivo é criado por meio da operação newSvgFile (arquivo aberto) e é finalizado pela operação closeSvgFile (arquivo fechado).
    Várias operações para a inclusão de elementos svg podem ser invocados em arquivos
abertos, por exemplo, insertQuadra.
    Os elementos inseridos podem seguir o estilo padrão definido pela operação defineEstiloPadrao (veja, por exemplo, a operação insertQuadraPadrao)

 */


/*Insere a estrutura de um grafico com inicio na origem do arquivo svg para posteriormente inserir pontos.
Tem como parametros os maiores valores representados e a escala de cada eixo para definir os limites 
e as faixas de valores do grafico*/
void insertGrafico(SvgFile f,double maiorX, double maiorY, int escalaX, int escalaY,double tamanhoX, double tamanhoY);

//Insere um circulo no svg cujas propriedades sao passadas nos parametros
void insertCircle(SvgFile f, double x, double y, double r, char *cp, char *cb, double wb);

void escreverNomeSvg(SvgFile f);

/*
    Cria um novo arquivo (texto) com o nome "nomeArq".
    Caso o arquivo não possa ser criado (por exemplo, path incorreto), retorna NULL.
    Caso o arquivo já exista, ele é sobre-escrito.
 */
SvgFile newSvgFile(char *nomeArq);

/* 
   Insere um retângulo no arquivo f.
 */
void insertQuadra(SvgFile f, double x, double y,double w, double h, char *cp, 
     char *cb, double wb);


// Insere um quadra com opacidade 0 (transparente)
void insertQuadraTransparent(SvgFile f, double x, double y,double w, double h, char *cp, char *cb, double wb);
  
  /*
    Fecha o arquivo f. O efeito de qualquer outra operação sobre f é indeterminado.
 */
void closeSvgFile(SvgFile f);

//Insere um texto com valor numerico nas coordenadas indicadas nos parametros
void insertTxt(SvgFile f, double x, double y, double valor);

//Insere uma linha grossa com inicio no ponto x,y e termino no ponto x2,y2
void insertLinhaGrossa(SvgFile f,double x, double y, double x2, double y2, char* cor);

//Insere um txt no arquivo. Recebe como parametros caracteres alfanumericos e as coordenadas
void insertPalavras(SvgFile f, double x, double y, char* frase, double tamanhoFonte);

//Gera o nome do svg formado pelas consultas do qry
char* nomeSvgQry(char* nomeArqGeo, char* nomeArqQry, char* pathBSD);

//Gera o nome do svg formado pelas consultas do geo
char* nomeSvgGeo(char* nomeArqGeo, char* pathBSD);

//Insere uma linha entre dois pontos
void insertLinha(SvgFile f,double x, double y, double x2, double y2);

//Insere uma arvore avl no svg
void inserirArvoreQuadrasSvg(SvgFile f, ArvoreAvl quadras);

//Insere o estado de um determinado contrado de locacao no svg
void inserirEstadoLocacao(SvgFile svg, TabelaEspalhamento tabelaQuadras, Locacao locacao,
Moradia moradia);

//Insere uma elipse no svg
void insertElipse(SvgFile f, double x, double y, double rx,double ry, char *cp, char *cb, double wb);

#endif
