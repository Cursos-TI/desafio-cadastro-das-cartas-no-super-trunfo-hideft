#include <stdio.h>

struct Carta {
    char codigo[4]; // Ex: A01
    int populacao;
    float area;
    float pib;
};

int main() {
    struct Carta carta1;

    printf("--- Cadastro da Carta ---\n");
    printf("Digite o código da carta (ex: A01): ");
    scanf("%s", carta1.codigo);
    printf("Digite a população (inteiro): ");
    scanf("%d", &carta1.populacao);
    printf("Digite a área (float): ");
    scanf("%f", &carta1.area);
    printf("Digite o PIB (float): ");
    scanf("%f", &carta1.pib);

    printf("\n--- Dados Cadastrados ---\n");
    printf("\nCarta (%s):\n", carta1.codigo);
    printf("População: %d\n", carta1.populacao);
    printf("Área: %.2f\n", carta1.area);
    printf("PIB: %.2f\n", carta1.pib);

    return 0;
}
