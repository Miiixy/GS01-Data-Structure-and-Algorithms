#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAX_HISTORICO 50

float temperatura = 0;
int energia = 0;
int comunicacao = 0;

float historicoTemperatura[MAX_HISTORICO];
int historicoEnergia[MAX_HISTORICO];
int historicoComunicacao[MAX_HISTORICO];
int totalLeituras = 0;

void inserirDados();
void visualizarStatus();
void analisarMissao();
void simularSensores();
void historicoLeituras();
void barraCarregamento();
void salvarNoHistorico();

int main()
{
    system("cls");
    system("color 3");

    srand(time(NULL));

    printf("Iniciando Sistema");
    barraCarregamento();
    system("cls");

    int opcao;

    do
    {

        printf("===================================\n");
        printf(" SISTEMA DE MONITORAMENTO ESPACIAL \n");
        printf("===================================\n");
        printf("1 - Inserir dados\n");
        printf("2 - Visualizar status\n");
        printf("3 - Executar analise\n");
        printf("4 - Simular sensores\n");
        printf("5 - Historico de leituras\n");
        printf("6 - Encerrar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        system("cls");

        switch (opcao)
        {
        case 1:
            inserirDados();

            Sleep(2200);
            break;

        case 2:

            if (totalLeituras == 0)
            {
                printf("Nenhum dado cadastrado.\n");
            }
            else
            {
                visualizarStatus();
            }

            printf("\nPressione ENTER para voltar ao menu...");
            getchar();
            getchar();
            break;

        case 3:

            if (totalLeituras == 0)
            {
                printf("Nenhum dado foi cadastrado ainda!\n");
                printf("Utilize a opcao 1 para inserir os dados.\n");
            }
            else
            {
                analisarMissao();
            }

            printf("\nPressione ENTER para voltar ao menu...");
            getchar();
            getchar();
            break;

        case 4:
            simularSensores();

            printf("\nPressione ENTER para voltar ao menu...");
            getchar();
            getchar();
            break;
        case 5:
            historicoLeituras();

            printf("\nPressione ENTER para voltar ao menu...");
            getchar();
            getchar();
            break;
        case 6:
            printf("Encerrando sistema!\n");

            barraCarregamento();
            break;

        default:
            printf("Opcao invalida!\n");
            Sleep(1500);
        }

        system("cls");

    } while (opcao != 6);

    printf("\nSistema encerrado com sucesso!\n");

    return 0;
}

void inserirDados()
{
    printf("==================================\n");
    printf("        CADASTRO DE DADOS         \n");
    printf("==================================\n");

    printf("Temperatura da nave: ");
    scanf("%f", &temperatura);

    do
    {

        printf("Nivel de energia (0 a 100): ");
        scanf("%d", &energia);

    } while (energia < 0 || energia > 100);

    do
    {

        printf("Status da comunicacao (1 = Operacional | 0 = Inoperante): ");
        scanf("%d", &comunicacao);

    } while (comunicacao != 0 && comunicacao != 1);

    salvarNoHistorico();

    printf("\nDados cadastrados com sucesso!\n");
}

void visualizarStatus()
{
    printf("==================================\n");
    printf("         STATUS DA MISSAO         \n");
    printf("==================================\n");
    printf("\n=== STATUS DA MISSAO ===\n");

    printf("Temperatura: %.1f C\n", temperatura);
    printf("Energia: %d%%\n", energia);

    if (comunicacao == 1)
    {
        printf("Comunicacao: Operacional\n");
    }
    else
    {
        printf("Comunicacao: Inoperante\n");
    }
}

void analisarMissao()
{
    printf("==================================\n");
    printf("       ANALISE DA MISSAO          \n");
    printf("==================================\n");

    int alertas = 0;

    if (temperatura > 80.0)
    {
        printf("[ALERTA] Temperatura critica: %.1f C (acima de 80 C)\n", temperatura);
        alertas++;
    }
    else if (temperatura < -50.0)
    {
        printf("[ALERTA] Temperatura critica: %.1f C (abaixo de -50 C)\n", temperatura);
        alertas++;
    }
    else if (temperatura > 60.0)
    {
        printf("[AVISO] Temperatura elevada: %.1f C\n", temperatura);
        alertas++;
    }
    else
    {
        printf("[OK] Temperatura dentro do normal: %.1f C\n", temperatura);
    }

    if (energia <= 10)
    {
        printf("[ALERTA] Energia critica: %d%% - Risco de falha total!\n", energia);
        alertas++;
    }
    else if (energia <= 25)
    {
        printf("[AVISO] Energia baixa: %d%% - Recarregar em breve.\n", energia);
        alertas++;
    }
    else if (energia <= 50)
    {
        printf("[AVISO] Energia moderada: %d%%\n", energia);
    }
    else
    {
        printf("[OK] Nivel de energia adequado: %d%%\n", energia);
    }

    if (comunicacao == 0)
    {
        printf("[ALERTA] Comunicacao inoperante - Contato com base perdido!\n");
        alertas++;
    }
    else
    {
        printf("[OK] Comunicacao operacional.\n");
    }

    printf("----------------------------------\n");

    if (alertas == 0)
    {
        printf("Situacao geral: MISSAO ESTAVEL\n");
    }
    else if (alertas == 1)
    {
        printf("Situacao geral: ATENCAO NECESSARIA (%d alerta)\n", alertas);
    }
    else
    {
        printf("Situacao geral: RISCO ELEVADO (%d alertas)\n", alertas);
    }
}

void salvarNoHistorico()
{
    if (totalLeituras < MAX_HISTORICO)
    {
        historicoTemperatura[totalLeituras] = temperatura;
        historicoEnergia[totalLeituras] = energia;
        historicoComunicacao[totalLeituras] = comunicacao;
        totalLeituras++;
    }
    else
    {
        printf("[AVISO] Limite do historico atingido. Leitura mais antiga removida.\n");

        for (int i = 0; i < MAX_HISTORICO - 1; i++)
        {
            historicoTemperatura[i] = historicoTemperatura[i + 1];
            historicoEnergia[i] = historicoEnergia[i + 1];
            historicoComunicacao[i] = historicoComunicacao[i + 1];
        }

        historicoTemperatura[MAX_HISTORICO - 1] = temperatura;
        historicoEnergia[MAX_HISTORICO - 1] = energia;
        historicoComunicacao[MAX_HISTORICO - 1] = comunicacao;
    }
}

void simularSensores()
{
    printf("==================================\n");
    printf("      SIMULACAO DE SENSORES       \n");
    printf("==================================\n");
    printf("Iniciando simulacao continua...\n");
    printf("Pressione Q para interromper a simulacao.\n\n");

    Sleep(1500);

    for (int rodada = 1; rodada <= 10; rodada++)
    {
        if (kbhit())
        {
            char tecla = getch();

            if (tecla == 'q' || tecla == 'Q')
            {
                printf("\nSimulacao interrompida pelo usuario.\n");
                break;
            }
        }

        temperatura = (float)((rand() % 1600) - 600) / 10.0;
        energia = rand() % 101;
        comunicacao = rand() % 2;

        salvarNoHistorico();

        system("cls");

        printf("==================================\n");
        printf("      SIMULACAO DE SENSORES       \n");
        printf("==================================\n");
        printf("Leitura %d de 10\n\n", rodada);

        printf("Temperatura: %.1f C\n", temperatura);
        printf("Energia: %d%%\n", energia);

        if (comunicacao == 1)
        {
            printf("Comunicacao: Operacional\n");
        }
        else
        {
            printf("Comunicacao: Inoperante\n");
        }

        printf("----------------------------------\n");

        if (temperatura > 80.0 || temperatura < -50.0)
        {
            printf("[ALERTA] Temperatura fora dos limites!\n");
        }

        if (energia <= 10)
        {
            printf("[ALERTA] Energia critica!\n");
        }

        if (comunicacao == 0)
        {
            printf("[ALERTA] Comunicacao inoperante!\n");
        }

        printf("\nAtualizando");
        barraCarregamento();
    }

    printf("\nSimulacao encerrada. %d leituras registradas no historico.\n", totalLeituras);
}

void historicoLeituras()
{
    printf("==================================\n");
    printf("       HISTORICO DE LEITURAS      \n");
    printf("==================================\n");

    if (totalLeituras == 0)
    {
        printf("Nenhuma leitura registrada ainda.\n");
        printf("Utilize a opcao 1 ou 4 para gerar leituras.\n");
        return;
    }

    printf("Total de leituras: %d\n\n", totalLeituras);
    printf(" Num | Temperatura |  Energia | Comunicacao\n");
    printf("-----|-------------|----------|--------------\n");

    for (int i = 0; i < totalLeituras; i++)
    {
        printf("  %2d | %8.1f C | %6d%% | ", i + 1, historicoTemperatura[i], historicoEnergia[i]);

        if (historicoComunicacao[i] == 1)
        {
            printf("Operacional\n");
        }
        else
        {
            printf("Inoperante\n");
        }
    }

    printf("----------------------------------\n");

    float somaTemp = 0;
    int somaEnergia = 0;

    for (int i = 0; i < totalLeituras; i++)
    {
        somaTemp += historicoTemperatura[i];
        somaEnergia += historicoEnergia[i];
    }

    printf("Media de temperatura: %.1f C\n", somaTemp / totalLeituras);
    printf("Media de energia: %d%%\n", somaEnergia / totalLeituras);
}

void barraCarregamento()
{
    printf("\n");

    for (int i = 0; i <= 20; i++)
    {
        printf("\r[");

        for (int j = 0; j < i; j++)
            printf("#");

        for (int j = i; j < 20; j++)
            printf(" ");

        printf("] %d%%", i * 5);

        Sleep(100);
    }

    printf("\n");
}
