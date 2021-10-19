#ifndef ARQUIVOPM_H
#define ARQUIVOPM_H

#include "quadra.h"
#include "arvoreAvl.h"
#include "tabelaEspalhamento.h"
#include "pessoa.h"
#include "moradia.h"
#include "qry.h"

/*
    Este modulo contem toda a implementacao referente a leitura dos arquivos pm
*/

//Função responsável por ler e armazenar os dados das pessoas descritas no arquivo pm
TabelaEspalhamento lerPessoas(char* arqPm, char* nomeArqPm);

//Função responsável por ler e armazenar os dados dos moradores descritos no arquivo pm
void lerMoradias(char* arqPm, char* nomeArqPm, 
TabelaEspalhamento pessoas, TabelaEspalhamento *moCep, TabelaEspalhamento *moCpf);


#endif