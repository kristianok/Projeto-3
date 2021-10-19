#ifndef TXT_H
#define TXT_H
#include <stdio.h>
#include "quadra.h"
#include "path.h"
#include "locacao.h"
#include "moradia.h"
#include "pessoa.h"

/*
    Este modulo prove operacoes para a criacao, delecao e manipulacao de arquivos no formato txt.
    Tambem eh responsavel por escrever dados especificos solicitados pelas funcoes de consulta.
 */

//Gera e abre um novo arquivo txt e o retorna
FILE* abrirNovoTxt(char* nomeArqGeo, char* nomeArqQry, char* pathBSD);

//Fecha um arquivo txt
void fecharArquivoTxt(FILE* txt);

//Escreve o nome do aluno no txt
void escreverNome(FILE* txt);

//Retorna os dados de uma quadra em formato de texto
char* dadosQuadra(Quadra quadra);

//Retorna os dados de uma locacao em formato de texto
char* dadosLocacao(Locacao locacao);

//Retorna os dados de uma moradia em formato de texto
char* dadosMoradia(Moradia moradia);

//Retorna os dados de uma pessoa em formato de texto
char* dadosPessoa(Pessoa pessoa);

//Insere uma linha vazia no txt
void pularLinha(FILE* txt);

//Escreve um determinado texto no txt
void escrever(FILE* txt, char* texto);
#endif