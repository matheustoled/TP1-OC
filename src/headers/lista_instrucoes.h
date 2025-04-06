#ifndef LISTA_INSTRUCOES_H_
#define LISTA_INSTRUCOES_H_

#include "instrucao.h"

typedef struct No {
    int valor;
    struct No *pProx;
} No;

typedef struct Lista {
    No *pPrimeiro;
    No *pUltimo;
} Lista;

// Função para inicializar a lista
void InicializarLista(Lista *lista);

// Verificar se lista está vazia
int VerificarLista(Lista *lista);

// Função para inserir no início da lista
void InserirInicio(Lista *lista, int valor);

// Função para inserir no final da lista
void InserirFim(Lista *lista, int valor);

// Função para remover do início da lista
void RemoverInicio(Lista *lista);

// Função para remover um elemento do final
int RemoverFim(Lista *lista);

// Função para remover de um índice específico
void RemoverIndice(Lista *lista, int indice);

// Função para imprimir a lista
void ImprimirLista(Lista *lista);

#endif