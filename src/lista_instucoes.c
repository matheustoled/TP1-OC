#include <stdio.h>
#include <stdlib.h>

#include "./headers/lista_instrucoes.h"

// Função para inicializar a lista
void InicializarLista(Lista *lista) {
    lista->pPrimeiro = NULL;
    lista->pUltimo = NULL;
}

int VerificarLista(Lista *lista) {
    return (lista->pPrimeiro == lista->pUltimo);
}

// Função para inserir no início da lista
void InserirInicio(Lista *lista, int valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->pProx = lista->pPrimeiro;
    lista->pPrimeiro = novoNo;
    if (lista->pUltimo == NULL) {
        lista->pUltimo = novoNo;
    }
}

// Função para inserir no final da lista
void InserirFim(Lista *lista, int valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->pProx = NULL;
    
    if (lista->pUltimo != NULL) {
        lista->pUltimo->pProx = novoNo;
    }
    lista->pUltimo = novoNo;

    if (lista->pPrimeiro == NULL) {
        lista->pPrimeiro = novoNo;
    }
}

// Função para remover do início da lista
void RemoverInicio(Lista *lista) {
    if (lista->pPrimeiro == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    No *temp = lista->pPrimeiro;
    lista->pPrimeiro = lista->pPrimeiro->pProx;

    // Se a lista estiver vazia após a remoção, ajustar pUltimo
    if (lista->pPrimeiro == NULL) {
        lista->pUltimo = NULL;
    }

    free(temp); // Liberar a memória do nó removido
    printf("Elemento removido do inicio.\n");
}

// Função para remover um elemento do final
int RemoverFim(Lista *lista) {
    if (VerificarLista(lista)) {
        return 0;  // Lista vazia
    }
    No *pAnt = lista->pPrimeiro;
    while (pAnt->pProx != lista->pUltimo) {
        pAnt = pAnt->pProx;
    }
    free(lista->pUltimo);
    lista->pUltimo = pAnt;
    pAnt->pProx = NULL;
    return 1;
}

// Função para remover de um índice específico
void RemoverIndice(Lista *lista, int indice) {
    if (lista->pPrimeiro == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }
    No *atual = lista->pPrimeiro;
    No *anterior = NULL;
    int contador = 0;
    // Se o índice solicitado for 0 (primeiro nó)
    if (indice == 0) {
        lista->pPrimeiro = atual->pProx;
        if (lista->pPrimeiro == NULL) {
            lista->pUltimo = NULL; // Se a lista ficar vazia
        }
        free(atual);
        return;
    }
    // Percorre a lista até o índice desejado
    while (atual != NULL && contador < indice) {
        anterior = atual;
        atual = atual->pProx;
        contador++;
    }
    // Se o índice estiver fora do alcance
    if (atual == NULL) {
        printf("Indice fora do alcance.\n");
        return;
    }
    // Remove o nó no índice especificado
    anterior->pProx = atual->pProx;
    if (atual == lista->pUltimo) {
        lista->pUltimo = anterior; // Se for o último nó
    }
    free(atual);
}

// Função para imprimir a lista
void ImprimirLista(Lista *lista) {
    No *atual = lista->pPrimeiro;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->pProx;
    }
    printf("NULL\n");
}
