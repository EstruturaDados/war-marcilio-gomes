// Biblioteca para entrada e saída de dados (printf, scanf)
#include <stdio.h>

// Biblioteca para manipular strings
#include <string.h>

// Definição da struct Territorio
// Ela agrupa informações sobre um território
typedef struct {
    
    // Armazena o nome do território (até 29 caracteres + \0)
    char nome[30];

    // Armazena a cor do exército (até 9 caracteres + \0)
    char cor[10];

    // Armazena a quantidade de tropas
    int tropas;

} Territorio;

int main() {

    // Declara um vetor que pode armazenar 5 territórios
    Territorio territorios[5];

    // Variável usada no laço de repetição
    int i;

    // Exibe uma mensagem inicial para o usuário
    printf("=== Cadastro de Territorios ===\n\n");

    // Laço para cadastrar os 5 territórios
    for (i = 0; i < 5; i++) {

        // Mostra qual território está sendo cadastrado
        printf("Cadastro do Territorio %d\n", i + 1);

        // Pede o nome do território
        printf("Digite o nome: ");
        scanf("%s", territorios[i].nome);

        // Pede a cor do exército
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        // Pede a quantidade de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);

        // Linha em branco para organização
        printf("\n");
    }

    // Exibe uma mensagem antes de mostrar os dados
    printf("\n=== Territorios Cadastrados ===\n\n");

    // Laço para exibir os dados dos territórios
    for (i = 0; i < 5; i++) {

        // Mostra o número do território
        printf("Territorio %d\n", i + 1);

        // Mostra o nome
        printf("Nome: %s\n", territorios[i].nome);

        // Mostra a cor do exército
        printf("Cor do Exercito: %s\n", territorios[i].cor);

        // Mostra o número de tropas
        printf("Tropas: %d\n", territorios[i].tropas);

        // Linha separadora
        printf("--------------------------\n");
    }

    // Finaliza o programa
    return 0;
}
