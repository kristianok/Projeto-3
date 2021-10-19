#include "lerArquivoGeo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArvoreAvl lerArquivoGeo(char* pathBSD, char* arqGeo, char* nomeArqGeo, TabelaEspalhamento* tabelaQuadras){
	ArvoreAvl quadras = NULL;
    Quadra quadra = NULL;

    char *nomeArqSvg,*arqSvg;
    char x[25]="0",y[25]="0",w[25]="0",h[25]="0",geoP[25],corBorda[30]=" ",
	corPreenchimento[30]=" ", cep[50],r[25], espessura[25], nx[25];

	int aux = 0; 

    FILE *geo;
    geo = fopen(arqGeo,"r");

    if(geo == NULL){
		printf("Nao foi possivel encontrar o arquivo geo");
		exit(0);
	}

	TabelaEspalhamento tabeQuadras = criarTabelaEspalhamento();
	arqSvg = nomeSvgGeo(nomeArqGeo,pathBSD);
	SvgFile svg = newSvgFile(arqSvg);

	fscanf(geo, "%s", geoP);

	while(1==1){	
		if(feof(geo)){
			break;	
		}
		else if(strcmp("nx",geoP)==0){
			fscanf(geo, "%s", nx);
		}
		else if(strcmp("cq",geoP)==0){
			fscanf(geo, "%s", espessura);
			fscanf(geo, "%s", corPreenchimento);
			fscanf(geo, "%s", corBorda);
		}
		else if(strcmp("q",geoP)==0){
			fscanf(geo, "%s", cep);	
			fscanf(geo, "%s", x);
			fscanf(geo, "%s", y);
			fscanf(geo, "%s", w);
			fscanf(geo, "%s", h);

			quadra = criarQuadra(atof(espessura),corBorda,corPreenchimento,
			cep,atof(x),atof(y),atof(w),atof(h));

			tabeQuadras = inserirElementoTabela(tabeQuadras,cep,quadra);
			quadras = inserirArvoreAvl(quadras,quadra,atof(x));
			insertQuadra(svg,atof(x),atof(y),atof(w),atof(h),
			corPreenchimento, corBorda, atof(espessura));
			insertPalavras(svg,atof(x)+2,atof(y)+5,cep,5.0);
		}
		fscanf(geo, "%s", geoP);
	}

	*tabelaQuadras = tabeQuadras;
	
	free(arqSvg);
	closeSvgFile(svg);
	fclose(geo);

	return quadras;
}