#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char estado[3]; 
    char codigo[5]; 
    char nome[50];
    unsigned long int populacao; 
    float area;
    float pib;
    int pontos_turisticos;
    
    
    float densidade_populacional; 
    float pib_per_capita;         
    float super_poder;            
} Carta;


void ler_carta(Carta *carta, int numero) {
    printf("\n--- Entrada de Dados para a Carta %d ---\n", numero);
    
    
    printf("Estado (2 letras, ex: SP): ");
    scanf("%2s", carta->estado);
    printf("Código (até 4 dígitos, ex: 1234): ");
    scanf("%4s", carta->codigo);
    printf("Nome da Cidade (até 49 caracteres): ");
    
    while (getchar() != '\n'); 
    fgets(carta->nome, 50, stdin);
    
    carta->nome[strcspn(carta->nome, "\n")] = 0;

    
    printf("População (unsigned long int): ");
    
    if (scanf("%lu", &carta->populacao) != 1) {
        fprintf(stderr, "Erro na leitura da população. Encerrando.\n");
        exit(1);
    }
    
    printf("Área (float): ");
    if (scanf("%f", &carta->area) != 1) {
        fprintf(stderr, "Erro na leitura da área. Encerrando.\n");
        exit(1);
    }
    
    printf("PIB (float): ");
    if (scanf("%f", &carta->pib) != 1) {
        fprintf(stderr, "Erro na leitura do PIB. Encerrando.\n");
        exit(1);
    }
    
    printf("Número de Pontos Turísticos (int): ");
    if (scanf("%d", &carta->pontos_turisticos) != 1) {
        fprintf(stderr, "Erro na leitura dos pontos turísticos. Encerrando.\n");
        exit(1);
    }
}


void calcular_atributos_derivados(Carta *carta) {
    
    if (carta->area > 0) {
        
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0.0f; 
    }

    
    if (carta->populacao > 0) {
        
        carta->pib_per_capita = carta->pib / (float)carta->populacao;
    } else {
        carta->pib_per_capita = 0.0f; 
    }
}


void calcular_super_poder(Carta *carta) {
    
    
    
    float inverso_densidade = 0.0f;
    if (carta->densidade_populacional > 0) {
        inverso_densidade = 1.0f / carta->densidade_populacional;
    }
    
    carta->super_poder = 
        (float)carta->populacao + 
        carta->area + 
        carta->pib + 
        (float)carta->pontos_turisticos + 
        carta->pib_per_capita + 
        inverso_densidade;
}


void exibir_carta(const Carta *carta, int numero) {
    printf("\n--- Dados da Carta %d ---\n", numero);
    printf("Estado: %s\n", carta->estado);
    printf("Código: %s\n", carta->codigo);
    printf("Nome: %s\n", carta->nome);
    printf("População: %lu\n", carta->populacao);
    printf("Área: %.2f\n", carta->area);
    printf("PIB: %.2f\n", carta->pib);
    printf("Pontos Turísticos: %d\n", carta->pontos_turisticos);
    printf("Densidade Populacional: %.4f\n", carta->densidade_populacional);
    printf("PIB per Capita: %.4f\n", carta->pib_per_capita);
    printf("Super Poder: %.4f\n", carta->super_poder);
}


int comparar_atributo(float valor1, float valor2, const char *nome_atributo, int menor_vence) {
    int carta1_vence;
    
    if (menor_vence) {
        
        carta1_vence = (valor1 < valor2);
    } else {
        
        carta1_vence = (valor1 > valor2);
    }
    
    printf("%s: Carta %d venceu (%d)\n", 
           nome_atributo, 
           carta1_vence ? 1 : 2, 
           carta1_vence);
           
    return carta1_vence;
}


void comparar_cartas(const Carta *carta1, const Carta *carta2) {
    printf("\n--- Comparação de Cartas ---\n");

    
    comparar_atributo((float)carta1->populacao, (float)carta2->populacao, "População", 0);
    
    
    comparar_atributo(carta1->area, carta2->area, "Área", 0);
    
    
    comparar_atributo(carta1->pib, carta2->pib, "PIB", 0);
    
    
    comparar_atributo((float)carta1->pontos_turisticos, (float)carta2->pontos_turisticos, "Pontos Turísticos", 0);
    
    
    comparar_atributo(carta1->densidade_populacional, carta2->densidade_populacional, "Densidade Populacional", 1);
    
    
    comparar_atributo(carta1->pib_per_capita, carta2->pib_per_capita, "PIB per Capita", 0);
    
    
    comparar_atributo(carta1->super_poder, carta2->super_poder, "Super Poder", 0);
}

int main() {
    Carta carta1, carta2;

    
    ler_carta(&carta1, 1);
    
    while (getchar() != '\n'); 
    
    ler_carta(&carta2, 2);
    
    while (getchar() != '\n'); 

    
    calcular_atributos_derivados(&carta1);
    calcular_atributos_derivados(&carta2);
    
    
    calcular_super_poder(&carta1);
    calcular_super_poder(&carta2);

    
    exibir_carta(&carta1, 1);
    exibir_carta(&carta2, 2);

    
    comparar_cartas(&carta1, &carta2);

    return 0;
}