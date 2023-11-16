#include <stdio.h>
#include <strings.h>
#include "Persistencia.h"
#include "Cap3/Lista.h"
#include "Utils.h"
#include "TAD_Persistencia.h"

struct cliente{
    int      cpf;
    char     nome[30];
    float      limiteCredito;
    float      limiteDisponivel;
};

struct cliente c;
    
int cadastrarCliente(struct cliente c){
    // Abrir o arquivo tab_cliente em modo de escrita binária
    FILE* fp = fopen("tab_cliente", "ab");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_cliente\n");
        return 0;
    }
    
    fflush(stdin);
    // Ler os dados do cliente do usuário
    printf("\nDigite o nome do cliente: ");
    scanf("%s", c.nome);
    printf("Digite o CPF do cliente: ");
    scanf("%d", &c.cpf);

    //verificar se o CPF já está cadastrado

    FILE* fp2 = fopen("tab_cliente", "rb");

    if(fp2 == NULL){
        printf("Erro ao abrir o arquivo tab_cliente\n");
        return 0;
    }

    struct cliente c2;

    while(fread(&c2, sizeof(struct cliente), 1, fp2) == 1){
        if(c2.cpf == c.cpf){
            printf("\nCPF ja cadastrado!\n");
            return 0;
        }
    }

    printf("Digite o limite do cliente: ");
    scanf("%f", &c.limiteCredito);
    
    c.limiteDisponivel = c.limiteCredito;
    
    // Escrever a estrutura cliente no arquivo
    fwrite(&c, sizeof(struct cliente), 1, fp);

    printf("\nCliente cadastrado com sucesso!\n");
    
    // Fechar o arquivo
    fclose(fp);
    
    // Retornar 1 em caso de sucesso e 0 em caso de falha
    return 1;
}

int consultarCliente(int cpf){
   FILE* fp = fopen("tab_cliente", "rb");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_cliente\n");
        return 0;
    }
    
    printf("\nDigite o CPF do cliente: ");
    scanf("%d", &cpf);
    
    struct cliente c;
    int encontrado = 0;
    while(fread(&c, sizeof(struct cliente), 1, fp) == 1){
        if(c.cpf == cpf){
            encontrado = 1;
            printf("\nCliente encontrado:\n");
            printf("Nome: %s\n", c.nome);
            printf("CPF: %d\n", c.cpf);
            printf("Limite: %.2f\n", c.limiteCredito);
            break;
        }
    }
    
    if(!encontrado){
        printf("\nCliente Inexistente!\n");
    }
    
    fclose(fp);
    
    return 1;

}

int listarClientes(){
    // Abrir o arquivo tab_cliente em modo de leitura binária
    FILE* fp = fopen("tab_cliente", "rb");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_cliente\n");
        return 0;
    }
    
    // Ler as estruturas cliente do arquivo e imprimir na tela
    struct cliente c;
    printf("\nClientes cadastrados:\n\n");
    while(fread(&c, sizeof(struct cliente), 1, fp) == 1){
        printf("Nome: %s\n", c.nome);
        printf("CPF: %d\n", c.cpf);
        printf("Limite: %.2f\n", c.limiteCredito);
        printf("Limite disponivel: %.2f\n\n", c.limiteDisponivel);
    }
    
    fclose(fp);
    
    return 1;
}

int atualizarCliente(int cpf){
    // Abrir o arquivo tab_cliente em modo de leitura e escrita binária
    FILE* fp = fopen("tab_cliente", "rb+");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_cliente\n");
        return 0;
    }
    
    printf("\nDigite o CPF do cliente: ");
    scanf("%d", &cpf);

    // Ler as estruturas cliente do arquivo e buscar pelo CPF
    struct cliente c;
    int encontrado = 0;
    while(fread(&c, sizeof(struct cliente), 1, fp) == 1){
        if(c.cpf == cpf){
            encontrado = 1;
            printf("\nCliente encontrado:\n");
            printf("Nome: %s\n", c.nome);
            printf("CPF: %d\n", c.cpf);
            printf("Limite: %.2f\n", c.limiteCredito);
            printf("Limite disponivel: %.2f\n", c.limiteDisponivel);

            float dif = c.limiteCredito - c.limiteDisponivel;

            // Ler os novos dados do cliente do usuário
            fflush(stdin);
            printf("\nDigite o novo nome do cliente: ");
            scanf("%s", c.nome);
            printf("Digite o novo limite do cliente: ");
            scanf("%.2f", &c.limiteCredito);
            
            //atualizar o limiteDisponivel

            if (c.limiteCredito < dif) {
                printf("\nO novo limite deve ser maior ou igual ao limite utilizado!\n");
                return 0;
            }

            c.limiteDisponivel = c.limiteCredito - dif;

            // Voltar o ponteiro do arquivo para a posição do cliente encontrado
            fseek(fp, -sizeof(struct cliente), SEEK_CUR);

            // Escrever a estrutura cliente atualizada no arquivo
            fwrite(&c, sizeof(struct cliente), 1, fp);

            printf("Cliente atualizado com sucesso!\n");
            break;
        }
    }
    
    if(!encontrado){
        printf("\nCliente Inexistente!\n");
    }
    
    fclose(fp);
    
    return 1;
}

int excluirCliente(int cpf){
    // Abrir o arquivo tab_cliente em modo de leitura e escrita binária
    FILE* fp = fopen("tab_cliente", "rb+");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_cliente\n");
        return 0;
    }
    
    printf("\nDigite o CPF do cliente: ");
    scanf("%d", &cpf);

    // Ler as estruturas cliente do arquivo e buscar pelo CPF
    struct cliente c;
    int encontrado = 0;
    while(fread(&c, sizeof(struct cliente), 1, fp) == 1){
        if(c.cpf == cpf){
            encontrado = 1;
            printf("\nCliente encontrado:\n\n");
            printf("Nome: %s\n", c.nome);
            printf("CPF: %d\n", c.cpf);
            printf("Limite: %.2f\n", c.limiteCredito);
            printf("Limite disponivel: %.2f\n", c.limiteDisponivel);

            //confirmacao de exclusao

            printf("\nDeseja realmente excluir o cliente? (S/N)\n");
            char opcao;
            scanf(" %c", &opcao);

            if(opcao == 'N' || opcao == 'n'){
                printf("\nCliente nao excluido!\n");
                return 0;
            }
            
            // Voltar o ponteiro do arquivo para a posição do cliente encontrado
            fseek(fp, -sizeof(struct cliente), SEEK_CUR);
            
            // Escrever uma estrutura cliente vazia no lugar do cliente a ser excluído
            struct cliente empty = {"", 0, 0};
            fwrite(&empty, sizeof(struct cliente), 1, fp);
            
            printf("\nCliente excluído com sucesso!\n");
            break;
        }
    }
    
    // Verificar se o cliente foi encontrado
    if(!encontrado){
        printf("\nCliente inexistente!\n");
    }
    
    // Fechar o arquivo
    fclose(fp);
    
    // Retornar 1 em caso de sucesso e 0 em caso de falha
    return 1;
}

struct produto{
    int      codigo;
    char     nome[30];
    float    preco;
    int      estoque;
};

struct produto p;

int cadastrarProduto(struct produto p){
    // Abrir o arquivo tab_produto em modo de leitura e escrita binária
    FILE* fp = fopen("tab_produto", "rb+");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        // Tentar criar o arquivo se ele não existir
        fp = fopen("tab_produto", "wb+");
        if(fp == NULL){
            printf("Erro ao abrir o arquivo tab_produto\n");
            return 0;
        }
    }
    
    fflush(stdin);
    // Ler os dados do produto do usuário
    printf("\nDigite o nome do produto: ");
    scanf("%s", p.nome);
    printf("Digite o codigo do produto: ");
    scanf("%d", &p.codigo);

    //verificar se o código inserido já existe

    FILE* fp2 = fopen("tab_produto", "rb");

    if(fp2 == NULL){
        printf("Erro ao abrir o arquivo tab_produto\n");
        return 0;
    }

    struct produto p2;

    while(fread(&p2, sizeof(struct produto), 1, fp2) == 1){
        if(p2.codigo == p.codigo){
            printf("\nCodigo ja cadastrado!\n");
            return 0;
        }
    }

    printf("Digite o preco do produto: ");
    scanf("%f", &p.preco);
    printf("Digite a quantidade em estoque do produto: ");
    scanf("%d", &p.estoque);
    
    // Escrever a estrutura produto no arquivo
    fwrite(&p, sizeof(struct produto), 1, fp);

    printf("\nProduto cadastrado com sucesso!\n");
    
    // Fechar o arquivo
    fclose(fp);
    
    // Retornar 1 em caso de sucesso e 0 em caso de falha
    return 1;
}

int consultarProduto(int codigo){
   FILE* fp = fopen("tab_produto", "rb");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_produto\n");
        return 0;
    }
    
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    
    struct produto p;
    int encontrado = 0;
    while(fread(&p, sizeof(struct produto), 1, fp) == 1){
        if(p.codigo == codigo){
            encontrado = 1;
            printf("\nProduto encontrado:\n");
            printf("Nome: %s\n", p.nome);
            printf("Codigo: %d\n", p.codigo);
            printf("Preco: %.2f\n", p.preco);
            printf("Estoque: %d\n", p.estoque);
            break;
        }
    }
    
    if(!encontrado){
        printf("\nProduto Inexistente!\n");
    }
    
    fclose(fp);
    
    return 1;

}

int listarProdutos(){
    // Abrir o arquivo tab_produto em modo de leitura binária
    FILE* fp = fopen("tab_produto", "rb");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_produto\n");
        return 0;
    }
    
    // Ler as estruturas produto do arquivo e imprimir na tela
    struct produto p;
    printf("\nProdutos cadastrados:\n\n");
    while(fread(&p, sizeof(struct produto), 1, fp) == 1){
        printf("Nome: %s\n", p.nome);
        printf("Codigo: %d\n", p.codigo);
        printf("Preco: %.2f\n", p.preco);
        printf("Estoque: %d\n\n", p.estoque);
    }
    
    fclose(fp);
    
    return 1;
}

int atualizarProduto(int codigo){
    // Abrir o arquivo tab_produto em modo de leitura e escrita binária
    FILE* fp = fopen("tab_produto", "rb+");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_produto\n");
        return 0;
    }
    
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    // Ler as estruturas produto do arquivo e buscar pelo codigo
    struct produto p;
    int encontrado = 0;
    while(fread(&p, sizeof(struct produto), 1, fp) == 1){
        if(p.codigo == codigo){
            encontrado = 1;
            printf("\nProduto encontrado:\n");
            printf("Nome: %s\n", p.nome);
            printf("Codigo: %d\n", p.codigo);
            printf("Preco: %.2f\n", p.preco);
            printf("Estoque: %d\n", p.estoque);

            // Ler os novos dados do produto do usuário
            fflush(stdin);
            printf("\nDigite o novo nome do produto: ");
            scanf("%s", p.nome);
            printf("Digite o novo preco do produto: ");
            scanf("%f", &p.preco);
            printf("Digite a nova quantidade em estoque do produto: ");
            scanf("%d", &p.estoque);

            // Voltar o ponteiro do arquivo para a posição do produto encontrado
            fseek(fp, -sizeof(struct produto), SEEK_CUR);

            // Escrever a estrutura produto atualizada no arquivo
            fwrite(&p, sizeof(struct produto), 1, fp);

            printf("Produto atualizado com sucesso!\n");
            break;
        }
    }
    
    if(!encontrado){
        printf("\nProduto Inexistente!\n");
    }
    
    fclose(fp);
    
    return 1;
}

int excluirProduto(int codigo){
    // Abrir o arquivo tab_produto em modo de leitura e escrita binária
    FILE* fp = fopen("tab_produto", "rb+");
    
    // Verificar se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_produto\n");
        return 0;
    }
    
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    // Ler as estruturas produto do arquivo e buscar pelo codigo
    struct produto p;
    int encontrado = 0;
    while(fread(&p, sizeof(struct produto), 1, fp) == 1){
        if(p.codigo == codigo){
            encontrado = 1;
            printf("\nProduto encontrado:\n\n");
            printf("Nome: %s\n", p.nome);
            printf("Codigo: %d\n", p.codigo);
            printf("Preco: %.2f\n", p.preco);
            printf("Estoque: %d\n", p.estoque);
            
            // Voltar o ponteiro do arquivo para a posição do produto encontrado
            fseek(fp, -sizeof(struct produto), SEEK_CUR);
            
            // Escrever uma estrutura produto vazia no lugar do produto a ser excluído
            struct produto empty = {"", 0, 0, 0};
            fwrite(&empty, sizeof(struct produto), 1, fp);
            
            printf("\nProduto excluido com sucesso!\n");
            break;
        }
    }
    
    // Verificar se o produto foi encontrado
    if(!encontrado){
        printf("\nProduto inexistente!\n");
    }
    
    // Fechar o arquivo
    fclose(fp);
    
    // Retornar 1 em caso de sucesso e 0 em caso de falha
    return 1;
}

struct venda_cliente {
    int codigo_venda;
    int codigo_cliente;
    int codigo_produto;
    int quantidade;
};

struct venda_cliente vc;

int cadastrarVendaCliente() {
    FILE* fp = fopen("tab_venda_cliente", "ab");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_venda_cliente\n");
        return 0;
    }

    // Ler o último código de venda do arquivo
    struct venda_cliente last_vc;
    fseek(fp, -sizeof(struct venda_cliente), SEEK_END);
    if (fread(&last_vc, sizeof(struct venda_cliente), 1, fp) == 1) {
        vc.codigo_venda = last_vc.codigo_venda + 1;
    } else {
        vc.codigo_venda = 1;
    }

    printf("Digite o CPF do cliente: ");
    scanf("%d", &vc.codigo_cliente);

    //verificar se o cliente está cadastrado

    FILE* fp2 = fopen("tab_cliente", "rb+");

    if(fp2 == NULL){
        printf("Erro ao abrir o arquivo tab_cliente\n");
        return 0;
    }

    struct cliente c;

    int encontrado_cliente = 0;

    while(fread(&c, sizeof(struct cliente), 1, fp2) == 1){
        if(c.cpf == vc.codigo_cliente){
            encontrado_cliente = 1;
            break;
        }
    }

    if(!encontrado_cliente){
        printf("\nCliente Inexistente!\n");
        fclose(fp2);
        return 0;
    }

    printf("Digite o codigo do produto: ");
    scanf("%d", &vc.codigo_produto);

    FILE* fp_produto = fopen("tab_produto", "rb+");
    if(fp_produto == NULL){
        printf("Erro ao abrir o arquivo tab_produto\n");
        return 0;
    }

    struct produto p;
    int encontrado = 0;
    while(fread(&p, sizeof(struct produto), 1, fp_produto) == 1){
        if(p.codigo == vc.codigo_produto){
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("\nProduto Inexistente!\n");
        fclose(fp_produto);
        return 0;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &vc.quantidade);

    // Atualizar o estoque do produto
    if (p.estoque < vc.quantidade) {
        printf("\nEstoque insuficiente!\n");
        fclose(fp_produto);
        return 0;
    }
    p.estoque -= vc.quantidade;
    fseek(fp_produto, -sizeof(struct produto), SEEK_CUR);
    fwrite(&p, sizeof(struct produto), 1, fp_produto);

    // Calcular o valor total da venda_cliente
    float valor_total = vc.quantidade * p.preco;

    //verificar se o cliente tem limite disponivel

    if(c.limiteDisponivel < valor_total){
        printf("\nLimite insuficiente!\n");
        fclose(fp_produto);
        return 0;
    }

    c.limiteDisponivel = c.limiteDisponivel - valor_total;
    fseek(fp2, -sizeof(struct cliente), SEEK_CUR);
    fwrite(&c, sizeof(struct cliente), 1, fp2);
    fclose(fp2);

    // Escrever a venda_cliente no arquivo
    fwrite(&vc, sizeof(struct venda_cliente), 1, fp);
    fclose(fp);
    fclose(fp_produto);

    printf("\nVenda do cliente cadastrada com sucesso!\n");
    printf("Codigo da venda: %d\n", vc.codigo_venda);
    printf("Valor total da venda: %.2f\n", valor_total);
    return 1;
}

int consultarVendaCliente(int codigo) {
    FILE* fp = fopen("tab_venda_cliente", "rb");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_venda_cliente\n");
        return 0;
    }

    printf("\nDigite o codigo da venda do cliente: ");
    scanf("%d", &codigo);

    struct venda_cliente vc;
    int encontrado = 0;
    while(fread(&vc, sizeof(struct venda_cliente), 1, fp) == 1){
        if(vc.codigo_venda == codigo){
            encontrado = 1;
            printf("\nVenda do cliente encontrada:\n");
            printf("Codigo da venda: %d\n", vc.codigo_venda);
            printf("Codigo do cliente: %d\n", vc.codigo_cliente);
            printf("Codigo do produto: %d\n", vc.codigo_produto);
            printf("Quantidade: %d\n", vc.quantidade);
        }
    }

    if(!encontrado){
        printf("\nVenda do cliente Inexistente!\n");
    }

    fclose(fp);
    return 1;
}

// Note: The following functions are simplified and do not handle the case where the file contains more than one sale client with the same code.

int atualizarVendaCliente(int codigo) {
    FILE* fp = fopen("tab_venda_cliente", "r+b");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_venda_cliente\n");
        return 0;
    }

    printf("\nDigite o codigo da venda do cliente: ");
    scanf("%d", &codigo);

    struct venda_cliente vc;
    int encontrado = 0;
    while(fread(&vc, sizeof(struct venda_cliente), 1, fp) == 1){
        if(vc.codigo_venda == codigo){
            encontrado = 1;
            printf("\nDigite o novo codigo do cliente: ");
            scanf("%d", &vc.codigo_cliente);
            printf("Digite o novo codigo do produto: ");
            scanf("%d", &vc.codigo_produto);
            printf("Digite a nova quantidade: ");
            scanf("%d", &vc.quantidade);

            // Buscar o produto correspondente ao codigo_produto
            FILE* fp_produto = fopen("tab_produto", "r+b");
            if(fp_produto == NULL){
                printf("Erro ao abrir o arquivo tab_produto\n");
                return 0;
            }

            struct produto p;
            int encontrado_produto = 0;
            while(fread(&p, sizeof(struct produto), 1, fp_produto) == 1){
                if(p.codigo == vc.codigo_produto){
                    encontrado_produto = 1;
                    break;
                }
            }

            if(!encontrado_produto){
                printf("\nProduto Inexistente!\n");
                fclose(fp_produto);
                return 0;
            }

            // Atualizar o estoque do produto
            p.estoque -= vc.quantidade;
            fseek(fp_produto, -sizeof(struct produto), SEEK_CUR);
            fwrite(&p, sizeof(struct produto), 1, fp_produto);
            fclose(fp_produto);

            // Calcular o valor total da venda_cliente
            float valor_total = vc.quantidade * p.preco;

            fseek(fp, -sizeof(struct venda_cliente), SEEK_CUR);
            fwrite(&vc, sizeof(struct venda_cliente), 1, fp);
            break;
        }
    }

    printf("\nVenda do cliente atualizada com sucesso!\n");

    if(!encontrado){
        printf("\nVenda do cliente Inexistente!\n");
    }

    fclose(fp);
    return 1;
}

int excluirVendaCliente(int codigo) {
    FILE* fp = fopen("tab_venda_cliente", "r+b");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo tab_venda_cliente\n");
        return 0;
    }

    printf("\nDigite o codigo da venda do cliente: ");
    scanf("%d", &codigo);

    struct venda_cliente vc;
    int encontrado = 0;
    FILE* temp = fopen("temp", "wb");
    while(fread(&vc, sizeof(struct venda_cliente), 1, fp) == 1){
        if(vc.codigo_venda == codigo){
            encontrado = 1;
        } else {
            fwrite(&vc, sizeof(struct venda_cliente), 1, temp);
        }
    }

    if(!encontrado){
        printf("\nVenda do cliente Inexistente!\n");
    } else {
        printf("\nVenda do cliente excluida com sucesso!\n");
    }

    fclose(fp);
    fclose(temp);

    remove("tab_venda_cliente");
    rename("temp", "tab_venda_cliente");

    return 1;
}
