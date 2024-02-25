#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// Função para abrir um arquivo com o nome e modo especificados
FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}

// Função para carregar um vetor de strings com nomes de cidades a partir de um arquivo
void carregar_vetor(FILE *arquivo, char cidades[][30]) {
    int i;
   
    // Ler a primeira linha sem armazenar nas cidades
    fscanf(arquivo, "%*[^\n]"); // Ignora a linha
   
    // Agora, carregar as cidades a partir da segunda linha
    for (i = 0; i < 30; i++) {
        fscanf(arquivo, " %30[^\n]s", cidades[i]);
        //printf("%s",cidades[i]);
    }
}

// Função para ler uma matriz de floats a partir de um arquivo
void ler_matriz(FILE *arquivo, float mat[][30]) {
    int i, j;
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            if (fscanf(arquivo, "%f;", &mat[i][j]) != 1) {
                printf("Erro!");
            }
        }
    }
}

// Função para encontrar a cidade com o maior número de vizinhos
void maior_vizinho(float distancia[][30], char cidades[][30])
{
    int i, j, vizinho = 0 ,maior = 0, cidade=0;

    for (i=0; i<30; i++)
    {
        for (j=0; j<30; j++)
        {
            if (distancia[i][j] != 0)
            {
                vizinho++;
            }
        }
   
        if (vizinho > maior)
        {
            maior = vizinho;
            cidade = i;
        }
        vizinho = 0;
    }
    printf("Cidade com o maior número de vizinhos: %s, quantidade de vizinhos: %d.",cidades[cidade],maior);
}

// Função para encontrar a cidade com o menor número de vizinhos
void menor_vizinho(float distancia[][30], char cidades[][30])
{
    int i, j, vizinho = 0 ,menor = 30, cidade=0;


    for (i=0; i<30; i++)
    {
        for (j=0; j<30; j++)
        {
            if (distancia[i][j] != 0)
            {
                vizinho++;
            }
        }
   
        if (vizinho < menor)
        {
            menor = vizinho;
            cidade = i;
        }
        vizinho = 0;
    }
    printf("Cidade com o menor número de vizinhos: %s, quantidade de vizinhos: %d.",cidades[cidade],menor);
}

// Função para encontrar a cidade com o vizinho mais distante
void vizinho_mais_distante (float distancia[][30], char cidades[][30])
{
    int i, j, cidade,vizinho;
    float dist= 00.00;
    for (i=0;i<30;i++)
    {
        for (j=0;j<30;j++)
        {
            if (distancia[i][j] != 0) {
                if (distancia[i][j] > dist)
                {
                    dist = distancia[i][j];
                    cidade = i;
                    vizinho = j;
                }
            }
        }
    }
    printf("Cidade com vizinho mais distante: %s, vizinho:%s, distância: %.2f.", cidades[cidade], cidades[vizinho], dist);
}

// Função para encontrar a cidade com o vizinho mais próximo
void vizinho_mais_proximo(float distancia[][30], char cidades[][30])
{
    int i,j,cidade,vizinho;
    float dist = distancia[0][1];

    for (i=0; i<30;i++)
    {
        for (j=0; j<30;j++)
        {
            if (distancia[i][j] != 0) {
                if (distancia[i][j] < dist ) {
                    dist = distancia[i][j];
                    cidade=i;
                    vizinho = j;
                }
            }
        }
    }
    printf("cidade com vizinho mais proximo:%s, vizinho:%s, distância:%.2f.", cidades[cidade], cidades[vizinho], dist);
}

// Função para calcular a distância entre duas cidades especificadas pelo usuário
void distancia_entre_cidades (float distancia[][30], char cidades[][30])
{
    int i,cidade1,cidade2;

    for (i = 0; i < 30; i++) {
        printf("%s\n",cidades[i]);
    }

    do {
        printf("Digite o numero da  1° cidade:");
        scanf("%d", &cidade1);
    } while (cidade1 < 0 || cidade1 > 29) ;

    do
    {
        printf("Digite o numero da 2° cidade:");
        scanf("%d", &cidade2);
    } while (cidade2 < 0 || cidade2 > 29);

    if (distancia[cidade1][cidade2] > 0)
    {
        printf("A distância entre a cidade %s e a cidade %s é: %.2f.", cidades[cidade1],cidades[cidade2], distancia[cidade1][cidade2]);
    }

    if (distancia[cidade1][cidade2] == 0 )
    {
        printf("Não são vizinhas");
    }

}

int menu ()
    {
        // Função que exibe um menu de opções e retorna a escolha do usuário
        int op;
        printf("\nEntrada de Dados\n");
        printf("1 - Qual cidade possui o maior número de vizinhos? \n");
        printf("2 - Qual cidade possui o menor número de vizinhos? \n");
        printf("3 - Qual cidade possui o vizinho mais distante? \n");
        printf("4 - Qual cidade possui o vizinho mais próximo? \n");
        printf("5 - Digite o índices de duas cidades pertencentes a matriz de adjacência, qual a distância entre elas?\n");
        printf("0 - Sair\n");

        //validação da escolha do numero que o usuário escolher
        do
        {
            printf("Escolha sua opção: ");
            scanf(" %d", & op);
        } while (op < 0 || op > 5);


        return op;
    }

int main ()
{
    //definção das variáveis
    SetConsoleOutputCP(65001);
    int op;
    float distancia[30][30];
    char cidades[30][30];
    FILE * arquivo;

    // Abre o arquivo de entrada
    arquivo = abrirArquivo("entrada_30_cidades.txt", "r");

    // Carrega o vetor de cidades e a matriz de distâncias do arquivo
    carregar_vetor(arquivo, cidades);
    ler_matriz(arquivo, distancia);

    do {
        op = menu();
        switch (op) {
            case 0:
                // Encerra o programa
                fclose(arquivo);
                break;
            case 1:
                //1. Qual cidade possui o maior número de vizinhos? Informar cidade e quantidade de vizinhos.
                maior_vizinho(distancia,cidades);
                break;
            case 2:
                //2. Qual cidade possui o menor número de vizinhos? Informar cidade e quantidade de vizinhos.
                menor_vizinho(distancia,cidades);
                break;
            case 3:
                //3. Qual cidade possui o vizinho mais distante? Informar cidade, vizinho e distancia.
                vizinho_mais_distante(distancia,cidades);
                break;
            case 4:
                //4. Qual cidade possui o vizinho mais próximo? Informar cidade, vizinho e distância.
                vizinho_mais_proximo(distancia,cidades);
                break;
            case 5:
                //5. Dado os nomes de duas cidades pertencentes a matriz de adjacência, qual a distância entre elas?
                distancia_entre_cidades(distancia,cidades);
                break;

            default:
                printf("\nOpção inválida!\n");
        }
    } while (op != 0);

    return 0;
}
