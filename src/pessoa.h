#ifndef PESSOA_H
#define PESSOA_H

typedef void* Pessoa;

#include "moradia.h"

/*
    Este modulo contem toda a implementacao referente ao TAD Pessoa
*/

//Aloca a memoria e inicializa o TAD pessoa
Pessoa criarPessoa(char* cpf, char* nome, char* sobrenome, 
char* nascimento, char sexo, Moradia moradia);

//Retorna o cpf de uma pessoa
char* getCpf(Pessoa p);

//Retorna o nome de uma pessoa
char* getNome(Pessoa p);

//Retorna o sobrenome de uma pessoa
char* getSobrenome(Pessoa p);

//Retorna o nascimento de uma pessoa
char* getNascimento(Pessoa p);

//Retorna o sexo de uma pessoa
char getSexo(Pessoa p);

//Retorna a moradia de uma pessoa
Moradia getMoradia(Pessoa p);

//Determina a moradia de uma pessoa
void setMoradia(Pessoa p, Moradia m);

//Desaloca a memoria utilizada pelo TAD pessoa
void freePessoa(Pessoa p);

#endif