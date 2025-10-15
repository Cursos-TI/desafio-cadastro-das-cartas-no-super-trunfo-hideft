#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar os dados da carta
typedef struct {
    char estado[3]; // Ex: SP, RJ, MG
    char codigo[5]; // Ex: 1234
    char nome[50];
    unsigned long int populacao; // unsigned long int para acomodar números maiores
    float area;
    float pib;
    int pontos_turisticos;
    
    // Atributos calculados
    float densidade_populacional; // População / Área
    float pib_per_capita;         // PIB / População
    float super_poder;            // Soma de atributos numéricos
} Carta;

// Função para ler os dados de uma carta
void ler_carta(Carta *carta, int numero) {
    printf("\n--- Entrada de Dados para a Carta %d ---\n", numero);
    
    // Leitura de strings (nome, estado, codigo)
    printf("Estado (2 letras, ex: SP): ");
    scanf("%2s", carta->estado);
    printf("Código (até 4 dígitos, ex: 1234): ");
    scanf("%4s", carta->codigo);
    printf("Nome da Cidade (até 49 caracteres): ");
    // Limpa o buffer antes de ler a string com espaços
    while (getchar() != '\n'); 
    fgets(carta->nome, 50, stdin);
    // Remove o newline adicionado pelo fgets
    carta->nome[strcspn(carta->nome, "\n")] = 0;

    // Leitura de valores numéricos
    printf("População (unsigned long int): ");
    // Usar %%lu para unsigned long int
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

// Função para calcular os atributos derivados (Densidade Populacional e PIB per Capita)
void calcular_atributos_derivados(Carta *carta) {
    // Densidade Populacional = População / Área
    if (carta->area > 0) {
        // Conversão explícita para float para garantir o cálculo correto
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0.0f; // Evita divisão por zero
    }

    // PIB per Capita = PIB / População
    if (carta->populacao > 0) {
        // Conversão explícita para float para garantir o cálculo correto
        carta->pib_per_capita = carta->pib / (float)carta->populacao;
    } else {
        carta->pib_per_capita = 0.0f; // Evita divisão por zero
    }
}

// Função para calcular o Super Poder
void calcular_super_poder(Carta *carta) {
    // Super Poder = População + Área + PIB + Pontos Turísticos + PIB per Capita + (1 / Densidade Populacional)
    // Atenção à conversão de tipos para float na soma
    
    float inverso_densidade = 0.0f;
    if (carta->densidade_populacional > 0) {
        inverso_densidade = 1.0f / carta->densidade_populacional;
    }
    
    carta->super_poder = 
        (float)carta->populacao + // unsigned long int para float
        carta->area + 
        carta->pib + 
        (float)carta->pontos_turisticos + // int para float
        carta->pib_per_capita + 
        inverso_densidade;
}

// Função para exibir os dados de uma carta
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

// Função para comparar um atributo e imprimir o resultado
// Retorna 1 se carta1 vence, 0 se carta2 vence
int comparar_atributo(float valor1, float valor2, const char *nome_atributo, int menor_vence) {
    int carta1_vence;
    
    if (menor_vence) {
        // Para Densidade Populacional: menor valor vence
        carta1_vence = (valor1 < valor2);
    } else {
        // Para os demais: maior valor vence
        carta1_vence = (valor1 > valor2);
    }
    
    printf("%s: Carta %d venceu (%d)\n", 
           nome_atributo, 
           carta1_vence ? 1 : 2, 
           carta1_vence);
           
    return carta1_vence;
}

// Função principal de comparação
void comparar_cartas(const Carta *carta1, const Carta *carta2) {
    printf("\n--- Comparação de Cartas ---\n");

    // População (maior vence)
    comparar_atributo((float)carta1->populacao, (float)carta2->populacao, "População", 0);
    
    // Área (maior vence)
    comparar_atributo(carta1->area, carta2->area, "Área", 0);
    
    // PIB (maior vence)
    comparar_atributo(carta1->pib, carta2->pib, "PIB", 0);
    
    // Pontos Turísticos (maior vence)
    comparar_atributo((float)carta1->pontos_turisticos, (float)carta2->pontos_turisticos, "Pontos Turísticos", 0);
    
    // Densidade Populacional (menor vence)
    comparar_atributo(carta1->densidade_populacional, carta2->densidade_populacional, "Densidade Populacional", 1);
    
    // PIB per Capita (maior vence)
    comparar_atributo(carta1->pib_per_capita, carta2->pib_per_capita, "PIB per Capita", 0);
    
    // Super Poder (maior vence)
    comparar_atributo(carta1->super_poder, carta2->super_poder, "Super Poder", 0);
}

int main() {
    Carta carta1, carta2;

    // 1. Leitura dos dados
    ler_carta(&carta1, 1);
    // Limpa o buffer após a leitura da última variável numérica da carta 1
    while (getchar() != '\n'); 
    
    ler_carta(&carta2, 2);
    // Limpa o buffer após a leitura da última variável numérica da carta 2
    while (getchar() != '\n'); 

    // 2. Cálculo dos atributos derivados
    calcular_atributos_derivados(&carta1);
    calcular_atributos_derivados(&carta2);
    
    // 3. Cálculo do Super Poder
    calcular_super_poder(&carta1);
    calcular_super_poder(&carta2);

    // 4. Exibição dos dados completos (opcional, mas útil para verificação)
    exibir_carta(&carta1, 1);
    exibir_carta(&carta2, 2);

    // 5. Comparação das Cartas
    comparar_cartas(&carta1, &carta2);

    return 0;
}
