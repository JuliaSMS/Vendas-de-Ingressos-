#include <stdio.h>
#include <string.h>
#include <time.h>

// Definicao da Constantes
#define Lotacao_Maxima 100
#define PRECO_INTEIRA 20.0
#define PRECO_MEIA 10.0
#define PRECO_ISENTO 0.0

//Funcao para Iniciar Sistema
void iniciarSistema(int* ingressos_disponiveis) {
    *ingressos_disponiveis = Lotacao_Maxima;
}

//Funcao para numero de validação
int gerarNumeroAleatorio() {
    srand(time(NULL));
    return rand();
}

//Funcao para Salvar As Vendas .txt
void salvarVendas(char nome[], int idade, float total, char metodo_pagamento[], int numero_validacao) {
    FILE* arquivo;
    arquivo = fopen("Historicos de Vendas.txt", "a");

    if (total == PRECO_ISENTO) {
        fprintf(arquivo, "Nome: %s, Idade: %d, Preco: %.2f, Pagamento: Isento, Numero do Ingresso: %d\n", nome, idade, total, numero_validacao);
    } else {
        fprintf(arquivo, "Nome: %s, Idade: %d, Preco: %.2f, Pagamento: %s, Numero do Ingresso: %d\n", nome, idade, total, (total == PRECO_ISENTO) ? "isento" : metodo_pagamento, numero_validacao);
    }

    fclose(arquivo);
}

// Função para comprar ingressos
void comprarIngressos(int* ingressos_disponiveis) {
    char nome[100];
    int idade;
    char metodo_pagamento[20];
    char pcd;

    printf("Informe o nome do cliente: ");
    scanf(" %99[^\n]", nome);

    printf("Informe a idade: ");
    scanf("%d", &idade);

    if (idade < 0) {
        printf("Desculpe, idade inválida.\n");
        return;
    }

    float total = 0.0;
    int numero_validacao = gerarNumeroAleatorio();

    printf("A pessoa é PCD (Pessoa com Deficiência)? (S/N): ");
    scanf(" %c", &pcd);

    if (idade < 5 || tolower(pcd) == 's') {
        total = PRECO_ISENTO; // Isento
    } else if (idade >= 6 && idade <= 21) {
        total = (pcd == 's') ? PRECO_ISENTO : PRECO_MEIA; // Meia-entrada
    } else if (idade >= 22 && idade <= 60) {
        total = (pcd == 's') ? PRECO_ISENTO : PRECO_INTEIRA; // Inteira
    } else if (idade > 60) {
        total = (pcd == 's') ? PRECO_ISENTO : PRECO_MEIA; // Meia-entrada para maiores de 60 anos
    } else {
        printf("Opção de ingresso inválida.\n");
        return;
    }
 // Se não for isento, pedir a forma de pagamento
    if (total > 0) {
        printf("Forma de pagamento (debito/credito/dinheiro): ");
        scanf("%19s", metodo_pagamento);
    }

    if (*ingressos_disponiveis > 0) {
        (*ingressos_disponiveis)--;
        printf("Compra realizada com sucesso!\n  Nome: %s, Idade: %d, Preco: %.2f, Pagamento: %s, Numero do Ingresso: %d\n", nome, idade, total, (total == PRECO_ISENTO) ? "isento" : metodo_pagamento, numero_validacao);
 // Salvar a venda no arquivo
        salvarVendas(nome, idade, total, metodo_pagamento, numero_validacao);
    } else {
        printf("Desculpe, ingressos esgotados.\n");
    }
}
// Função o historico de vendas
void listarVendas() {
    FILE* arquivo;
    char linha[100];

    arquivo = fopen("Historicos de Vendas.txt", "r");

    if (arquivo == NULL) {
        printf("Nenhuma venda encontrada.\n");
        return;
    }

    printf("=== Vendas Realizadas ===\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}
// Função para exibir o menu principal
int menuPrincipal() {
    int escolha;

    printf("\n=== Menu Principal ===\n");
    printf("1. Comprar Ingressos\n");
    printf("2. Listar Vendas\n");
    printf("3. Sair\n");
    printf("Escolha a opcao: ");
    scanf("%d", &escolha);

    return escolha;
}

int main() {
    int ingressos_disponiveis;
    iniciarSistema(&ingressos_disponiveis);

    int opcao;

    do {
        opcao = menuPrincipal();

        switch (opcao) {
            case 1:
                comprarIngressos(&ingressos_disponiveis);
                break;
            case 2:
                listarVendas();
                break;
            case 3:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}

