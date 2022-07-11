#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

#include "funcoes.hpp"

using namespace std;

int main(int argc, char **argv)
{
    int c, pivo, TamParticao;
    string inputFileName, outputFileName;
    extern char *optarg;

    while ((c = getopt(argc, argv, "i:I:o:O:m:M:S:s:h")) != EOF) // Leitura dos parametros de execução
    {
        c = ::tolower(c);
        switch (c)
        {
        case 'i':
            inputFileName = optarg;
            break;
        case 'o':
            outputFileName = optarg;
            break;
        case 'm':
            pivo = atoi(optarg);
            break;
        case 's':
            TamParticao = atoi(optarg);
            break;
        };
    };

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    string ordemLex;
    string stringAux;
    string texto;
    string line;
    getline(inputFile, line);     // Consome a primeira linha do arquivo de entrada "#ORDEM"
    getline(inputFile, ordemLex); // Lê a nova ordem lexicografica

    int localInsere = 0;
    string ordemLexi[25];
    for (unsigned int j = 0; j <= ordemLex.size(); j++) // Armazena letras da ordem sem os espaços entre elas
    {
        if (ordemLex[j] == ' ')
        {
            if (stringAux != "")
            {
                ordemLexi[localInsere] = stringAux;
                stringAux = "";
                localInsere++;
            }
        }
        else
        {
            stringAux += ordemLex[j];
        }
    }
    ordemLexi[localInsere] = ordemLex[ordemLex.size() - 1];
    ordemLex = "-0123456789";

    for (int i = 0; i <= localInsere; i++) // armazena ordem em uma unica string junto com elementos pertinentes da tabela ASCII
    {
        ordemLex += ordemLexi[i];
    }

    localInsere = 0;
    getline(inputFile, line);                           // Consome #TEXTO do arquivo de entrada
    for (unsigned int i = 11; i < ordemLex.size(); i++) // Tranforma os caracteres da ordem em seu respectivo minusculo
    {
        ordemLex[i] = ::tolower(ordemLex[i]);
    }

    while (inputFile.peek() != EOF) // Lê texto do arquivo de entrada
    {
        getline(inputFile, stringAux);
        texto.append(" ");
        texto.append(stringAux);
    }

    for (unsigned int i = 0; i < texto.size(); i++) // Tranforma os caracteres do texto em seu respectivo minusculo
    {
        texto[i] = ::tolower(texto[i]);
    }

    string palavras[10000];

    stringAux = "";
    for (unsigned int j = 0; j < texto.size(); j++) // remove as pontuaçoes indevidas do texto, e armazena palavra por palavra em um array de strings
    {
        if (texto[j] == ' ' || texto[j] == ',' || texto[j] == '.' || texto[j] == '!' || texto[j] == '?' || texto[j] == ':' || texto[j] == ';' || texto[j] == '_')
        {
            if (stringAux != "")
            {
                palavras[localInsere] = stringAux;
                stringAux = "";
                localInsere++;
            }
        }
        else
        {
            stringAux += texto[j];
        }
    }
    if (stringAux != "")
    {
        palavras[localInsere] = stringAux;
        localInsere++;
    };

    quickSortMain(palavras, localInsere, ordemLex, TamParticao, pivo); // Ordena

    for (int i = 1; i < localInsere + 1; i++)
    {
        int j = 1; // Contador de ocorrencia
        while (palavras[i] == palavras[i + j])
        {
            j++;
        }
        i = i + j - 1;
        outputFile << palavras[i] << " " << j << endl;
    }
    outputFile << "#FIM" << endl;
    return 0;
}