#include <stdio.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int inicio;
    int fim;
    int quantidade;
} Fila;

void inicializar(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == MAX;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

void mostrarEstado(Fila *f) {
    printf("Estado -> inicio: %d | fim: %d | quantidade: %d\n", f->inicio, f->fim, f->quantidade);
}

void inserir(Fila *f, int valor) {
    if (filaCheia(f)) {
        printf("Fila cheia! Overflow: insercao nao permitida.\n");
        return;
    }
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;
    printf("Elemento %d inserido.\n", valor);
}

void remover(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Underflow: remocao nao permitida.\n");
        return;
    }
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;
    printf("Elemento %d removido.\n", valor);
}

void listar(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Elementos (do primeiro ao ultimo): ");
    for (int i = 0; i < f->quantidade; i++) {
        int indice = (f->inicio + i) % MAX;
        printf("%d ", f->dados[indice]);
    }
    printf("\n");
}

int main() {
    Fila fila;
    int opcao;
    int valor;

    inicializar(&fila);

    do {
        printf("\n===== FILA CIRCULAR =====\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Listar elementos\n");
        printf("4. Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            break;
        }

        switch (opcao) {
            case 1:
                printf("Valor: ");
                if (scanf("%d", &valor) != 1) {
                    return 0;
                }
                inserir(&fila, valor);
                break;
            case 2:
                remover(&fila);
                break;
            case 3:
                listar(&fila);
                break;
            case 4:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

        if (opcao >= 1 && opcao <= 3) {
            mostrarEstado(&fila);
        }
    } while (opcao != 4);

    return 0;
}
