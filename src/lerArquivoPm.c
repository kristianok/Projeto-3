#include "lerArquivoPm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TabelaEspalhamento lerPessoas(char* arqPm, char* nomeArqPm){
    char pmP[25], cpf[25],nome[25], sobrenome[50],sexo,nasc[25];

    Pessoa pessoa = NULL;
    TabelaEspalhamento pessoas = criarTabelaEspalhamento();

    if(arqPm == NULL || nomeArqPm == NULL){
        return NULL;
    }

    FILE *pm;
    pm = fopen(arqPm,"r");

    if(pm == NULL){
        printf("%s",arqPm);
		printf("Nao foi possivel encontrar o arquivo pm");
		exit(0);
	}

    fscanf(pm, "%s", pmP);

	while(1==1){	
		if(feof(pm)){
			break;	
		}
        else if(strcmp("p",pmP)==0){
			fscanf(pm, "%s", cpf);
			fscanf(pm, "%s", nome);
			fscanf(pm, "%s", sobrenome);
            fscanf(pm, " %c", &sexo);
            fscanf(pm, "%s", nasc);
            pessoa = criarPessoa(cpf,nome,sobrenome,nasc,sexo,NULL);
            inserirElementoTabela(pessoas,cpf,pessoa);
		}
		fscanf(pm, "%s", pmP);
	}
    fclose(pm);
    return pessoas;
}

void lerMoradias(char* arqPm, char* nomeArqPm, 
TabelaEspalhamento pessoas, TabelaEspalhamento *moCep, TabelaEspalhamento *moCpf){
    char cpf[25],cep[25],face,num[25],compl[25], pmP[25];

    TabelaEspalhamento moradiasCep = criarTabelaEspalhamento();
    TabelaEspalhamento moradiasCpf = criarTabelaEspalhamento();

    if(arqPm == NULL || nomeArqPm == NULL){
        return;
    }

    FILE *pm;
    pm = fopen(arqPm,"r");

    if(pm == NULL){
		printf("Nao foi possivel encontrar o arquivo pm");
		exit(0);
	}

    fscanf(pm, "%s", pmP);

	while(1==1){	
		if(feof(pm)){
			break;	
		}
        else if(strcmp("m",pmP)==0){
		    fscanf(pm, "%s", cpf);
			fscanf(pm, "%s", cep);
			fscanf(pm, " %c", &face);
            fscanf(pm, "%s", num);
            fscanf(pm, "%s", compl);
            Pessoa pessoa = buscarItemTabela(pessoas,cpf);
            if(pessoa != NULL){
                Moradia moradia = criarMoradia(cep,face,atof(num),compl,pessoa,NULL);
                setMoradia(pessoa,moradia);
                inserirElementoTabela(moradiasCep,cep,moradia);
                inserirElementoTabela(moradiasCpf,cpf,moradia);
            }
		}
		fscanf(pm, "%s", pmP);
	}
    fclose(pm);
    *moCep = moradiasCep;
    *moCpf = moradiasCpf;
}