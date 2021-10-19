#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerArquivoQry.h"

void lerArquivoQry(char* arqQry, char* nomeArqQry, char* pathBSD, char* nomeArqGeo, 
ArvoreAvl quadras, TabelaEspalhamento pessoas, TabelaEspalhamento moradiasCep,
TabelaEspalhamento moradiasCpf, TabelaEspalhamento tabelaQuadras){
	TabelaEspalhamento locacoes = criarTabelaEspalhamento();
	FILE *qry, *txt;
	char qryP[25], *svgNome;
	qry = fopen(arqQry,"r");

	if(qry == NULL){
		printf("Nao foi possivel encontrar o arquivo qry");
		exit(0);
	}
	
	fscanf(qry,"%s",qryP);
	txt = abrirNovoTxt(nomeArqGeo, nomeArqQry, pathBSD);
	svgNome = nomeSvgQry(nomeArqGeo, nomeArqQry, pathBSD); 
    SvgFile svgQry = newSvgFile(svgNome);

	char cpf[25],id[25],cep[25],face,compl[25],num[25], ar[25], v[25], x[25],
	y[25],w[25],h[25], sfx[25];
	int altura =-10;

	while(1==1){
		if(feof(qry)){
			break;
		}
		else if(strcmp("del",qryP)==0){
			fscanf(qry, "%s", cep);
			escrever(txt,"del\n");
			quadras = del(quadras,moradiasCep,moradiasCpf,locacoes, pessoas, cep,svgQry,txt,tabelaQuadras,0,altura);
			altura -=10;
		}
		else if(strcmp("m?",qryP)==0){
			fscanf(qry, "%s", cep);
			escrever(txt,"m?\n");
			m(moradiasCep,cep,txt);
		}
		else if(strcmp("dm?",qryP)==0){
			fscanf(qry, "%s", cpf);
			escrever(txt,"dm?\n");
			dm(quadras,moradiasCpf,cpf,txt,svgQry,tabelaQuadras,altura);
			altura-=20;
		}
		else if(strcmp("mud",qryP)==0){		
			fscanf(qry, "%s", cpf);	
			fscanf(qry, "%s", cep);
			fscanf(qry, " %c", &face);
			fscanf(qry, "%s", num);
			fscanf(qry, "%s", compl);
			escrever(txt,"\nmud\n");
			Moradia moradia = criarMoradia(cep,face,atof(num),compl,NULL,NULL);
			mud(cpf,moradia,moradiasCep,moradiasCpf,txt,svgQry, tabelaQuadras);
		}
		else if(strcmp("oloc",qryP)==0){
			fscanf(qry, "%s", id);	
			fscanf(qry, "%s", cep);
			fscanf(qry, " %c", &face);
			fscanf(qry, "%s", num);
			fscanf(qry, "%s", compl);
			fscanf(qry, "%s", ar);
			fscanf(qry, "%s", v);
			escrever(txt,"oloc\n");
			locacoes = oloc(locacoes,moradiasCep,id,cep,face,atof(num),compl,atof(ar),atof(v));
		}
		else if(strcmp("oloc?",qryP)==0){
			fscanf(qry, "%s", x);	
			fscanf(qry, "%s", y);
			fscanf(qry, "%s", w);
			fscanf(qry, "%s", h);
			escrever(txt,"oloc?\n");
			Quadra regiao = criarQuadra(1.0," "," "," ",atof(x),atof(y),atof(w),atof(h));
			insertQuadraTransparent(svgQry,atof(x),atof(y),atof(w),atof(h),"black","black",2.0);
			oloc2(quadras,moradiasCep,locacoes,regiao,txt,svgQry);
			freeQuadra(regiao);
		}
		else if(strcmp("loc",qryP)==0){
			fscanf(qry, "%s", id);	
			fscanf(qry, "%s", cpf);
			escrever(txt,"loc\n");
			loc(cpf,id,txt,svgQry,tabelaQuadras,locacoes,pessoas,moradiasCpf,altura);
			altura -=30;
		}
		else if(strcmp("loc?",qryP)==0){
			fscanf(qry, "%s", id);	
			escrever(txt,"loc?\n");
			loc2(id,txt,svgQry,tabelaQuadras,locacoes,pessoas);
		}
		else if(strcmp("dloc",qryP)==0){
			fscanf(qry, "%s", id);	
			escrever(txt,"dloc\n");
			dloc(id,txt,svgQry,tabelaQuadras,locacoes,altura);
			altura -=30;
		}
		else if(strcmp("hom",qryP)==0){
			fscanf(qry, "%s", x);	
			fscanf(qry, "%s", y);	
			fscanf(qry, "%s", w);	
			fscanf(qry, "%s", h);
			escrever(txt,"hom\n");	
			Quadra regiao = criarQuadra(1.0," "," "," ",atof(x),atof(y),atof(w),atof(h));
			insertQuadraTransparent(svgQry,atof(x),atof(y),atof(w),atof(h),"black","black",2.0);
			homMul(quadras,moradiasCep,tabelaQuadras,regiao,'M',txt,svgQry,altura);
			free(regiao);
		}
		else if(strcmp("mul",qryP)==0){
			fscanf(qry, "%s", x);	
			fscanf(qry, "%s", y);	
			fscanf(qry, "%s", w);	
			fscanf(qry, "%s", h);	
			escrever(txt,"mul\n");
			Quadra regiao = criarQuadra(1.0," "," "," ",atof(x),atof(y),atof(w),atof(h));
			insertQuadraTransparent(svgQry,atof(x),atof(y),atof(w),atof(h),"black","black",2.0);
			homMul(quadras,moradiasCep,tabelaQuadras,regiao,'F',txt,svgQry,altura);
			free(regiao);
		}
		else if(strcmp("dmpt",qryP)==0){
			fscanf(qry, "%s", sfx);	
			escrever(txt,"dmpt\n");
			char* Sfx = addSuffix(sfx,".dot");
			char* arqDotSfx = addPreffix(Sfx,"-");
			char* nomeSvgSemPath = removerPathDoNome(svgNome);
			char* nomeDotSemSfx = removeSuffix(nomeSvgSemPath);
			char* nomeDotSemPath = addPreffix(arqDotSfx,nomeDotSemSfx);
			char* arqDot = concatPathFile(pathBSD,nomeDotSemPath);
			desenharArvoreAvl(quadras,arqDot);
			free(Sfx);
			free(arqDotSfx);
			free(nomeDotSemPath);
			free(nomeDotSemSfx);
			free(arqDot);
		}
		else if(strcmp("catac",qryP)==0){
			fscanf(qry, "%s", x);	
			fscanf(qry, "%s", y);	
			fscanf(qry, "%s", w);	
			fscanf(qry, "%s", h);	
			escrever(txt,"catac\n");
			Quadra regiao = criarQuadra(1.0," "," "," ",atof(x),atof(y),atof(w),atof(h));
			insertQuadra(svgQry,atof(x),atof(y),atof(w),atof(h),"#AB37C8", "#AA0044",1.0);
			quadras = catac(quadras,moradiasCep,moradiasCpf,tabelaQuadras,locacoes, pessoas, regiao,txt,svgQry);
			free(regiao);
		}
		fscanf(qry,"%s",qryP);	
	}
	fclose(qry);
	inserirArvoreQuadrasSvg(svgQry,quadras);
	closeSvgFile(svgQry);
	fecharArquivoTxt(txt);
	free(svgNome);
	liberarTabelasEspeciais(locacoes, 1);
}