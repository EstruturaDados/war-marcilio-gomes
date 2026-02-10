// Biblioteca para entrada e saída (printf, scanf)
#include <stdio.h>

// Biblioteca para alocação dinâmica (malloc, calloc, free)
#include <stdlib.h>

// Biblioteca para manipular strings (strcpy, strcmp)
#include <string.h>

// Biblioteca para gerar números aleatórios com tempo
#include <time.h>

// Definição da struct Territorio
typedef struct {

    // Nome do território
    char nome[30];

    // Cor do exército dono
    char cor[10];

    // Quantidade de tropas
    int tropas;

} Territorio;


/*
 Função para cadastrar os territórios
 Recebe:
 - ponteiro para o vetor de territórios
 - quantidade de territórios
*/
void cadastrarTerritorios(Territorio* mapa, int quantidade) {

    int i;

    // Laço para cadastrar todos os territórios
    for (i = 0; i < quantidade; i++) {

        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        // Lê o nome
        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        // Lê a cor
        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        // Lê as tropas
        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


/*
 Função para exibir os territórios
 Recebe:
 - ponteiro para o vetor
 - quantidade
*/
void exibirTerritorios(Territorio* mapa, int quantidade) {

    int i;

    printf("\n=== MAPA ATUAL ===\n\n");

    // Percorre todos os territórios
    for (i = 0; i < quantidade; i++) {

        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("--------------------------\n");
    }
}


/*
 Função que simula o ataque
 Recebe:
 - ponteiro para o atacante
 - ponteiro para o defensor
*/
void atacar(Territorio* atacante, Territorio* defensor) {

    // Sorteia número de 1 a 6 para o atacante
    int dadoAtacante = rand() % 6 + 1;

    // Sorteia número de 1 a 6 para o defensor
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("Atacante (%s) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) tirou: %d\n", defensor->nome, dadoDefensor);

    // Se o atacante vencer
    if (dadoAtacante > dadoDefensor) {

        printf(">>> Atacante venceu!\n");

        // Copia a cor do atacante para o defensor
        strcpy(defensor->cor, atacante->cor);

        // Transfere metade das tropas
        defensor->tropas = atacante->tropas / 2;

    } 
    // Se o defensor vencer ou empatar
    else {

        printf(">>> Defensor resistiu!\n");

        // Atacante perde uma tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}


/*
 Função para liberar a memória
 Recebe:
 - ponteiro do vetor
*/
void liberarMemoria(Territorio* mapa) {

    // Libera o espaço alocado
    free(mapa);

    printf("\nMemoria liberada com sucesso.\n");
}


int main() {

    // Ponteiro para armazenar os territórios
    Territorio* mapa;

    // Quantidade de territórios
    int quantidade;

    // Índices escolhidos
    int atacante, defensor;

    // Inicializa o gerador aleatório
    srand(time(NULL));

    printf("=== WAR ESTRUTURADO - NIVEL AVENTUREIRO ===\n\n");

    // Pede a quantidade
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);

    // Aloca memória dinamicamente com calloc
    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    // Verifica se a alocação deu certo
    if (mapa == NULL) {

        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastra os territórios
    cadastrarTerritorios(mapa, quantidade);

    // Mostra o mapa inicial
    exibirTerritorios(mapa, quantidade);

    // Pergunta se deseja atacar
    printf("\nDeseja realizar um ataque? (1 = Sim / 0 = Nao): ");
    int opcao;
    scanf("%d", &opcao);

    // Enquanto o jogador quiser atacar
    while (opcao == 1) {

        // Mostra os territórios
        exibirTerritorios(mapa, quantidade);

        // Escolhe o atacante
        printf("\nEscolha o numero do territorio atacante: ");
        scanf("%d", &atacante);

        // Escolhe o defensor
        printf("Escolha o numero do territorio defensor: ");
        scanf("%d", &defensor);

        // Ajusta para índice do vetor
        atacante--;
        defensor--;

        // Verifica se são válidos
        if (atacante < 0 || atacante >= quantidade ||
            defensor < 0 || defensor >= quantidade) {

            printf("Escolha invalida!\n");
        }

        // Verifica se é da mesma cor
        else if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {

            printf("Nao pode atacar territorio da mesma cor!\n");
        }

        // Executa o ataque
        else {

            atacar(&mapa[atacante], &mapa[defensor]);
        }

        // Mostra resultado
        exibirTerritorios(mapa, quantidade);

        // Pergunta novamente
        printf("\nDeseja realizar outro ataque? (1 = Sim / 0 = Nao): ");
        scanf("%d", &opcao);
    }

    // Libera memória no final
    liberarMemoria(mapa);

    printf("\nPrograma finalizado.\n");

    return 0;
}
