#include "main.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
	int i=1;
	char *nomeArqGeo=NULL, *nomeArqQry=NULL, *nomeArqPm=NULL, *pathBED=NULL, 
	*pathBSD=NULL, *arqGeo=NULL, *arqQry=NULL, *arqPm=NULL; 

	while(i<argc){
		if (strcmp("-e",argv[i])==0){
		i++;
		if(argc-1 < i){
			printf("Parametros insuficientes");
			exit(0);
		}
		pathBED = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
		strcpy(pathBED,argv[i]);
		}
	
		else if (strcmp("-f",argv[i])==0){
			i++;
			if(argc-1 < i){
				printf("Parametros insuficientes");
				exit(0);
			}
		nomeArqGeo = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
		strcpy(nomeArqGeo,argv[i]);
		}	
	
		else if (strcmp("-o",argv[i])==0){
			i++;
			if(argc-1 < i){
				printf("Parametros insuficientes");
				exit(0);
			}
			pathBSD = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
			strcpy(pathBSD,argv[i]);
		}
	
		else if (strcmp("-q",argv[i])==0){
			i++;
			if(argc-1 < i){
				printf("Parametros insuficientes");
				exit(0);
			}
			nomeArqQry = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
			strcpy(nomeArqQry,argv[i]);
		}
		else if (strcmp("-pm",argv[i])==0){
			i++;
			if(argc-1 < i){
				printf("Parametros insuficientes");
				exit(0);
			}
			nomeArqPm = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
			strcpy(nomeArqPm,argv[i]);
		}
		i++;
	}

	char* auxNomeGeo, *auxNomeQry, *auxNomePm;

	TabelaEspalhamento pessoas = NULL, moradiasCep = NULL, moradiasCpf = NULL, tabelaQuadras = NULL;

	arqGeo = concatPathFile(pathBED,nomeArqGeo);
	auxNomeGeo = removerPathDoNome(nomeArqGeo);

	arqQry = concatPathFile(pathBED,nomeArqQry);
	auxNomeQry = removerPathDoNome(nomeArqQry);

	arqPm = concatPathFile(pathBED,nomeArqPm);
	auxNomePm = removerPathDoNome(nomeArqPm);

	ArvoreAvl quadras = lerArquivoGeo(pathBSD,arqGeo,auxNomeGeo,&tabelaQuadras);

	if(arqPm != NULL){
		pessoas = lerPessoas(arqPm,auxNomePm);
		lerMoradias(arqPm,auxNomePm,pessoas,&moradiasCep,&moradiasCpf);
	}

	if(arqQry != NULL){
		lerArquivoQry(arqQry,auxNomeQry,pathBSD,nomeArqGeo,quadras,pessoas,moradiasCep, moradiasCpf, tabelaQuadras);
	}

	free(arqGeo);
	free(nomeArqGeo);
	free(pathBSD);

	if(pathBED != NULL){
		free(pathBED);
	}

	if(nomeArqQry != NULL){
		free(arqQry);
		free(nomeArqQry);
	}
	if(nomeArqPm != NULL){
		free(arqPm);
		free(nomeArqPm);
	}

	liberarArvoreQuadras(quadras);
	freeArvoreAvl(quadras);
	liberarTabelasEspeciais(moradiasCep,0);
	liberarTabelasEspeciais(moradiasCpf,3);
	liberarTabelasEspeciais(pessoas,2);
	liberarTabelasEspeciais(tabelaQuadras,3);

	return 0;
}
