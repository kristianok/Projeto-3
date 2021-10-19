#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txt.h"

FILE* abrirNovoTxt(char* nomeArqGeo, char* nomeArqQry, char* pathBSD){
	char* nomeArqGeoSemSuffix = removeSuffix(nomeArqGeo);
	char* nomeArqQrySemSuffix = removeSuffix(nomeArqQry);
	char* nomeArqGeoComTraco = addSuffix(nomeArqGeoSemSuffix,"-");
	char* nomeArqGeoQryJunto = addSuffix(nomeArqGeoComTraco,nomeArqQrySemSuffix);
	char* txtNomeSemPath = addSuffix(nomeArqGeoQryJunto,".txt");
	char* txtNome = concatPathFile(pathBSD,txtNomeSemPath);

	FILE* txt = fopen(txtNome,"w");
	if(txt == NULL){
		printf("Nao foi possivel dados no arquivo txt");
		exit(0);
	}

	escreverNome(txt);
	free(nomeArqGeoSemSuffix);
	free(nomeArqQrySemSuffix);
	free(nomeArqGeoComTraco);
	free(nomeArqGeoQryJunto);
	free(txtNomeSemPath);
	free(txtNome);
	
    return txt;
}

void fecharArquivoTxt(FILE* txt){
    if(txt != NULL){
        fclose(txt);
    }
}

void escreverNome(FILE* txt){
	fprintf(txt,"Kristiano Pasini de Oliveira\n");
}

char* dadosQuadra(Quadra quadra){
	char *texto = (char*) malloc(sizeof(char)*500);
	sprintf(texto,"Quadra: Cep - %s - Cor do preenchimento - %s - Cor da borda - %s - Espessura - %f x - %f  y - %f  w - %f  h - %f \n",
	getCep(quadra),getPreenchimento(quadra),getBorda(quadra),getEspessura(quadra),
	getX(quadra),getY(quadra),getW(quadra),getH(quadra));
	return texto;
}

char* dadosLocacao(Locacao locacao){
	char *texto = (char*) malloc(sizeof(char)*500);
	sprintf(texto,"Locacao: Id - %s  Area - %f  Valor - %f  Situacao - %s \n",getId(locacao),
	getArea(locacao),getValor(locacao),getSituacao(locacao));
	return texto;
}

char* dadosMoradia(Moradia moradia){
	char *texto = (char*) malloc(sizeof(char)*500);
	sprintf(texto,"Moradia: Cep - %s - Face - %c - Complemento - %s - Numero - %f \n"
	,getCepMoradia(moradia),getFace(moradia),getComplemento(moradia), getNumero(moradia));
	return texto;
}

char* dadosPessoa(Pessoa pessoa){
	char *texto = (char*) malloc(sizeof(char)*500);
	sprintf(texto,"Pessoa:  Cpf - %s -  Nome - %s - Sobrenome - %s - Nascimento - %s - Sexo - %c \n"
	,getCpf(pessoa),getNome(pessoa),getSobrenome(pessoa), getNascimento(pessoa),getSexo(pessoa));
	return texto;
}

void pularLinha(FILE* txt){
	fprintf(txt,"\n");
}

void escrever(FILE* txt, char* texto){
	fprintf(txt,"%s",texto);
}


