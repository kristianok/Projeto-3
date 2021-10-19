#ifndef ARQUIVOGEO_H
#define ARQUIVOGEO_H

#include "arvoreAvl.h"
#include "quadra.h"
#include "svg.h"
#include "listaDup.h"
#include "txt.h"
#include "tabelaEspalhamento.h"

/*
    Este modulo contem toda a implementacao referente a leitura dos arquivos geo
*/

//Função responsável por ler e interpretar os dados do arquivo geo passado nos parametros
ArvoreAvl lerArquivoGeo(char* pathBSD, char* arqGeo, char* nomeArqGeo,
TabelaEspalhamento* tabelaQuadras);

#endif