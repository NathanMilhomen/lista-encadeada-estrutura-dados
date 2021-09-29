// Nathan Milhomen, Victor Rodrigues Perigo de Oliveira, Caio Alexandre Reis, Ana Vitoria Rezende de Oliveira

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento Elemento;
typedef struct data Data;

typedef struct Lista
{
    Elemento *inicio;
    int tamanho;
};
struct data
{
    char dia[2];
    char mes[2];
    char ano[4];
};

struct elemento
{
    Data *data;
    double valor;
    bool situacao;
    Elemento *proximo;
};

bool estaVazia(Lista *lista)
{
    return lista->inicio == NULL;
}

Lista *novaLista();
Data *criaData(char dia[], char mes[], char ano[]);
Elemento *novoElemento(Data *data, double valor, bool situacao);
void adicionaElementoNoInicio(Elemento *novoElemento, Lista *lista);
void adicionarElementoNoMeio(Elemento *novoElemento, Lista *lista, int index);
void adicionarElementoNoFinal(Elemento *novoElemento, Lista *lista);
void removerElementoInicio(Lista *lista);
void removerElementoMeio(Lista *lista, int index);
void removerElementoFinal(Lista *lista);
void imprimirLista(Lista *lista);
void imprimirElemento(Elemento *elemento);

Lista *novaLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    lista->inicio = NULL;
    lista->tamanho = 0;

    return lista;
}

Data *criaData(char dia[2], char mes[2], char ano[4])
{
    Data *novo = (Data *)malloc(sizeof(Data));

    strcpy(novo->dia, dia);
    strcpy(novo->mes, mes);
    strcpy(novo->ano, ano);

    return novo;
}

Elemento *novoElemento(Data *data, double valor, bool situacao)
{
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

    novo->data = data;
    novo->valor = valor;
    novo->situacao = situacao;

    novo->proximo = NULL;

    return novo;
}

void adicionaElementoNoInicio(Elemento *novoElemento, Lista *lista)
{
    if (estaVazia(lista))
    {
        lista->inicio = novoElemento;
    }
    else
    {
        novoElemento->proximo = lista->inicio;
        lista->inicio = novoElemento;
    }
    lista->tamanho++;
}

void adicionarElementoNoMeio(Elemento *novoElemento, Lista *lista, int index)
{
    if (estaVazia(lista) || index == 0)
    {
        novoElemento->proximo = lista->inicio;
        lista->inicio = novoElemento;
    }
    else
    {
        Elemento *elemento = lista->inicio;
        int cont = 1;
        while (cont < index && elemento->proximo != NULL)
        {
            elemento = elemento->proximo;
            cont++;
        }
        novoElemento->proximo = elemento->proximo;
        elemento->proximo = novoElemento;
    }
}

void adicionarElementoNoFinal(Elemento *novoElemento, Lista *lista)
{
    if (estaVazia(lista))
    {
        lista->inicio = novoElemento;
    }
    else
    {
        Elemento *elemento = lista->inicio;
        while (elemento->proximo != NULL)
        {
            elemento = elemento->proximo;
        }
        elemento->proximo = novoElemento;
    }
}
void removerElementoInicio(Lista *lista)
{
    Elemento *elemento = lista->inicio;

    lista->inicio = elemento->proximo;

    free(elemento);
}

void removerElementoMeio(Lista *lista, int index)
{
    if (estaVazia(lista) || index == 0)
    {
        return;
    }
    else
    {

        Elemento *elementoAnterior = lista->inicio;
        Elemento *elementoAtual = lista->inicio;
        int cont = 0;
        while (cont < index && elementoAtual->proximo != NULL)
        {
            elementoAnterior = elementoAtual;
            elementoAtual = elementoAtual->proximo;
            cont++;
        }
        elementoAnterior->proximo = elementoAtual->proximo;

        elementoAtual->proximo = NULL;
        free(elementoAtual);
    }
}

void removerElementoFinal(Lista *lista)
{

    Elemento *elementoAtual = lista->inicio;

    if (elementoAtual->proximo == NULL)
    {
        lista->inicio = NULL;
    }
    else
    {
        Elemento *elementoAnterior = lista->inicio;
        while (elementoAtual->proximo != NULL)
        {
            elementoAnterior = elementoAtual;
            elementoAtual = elementoAtual->proximo;
        }
        elementoAnterior->proximo = NULL;
    }

    free(elementoAtual);
}

void imprimirLista(Lista *lista)
{
    if (estaVazia(lista))
    {
        printf("Lista vazia \n");
    }
    else
    {
        Elemento *elementoAtual = lista->inicio;
        printf("[");
        while (elementoAtual != NULL)
        {
            imprimirElemento(elementoAtual);
            elementoAtual = elementoAtual->proximo;
            if (elementoAtual != NULL)
            {
                printf(", ");
            }
        }
        printf("]\n");
    }
}
void imprimirData(Data *data)
{
    printf("%s", data->dia);
}
void imprimirElemento(Elemento *elemento)
{

    printf(
        "@Valor: %.2f", elemento->valor);
}

int main()
{

    Lista *lista = novaLista();
    Data *data = criaData("05", "15", "2010");

    Elemento *elemento = novoElemento(data, 100, false);
    Elemento *elemento1 = novoElemento(data, 200, false);
    Elemento *elemento2 = novoElemento(data, 300, false);
    Elemento *elemento3 = novoElemento(data, 400, false);
    Elemento *elemento4 = novoElemento(data, 500, false);

    adicionarElementoNoFinal(elemento2, lista);
    adicionarElementoNoFinal(elemento3, lista);
    adicionarElementoNoFinal(elemento4, lista);
    adicionaElementoNoInicio(elemento1, lista);
    adicionaElementoNoInicio(elemento, lista);

    imprimirLista(lista);
    printf("Removendo o segundo elemento da lista: ");
    removerElementoMeio(lista, 1);

    imprimirLista(lista);
    printf("Removendo o ultimo elemento da lista: ");
    removerElementoFinal(lista);

    imprimirLista(lista);
    printf("Removendo o primeiro elemento da lista: ");
    removerElementoInicio(lista);
    printf("\n");

    imprimirLista(lista);

    return 0;
}