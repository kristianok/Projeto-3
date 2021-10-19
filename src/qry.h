#ifndef QRY_H
#define QRY_H
#include "quadra.h"
#include "path.h"
#include "svg.h"
#include "txt.h"
#include "tabelaEspalhamento.h"
#include "arvoreAvl.h"
#include "moradia.h"
#include "pessoa.h"
#include "locacao.h"

/*
    Este módulo prove operacoes para o funcionamento
    de todos os comandos de consultas solicitadas
    pelos arquivos qry
*/

//Funcao responsavel pelo comando oloc?
void oloc2(ArvoreAvl quadras, TabelaEspalhamento moradiasCep, TabelaEspalhamento locacoes,
Quadra regiao, FILE* txt, SvgFile svg);

//Funcao responsavel pelo comando oloc
TabelaEspalhamento oloc(TabelaEspalhamento locacoes, TabelaEspalhamento moradiasCep,
char* id, char* cep, char face,double num, char* compl, double ar, double v);

//Funcao responsavel pelo comando mud
void mud(char* cpf, Moradia moradia, TabelaEspalhamento moradiasCep,
TabelaEspalhamento moradiasCpf,FILE* txt, SvgFile svg, TabelaEspalhamento tabelaQuadras);

//Funcao responsavel pelo comando dm
void dm(ArvoreAvl quadras, TabelaEspalhamento moradiasCpf,char* cpf, FILE* txt,
SvgFile svg, TabelaEspalhamento tabelaQuadras, int altura);

//Funcao responsavel pelo comando m
void m(TabelaEspalhamento moradiasCep, char* cep, FILE* txt);

//Funcao responsavel pelo comando del e reaproveitada para o comando catac
ArvoreAvl del(ArvoreAvl quadras,TabelaEspalhamento moradiasCep, TabelaEspalhamento moradiasCpf,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas, char* cep, SvgFile svg, FILE* txt,
 TabelaEspalhamento tabelaQuadras, int catac, int altura);

//Funcao responsavel pelo comando loc
void loc(char* cpf, char* id, FILE* txt, SvgFile svg,TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas, TabelaEspalhamento moradiasCpf, int altura);

//Funcao responsavel pelo comando loc?
void loc2(char* id, FILE* txt, SvgFile svg,TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas);

//Funcao responsavel pelo comando dloc
void dloc(char* id, FILE* txt,SvgFile svg, TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, int altura);

//Funcao responsavel pelo comando hom e mul, a depender do sexo passado como parametro
void homMul(ArvoreAvl quadras, TabelaEspalhamento moradiasCep, TabelaEspalhamento tabelaQuadras,
Quadra regiao, char sexo, FILE* txt, SvgFile svg, int altura);

//Funcao responsavel pelo comando catac
ArvoreAvl catac(ArvoreAvl quadras, TabelaEspalhamento moradiasCep,
TabelaEspalhamento moradiasCpf, TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas, Quadra regiao, FILE* txt, SvgFile svg);

#endif