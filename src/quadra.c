#include "quadra.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct quadr {
	char cep[50], corPreenchimento[25], corBorda[25];
	double espessura,x,y,w,h;
};

typedef struct quadr quadra;

void freeQuadra(Quadra Qua){
	quadra* quad = (quadra*) Qua;
	free(quad);
}

Quadra criarQuadra(double espessura, char* corBorda, char* corPreenchimento, char* cep, double x, double y, double w, double h){
	quadra* quad = (quadra*)malloc(sizeof(quadra));
	strcpy(quad->cep,cep);
	strcpy(quad->corBorda,corBorda);
	strcpy(quad->corPreenchimento,corPreenchimento);
	quad->espessura = espessura;
	quad->x = x;
	quad->y = y;
	quad->w = w;
	quad->h = h;	
	return quad;
}

double getEspessura(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->espessura;
}

void setX(Quadra Qua, double x){
	quadra* qua= (quadra*) Qua;
	qua->x = x;
}

void setY(Quadra Qua, double y){
	quadra* qua= (quadra*) Qua;
	qua->y = y;	
}

void setW(Quadra Qua, double w){
	quadra* qua= (quadra*) Qua;
	qua->w = w;
}

void setH(Quadra Qua, double h){
	quadra* qua= (quadra*) Qua;
	qua->h = h;	
}

char* getCep(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->cep;
}

double getX(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->x;
}

double getY(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->y;	
}

double getW(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->w;
}

double getH(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->h;	
}

char* getPreenchimento(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->corPreenchimento;
}

char* getBorda(Quadra Qua){
	quadra* qua= (quadra*) Qua;
	return qua->corBorda;
}

void setPreenchimento(Quadra Qua, char* corP){
	quadra* qua= (quadra*) Qua;
	strcpy(qua->corPreenchimento, corP);
}

void setBorda(Quadra Qua, char* corB){
	quadra* qua= (quadra*) Qua;
	strcpy(qua->corBorda, corB);
}

//Retorna verdadeiro quando o quad2 esta dentro do quad1
int checarInterior(Quadra Quad1, Quadra Quad2){
	if(Quad1 == NULL || Quad2 == NULL){
		return 0;
	}
	quadra* quad1 = (quadra*) Quad1;
	quadra* quad2 = (quadra*) Quad2;
	double x,y,w,h,xl1,xr1,yl1,yr1,xl3,xr3,yl3,yr3;
	x = quad1->x;
    y = quad1->y;
    w = quad1->w;
    h = quad1->h;
    xl3 = x;
    xr3 = x+w;
    yl3 = y+h;
    yr3 = y;
	x = quad2->x;
    y = quad2->y;
    w = quad2->w;
    h = quad2->h;
    xl1 = x;
    xr1 = x+w;
    yl1 = y+h;
    yr1 = y;  
	if(xl1 >= xl3 && xr1<= xr3 && yr1 >= yr3 && yl1 <= yl3){
		return 1;
	}
	return 0;
}

int checarPontoInterno(int x1, int y1, Quadra quad1){
	if(quad1 == NULL){
		return 0;
	}
	quadra *qua= (quadra*) quad1;
	double x,y,w,h;
	x = qua->x;
    y = qua->y;
    w = qua->w;
    h = qua->h;
	if(x1 < x + w && x1 > x && y1 > y && y1 < y+h){
		return 1;
	}
	return 0;
}
double* centroQuadra(Quadra qua){
	if(qua== NULL){
		return NULL;
	}
	quadra *quadr = (quadra*) qua;
    double* centroQua = (double*) malloc(sizeof(double)*2);
    centroQua[0] = quadr->x + (quadr->w/2);
    centroQua[1] = quadr->y + (quadr->h/2);
	return centroQua;
}

ArvoreAvl liberarArvoreQuadras(ArvoreAvl quadras){
	if(quadras == NULL){
		return NULL;
	}
	Lista quadrasMesmoX = getItemAvl(quadras);
	for(Posic p = getFirst(quadrasMesmoX); p != NULL; p = getNext(quadras,p)){
		freeQuadra(getItem(p));
	}
	apagarLista(quadrasMesmoX);
	liberarArvoreQuadras(getNoAvlDireito(quadras));
	liberarArvoreQuadras(getNoAvlEsquerdo(quadras));
	return NULL;
}




