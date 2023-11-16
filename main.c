#include <stdio.h>
#include <strings.h>
#include "Persistencia.h"
#include "Cap3/Lista.h"
#include "Utils.h"
#include "CRUD.h"

FILE* tab_cliente;
FILE* tab_produto;
FILE* tab_venda;
FILE* tab_venda_produto;

int main(){
    int opcao = 0;
    while (opcao != 4) {
        printf("\n=====================================\n");
        printf(" Selecione uma opcao:\n");
        printf("=====================================\n");
        printf(" 1 - Cliente\n");
        printf(" 2 - Produto\n");
        printf(" 3 - Venda\n");
        printf(" 4 - Sair\n");
        printf("=====================================\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuCliente();
                break;
            case 2:
                menuProduto();
                break;
            case 3:
                menuVenda();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
    return 0;
    }