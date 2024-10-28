# Sistema de Vendas de Jogos

## Documentação da Implementação

**Alunos:** Ryan Cavalcanti, Pedro Augusto Calil, Luan Ramiro, Icaro Sousa

---

### Descrição Geral

Este documento detalha a implementação do sistema de vendas de jogos, incluindo uma interface prática e funcional que oferece ao usuário cinco opções principais.

### Menu de Interface Base

#### 1. Cadastrar Jogo
- **Nome do Jogo:** Armazena o nome dos jogos utilizando um vetor de caracteres (`char`). O cadastro é finalizado ao pressionar “enter”.
- **Plataforma:** Salva a plataforma do jogo, utilizando apenas caracteres e finalizando com “enter”.
- **Preço:** Define o preço do jogo.
- **Quantidade em Estoque:** Registra a quantidade disponível do jogo.
- **Código do Produto:** Atribui um código único para cada produto.

#### 2. Consultar Estoque
Permite ao usuário buscar produtos no estoque por:
1. Nome do jogo
2. Plataforma
3. Código do produto

#### 3. Fazer Vendas
Permite ao usuário realizar uma ou mais vendas. O usuário insere o código do produto e a quantidade desejada, e o sistema realiza a venda.

#### 4. Exibir Vendas
Exibe o histórico de vendas, listando as informações de cada produto, incluindo nome, quantidade e preço unitário. Se não houver vendas registradas, exibe uma mensagem informativa.

#### 5. Sair do Sistema
Encerra o sistema e exibe uma mensagem de saída.

### Decisões de Implementação

#### Funções de Validação
- **Ler Inteiro e Ler Float:** Essas funções solicitam ao usuário um número inteiro ou decimal e verificam se a entrada é válida. Caso o usuário insira um valor inválido (como letras), a função limpa o buffer e exibe uma mensagem de erro, solicitando nova entrada. São usadas para validar entradas numéricas como quantidades, códigos de produtos e preços.

---

### Divisão de Tarefas

- **Código:** Ryan Cavalcanti, Pedro Augusto
- **Documentação:** Ícaro Sousa, Pedro Augusto, Ryan Cavalcanti
- **Vídeo:** Luan Ramiro

---
