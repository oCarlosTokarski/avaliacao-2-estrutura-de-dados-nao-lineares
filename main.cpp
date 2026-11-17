#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pais
{
    const char* nome;
    const char* pontoTuristico;
};

struct Aresta {
    int destino;
    double distancia;
    double tempo;
    double preco;
    const char* transporte;
};

struct Conexao {
    int origem;
    int destino;
    double distancia;
    double tempo;
    double preco;
    const char* transporte;
};


struct Grafo {
    vector<Pais> paises;
    vector<vector<Aresta>> adj;
};

struct TrechoInicial {
    double distancia;
    double tempo;
    double preco;
    const char* transporte;
};


int main(int argc, char const *argv[])
{

    return 0;
}
