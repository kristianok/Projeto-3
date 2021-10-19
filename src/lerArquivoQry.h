#ifndef LERQRY_H
#define LERQRY_H

#include "tabelaEspalhamento.h"
#include "arvoreAvl.h"
#include "svg.h"
#include "moradia.h"
#include "txt.h"
#include "qry.h"

/*
    Este modulo contem toda a implementacao referente a leitura dos arquivos qry
*/

//Função responsável por ler e interpretar os dados do arquivo qry passado nos parametros
void lerArquivoQry(char* arqQry, char* nomeArqQry, char* pathBSD, char* nomeArqGeo,
ArvoreAvl quadras,TabelaEspalhamento pessoas, TabelaEspalhamento moradiasCep,
TabelaEspalhamento moradiasCpf, TabelaEspalhamento tabelaQuadras);

#endif