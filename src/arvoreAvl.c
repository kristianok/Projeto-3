#include "arvoreAvl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct nodoAvl{
    Item item;
    double x, xMax, xMin;
	struct nodoAvl *esquerda, *direita;
    int altura;
};

typedef struct nodoAvl *noAvl;

ArvoreAvl criarFolha(Item item, double x){
    noAvl avl = (noAvl) malloc(sizeof(struct nodoAvl));
    //Especial da lista na avl
    Lista lista = createLista();
    insert(lista,item," ");
    avl->item = lista;
    avl->direita = NULL;
    avl->esquerda = NULL;
    avl->x = x;
    avl->xMin = x;
    avl->xMax = x + getW(item);
    avl->altura = 1;
    return avl;
}

ArvoreAvl inserirArvoreAvl(ArvoreAvl Avl,Item item, double x){
    if(Avl == NULL){
        noAvl avl = criarFolha(item,x);
        return avl;
    }
    noAvl aux;
    noAvl arvore = (noAvl) Avl;

    if (x < arvore->x){
        arvore->esquerda  = inserirArvoreAvl(arvore->esquerda, item, x);
        aux = arvore->esquerda;
    }
    else if (x > arvore->x){
        arvore->direita = inserirArvoreAvl(arvore->direita, item, x);
        aux = arvore->direita;
    }
    else {
        insert(arvore->item, item," ");
        if(arvore->xMax < x+getW(item)){
			arvore->xMax = x+getW(item);
        }
		if(arvore->xMin > x){
			arvore->xMin = x;
        }
        return arvore;
    }  
    noAvl no = balancearArvoreAvl(arvore);
    if(no == arvore){
        determinarMinMax(Avl,aux);
    }
    else{
        return no;
    }
    return arvore;
}

ArvoreAvl removerArvoreAvl(ArvoreAvl arvore, int x, Item item){
    if (arvore == NULL){
        return arvore;
    }
    noAvl aux;
    
    noAvl raiz = (noAvl) arvore;

    if (x < raiz->x){
        raiz->esquerda = removerArvoreAvl(raiz->esquerda, x, item);
    }
    else if(x > raiz->x){
        raiz->direita = removerArvoreAvl(raiz->direita, x, item);
    }
    else {
        if(raiz->item != NULL && length(raiz->item) > 1){
            removePeloItemD(raiz->item,item);
            return raiz;
        }
        if(raiz->item != NULL && length(raiz->item) == 1){
            removePeloItemD(raiz->item,item);
            apagarLista(raiz->item);
        }
        if((raiz->esquerda == NULL) || (raiz->direita == NULL)){
            if(raiz->esquerda != NULL){
                aux = raiz->esquerda;
            }
            else {
                aux = raiz->direita;
            }
            if (aux == NULL) {
                aux = raiz;
                raiz = NULL;
            }
            else{
                *raiz = *aux; 
            }
            free(aux);
        }
        else {
            noAvl filho = (noAvl) minimoNoArvore(raiz->direita);
            copiarNo(raiz,filho);
            raiz->direita = removerArvoreAvl(raiz->direita, filho->x, item);
        }
    }
    if(raiz == NULL){
      return raiz;
    }

    noAvl no = balancearArvoreAvl(raiz);

	if(no == raiz){
		retornarMinMax(no);
    }
	else{
		return no;
    }
    return raiz;
}

ArvoreAvl balancearArvoreAvl(ArvoreAvl a){
    noAvl raiz = (noAvl) a;
    raiz->altura = 1 + maiorValor(getAlturaAvl(raiz->esquerda),getAlturaAvl(raiz->direita));
    int balanceamento = calcularBalanceamento(raiz);
    // esquerda esquerda
    if (balanceamento > 1 && calcularBalanceamento(raiz->esquerda) >= 0){
        return rotacionarDireita(raiz);
    }
 
    // esquerda direita
    if (balanceamento > 1 && calcularBalanceamento(raiz->esquerda) < 0){
        raiz->esquerda =  rotacionarEsquerda(raiz->esquerda);
        return rotacionarDireita(raiz);
    }
 
    // direita direita
    if (balanceamento < -1 && calcularBalanceamento(raiz->direita) <= 0){
        return rotacionarEsquerda(raiz);
    }
 
    // direita esquerda
    if (balanceamento < -1 && calcularBalanceamento(raiz->direita) > 0){
        raiz->direita = rotacionarDireita(raiz->direita);
        return rotacionarEsquerda(raiz);
    }
    return raiz;
}

ArvoreAvl rotacionarDireita(ArvoreAvl No){
    noAvl no = (noAvl) No;

    noAvl noEsquerda = no->esquerda;
    noAvl noDireitaEsquerda = noEsquerda->direita;
 
    noEsquerda->direita = no;
    no->esquerda = noDireitaEsquerda;
 
    no->altura = maiorValor(getAlturaAvl(no->esquerda), getAlturaAvl(no->direita))+1;
    noEsquerda->altura = maiorValor(getAlturaAvl(noEsquerda->esquerda), getAlturaAvl(noEsquerda->direita))+1;

    retornarMinMax(no);
    determinarMinMax(noEsquerda, no);
 
    return noEsquerda;
}

ArvoreAvl rotacionarEsquerda(ArvoreAvl No){
    noAvl no = (noAvl) No;

    noAvl noDireita = no->direita;
    noAvl noDireitaEsquerda = noDireita->esquerda;
 
    noDireita->esquerda = no;
    no->direita = noDireitaEsquerda;
 
    no->altura = maiorValor(getAlturaAvl(no->esquerda),getAlturaAvl(no->direita))+1;
    noDireita->altura = maiorValor(getAlturaAvl(noDireita->esquerda),getAlturaAvl(noDireita->direita))+1;

    retornarMinMax(no);
    determinarMinMax(noDireita, no);
 
    return noDireita;
}

int maiorValor(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int getAlturaAvl(ArvoreAvl Arvore){
    if(Arvore == NULL){
        return 0;
    }
    noAvl avl = (noAvl) Arvore;
    return avl->altura;
}

int calcularBalanceamento(ArvoreAvl Avl){
    if (Avl == NULL){
        return 0;
    }
    noAvl avl = (noAvl) Avl;
    return getAlturaAvl(avl->esquerda) - getAlturaAvl(avl->direita);
}

ArvoreAvl minimoNoArvore(ArvoreAvl arvore){
    noAvl atual = (noAvl) arvore;
    while (atual->esquerda != NULL){
        atual = atual->esquerda;
    }
    return atual;
}

ArvoreAvl getNoAvlEsquerdo(ArvoreAvl ar){
    if(ar == NULL){
        return NULL;
    }
    noAvl no = (noAvl) ar;
    return no->esquerda;
}

ArvoreAvl getNoAvlDireito(ArvoreAvl ar){
    if(ar == NULL){
        return NULL;
    }
    noAvl no = (noAvl) ar;
    return no->direita;
}

ArvoreAvl getItemAvl(ArvoreAvl ar){
    if(ar == NULL){
        return NULL;
    }
    noAvl no = (noAvl) ar;
    return no->item;
}

double getXAvl(ArvoreAvl ar){
    if(ar == NULL){
        return 0;
    }
    noAvl no = (noAvl) ar;
    return no->x;
}

double getXMax(ArvoreAvl ar){
    if(ar == NULL){
        return 0;
    }
    noAvl no = (noAvl) ar;
    return no->xMax;
}

double getXMin(ArvoreAvl ar){
    if(ar == NULL){
        return 0;
    }
    noAvl no = (noAvl) ar;
    return no->xMin;
}

void determinarMinMax(ArvoreAvl p, ArvoreAvl f){
    noAvl pai = (noAvl) p;
    noAvl filho = (noAvl) f; 
    if(filho == NULL || pai == NULL){
        return;
    }
    if(filho->xMax > pai->xMax){
        pai->xMax = filho->xMax ;
    }
     if(filho->xMin < pai->xMin){
        pai->xMin = filho->xMin ;
    }
}

void retornarMinMax(ArvoreAvl ar){
    noAvl no = (noAvl) ar;
    if(no == NULL){
        return;
    }
    no->xMin = no->x;
    no->xMax = 0;
    determinarMinMax(no,no->direita);
    determinarMinMax(no,no->esquerda);
    Lista listaQuadras = no->item;
    Posic p = getFirst(listaQuadras);
    while(p != NULL){
        Quadra quadra = getItem(p);
        if(getX(quadra) + getW(quadra) > no->xMax){
            no->xMax = getX(quadra) + getW(quadra);
        }
        p = getNext(listaQuadras,p);
    }
}

void copiarNo(ArvoreAvl no1, ArvoreAvl no2){
    noAvl ar1 = (noAvl) no1;
    noAvl ar2 = (noAvl) no2;

    ar1->item = ar2->item;
    ar1->x = ar2->x;
    ar1->xMax = ar2->xMax;
    ar1->xMin = ar2->xMin;
    ar2->item = NULL;
}

ArvoreAvl freeArvoreAvl(ArvoreAvl arvore){
    if(arvore == NULL){
        return NULL;
    }
    noAvl no = (noAvl) arvore;
    freeArvoreAvl(no->direita);
    freeArvoreAvl(no->esquerda);
    free(no);
    return NULL;
}

void gerarDadosDot(ArvoreAvl no, FILE *tf){
    noAvl p = (noAvl) no;
    char *s;
    char *edge = " -> ";
    char *NullNode = " [shape=point, style=\"invis\"]";
    char *invisEdge = " [style=\"invis\"]";
    char *ident = "   ";

    if (p == NULL){
      return;
    }

    char rtkey[75];
    char rtlabel[200];
    sprintf(rtkey,"%f",p->x);
    int qtdRet = length(getItemAvl(p));
    char* cep1 = getCep(getItem(getFirst(getItemAvl(p))));
    if(qtdRet > 1){
        char* cep2 = getCep(getItem(getNext(getItemAvl(p),getFirst(getItemAvl(p)))));
        sprintf(rtlabel,"%s [label=\"(%f)\n xMin: %f xMax: %f \n qtdQuadras: %d ceps: %s, %s (...) bf: %d\"]",
        rtkey,p->x,p->xMin, p->xMax,qtdRet, cep1,cep2,calcularBalanceamento(p));
    }
    else {
        sprintf(rtlabel,"%s [label=\"(%f)\n xMin: %f xMax: %f \n qtdQuadras: %d cep: %s bf: %d\"]",
        rtkey,p->x,p->xMin, p->xMax, qtdRet,cep1,calcularBalanceamento(p));
    }

    char lst[600];
    char rst[600];

    char lkey[100];
    char rkey[100];
    char lpreamb[300];
    char rpreamb[300];
    char lpost[100];
    char rpost[100];


    if (p->esquerda != 0){
      sprintf(lpreamb," ");
      sprintf(lkey,"%f",p->esquerda->x);
      sprintf(lpost," ");
    }
    else{
      /* Nao existe sub-arvore esquerda. Coloca uma
         "folha falsa" invisivel para tentar garantir
         que a sub-arvore direita  seja desenhada um pouco
         para a direita */

      sprintf(lkey, "nullL%s",rtkey);
      sprintf(lpreamb,"%s%s%s;\n", ident, lkey, NullNode);
      sprintf(lpost,"%s",invisEdge);
    }


    if (p->direita != 0){
      sprintf(rpreamb, " ");
      sprintf(rkey, "%f",p->direita->x);
      sprintf(rpost," ");
    }
    else{
      /* Não existe sub-arvore direita. Coloca "folha falsa" invisivel" */
      sprintf(rkey,"nullR%s",rtkey);
      sprintf(rpreamb,"%s%s%s;\n",ident, rkey, NullNode);
      sprintf(rpost,"%s", invisEdge);
    }


    sprintf(lst,"%s%s%s%s%s%s ;\n",lpreamb,ident,rtkey,edge,lkey,lpost);
    sprintf(rst,"%s%s%s%s%s%s ;\n",rpreamb,ident,rtkey,edge,rkey,rpost);
    fprintf(tf,"%s",rtlabel);
    fprintf(tf,"%s",lst);
    fprintf(tf,"%s",rst);

    gerarDadosDot(p->esquerda,tf);
    gerarDadosDot(p->direita,tf);
}

void desenharArvoreAvl(ArvoreAvl arvore,const char *narq){
    if(arvore == NULL){
        return;
    }
    noAvl avl = (noAvl) arvore;
    FILE *dot;
    dot = fopen(narq,"w");
    fprintf(dot,"digraph T {\n");
    gerarDadosDot(avl,dot);
    fprintf(dot,"}\n");
    fclose(dot);
}

Lista buscarRegiao(ArvoreAvl arvore, Lista encontrados, Quadra regiao, double x, double xMax){
    noAvl quadras = (noAvl) arvore;
    Lista listaQuadras = getItemAvl(quadras);
    Posic p = getFirst(listaQuadras);
    Quadra quadra;
    for(p = getFirst(listaQuadras); p != NULL; p= getNext(listaQuadras,p)){
        quadra = getItem(p);
        if(checarInterior(regiao, quadra)){
            insert(encontrados,quadra," ");
        }
    }
    if(quadras->esquerda != NULL && quadras->esquerda->xMax >= x &&
    quadras->esquerda->xMin <= xMax){
        buscarRegiao(quadras->esquerda, encontrados, regiao, x, xMax);         
    }
    if(quadras->direita != NULL && quadras->direita->xMax >= x &&
    quadras->direita->xMin <= xMax){
        buscarRegiao(quadras->direita, encontrados, regiao, x, xMax);
    }
    return encontrados;
}