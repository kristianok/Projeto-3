#ifndef TABELA_H
#define TABELA_H

typedef void* TabelaEspalhamento;
typedef void* Elemento;
typedef void* Item;

#include "listaDup.h"
#include "locacao.h"
#include "moradia.h"
#include "pessoa.h"

/*
    Este modulo contem toda a implementacao referente ao TAD Tabela de Espalhamente
    Contem as funcoes responsaveis pela organizacao desta estrutura de dados
*/

//Cria uma nova tabela de espalhamento
TabelaEspalhamento criarTabelaEspalhamento();

//Remove um elemento da tabelha de espalhamento
TabelaEspalhamento removerElementoTabela(TabelaEspalhamento Tabela, char* chave);

//Insere um elemento na tabela de espalhamento
TabelaEspalhamento inserirElementoTabela(TabelaEspalhamento Tabela, char* chave, Item item);

//Busca a lista de todos os elementos daquela posicao da tabela. Inclui colisoes
Lista buscarElementoTabela(TabelaEspalhamento Tabela, char* chave);

//Transforma uma chave de caracteres em uma posicao na tabela
int transformarChave(char* chave);

//Desaloca a memoria utilizada pela tabela
TabelaEspalhamento freeTabela(TabelaEspalhamento Tabela);

//Funcao para liberar as listas e TADS especificos da tabela
TabelaEspalhamento liberarTabelasEspeciais(TabelaEspalhamento Tabela, int tipo);

//Busca um item com determinada chave na tabela
Item buscarItemTabela(TabelaEspalhamento tabela, char* chave);

#endif