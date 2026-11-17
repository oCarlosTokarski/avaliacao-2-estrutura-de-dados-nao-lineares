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

TrechoInicial brasilPortugal = {
    8274, 14.50, 2400, "Aviao"
};

//Cadastrando os paises

void cadastrarPaises(Grafo &g) {
    g.paises = {
        {"Portugal", "Torre de Belem"},
        {"Espanha", "Sagrada Familia"},
        {"Franca", "Torre Eiffel"},
        {"Alemanha", "Portao de Brandemburgo"},
        {"Dinamarca", "Nyhavn"},
        {"Polonia", "Castelo de Wawel"},
        {"Grecia", "Acropole"},
        {"Italia", "Coliseu"}
    };

    g.adj.resize(8);
};

void adicionarAresta(  //Trecho feito com auxilio de IA
    Grafo &g,
    int origem,
    int destino,
    double distancia,
    double tempo,
    double preco,
    const char* transporte
) {

    g.adj[origem].push_back({
        destino, distancia, tempo, preco, transporte
    });

    g.adj[destino].push_back({
        origem, distancia, tempo, preco, transporte
    });
};

void cadastrarConexoes(Grafo &g) { //Pedimos ajuda para o chat sobre o conceito dessa parte codigo foi feito a mao
    //Portugal
    adicionarAresta(g, 0, 1, 995, 1.75, 400, "Aviao");
    adicionarAresta(g, 0, 7, 1839, 3.20, 650, "Aviao");
    adicionarAresta(g, 0, 2, 1470, 2.80, 550, "Aviao");
    adicionarAresta(g, 0, 3, 1850, 3, 700, "Aviao");

    //Espanha
    adicionarAresta(g, 1, 2, 858, 1.75, 450, "Aviao");
    adicionarAresta(g, 1, 4, 1500, 2.5, 600, "Aviao");

    //França
    adicionarAresta(g, 2, 3, 856, 1.75, 500, "Avião");
    adicionarAresta(g, 2, 7, 846, 1.8, 350, "Aviao");

    //Alemanha
    adicionarAresta(g, 3, 4, 366, 1.10, 350, "Avião");
    adicionarAresta(g, 3, 5, 506, 1.20, 450, "Avião");
    adicionarAresta(g, 3, 7, 1100, 2, 550, "Aviao");

    //Dinamarca
    adicionarAresta(g, 4, 5, 779, 1.50, 450, "Avião");
    adicionarAresta(g, 4, 6, 2139, 3.50, 800, "Aviao");

    //Polonia
    adicionarAresta(g, 5, 6, 1390, 2.50, 850, "Aviao");

    //Grecia
    adicionarAresta(g, 6, 7, 1086, 2.00, 500, "Aviao");
};

int main(int argc, char const *argv[])
{

    return 0;
}
