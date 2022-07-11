#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

using namespace std;

int ComparaString(string s1, string s2, string ordemLex);
void InsertSort(string palavras[], int esq, int dir, string Ordem); // Função de ordenação por inserção
void quickSort(string palavras[], int left, int right, string ordem, int Particao, int Pivo);
void quickSortMain(string palavras[], int count, string ordem, int Particao, int Pivo);
