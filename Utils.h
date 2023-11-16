#ifndef UTILS_H
#define UTILS_H

void menuCliente() {
    int opcao = 0;
    while (opcao != 6) {
        printf("\n=========================================\n");
        printf("           MENU DE CLIENTES\n");
        printf("=========================================\n");
        printf("Selecione uma opcao:\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Consultar cliente\n");
        printf("3 - Lista de clientes\n");
        printf("4 - Atualizar cliente\n");
        printf("5 - Excluir cliente\n");
        printf("6 - Voltar\n");
        printf("=========================================\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                consultarCliente();
                break;
            case 3:
                listarClientes();
                break;
            case 4:
                atualizarCliente();
                break;
            case 5:
                excluirCliente();
                break;
            case 6:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

void menuProduto() {
    int opcao = 0;
    while (opcao != 6) {
        printf("\n=========================================\n");
        printf("           MENU DE PRODUTOS\n");
        printf("=========================================\n");
        printf("Selecione uma opcao:\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Consultar produto\n");
        printf("3 - Lista de produtos\n");
        printf("4 - Atualizar produto\n");
        printf("5 - Excluir produto\n");
        printf("6 - Voltar\n");
        printf("=========================================\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                consultarProduto();
                break;
            case 3:
                listarProdutos();
                break;
            case 4:
                atualizarProduto();
                break;
            case 5:
                excluirProduto();
                break;
            case 6:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

void menuVenda() {
    int opcao = 0;
    while (opcao != 5) {
        printf("\n=========================================\n");
        printf("           MENU DE VENDAS\n");
        printf("=========================================\n");
        printf("Selecione uma opcao:\n");
        printf("1 - Cadastrar venda\n");
        printf("2 - Consultar venda\n");
        printf("3 - Atualizar venda\n");
        printf("4 - Excluir venda\n");
        printf("5 - Voltar\n");
        printf("=========================================\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarVendaCliente();
                break;
            case 2:
                consultarVendaCliente();
                break;
            case 3:
                atualizarVendaCliente();
                break;
            case 4:
                excluirVendaCliente();
                break;
            case 5:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

/* aloca memoria para um inteiro e armazena o valor naquele espaco */
int* alocaInt(int n){
   int * pi = (int *) malloc(sizeof(int));
   *pi = n;
   return pi;
}

#endif