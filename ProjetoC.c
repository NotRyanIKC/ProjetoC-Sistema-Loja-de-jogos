#include <stdio.h>
#include <string.h>

#define JOGOS 100
#define VENDAS 50
#define PRODUTOS_VENDA 10

char nomes[JOGOS][50];
char plataformas[JOGOS][30];
float precos[JOGOS];
int quantidades[JOGOS];
int codigos[JOGOS];
int contadorJogos = 0;
int vendas[VENDAS][PRODUTOS_VENDA]; 
int quantidadesVendidas[VENDAS][PRODUTOS_VENDA];  
int totalProdutosPorVenda[VENDAS];  
int contadorVendas = 0;

//verifica se o numero eh valido
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int lerInteiro(char* mensagem) {
    int valor;
    char c;

    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            if (valor >= 0) return valor;
            else printf("Erro: O valor deve ser positivo.\n");
        } else {
            printf("Erro: Entrada invalida. Insira um numero inteiro.\n");
            while ((c = getchar()) != '\n' && c != EOF); 
        }
    }
}
float lerFloat(char* mensagem) {
    float valor;
    char c;
    
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) == 1) { 
            if (valor >= 0) return valor;
            else printf("Erro: O valor deve ser positivo.\n");
        } else {
            printf("Erro: Entrada invalida. Insira um numero.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

//Cadastro dos jogos
void cadastrarJogo() {
    if (contadorJogos < JOGOS) {
        printf("Nome do Jogo: ");
        scanf(" %[^\n]s", nomes[contadorJogos]);
        printf("Plataforma: ");
        scanf(" %[^\n]s", plataformas[contadorJogos]);
        precos[contadorJogos] = lerFloat("Preco: ");
        quantidades[contadorJogos] = lerInteiro("Quantidade em Estoque: ");
        codigos[contadorJogos] = lerInteiro("Codigo do Produto: ");
        contadorJogos++;
        printf("\nJogo cadastrado com sucesso\n");
    } else {
        printf("Erro: Limite de jogos cadastrados atingido.\n");
    }
}

//consulta o estoque dos jogos cadastrados
void consultarEstoque() {
    int opcao, codigo, encontrado = 0;
    char nome[50], plataforma[30];
    int i;
    printf("Consultar por:\n1. Nome\n2. Plataforma\n3. Codigo\nEscolha a opcao: ");
    opcao = lerInteiro("");
    
    if (opcao == 1) {
        printf("Digite o nome do jogo: ");
        scanf(" %[^\n]s", nome);
        for ( i = 0; i < contadorJogos; i++) {
            if (strcmp(nomes[i], nome) == 0) {
                printf("\nNome: %s\nPlataforma: %s\nPreco: R$%.2f\nEstoque: %d\nCodigo: %d\n",
                       nomes[i], plataformas[i], precos[i], quantidades[i], codigos[i]);
                encontrado = 1;
            }
        }
    } else if (opcao == 2) {
        printf("Digite a plataforma: ");
        scanf(" %[^\n]s", plataforma);
        for ( i = 0; i < contadorJogos; i++) {
            if (strcmp(plataformas[i], plataforma) == 0) {
                printf("\nNome: %s\nPlataforma: %s\nPreco: R$%.2f\nEstoque: %d\nCodigo: %d\n",
                       nomes[i], plataformas[i], precos[i], quantidades[i], codigos[i]);
                encontrado = 1;
            }
        }
    } else if (opcao == 3) {
        codigo = lerInteiro("Digite o codigo do jogo: ");
        for ( i = 0; i < contadorJogos; i++) {
            if (codigos[i] == codigo) {
                printf("\nNome: %s\nPlataforma: %s\nPreco: R$%.2f\nEstoque: %d\nCodigo: %d\n",
                       nomes[i], plataformas[i], precos[i], quantidades[i], codigos[i]);
                encontrado = 1;
            }
        }
    } else {
        printf("Erro: Opcao invalida\n");
    }

    if (!encontrado) {
        printf("Jogo nao encontrado.\n");
    }
}

//registra as vendas
void fazerVenda() {
    int i,j;
    if (contadorVendas < VENDAS) {
        int numProdutos = lerInteiro("Quantos produtos serao registrados nesta venda? ");
        if (numProdutos > PRODUTOS_VENDA) {
            printf("Erro: Numero maximo de produtos por venda eh %d\n", PRODUTOS_VENDA);
            return;
        }

        float totalVenda = 0;
        for ( i = 0; i < numProdutos; i++) {
            int codigo = lerInteiro("Digite o codigo do produto: ");
            int quantidade = lerInteiro("Digite a quantidade vendida: ");
            int encontrado = 0;

            for ( j = 0; j < contadorJogos; j++) {
                if (codigos[j] == codigo) {
                    encontrado = 1;
                    if (quantidade > quantidades[j]) {
                        printf("Erro: Estoque insuficiente para o produto %s (Estoque: %d).\n", nomes[j], quantidades[j]);
                        return;
                    }
                   
                    quantidades[j] -= quantidade;
                    vendas[contadorVendas][i] = codigo;
                    quantidadesVendidas[contadorVendas][i] = quantidade;
                    totalProdutosPorVenda[contadorVendas] = numProdutos;
                    totalVenda += quantidade * precos[j];

                    printf("Produto %s adicionado a venda\n Subtotal: R$%.2f\n\n", nomes[j], quantidade * precos[j]);
                    break;
                }
            }
            if (!encontrado) {
                printf("Erro: Produto com codigo %d nao encontrado.\n", codigo);
                return;
            }
        }
        contadorVendas++;
        printf("Venda registrada com sucesso\n Total da venda: R$%.2f\n", totalVenda);
    } else {
        printf("Erro: Limite de vendas atingido\n");
    }
}

//Exibicao das vendas
void exibirVendas() {
    int i,j,k;
    if (contadorVendas == 0) {
        printf("Nenhuma venda registrada\n");
        return;
    }
    for ( i = 0; i < contadorVendas; i++) {
        printf("\nVenda #%d\n", i + 1);
        for ( j = 0; j < totalProdutosPorVenda[i]; j++) {
            for ( k = 0; k < contadorJogos; k++) {
                if (codigos[k] == vendas[i][j]) {
                    printf("Produto: %s, Quantidade: %d, Preco Unitario: R$%.2f\n", 
                           nomes[k], quantidadesVendidas[i][j], precos[k]);
                }
            }
        }
    }
}

//Menu do sistema
int main() {
    int opcao = 0;

    while (opcao != 5) {
        printf("\nMenu:\n");
        printf("1. Cadastrar Jogo\n");
        printf("2. Consultar Estoque\n");
        printf("3. Fazer Venda\n");
        printf("4. Exibir Vendas\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        opcao = lerInteiro("");

        if (opcao == 1) {
            cadastrarJogo();
        } else if (opcao == 2) {
            consultarEstoque();
        } else if (opcao == 3) {
            fazerVenda();
        } else if (opcao == 4) {
            exibirVendas();
        } else if (opcao == 5) {
            printf("Saindo do sistema\n");
        } else {
            printf("Erro: Opcao invalida.\n");
        }
    }
    return 0;
}
