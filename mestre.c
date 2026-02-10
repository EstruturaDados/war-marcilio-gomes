// Biblioteca de entrada e saída
#include <stdio.h>

// Biblioteca de alocação dinâmica
#include <stdlib.h>

// Biblioteca de strings
#include <string.h>

// Biblioteca de tempo (para srand)
#include <time.h>


// ================= STRUCT =================

// Estrutura que representa um território
typedef struct {

    // Nome do território
    char nome[30];

    // Cor do exército
    char cor[10];

    // Número de tropas
    int tropas;

} Territorio;


// ================= FUNÇÕES =================


/*
 Função para cadastrar territórios
*/
void cadastrarTerritorios(Territorio* mapa, int qtd) {

    int i;

    for (i = 0; i < qtd; i++) {

        printf("\n=== Territorio %d ===\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


/*
 Função para mostrar o mapa
*/
void exibirMapa(Territorio* mapa, int qtd) {

    int i;

    printf("\n=== MAPA ===\n\n");

    for (i = 0; i < qtd; i++) {

        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }

    printf("\n");
}


/*
 Função para sortear e atribuir missão
*/
void atribuirMissao(char* destino, char* missoes[], int total) {

    // Sorteia índice
    int sorteio = rand() % total;

    // Copia a missão sorteada
    strcpy(destino, missoes[sorteio]);
}


/*
 Função para exibir missão
*/
void exibirMissao(char* missao) {

    printf("\n=== SUA MISSAO ===\n");
    printf("%s\n\n", missao);
}


/*
 Função de ataque
*/
void atacar(Territorio* atacante, Territorio* defensor) {

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nBATALHA!\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoA);
    printf("Defensor (%s): %d\n", defensor->nome, dadoD);

    // Atacante vence
    if (dadoA > dadoD) {

        printf(">>> Atacante venceu!\n");

        // Muda cor
        strcpy(defensor->cor, atacante->cor);

        // Transfere tropas
        defensor->tropas = atacante->tropas / 2;
    }
    // Defensor vence
    else {

        printf(">>> Defensor resistiu!\n");

        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}


/*
 Função para verificar missão
*/
int verificarMissao(char* missao, Territorio* mapa, int qtd) {

    int i;
    int contador = 0;

    // Missão: Conquistar 3 territórios
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {

        for (i = 0; i < qtd; i++) {

            if (strcmp(mapa[i].cor, "Azul") == 0) {
                contador++;
            }
        }

        if (contador >= 3)
            return 1;
    }


    // Missão: Dominar tudo
    if (strcmp(missao, "Dominar todo o mapa") == 0) {

        for (i = 0; i < qtd; i++) {

            if (strcmp(mapa[i].cor, "Azul") != 0) {
                return 0;
            }
        }

        return 1;
    }


    // Missão: Ter 20 tropas
    if (strcmp(missao, "Ter 20 tropas") == 0) {

        int total = 0;

        for (i = 0; i < qtd; i++) {

            if (strcmp(mapa[i].cor, "Azul") == 0) {
                total += mapa[i].tropas;
            }
        }

        if (total >= 20)
            return 1;
    }


    return 0;
}


/*
 Função para liberar memória
*/
void liberarMemoria(Territorio* mapa, char* missao) {

    free(mapa);
    free(missao);

    printf("\nMemoria liberada.\n");
}


// ================= MAIN =================

int main() {

    srand(time(NULL));

    Territorio* mapa;
    char* missaoJogador;

    int qtd;
    int opcao;

    // Vetor de missões
    char* missoes[] = {

        "Conquistar 3 territorios",
        "Dominar todo o mapa",
        "Ter 20 tropas",
        "Eliminar inimigos",
        "Expandir dominio"
    };

    int totalMissoes = 5;


    printf("=== WAR NIVEL MESTRE ===\n\n");

    // Quantidade de territórios
    printf("Quantos territorios? ");
    scanf("%d", &qtd);


    // Aloca mapa
    mapa = (Territorio*) calloc(qtd, sizeof(Territorio));

    // Aloca missão
    missaoJogador = (char*) malloc(100 * sizeof(char));


    // Verifica erro
    if (mapa == NULL || missaoJogador == NULL) {

        printf("Erro de memoria!\n");
        return 1;
    }


    // Cadastro
    cadastrarTerritorios(mapa, qtd);

    // Sorteia missão
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    // Mostra missão apenas uma vez
    exibirMissao(missaoJogador);


    // Loop principal
    do {

        exibirMapa(mapa, qtd);

        int a, d;

        printf("Atacante: ");
        scanf("%d", &a);

        printf("Defensor: ");
        scanf("%d", &d);

        a--;
        d--;


        // Valida
        if (a < 0 || a >= qtd || d < 0 || d >= qtd) {

            printf("Escolha invalida!\n");
        }

        else if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {

            printf("Nao pode atacar aliado!\n");
        }

        else {

            atacar(&mapa[a], &mapa[d]);
        }


        // Verifica missão
        if (verificarMissao(missaoJogador, mapa, qtd)) {

            printf("\n====================\n");
            printf("VOCE VENCEU O JOGO!\n");
            printf("====================\n");
            break;
        }


        printf("\nContinuar jogando? (1 = Sim / 0 = Nao): ");
        scanf("%d", &opcao);

    } while (opcao == 1);


    // Libera memória
    liberarMemoria(mapa, missaoJogador);

    printf("\nFim do jogo.\n");

    return 0;
}
