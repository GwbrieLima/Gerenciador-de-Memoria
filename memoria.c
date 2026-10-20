#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

static BlocoMemoria blocos[MAX_BLOCOS];
static int totalRegistros = 0;
static int proximoId = 1;

void inicializarMemoria(void) {
    totalRegistros = 0;
    proximoId = 1;

    for (int i = 0; i < MAX_BLOCOS; i++) {
        blocos[i].id = 0;
        blocos[i].endereco = NULL;
        blocos[i].tamanho = 0;
        blocos[i].ocupado = 0;
    }
}

int alocarBloco(size_t tamanho) {
    if (tamanho == 0) {
        printf("Erro: o tamanho deve ser maior que zero.\n");
        return 0;
    }

    if (totalRegistros >= MAX_BLOCOS) {
        printf("Erro: limite de registros atingido.\n");
        return 0;
    }

    void *memoria = malloc(tamanho);
    if (memoria == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return 0;
    }

    blocos[totalRegistros].id = proximoId++;
    blocos[totalRegistros].endereco = memoria;
    blocos[totalRegistros].tamanho = tamanho;
    blocos[totalRegistros].ocupado = 1;

    printf("\nBloco alocado com sucesso!\n");
    printf("Identificador: %d\n", blocos[totalRegistros].id);
    printf("Endereco: %p\n", blocos[totalRegistros].endereco);
    printf("Tamanho: %zu bytes\n", blocos[totalRegistros].tamanho);
    printf("Estado: OCUPADO\n");

    totalRegistros++;
    return 1;
}

int liberarBloco(int id) {
    for (int i = 0; i < totalRegistros; i++) {
        if (blocos[i].id == id) {
            if (!blocos[i].ocupado) {
                printf("Erro: o bloco %d ja esta livre.\n", id);
                return 0;
            }

            free(blocos[i].endereco);
            blocos[i].endereco = NULL;
            blocos[i].ocupado = 0;

            printf("Bloco %d liberado com sucesso.\n", id);
            return 1;
        }
    }

    printf("Erro: o identificador %d nao existe.\n", id);
    return 0;
}

void exibirEstadoMemoria(void) {
    if (totalRegistros == 0) {
        printf("Nenhum bloco foi registrado ainda.\n");
        return;
    }

    printf("\n%-5s %-20s %-16s %-10s\n",
           "ID", "ENDERECO", "TAMANHO", "ESTADO");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < totalRegistros; i++) {
        printf("%-5d ", blocos[i].id);

        if (blocos[i].ocupado) {
            printf("%-20p %-16zu %-10s\n",
                   blocos[i].endereco, blocos[i].tamanho, "OCUPADO");
        } else {
            printf("%-20s %-16zu %-10s\n",
                   "(liberado)", blocos[i].tamanho, "LIVRE");
        }
    }
}

void exibirResumoMemoria(void) {
    int ocupados = 0;
    int livres = 0;
    size_t bytesAlocados = 0;

    for (int i = 0; i < totalRegistros; i++) {
        if (blocos[i].ocupado) {
            ocupados++;
            bytesAlocados += blocos[i].tamanho;
        } else {
            livres++;
        }
    }

    printf("\nResumo da memoria\n");
    printf("Total de registros: %d\n", totalRegistros);
    printf("Blocos ocupados: %d\n", ocupados);
    printf("Blocos livres: %d\n", livres);
    printf("Bytes atualmente alocados: %zu\n", bytesAlocados);
}

void liberarTodosBlocos(void) {
    for (int i = 0; i < totalRegistros; i++) {
        if (blocos[i].ocupado) {
            free(blocos[i].endereco);
            blocos[i].endereco = NULL;
            blocos[i].ocupado = 0;
        }
    }
}
