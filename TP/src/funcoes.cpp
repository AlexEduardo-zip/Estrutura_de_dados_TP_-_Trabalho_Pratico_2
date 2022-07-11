#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
#include "funcoes.hpp"

using namespace std;

int ComparaString(string s1, string s2, string ordemLex)
{
    if (s1 == s2)
    {
        return 0; // Retorna 0, se as palavras sao iguais
    }
    int indiceS1 = 30, indiceS2 = 30;
    for (unsigned int i = 0; i < min(s1.size(), s2.size()); i++)
    {
        for (unsigned int j = 0; j < ordemLex.size(); j++)
        {
            if (s1[i] == ordemLex[j])
            {
                indiceS1 = j;
            }
            if (s2[i] == ordemLex[j])
            {
                indiceS2 = j;
            }
        }
        if (indiceS1 != indiceS2) // Para o laço quando possuem caracteres diferentes nas mesmas posiçoes
            break;
    }
    if (indiceS1 == indiceS2)
    {                              // Se nao for indentificado diferença nas palavras
        if (s1.size() < s2.size()) // Então alguma é menor que outra apesar de terem os mesmo caracteres iniciais

            return -1; // Retorna -1, se a primeira palavra vem antes
        else
            return 1; // Retorna 1, se a segunda palavra vem antes
    }
    else if (indiceS1 > indiceS2) // Retorna 1, se a segunda palavra vem antes
        return 1;
    else if (indiceS1 < indiceS2) // Retorna -1, se a primeira palavra vem antes
        return -1;
    return 0; // Nunca é chamado, mas evita Warning na compilação
};

void InsertSort(string palavras[], int esq, int dir, string Ordem) // Função de ordenação por inserção
{
    int i, j;
    string aux;
    for (i = esq; i <= dir; i++)
    {
        aux = palavras[i];
        j = i - 1;
        while ((j >= 0) && (ComparaString(aux, palavras[j], Ordem)) < 0)
        {
            palavras[j + 1] = palavras[j];
            j--;
        }
        palavras[j + 1] = aux;
    }
};

void quickSort(string palavras[], int left, int right, string ordem, int Particao, int Pivo) // Função de ordenação pelo QuickSort
{
    int i, j;
    string *x;
    string temp;

    i = left;
    j = right;
    InsertSort(palavras, left, (left + Pivo - 1), ordem);
    // if (Pivo == 3)
    //     x = &palavras[left + 1];
    // else
    x = &palavras[left + (Pivo / 2)]; // Pivo
    // cout << *x << endl;
    // cout << left + (Pivo / 2) << endl;
    // cout << palavras[left + 1] << " " << palavras[left + 2] << endl
    //      << endl;

    while (i <= j)
    {
        while ((ComparaString(palavras[i], *x, ordem) < 0) && (i < right))
        {
            i++;
        }
        while ((ComparaString(palavras[j], *x, ordem) > 0) && (j > left))
        {
            j--;
        }
        if (i <= j)
        {
            temp = palavras[i];
            palavras[i] = palavras[j];
            palavras[j] = temp;
            i++;
            j--;
        }
    };

    if (left < j)
    {
        int tam_particao = right + 1 - left;
        if (tam_particao < Particao)
            InsertSort(palavras, left, j + 1, ordem); // Chama InsertSort se a partição for menor que o parametro S
        else
            quickSort(palavras, left, j, ordem, Particao, Pivo);
    }
    if (i < right)
    {
        int tam_particao = right - i;
        if (tam_particao < Particao)
            InsertSort(palavras, i, right + 1, ordem);
        else
            quickSort(palavras, i, right, ordem, Particao, Pivo);
    }
};
void quickSortMain(string palavras[], int count, string ordem, int Particao, int Pivo) // Função de ordernação por quickSort
{
    if (Particao <= 0 || Particao == 1 || Particao == 2) // Ajustes de Robustez
        Particao = 4;
    if (Pivo == 2 || Pivo <= 0)
        Pivo = 1;
    if (Particao < Pivo)
        Particao = Pivo;
    if (Pivo > count)
        Pivo = count;
    quickSort(palavras, 0, count - 1, ordem, Particao, Pivo); // Chama o metodo quickSort com correção no parametro
};
