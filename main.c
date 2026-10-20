#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>
#include "memoria.h"

static int lerInteiro(const char *mensagem, int *valor) {
    char linha[128];
    char *fim;
    long numero;

    printf("%s", mensagem);

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    numero = strtol(linha, &fim, 10);

    while (isspace((unsigned char)*fim)) {
        fim++;
    }

    if (fim == linha || *fim != '\0' || errno == ERANGE ||
        numero < INT_MIN || numero > INT_MAX) {
        printf("Entrada invalida. Digite um numero inteiro.\n");
        return 0;
    }

    *valor = (int)numero;
    return 1;
}

static int lerTamanho(size_t *tamanho) {
    char linha[128];
    char *fim;
    unsigned long long numero;

    printf("Informe o tamanho do bloco em bytes: ");

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 0;
    }

    char *inicio = linha;
    while (isspace((unsigned char)*inicio)) {
        inicio++;
    }

    if (*inicio == '-' || *inicio == '\0') {
        printf("Tamanho invalido. Informe um inteiro positivo.\n");
        return 0;
    }

    errno = 0;
    numero = strtoull(inicio, &fim, 10);

    while (isspace((unsigned char)*fim)) {
        fim++;
    }

    if (fim == inicio || *fim != '\0' || errno == ERANGE ||
        numero == 0 || numero > SIZE_MAX) {
        printf("Tamanho invalido. Informe um inteiro positivo valido.\n");
        return 0;
    }

    *tamanho = (size_t)numero;
    return 1;
}

static void exibirMenu(void) {
    printf("\n========== GERENCIADOR DE MEMORIA ==========\n");
    printf("1 - Alocar bloco de memoria\n");
    printf("2 - Liberar bloco de memoria\n");
    printf("3 - Exibir estado da memoria\n");
    printf("4 - Exibir resumo da memoria\n");
    printf("0 - Encerrar\n");
}

int main(void) {
    int opcao;
    int id;
    size_t tamanho;

    inicializarMemoria();

    do {
        exibirMenu();

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            continue;
        }

        switch (opcao) {
            case 1:
                if (lerTamanho(&tamanho)) {
                    alocarBloco(tamanho);
                }
                break;

            case 2:
                if (lerInteiro("Informe o identificador do bloco: ", &id)) {
                    liberarBloco(id);
                }
                break;

            case 3:
                exibirEstadoMemoria();
                break;

            case 4:
                exibirResumoMemoria();
                break;

            case 0:
                printf("\nLiberando blocos restantes...\n");
                liberarTodosBlocos();
                printf("Todos os recursos foram liberados.\n");
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
