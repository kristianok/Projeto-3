#include "qry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista buscarListaMoradiasCep(TabelaEspalhamento moradiasCep, char* chave);
void buscarSexo(TabelaEspalhamento moradiasCep, TabelaEspalhamento tabelaQuadras,
char* chave, FILE* txt, SvgFile svg, char sexo);

ArvoreAvl del(ArvoreAvl quadras,TabelaEspalhamento moradiasCep, TabelaEspalhamento moradiasCpf,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas,  char* cep, SvgFile svg, FILE* txt, 
TabelaEspalhamento tabelaQuadras, int catac, int altura){

    Quadra quadra = buscarItemTabela(tabelaQuadras,cep);
    if(quadra == NULL){
        escrever(txt,"Quadra com este cep nao encontrada\n");
        return quadras;
    }
    
	quadras = removerArvoreAvl(quadras,getX(quadra),quadra);
    double xMeio = getX(quadra) + getW(quadra)/2;
    double yMeio = getY(quadra) + getH(quadra)/2;

    char* dQuadra = dadosQuadra(quadra);
    escrever(txt,dQuadra);
    if(catac == 0){
        insertLinha(svg,xMeio,yMeio,xMeio,altura);
        insertPalavras(svg,xMeio + 2,altura,getCep(quadra),10.0);
    }
    free(dQuadra);
        
	Lista moradias = buscarElementoTabela(moradiasCep,cep);
    Posic p = getFirst(moradias);
    while(p != NULL){
        Moradia moradia = getItem(p);
        Pessoa pessoa = getPessoa(moradia);
        Locacao locacao = getLocacao(moradia);

        if(moradia != NULL && strcmp(getCepMoradia(moradia),cep) == 0){
            p = getNext(moradias,p);
            moradiasCep = removerElementoTabela(moradiasCep,cep);
            char* dMoradia = dadosMoradia(moradia);
            escrever(txt,dMoradia);
            free(dMoradia);
            if(pessoa != NULL){
                moradiasCpf = removerElementoTabela(moradiasCpf,getCpf(pessoa));
                if(catac == 1){
                    char* dPessoa = dadosPessoa(pessoa);
                    pessoas = removerElementoTabela(pessoas,getCpf(pessoa));
                    escrever(txt,dPessoa);
                    free(dPessoa);
                    free(pessoa);
                }
            }
            if(locacao != NULL){
                char* dLocacao = dadosLocacao(locacao);
                locacoes = removerElementoTabela(locacoes,getId(locacao));
                escrever(txt,dLocacao);
                free(dLocacao);
                freeLocacao(locacao);
            }
            freeMoradia(moradia);
        }
        else{
            p = getNext(moradias,p);
        }
    }
    escrever(txt,"----------------------\n");
    tabelaQuadras = removerElementoTabela(tabelaQuadras,cep);
    freeQuadra(quadra);
    return quadras;
}

void m(TabelaEspalhamento moradiasCep, char* cep, FILE* txt){
    Lista moradias = buscarElementoTabela(moradiasCep,cep);
    Posic p = getFirst(moradias);
    if(p == NULL){
        escrever(txt,"Quadra nao existe ou nao ha moradias (m)\n");
        return;
    }
	while(p != NULL){
		Moradia moradia = getItem(p);
        if(strcmp(getCepMoradia(moradia),cep) == 0){
            if(getPessoa(moradia) != NULL){
                char* dMoradia = dadosMoradia(moradia);
		        escrever(txt,dMoradia);
                free(dMoradia);
                char* dPessoa = dadosPessoa(getPessoa(moradia));
		        escrever(txt,dPessoa);
                free(dPessoa);
            }
        }
		p = getNext(moradias,p);
	}
    return;
}

void dm(ArvoreAvl quadras, TabelaEspalhamento moradiasCpf,char* cpf, FILE* txt,
SvgFile svg, TabelaEspalhamento tabelaQuadras, int altura){
    Moradia moradia = buscarItemTabela(moradiasCpf,cpf);
    if(moradia == NULL){
        escrever(txt,"Pessoa nao foi encontrada ou nao possui endereco\n");
        return;
    }

    Quadra quadra = buscarItemTabela(tabelaQuadras,getCepMoradia(moradia));
    Pessoa pessoa = getPessoa(moradia);

    if(pessoa != NULL && quadra != NULL){
        char* dPessoa = dadosPessoa(pessoa);
        char* dMoradia = dadosMoradia(moradia);
        double* coordenadasMoradia = getCoordenadaMoradia(quadra,moradia);
        insertLinha(svg,coordenadasMoradia[0],coordenadasMoradia[1],coordenadasMoradia[0],altura-8);
        insertPalavras(svg,coordenadasMoradia[0]+5,altura,dMoradia,10.0);
        insertPalavras(svg,coordenadasMoradia[0]+5,altura-8,dPessoa,10.0);
        free(coordenadasMoradia);
        escrever(txt,dMoradia);
        if(getLocacao(moradia) != NULL){
		    escrever(txt,"Moradia eh alugada\n");
	    }
	    else {
    	    escrever(txt,"Moradia nao eh alugada\n");
	    }
        escrever(txt,dPessoa);
        free(dPessoa);
        free(dMoradia);
	}
}

void mud(char* cpf, Moradia moradia, TabelaEspalhamento moradiasCep,
TabelaEspalhamento moradiasCpf,FILE* txt, SvgFile svg, TabelaEspalhamento tabelaQuadras){
    Moradia moradiaAtual = buscarItemTabela(moradiasCpf,cpf);
    if(moradiaAtual == NULL){
        escrever(txt,"pessoa nao tem endereco atual");
        return;
    }
    Quadra quadra = buscarItemTabela(tabelaQuadras,getCepMoradia(moradiaAtual));
    Quadra quadraNova = buscarItemTabela(tabelaQuadras,getCepMoradia(moradia));

    Pessoa pessoa = getPessoa(moradiaAtual);
    setPessoa(moradiaAtual,NULL);
    setPessoa(moradia,pessoa);
    setMoradia(pessoa,moradia);

    char* dPessoa = dadosPessoa(pessoa);
    escrever(txt,dPessoa);
    free(dPessoa);

    escrever(txt,"Endereco antigo => ");
    char* dMoradia = dadosMoradia(moradiaAtual);
    escrever(txt,dMoradia);
    free(dMoradia);

    escrever(txt,"Endereco novo => ");
    dMoradia = dadosMoradia(moradia);
    escrever(txt,dMoradia);
    free(dMoradia);

    double *atual,*novo;
    atual = getCoordenadaMoradia(quadra,moradiaAtual);
    novo = getCoordenadaMoradia(quadraNova,moradia);
    insertCircle(svg,atual[0],atual[1],7.0,"red","white",2.0);
    insertCircle(svg,novo[0],novo[1],7.0,"blue","white",2.0);
    insertLinhaGrossa(svg,atual[0],atual[1],novo[0],novo[1],"red");
    free(atual);
    free(novo);

    moradiasCpf = removerElementoTabela(moradiasCpf,cpf);
    moradiasCep = inserirElementoTabela(moradiasCep,getCepMoradia(moradia),moradia);
	moradiasCpf = inserirElementoTabela(moradiasCpf,cpf,moradia);
}

TabelaEspalhamento oloc(TabelaEspalhamento locacoes, TabelaEspalhamento moradiasCep,
char* id, char* cep, char face,double num, char* compl, double ar, double v){
    Moradia moradia = NULL;
	Lista moradias = buscarElementoTabela(moradiasCep,cep);
	Posic p = getFirst(moradias);
	while(p != NULL){
		Moradia m = getItem(p);
		if(getNumero(m) == num && getFace(m) == face && strcmp(getComplemento(m),compl) == 0){
			moradia = m;
			break;
		}
        p = getNext(moradias,p);			
	}
	if(moradia == NULL){
		moradia = criarMoradia(cep,face,num,compl,NULL,NULL);
        moradiasCep = inserirElementoTabela(moradiasCep,cep,moradia);
	}
	Locacao locacao = criarLocacao(id,ar,v,moradia);
	setLocacao(moradia,locacao);
	locacoes = inserirElementoTabela(locacoes,id,locacao);   
    return locacoes;
}


void oloc2(ArvoreAvl quadras, TabelaEspalhamento moradiasCep, TabelaEspalhamento locacoes,
Quadra regiao, FILE* txt, SvgFile svg){
    if(quadras == NULL){
        return;
    }
    Lista encontrados = createLista();
    double x = getX(regiao);
    double xMax = getX(regiao) + getW(regiao);
    encontrados = buscarRegiao(quadras,encontrados,regiao,x,xMax);
    Quadra quadra = NULL;
    Moradia moradia = NULL;

    for(Posic p = getFirst(encontrados);p != NULL;p = getNext(encontrados,p)){
        quadra = getItem(p);
        char* cep = getCep(quadra);
        Lista moradias = buscarElementoTabela(moradiasCep,cep);
        for(Posic m = getFirst(moradias);m != NULL;m = getNext(moradias,m)){
            moradia = getItem(m);
            if(moradia != NULL && strcmp(getCepMoradia(moradia),cep) == 0 &&
             getLocacao(moradia) != NULL){
                char* dLocacao = dadosLocacao(getLocacao(moradia));
                escrever(txt,dLocacao);
                free(dLocacao);

                char* dMoradia = dadosMoradia(moradia);
                escrever(txt,dMoradia);
                free(dMoradia);

                double* coordenadasMoradia = getCoordenadaMoradia(quadra,moradia);
                insertPalavras(svg,coordenadasMoradia[0]+5,coordenadasMoradia[1],"*",10.0);
                free(coordenadasMoradia);
            }
        }
    }
    apagarLista(encontrados);
}

void loc(char* cpf, char* id, FILE* txt, SvgFile svg,TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas, TabelaEspalhamento moradiasCpf, int altura){
    Locacao locacao = buscarItemTabela(locacoes,id);
    Moradia moradia = getMoradiaLocacao(locacao);
    Pessoa pessoa = buscarItemTabela(pessoas,cpf);
    Quadra quadra = buscarItemTabela(tabelaQuadras,getCepMoradia(moradia));
    if(locacao == NULL || quadra == NULL || pessoa == NULL){
        escrever(txt,"locacao ou pessoa nao foi identificada");
        return;
    }
    if(strcmp(getSituacao(locacao),"encerrado") == 0 || strcmp(getSituacao(locacao),"alugada") == 0){
        escrever(txt,"contrato de locacao esta encerrado ou o local ja foi alugado");
        return; 
    }
    if(getMoradia(pessoa) != NULL){
        setPessoa(getMoradia(pessoa),NULL);
        moradiasCpf = removerElementoTabela(moradiasCpf,cpf);
    }
    setMoradia(pessoa,getMoradiaLocacao(locacao));
    setPessoa(getMoradiaLocacao(locacao),pessoa);
    setSituacao(locacao,"alugada");

    char* dPessoa = dadosPessoa(pessoa);
    char* dMoradia = dadosMoradia(moradia);
    char* dLocacao = dadosLocacao(locacao);
    double* coordenadasMoradia = getCoordenadaMoradia(quadra,moradia);

    insertLinha(svg,coordenadasMoradia[0],coordenadasMoradia[1],coordenadasMoradia[0],altura-16);
    insertPalavras(svg,coordenadasMoradia[0]+5,altura,dPessoa,10.0);
    insertPalavras(svg,coordenadasMoradia[0]+5,altura - 8,dMoradia,10.0);
    insertPalavras(svg,coordenadasMoradia[0]+5,altura - 16,dLocacao,10.0);
    escrever(txt,dLocacao);
    escrever(txt,dMoradia);
    escrever(txt,dPessoa);

    free(coordenadasMoradia);
    free(dPessoa);
    free(dMoradia);
    free(dLocacao);
}

void loc2(char* id, FILE* txt, SvgFile svg,TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas){
    Locacao locacao = buscarItemTabela(locacoes,id);
    if(locacao == NULL){
        return;
    }
    if(strcmp(getSituacao(locacao),"encerrado") == 0){
        escrever(txt,"Contrado de locacao encerrado\n");
    }
    else{
        char* dLocacao = dadosLocacao(locacao);
        escrever(txt,dLocacao);
        free(dLocacao);
    }
    Moradia moradia = getMoradiaLocacao(locacao);
    if(moradia != NULL){
        char* dMoradia = dadosMoradia(moradia);
        escrever(txt,dMoradia);
        free(dMoradia);     
        if(getPessoa(moradia)!= NULL){
            char* dPessoa = dadosPessoa(getPessoa(moradia));
            escrever(txt,dPessoa);
            free(dPessoa);
        }
       inserirEstadoLocacao(svg,tabelaQuadras,locacao,moradia);
    }
}

void dloc(char* id, FILE* txt,SvgFile svg, TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, int altura){
    Locacao locacao = buscarItemTabela(locacoes,id);
    if(locacao == NULL){
        return;
    }
    setSituacao(locacao,"encerrado");
    char* dLocacao = dadosLocacao(locacao);
    escrever(txt,dLocacao);
    Moradia moradia = getMoradiaLocacao(locacao);

    if(moradia != NULL){
        Quadra quadra = buscarItemTabela(tabelaQuadras,getCepMoradia(moradia));
        double* coordenadasMoradia = getCoordenadaMoradia(quadra,moradia);
        insertLinha(svg,coordenadasMoradia[0],coordenadasMoradia[1],coordenadasMoradia[0],altura-16);
        insertPalavras(svg,coordenadasMoradia[0]+5,altura,dLocacao,10.0);
        char* dMoradia = dadosMoradia(moradia);
        escrever(txt,dMoradia);
        insertPalavras(svg,coordenadasMoradia[0]+5,altura-8,dMoradia,10.0);
        free(dMoradia);
        Pessoa pessoa = getPessoa(moradia);
        if(pessoa != NULL){
            char* dPessoa = dadosPessoa(pessoa);
            escrever(txt,dPessoa);
            insertPalavras(svg,coordenadasMoradia[0]+5,altura-16,dPessoa,10.0);
            free(dPessoa);
        }
        free(dLocacao);
        free(coordenadasMoradia);
    }
}

void homMul(ArvoreAvl quadras, TabelaEspalhamento moradiasCep, TabelaEspalhamento tabelaQuadras,
Quadra regiao, char sexo, FILE* txt, SvgFile svg, int altura){
    if(quadras == NULL){
        return;
    }
    Lista encontrados = createLista();
    double x = getX(regiao);
    double xMax = getX(regiao) + getW(regiao);
    encontrados = buscarRegiao(quadras,encontrados,regiao,x,xMax);

    for(Posic p = getFirst(encontrados); p != NULL; p = getNext(encontrados,p)){
        Quadra quadra = getItem(p);
        buscarSexo(moradiasCep,tabelaQuadras,getCep(quadra),txt,svg, sexo);
    }
    apagarLista(encontrados);
}

ArvoreAvl catac(ArvoreAvl quadras, TabelaEspalhamento moradiasCep,
TabelaEspalhamento moradiasCpf, TabelaEspalhamento tabelaQuadras,
TabelaEspalhamento locacoes, TabelaEspalhamento pessoas, Quadra regiao,
FILE* txt, SvgFile svg){
    if(quadras == NULL){
        return quadras;
    }
    Lista encontrados = createLista();
    double x = getX(regiao);
    double xMax = getX(regiao) + getW(regiao);
    encontrados = buscarRegiao(quadras,encontrados,regiao,x,xMax);

   for(Posic p = getFirst(encontrados); p != NULL; p = getNext(encontrados,p)){
        Quadra quadra = getItem(p);
        quadras = del(quadras,moradiasCep,moradiasCpf,locacoes,pessoas,getCep(quadra),
        svg,txt,tabelaQuadras,1,0);
    }
    apagarLista(encontrados);
    return quadras;
}

void buscarSexo(TabelaEspalhamento moradiasCep, TabelaEspalhamento tabelaQuadras,
char* chave, FILE* txt, SvgFile svg, char sexo){
    Lista moradores = buscarListaMoradiasCep(moradiasCep,chave);
    for(Posic p = getFirst(moradores); p != NULL; p = getNext(moradores,p)){
        Moradia moradia = getItem(p);
        Pessoa pessoa = getPessoa(moradia);
        Locacao locacao = getLocacao(moradia);
        if(pessoa != NULL && getSexo(pessoa) == sexo){
            char* dMoradia = dadosMoradia(moradia);
            char* dPessoa = dadosPessoa(pessoa);  
            escrever(txt,dMoradia);
            escrever(txt,dPessoa);
            free(dMoradia);
            free(dPessoa);
            if(locacao != NULL){
                char* dLocacao = dadosLocacao(locacao);   
                escrever(txt,dLocacao);
                free(dLocacao);
            }
            Quadra quadra = buscarItemTabela(tabelaQuadras, getCepMoradia(moradia));
            double* coordenadas = getCoordenadaMoradia(quadra, moradia);  
            if(sexo == 'F'){
                insertElipse(svg,coordenadas[0],coordenadas[1],7.0,3.5,"deeppink","deeppink",1.0);
            }
            else{
                insertElipse(svg,coordenadas[0],coordenadas[1],7.0,3.5,"blue","blue",1.0);
            }
            free(coordenadas);
        }
    }
    apagarLista(moradores);
}

Lista buscarListaMoradiasCep(TabelaEspalhamento moradiasCep, char* chave){
    Lista moradias = buscarElementoTabela(moradiasCep,chave);
    Lista moradores = createLista();
    Posic p = getFirst(moradias);
    while(p != NULL){
        Moradia m = getItem(p);
        if(m != NULL && strcmp(getCepMoradia(m),chave)==0){
           insert(moradores,m,chave);
        }
        p = getNext(moradias,p);
    }
    return moradores;
}
