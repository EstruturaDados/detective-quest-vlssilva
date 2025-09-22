#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um nó da árvore binária (cada nó é uma sala)
typedef struct No {
    char* nome;
    struct No* esquerda;
    struct No* direita;
} No;

// Função para criar um novo nó (sala) dinamicamente
No* criarSala(char* nome) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novoNo->nome = (char*)malloc(strlen(nome) + 1);
    strcpy(novoNo->nome, nome);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para explorar as salas interativamente
// Mostra o nome da sala atual e permite navegação
void explorarSalas(No* atual) {
    if (atual == NULL) {
        printf("Fim do caminho! Você chegou a uma sala sem saídas.\n");
        return;
    }

    printf("\nVocê está na sala: %s\n", atual->nome);

    // Verifica se é uma folha (sem filhos)
    if (atual->esquerda == NULL && atual->direita == NULL) {
        printf("Esta é uma sala final (folha). Fim do caminho!\n");
        return;
    }

    // Opções disponíveis
    printf("Opções:\n");
    if (atual->esquerda != NULL) {
        printf("e -> Ir para a esquerda\n");
    }
    if (atual->direita != NULL) {
        printf("d -> Ir para a direita\n");
    }
    printf("s -> Sair da exploração\n");

    char opcao;
    printf("Escolha (e/d/s): ");
    scanf(" %c", &opcao);

    switch (opcao) {
        case 'e':
        case 'E':
            if (atual->esquerda != NULL) {
                explorarSalas(atual->esquerda);
            } else {
                printf("Não há saída para a esquerda! Fim do caminho.\n");
            }
            break;
        case 'd':
        case 'D':
            if (atual->direita != NULL) {
                explorarSalas(atual->direita);
            } else {
                printf("Não há saída para a direita! Fim do caminho.\n");
            }
            break;
        case 's':
        case 'S':
            printf("Exploração encerrada pelo jogador.\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            // Recursão para tentar novamente na mesma sala
            explorarSalas(atual);
            break;
    }
}

// Função auxiliar para liberar a memória da árvore (boa prática)
void liberarArvore(No* no) {
    if (no == NULL) return;
    liberarArvore(no->esquerda);
    liberarArvore(no->direita);
    free(no->nome);
    free(no);
}

int main() {
    // Construção estática da árvore via código (dinamicamente alocada)
    // Raiz: Hall de Entrada
    No* raiz = criarSala("Hall de Entrada");

    // Filhos da raiz
    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Quarto Principal");

    // Filhos da Sala de Estar
    raiz->esquerda->esquerda = criarSala("Cozinha");
    raiz->esquerda->direita = criarSala("Banheiro");

    // Filhos do Quarto Principal (exemplo simples: só esquerda é folha, direita sem filhos para teste)
    raiz->direita->esquerda = criarSala("Biblioteca");
    // raiz->direita->direita = NULL; (já é NULL por padrão)

    // Início da exploração
    printf("🎮 Bem-vindo ao Mapa da Mansão!\n");
    printf("Você começa no Hall de Entrada. Explore usando 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");
    explorarSalas(raiz);

    // Liberação de memória
    liberarArvore(raiz);

    printf("\nFim do programa. Obrigado por explorar a mansão!\n");
    return 0;
}
