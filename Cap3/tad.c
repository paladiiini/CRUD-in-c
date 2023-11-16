#ifndef LISTA_TAD_H
#define LISTA_TAD_H

/*tipos de dados*/

typedef struct noh Noh;
typedef Noh* pNoh;

/*descritor da lista*/

typedef  struct dLista DLista;
typedef DLista * pDLista;

/*3 tipos que representam ponteiros para funcao*/

typedef int(*FuncaoComparacao) (void * , void *) ;
typedef void(*FuncaoImpressao) (void *);
typedef void* (*FuncaoAlocacao) (void *);
typedef void (*FuncaoLiberacao) (void *);
typedef int (*FuncaoMapeamento) (void *);

/*operacoes*/

pDLista criarLista( );

void incluirInfo(pDLista, void *);
void incluirInfoInicio(pDLista, void *);
void incluirInfoNoMeio(pDLista, void * , int);

int excluirInfo(pDLista, void *,FuncaoComparacao);
int contemInfo(pDLista, void *,FuncaoComparacao);
void imprimirLista(pDLista, FuncaoImpressao);

void destruirLista(pDLista);
void destruirListaNormal(pDLista);
void destruirListaInfo(pDLista, FuncaoLiberacao);

pDListaduplicarLista(pDLista, FuncaoAlocacao);

/*o parametro int estabelece a posicao da lista onde a divisao deve acontecer*/

pDListadividirLista(pDLista, int);

void* buscarNohInfo(pDLista, void *, FuncaoComparacao);
void* buscarInfoPos(pDLista, int);

void* maiorInfo(pDLista, FuncaoComparacao);
float calcularMedia(pDLista, FuncaoMapeamento);

#endif