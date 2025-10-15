#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 


typedef struct {
    char nome[50];
    char estado[3];
    char codigo[5];
    unsigned long int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    
    
    float densidade_populacional; 
    float pib_per_capita;         
} Carta;


typedef struct {
    int indice;
    const char *nome;
    int menor_vence; 
} Atributo;


Atributo atributos[] = {
    {1, "População", 0},
    {2, "Área", 0},
    {3, "PIB", 0},
    {4, "Pontos Turísticos", 0},
    {5, "Densidade Populacional", 1}, 
    {6, "PIB per Capita", 0}
};
const int NUM_ATRIBUTOS = 6;


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


float obter_valor_atributo(const Carta *carta, int indice) {
    switch (indice) {
        case 1: return (float)carta->populacao;
        case 2: return carta->area;
        case 3: return carta->pib;
        case 4: return (float)carta->pontos_turisticos;
        case 5: return carta->densidade_populacional;
        case 6: return carta->pib_per_capita;
        default: return 0.0f;
    }
}


void exibir_menu_atributos(int atributo_ignorar) {
    printf("\n--- Escolha um Atributo para Comparação ---\n");
    for (int i = 0; i < NUM_ATRIBUTOS; i++) {
        if (atributos[i].indice != atributo_ignorar) {
            printf("%d - %s\n", atributos[i].indice, atributos[i].nome);
        }
    }
    printf("------------------------------------------\n");
    printf("Opção: ");
}


int ler_escolha_atributo(int atributo_ignorar) {
    int escolha;
    int valido = 0;
    
    while (!valido) {
        exibir_menu_atributos(atributo_ignorar);
        if (scanf("%d", &escolha) != 1) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            
            while (getchar() != '\n');
            continue;
        }
        
        
        if (escolha >= 1 && escolha <= NUM_ATRIBUTOS && escolha != atributo_ignorar) {
            valido = 1;
        } else {
            printf("Opção inválida. Por favor, escolha um número válido e não repetido.\n");
        }
    }
    return escolha;
}


const char* obter_nome_atributo(int indice) {
    for (int i = 0; i < NUM_ATRIBUTOS; i++) {
        if (atributos[i].indice == indice) {
            return atributos[i].nome;
        }
    }
    return "Atributo Desconhecido";
}


int obter_regra_atributo(int indice) {
    for (int i = 0; i < NUM_ATRIBUTOS; i++) {
        if (atributos[i].indice == indice) {
            return atributos[i].menor_vence;
        }
    }
    return 0; 
}


int comparar_atributo(float valor1, float valor2, int menor_vence) {
    if (menor_vence) {
        
        if (valor1 < valor2) return 1;
        if (valor2 < valor1) return 2;
    } else {
        
        if (valor1 > valor2) return 1;
        if (valor2 > valor1) return 2;
    }
    return 0; 
}


void exibir_comparacao_atributo(const Carta *c1, const Carta *c2, int indice) {
    float v1 = obter_valor_atributo(c1, indice);
    float v2 = obter_valor_atributo(c2, indice);
    const char *nome = obter_nome_atributo(indice);
    int menor_vence = obter_regra_atributo(indice);
    int vencedor = comparar_atributo(v1, v2, menor_vence);
    
    printf("  - %s: %.2f (Carta 1) vs %.2f (Carta 2) -> Vencedor: %s\n", 
           nome, 
           v1, 
           v2, 
           (vencedor == 1) ? c1->nome : (vencedor == 2) ? c2->nome : "Empate");
}

int main() {
    
    Carta carta1 = {"São Paulo", "SP", "1234", 12396372, 1521.1f, 763800000000.0f, 100};
    Carta carta2 = {"Rio de Janeiro", "RJ", "5678", 6718903, 1200.0f, 350000000000.0f, 50};

    
    calcular_atributos_derivados(&carta1);
    calcular_atributos_derivados(&carta2);

    int escolha1, escolha2;
    
    
    printf("\n========================================\n");
    printf("         SUPER TRUNFO DE CIDADES        \n");
    printf("========================================\n");
    printf("Carta 1: %s\n", carta1.nome);
    printf("Carta 2: %s\n", carta2.nome);
    
    printf("\n--- Escolha do Primeiro Atributo ---\n");
    escolha1 = ler_escolha_atributo(0); 
    
    
    printf("\n--- Escolha do Segundo Atributo ---\n");
    escolha2 = ler_escolha_atributo(escolha1); 

    
    float valor1_c1 = obter_valor_atributo(&carta1, escolha1);
    float valor2_c1 = obter_valor_atributo(&carta1, escolha2);
    float valor1_c2 = obter_valor_atributo(&carta2, escolha1);
    float valor2_c2 = obter_valor_atributo(&carta2, escolha2);
    
    const char *nome1 = obter_nome_atributo(escolha1);
    const char *nome2 = obter_nome_atributo(escolha2);

    
    
    
    printf("\n--- Comparação Individual ---\n");
    exibir_comparacao_atributo(&carta1, &carta2, escolha1);
    exibir_comparacao_atributo(&carta1, &carta2, escolha2);
    
    
    float soma_c1 = valor1_c1 + valor2_c1;
    float soma_c2 = valor1_c2 + valor2_c2;

    
    printf("\n========================================\n");
    printf("           RESULTADO DA RODADA          \n");
    printf("========================================\n");
    printf("Cidades: %s (Carta 1) vs %s (Carta 2)\n", carta1.nome, carta2.nome);
    printf("Atributos Escolhidos: %s e %s\n", nome1, nome2);
    
    printf("\nValores de %s:\n", nome1);
    printf("  %s: %.2f\n", carta1.nome, valor1_c1);
    printf("  %s: %.2f\n", carta2.nome, valor1_c2);
    
    printf("\nValores de %s:\n", nome2);
    printf("  %s: %.2f\n", carta1.nome, valor2_c1);
    printf("  %s: %.2f\n", carta2.nome, valor2_c2);
    
    printf("\nSoma dos Atributos:\n");
    printf("  %s (Carta 1): %.2f\n", carta1.nome, soma_c1);
    printf("  %s (Carta 2): %.2f\n", carta2.nome, soma_c2);

    
    printf("\n--- VENCEDOR DA RODADA ---\n");
    
    int vencedor_soma = comparar_atributo(soma_c1, soma_c2, 0); 
    
    switch (vencedor_soma) {
        case 1:
            printf("Vencedor: %s (Carta 1) com a maior soma!\n", carta1.nome);
            break;
        case 2:
            printf("Vencedor: %s (Carta 2) com a maior soma!\n", carta2.nome);
            break;
        default:
            printf("Empate! A soma dos atributos é igual.\n");
            break;
    }
    printf("========================================\n");

    return 0;
}
