#include <stdio.h>
#include <string.h>

#define MAX 5
#define TAM_NOME 50

typedef struct {
    int senha;
    char nome[TAM_NOME];
} Pessoa;

typedef struct {
    Pessoa pessoas[MAX];
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
    if (filaCheia(f)) {
        printf("Situacao: FILA CHEIA\n");
    } else if (filaVazia(f)) {
        printf("Situacao: FILA VAZIA\n");
    } else {
        printf("Situacao: fila com vagas\n");
    }
}

void inserir(Fila *f, int senha, const char *nome) {
    if (filaCheia(f)) {
        printf("Fila cheia! Overflow: insercao nao permitida.\n");
        return;
    }
    f->pessoas[f->fim].senha = senha;
    strncpy(f->pessoas[f->fim].nome, nome, TAM_NOME - 1);
    f->pessoas[f->fim].nome[TAM_NOME - 1] = '\0';
    printf("Senha %d (%s) inserida na posicao %d do array.\n", senha, f->pessoas[f->fim].nome, f->fim);
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;
}

void chamarProximo(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Underflow: nao ha ninguem para chamar.\n");
        return;
    }
    Pessoa p = f->pessoas[f->inicio];
    printf("Chamando senha %d - %s (posicao %d do array liberada).\n", p.senha, p.nome, f->inicio);
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;
}

void visualizar(Fila *f) {
    printf("Fila de espera (ordem de atendimento):\n");
    if (filaVazia(f)) {
        printf("  (vazia)\n");
    } else {
        for (int i = 0; i < f->quantidade; i++) {
            int indice = (f->inicio + i) % MAX;
            printf("  %d. Senha %d - %s (posicao %d)\n", i + 1, f->pessoas[indice].senha, f->pessoas[indice].nome, indice);
        }
    }
    printf("Posicoes do array:\n");
    for (int i = 0; i < MAX; i++) {
        int ocupada = 0;
        for (int j = 0; j < f->quantidade; j++) {
            if ((f->inicio + j) % MAX == i) {
                ocupada = 1;
                break;
            }
        }
        if (ocupada) {
            printf("  [%d] senha %d - %s\n", i, f->pessoas[i].senha, f->pessoas[i].nome);
        } else {
            printf("  [%d] livre\n", i);
        }
    }
}

int main() {
    Fila fila;
    int opcao;
    int proximaSenha = 1;
    char nome[TAM_NOME];

    inicializar(&fila);

    do {
        printf("\n===== FILA DE ATENDIMENTO =====\n");
        printf("1. Inserir pessoa\n");
        printf("2. Chamar proximo\n");
        printf("3. Visualizar fila\n");
        printf("4. Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            break;
        }

        switch (opcao) {
            case 1:
                if (filaCheia(&fila)) {
                    inserir(&fila, proximaSenha, "");
                } else {
                    printf("Nome: ");
                    if (scanf(" %49[^\n]", nome) != 1) {
                        return 0;
                    }
                    inserir(&fila, proximaSenha, nome);
                    proximaSenha++;
                }
                break;
            case 2:
                chamarProximo(&fila);
                break;
            case 3:
                visualizar(&fila);
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
