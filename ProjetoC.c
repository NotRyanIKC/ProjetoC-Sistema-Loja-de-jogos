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


int lerInteiro(char* mensagem) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            if (valor >= 0) return valor;
            else printf("Erro: O valor deve ser positivo.\n");
        } else {
            printf("Erro: Entrada inválida. Insira um número inteiro.\n");
        }
    }
}

float lerFloat(char* mensagem) {
    float valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) == 1) {
            if (valor >= 0) return valor;
            else printf("Erro: O valor deve ser positivo.\n");
        } else {
            printf("Erro: Entrada inválida. Insira um número.\n");
        }
    }
}

void cadastrarJogo() {
    if (contadorJogos < JOGOS) {
        printf("Nome do Jogo: ");
        scanf(" %[^\n]s", nomes[contadorJogos]);
        printf("Plataforma: ");
        scanf(" %[^\n]s", plataformas[contadorJogos]);
        precos[contadorJogos] = lerFloat("Preço: ");
        quantidades[contadorJogos] = lerInteiro("Quantidade em Estoque: ");
        codigos[contadorJogos] = lerInteiro("Código do Produto: ");
        
        contadorJogos++;
        printf("\nJogo cadastrado com sucesso!\n");
    } else {
        printf("Erro: Limite de jogos cadastrados atingido.\n");
    }
}


void consultarEstoque() {
    int opcao, codigo, encontrado = 0;
    char nome[50], plataforma[30];
    int i;
    printf("Consultar por:\n1. Nome\n2. Plataforma\n3. Código\nEscolha a opção: ");
    opcao = lerInteiro("");
    
    if (opcao == 1) {
        printf("Digite o nome do jogo: ");
        scanf(" %[^\n]s", nome);
        for ( i = 0; i < contadorJogos; i++) {
            if (strcmp(nomes[i], nome) == 0) {
                printf("\nNome: %s\nPlataforma: %s\nPreço: R$%.2f\nEstoque: %d\nCódigo: %d\n",
                       nomes[i], plataformas[i], precos[i], quantidades[i], codigos[i]);
                encontrado = 1;
            }
        }
    } else if (opcao == 2) {
        printf("Digite a plataforma: ");
        scanf(" %[^\n]s", plataforma);
        for ( i = 0; i < contadorJogos; i++) {
            if (strcmp(plataformas[i], plataforma) == 0) {
                printf("\nNome: %s\nPlataforma: %s\nPreço: R$%.2f\nEstoque: %d\nCódigo: %d\n",
                       nomes[i], plataformas[i], precos[i], quantidades[i], codigos[i]);
                encontrado = 1;
            }
        }
    } else if (opcao == 3) {
        codigo = lerInteiro("Digite o código do jogo: ");
        for ( i = 0; i < contadorJogos; i++) {
            if (codigos[i] == codigo) {
                printf("\nNome: %s\nPlataforma: %s\nPreço: R$%.2f\nEstoque: %d\nCódigo: %d\n",
                       nomes[i], plataformas[i], precos[i], quantidades[i], codigos[i]);
                encontrado = 1;
            }
        }
    } else {
        printf("Erro: Opção inválida.\n");
    }

    if (!encontrado) {
        printf("Jogo não encontrado.\n");
    }
}


void registrarVenda() {
    int i,j;
    if (contadorVendas < VENDAS) {
        int numProdutos = lerInteiro("Quantos produtos serão registrados nesta venda? ");
        if (numProdutos > PRODUTOS_VENDA) {
            printf("Erro: Número máximo de produtos por venda é %d.\n", PRODUTOS_VENDA);
            return;
        }

        float totalVenda = 0;
        for ( i = 0; i < numProdutos; i++) {
            int codigo = lerInteiro("Digite o código do produto: ");
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
                    printf("Produto %s adicionado à venda. Subtotal: R$%.2f\n", nomes[j], quantidade * precos[j]);
                    break;
                }
            }
            if (!encontrado) {
                printf("Erro: Produto com código %d não encontrado.\n", codigo);
                return;
            }
        }
        contadorVendas++;
        printf("Venda registrada com sucesso! Total da venda: R$%.2f\n", totalVenda);
    } else {
        printf("Erro: Limite de vendas atingido.\n");
    }
}


void exibirVendas() {
    int i,j,k;
    if (contadorVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    for ( i = 0; i < contadorVendas; i++) {
        printf("\nVenda #%d\n", i + 1);
        for ( j = 0; j < totalProdutosPorVenda[i]; j++) {
            for ( k = 0; k < contadorJogos; k++) {
                if (codigos[k] == vendas[i][j]) {
                    printf("Produto: %s, Quantidade: %d, Preço Unitário: R$%.2f\n", 
                           nomes[k], quantidadesVendidas[i][j], precos[k]);
                }
            }
        }
    }
}

int main() {
    int opcao = 0;

    while (opcao != 5) {
        printf("\nMenu:\n");
        printf("1. Cadastrar Jogo\n");
        printf("2. Consultar Estoque\n");
        printf("3. Registrar Venda\n");
        printf("4. Exibir Vendas\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        opcao = lerInteiro("");

        if (opcao == 1) {
            cadastrarJogo();
        } else if (opcao == 2) {
            consultarEstoque();
        } else if (opcao == 3) {
            registrarVenda();
        } else if (opcao == 4) {
            exibirVendas();
        } else if (opcao == 5) {
            printf("Saindo do sistema...\n");
        } else {
            printf("Erro: Opção inválida.\n");
        }
    }

    return 0;
}
