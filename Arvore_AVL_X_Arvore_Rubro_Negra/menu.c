#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "auxiliar.h"

// windows
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define COR_PADRAO 7
#define COR_CIANO 11
#define COR_AMARELO 14
#define COR_ROXO 13
#define COR_VERDE 10
static void definir_cor(WORD cor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}
static void limpar_tela()
{
    system("cls");
}
static void esconder_cursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}
// linux
#else
#include <termios.h>
#include <unistd.h>
#define COR_PADRAO "\x1B[0m"
#define COR_CIANO "\x1B[96m"
#define COR_AMARELO "\x1B[93m"
#define COR_ROXO "\x1B[95m"
#define COR_VERDE "\x1B[92m"
static void definir_cor(const char *cor)
{
    printf("%s", cor);
}
static void limpar_tela()
{
    system("clear");
}
static void esconder_cursor()
{
    printf("\e[?25l");
}
static void mostrar_cursor()
{
    printf("\e[?25h");
}
static int _getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#define SETA_CIMA 72
#define SETA_BAIXO 80
#define ENTER 13

static const char *opcoes_menu[] = {
    "Inserir em Arvore AVL (Dados Desordenados)",
    "Inserir em Arvore AVL (Dados Ordenados)",
    "Inserir em Arvore Rubro-Negra (Dados Desordenados)",
    "Inserir em Arvore Rubro-Negra (Dados Ordenados)",
    "Exibir Relatorio de Tempos",
    "Sair do Programa"};
static int total_opcoes = sizeof(opcoes_menu) / sizeof(opcoes_menu[0]);

static void desenhar_menu(int item_selecionado)
{
    limpar_tela();
    definir_cor(COR_CIANO);

#ifdef _WIN32
    printf("\n  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
    printf("  \xBA      Desempenho da Arvore AVL x Rubro Negra       \xBA\n");
    printf("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
#else
    printf("\n  ╔═════════════════════════════════════════════════════╗\n");
    printf("  ║      Desempenho da Arvore AVL x Rubro Negra         ║\n");
    printf("  ╚═════════════════════════════════════════════════════╝\n");
#endif

    definir_cor(COR_PADRAO);
    printf("\n");

    for (int i = 0; i < total_opcoes; i++)
    {
        if (i == item_selecionado)
        {
            definir_cor(COR_AMARELO);
            printf("  > %s\n", opcoes_menu[i]);
            definir_cor(COR_PADRAO);
        }
        else
        {
            printf("    %s\n", opcoes_menu[i]);
        }
    }
    printf("\n");
    definir_cor(COR_CIANO);
    printf("  Use as setas para navegar e enter para selecionar\n");
    definir_cor(COR_PADRAO);
}

static void executar_acao(int opcao)
{
    limpar_tela();
    definir_cor(COR_ROXO);
    printf("\nExecutando: %s\n\n", opcoes_menu[opcao]);
    definir_cor(COR_VERDE);

    switch (opcao)
    {
    case 0:
        alimenta_arvore(ARVORE_AVL, "massaDados.csv");
        break;
    case 1:
        alimenta_arvore(ARVORE_AVL, "funcionarios_ordenados.csv");
        break;
    case 2:
        alimenta_arvore(ARVORE_RUBRO_NEGRA, "massaDados.csv");
        break;
    case 3:
        alimenta_arvore(ARVORE_RUBRO_NEGRA, "funcionarios_ordenados.csv");
        break;
    case 4:
        exibeTempos();
        break;
    }

    definir_cor(COR_PADRAO);

    if (opcao != 5)
    {
        printf("\n\nPressione qualquer tecla para voltar ao menu...");
        _getch();
    }
}

void iniciar_menu(void)
{
    limpar_tela();
    int item_selecionado = 0;
    int tecla = 0;

    esconder_cursor();

    while (1)
    {
        desenhar_menu(item_selecionado);
        tecla = _getch();

#ifdef _WIN32
        if (tecla == 224)
        {
            tecla = _getch();
        }
#else
        if (tecla == 27)
        {
            _getch();
            switch (_getch())
            {
            case 'A':
                tecla = SETA_CIMA;
                break;
            case 'B':
                tecla = SETA_BAIXO;
                break;
            }
        }
#endif

        switch (tecla)
        {
        case SETA_CIMA:
            if (item_selecionado == 0)
            {
                item_selecionado = total_opcoes - 1;
            }
            else
            {
                item_selecionado--;
            }
            break;
        case SETA_BAIXO:
            if (item_selecionado == total_opcoes - 1)
            {
                item_selecionado = 0;
            }
            else
            {
                item_selecionado++;
            }
            break;
        case ENTER:
            if (item_selecionado == total_opcoes - 1)
            { // sair
                limpar_tela();
#ifndef _WIN32
                mostrar_cursor();
#endif
                printf("\nSaindo...\n\n");
                return;
            }
            else
            {
                executar_acao(item_selecionado);
            }
            break;
        }
    }
}
