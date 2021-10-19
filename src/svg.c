#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"

struct StSvgFile {
   FILE *fsvg;
   char *cp, *cb;
   double wb;
};

struct linha {
   double x1,x2,y1,y2;
};

typedef struct StSvgFile *SvgFileImpl;

SvgFile newSvgFile(char *nomeArq){
   FILE *f = fopen(nomeArq,"w");
   if (f == NULL){
     return NULL;
   }

   SvgFileImpl fsf = (SvgFileImpl) malloc (sizeof(struct StSvgFile));
   fsf->fsvg = f;
   fsf->cp = NULL;
   fsf->cb = NULL;
   fsf->wb = 0.0;

   fprintf(fsf->fsvg,"<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
   escreverNomeSvg(fsf);
   return fsf;
}


void insertQuadra(SvgFile f, double x, double y,double w, double h, char *cp, char *cb, double wb){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\"  fill=\"%s\" fill-opacity=\"0.5\"  stroke-width=\"%f\"/>\n", x,y,w,h,cb,cp,wb);

}

void insertQuadraTransparent(SvgFile f, double x, double y,double w, double h, char *cp, char *cb, double wb){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill-opacity=\"0\" stroke=\"%s\" stroke-dasharray=\"4\" fill=\"%s\"  stroke-width=\"%f\"/>\n", x,y,w,h,cb,cp,wb);

}

void insertCircle(SvgFile f, double x, double y, double r, char *cp, char *cb, double wb){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"%f\" fill=\"%s\"/>\n",x,y,r,cb,wb,cp);
}

void insertElipse(SvgFile f, double x, double y, double rx,double ry, char *cp, char *cb, double wb){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" stroke=\"%s\" stroke-width=\"%f\" fill=\"%s\"/>\n",x,y,rx,ry,cb,wb,cp);
}

void insertQuadraPadrao(SvgFile f, double x1, double y1,double x2, double y2){
   SvgFileImpl fsf = (SvgFileImpl) f;
   insertQuadra(f,x1,y1,x2,y2,fsf->cp,fsf->cb,fsf->wb);
}

void closeSvgFile(SvgFile f){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"</svg>\n");
   fclose(fsf->fsvg);
   free(fsf);
}

void insertTxt(SvgFile f, double x, double y, double valor){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<text x=\"%f\" y=\"%f\" fill=\"black\" font-size=\"8\"> %.0f </text>\n",x,y,valor);
}

void insertLinhaGrossa(SvgFile f,double x, double y, double x2, double y2, char* cor){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" stroke-width=\"4.0\" stroke=\"%s\" fill=\"black\"/>\n",x,x2,y,y2, cor);
}

void insertLinha(SvgFile f,double x, double y, double x2, double y2){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" stroke-width=\"1.0\" stroke=\"black\" fill=\"black\"/>\n",x,x2,y,y2);
}

void insertPalavras(SvgFile f, double x, double y, char* frase, double tamanhoFonte){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"<text x=\"%f\" y=\"%f\" fill=\"black\" font-size=\"%f\"> %s </text>\n",x,y,tamanhoFonte,frase);
}

char* nomeSvgQry(char* nomeArqGeo, char* nomeArqQry, char* pathBSD){
   char* nomeArqGeoSemSuffix = removeSuffix(nomeArqGeo);
   char* nomeArqQrySemSuffix = removeSuffix(nomeArqQry);
   char* nomeArqGeoComTraco = addSuffix(nomeArqGeoSemSuffix,"-");
   char* nomeArqGeoQryJunto = addSuffix(nomeArqGeoComTraco,nomeArqQrySemSuffix);
   char* svgNomeSemPath = addSuffix(nomeArqGeoQryJunto,".svg");
   char* svgNome = concatPathFile(pathBSD,svgNomeSemPath);
   free(nomeArqGeoSemSuffix);
	free(nomeArqQrySemSuffix);
	free(nomeArqGeoComTraco);
	free(nomeArqGeoQryJunto);
	free(svgNomeSemPath);
   return svgNome;
}

char* nomeSvgGeo(char* nomeArqGeo, char* pathBSD){
   char* arqGeoSemSuffix = removeSuffix(nomeArqGeo);
   char* svgNomeSemPath = addSuffix(arqGeoSemSuffix,".svg");
   char* svgNome = concatPathFile(pathBSD,svgNomeSemPath);
   free(arqGeoSemSuffix);
   free(svgNomeSemPath);
   return svgNome;
}

void escreverNomeSvg(SvgFile f){
   SvgFileImpl fsf = (SvgFileImpl) f;
   fprintf(fsf->fsvg,"\n\t<!-- Kristiano Pasini de Oliveira -->\n\n");
}

void inserirArvoreQuadrasSvg(SvgFile f,ArvoreAvl quadras){
   SvgFileImpl fsf = (SvgFileImpl) f;
   if(quadras == NULL){
      return;
   }
   inserirArvoreQuadrasSvg(f,getNoAvlDireito(quadras));
   inserirArvoreQuadrasSvg(f,getNoAvlEsquerdo(quadras));

   Lista Xquadras = getItemAvl(quadras);
   Posic p = getFirst(Xquadras);
   while(p!=NULL){
      Quadra quadra = getItem(p);
      double xMeio = getX(quadra) + getW(quadra)/2;
      double yMeio = getY(quadra) + getH(quadra)/2;
      insertQuadra(f,getX(quadra),getY(quadra),getW(quadra),getH(quadra),
      getPreenchimento(quadra),getBorda(quadra),1.0);
      insertPalavras(f,xMeio,yMeio,getCep(quadra),5.0);
      p = getNext(Xquadras,p);
   }
}

void inserirEstadoLocacao(SvgFile svg, TabelaEspalhamento tabelaQuadras,
Locacao locacao, Moradia moradia){
     Quadra quadra = buscarItemTabela(tabelaQuadras,getCepMoradia(moradia));
        double* coordenadasMoradia = getCoordenadaMoradia(quadra,moradia);
        if(strcmp(getSituacao(locacao),"alugada") == 0){
            insertPalavras(svg,coordenadasMoradia[0],coordenadasMoradia[1],"*",10.0);
        }
        else if(strcmp(getSituacao(locacao),"disponivel") == 0){
            insertPalavras(svg,coordenadasMoradia[0],coordenadasMoradia[1],"$",10.0);
        }
        else if(strcmp(getSituacao(locacao),"encerrado") == 0){
            insertPalavras(svg,coordenadasMoradia[0],coordenadasMoradia[1],"#",10.0);
        }  
        free(coordenadasMoradia);
}