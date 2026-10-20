#ifndef MEMORIA_H
#define MEMORIA_H

#include <stddef.h>

#define MAX_BLOCOS 1000

typedef struct {
    int id;
    void *endereco;
    size_t tamanho;
    int ocupado;
} BlocoMemoria;

void inicializarMemoria(void);
int alocarBloco(size_t tamanho);
int liberarBloco(int id);
void exibirEstadoMemoria(void);
void exibirResumoMemoria(void);
void liberarTodosBlocos(void);

#endif
