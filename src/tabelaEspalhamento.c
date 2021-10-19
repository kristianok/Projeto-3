#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabelaEspalhamento.h"

#define tam 5000

struct ele {
    char chave[30];
    Lista item;
};

typedef struct ele *elemento;

struct tab {
    int tamanho;
    elemento elementos;
};

typedef struct tab *tabela;

TabelaEspalhamento criarTabelaEspalhamento(){
    tabela tabe = (tabela) malloc(sizeof(struct tab));
    int tamanho = tam;
    tabe->tamanho = tamanho;
    tabe->elementos = (elemento)malloc(sizeof(struct ele)*tabe->tamanho);
    for(int i =0;i<tabe->tamanho;i++){
        tabe->elementos[i].item = createLista();
    }  
    return tabe;
}

TabelaEspalhamento removerElementoTabela(TabelaEspalhamento Tabela, char* chave){
    if(Tabela == NULL){
        return Tabela;
    }

    tabela tabe = (tabela) Tabela;
    int posicao = transformarChave(chave);

    Lista l = tabe->elementos[posicao].item;
    Posic p = getFirst(l);
    while(p != NULL){
        if(strcmp(getChaveD(p),chave) == 0){
            tabe->elementos[posicao].item = removeD(l,p);
            break;
        }
        p = getNext(l,p);
    }
    return tabe;
}

TabelaEspalhamento inserirElementoTabela(TabelaEspalhamento Tabela, char* chave, Item item){
    tabela tabe = (tabela) Tabela;
    int posicao = transformarChave(chave);
    memcpy(tabe->elementos[posicao].chave, chave, strlen(chave)+1);
    insert(tabe->elementos[posicao].item,item,chave);
    return tabe;
}

Lista buscarElementoTabela(TabelaEspalhamento Tabela, char* chave){
    tabela tabe = (tabela) Tabela;
    int posicao = transformarChave(chave);
    return tabe->elementos[posicao].item;
}

Item buscarItemTabela(TabelaEspalhamento tabela, char* chave){
    Lista items = buscarElementoTabela(tabela,chave);
    Posic p = getFirst(items);
    while(p != NULL){ 
        if(strcmp(getChaveD(p),chave)==0){
            Item item = getItem(p);
            return item;
        }
        p = getNext(items,p);
    }
    return NULL; 
}

int transformarChave(char* chave){
    int posicao = 0;
    for(int i = 0; i< strlen(chave);i++){
        posicao += (int) chave[i];
    }
    posicao = posicao % tam;
    return posicao;
}

TabelaEspalhamento freeTabela(TabelaEspalhamento Tabela){
    tabela tab = (tabela) Tabela;
    free(tab->elementos);
    free(tab);
    return NULL;
}

TabelaEspalhamento liberarTabelasEspeciais(TabelaEspalhamento Tabela, int tipo){
    if(Tabela == NULL){
        return NULL;
    }
    tabela tab = (tabela) Tabela;
    for(int i = 0; i < tab->tamanho; i++){
        Lista items = tab->elementos[i].item;
        Posic p = getFirst(items);
	    while(p != NULL && tipo != 3){
            if(tipo == 0){
		        freeMoradia(getItem(p));
            }
            else if (tipo == 1){
		        freeLocacao(getItem(p));
            }
            else if (tipo == 2) {
                freePessoa(getItem(p));
            }
            p = getNext(items,p);
	    }
        items = apagarLista(items);
    }
    freeTabela(tab);
}