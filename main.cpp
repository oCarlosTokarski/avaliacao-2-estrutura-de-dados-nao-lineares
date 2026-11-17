#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <iomanip>
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

    g.adj.resize(g.paises.size());
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


void mostrarGrafo(Grafo &g) {
    cout << "---------------- Grafo Original ------------------\n";
    cout << "\nBrasil -> Portugal";
    cout << "\nDistancia: " << brasilPortugal.distancia << " km";
    cout << "\nTempo: " << brasilPortugal.tempo << " horas";
    cout << "\nPreco: R$ " << brasilPortugal.preco;
    cout << "\nTransporte: " << brasilPortugal.transporte << "\n";


    for(int i  = 0; i < g.paises.size(); i++) {
        cout << "\n -----------------------------------\n";

        cout << g.paises[i].nome;
        cout << "\nPonto Turistico: " << g.paises[i].pontoTuristico;

        cout << "\nConexoes:\n";

         for (Aresta a : g.adj[i]) { //Trecho feito por ia

            cout << " -> " << g.paises[a.destino].nome;

            cout << " | " << a.distancia << " km";

            cout << " | " << a.tempo << " h";

            cout << " | R$ " << a.preco;

            cout << " | " << a.transporte << endl;
         }

    }
};

double peso(Aresta a, int criterio){
    if (criterio == 0) return a.preco;
    if (criterio == 1) return a.distancia;
    else return a.tempo;
};

//Matrizes feita com o auxilio de ia (não consegui achar um exemplo do professor com codigo de matrizes de custo)

void mostrarMatriz(Grafo &g, int criterio, const char* titulo) {
    int n = g.paises.size();
    double INF = numeric_limits<double>::infinity();

    vector<vector<double>> matriz(n, vector<double>(n, INF));

    for (int i = 0; i < n; i++) {
        matriz[i][i] = 0;

        for (Aresta a : g.adj[i])
            matriz[i][a.destino] = peso(a, criterio);
    }

    cout << "\n-------- MATRIZ DE " << titulo << " -------\n";

    cout << setw(12) << " ";
    for (Pais p : g.paises)
        cout << setw(12) << p.nome;

    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << setw(12) << g.paises[i].nome;

        for (int j = 0; j < n; j++) {
            if (matriz[i][j] == INF)
                cout << setw(12) << "-";
            else
                cout << setw(12) << matriz[i][j];
        }
        cout << "\n";
    }
}

void mostrarMatrizes(Grafo &g) {
    mostrarMatriz(g, 0, "CUSTOS (R$)");
    mostrarMatriz(g, 1, "DISTANCIAS (KM)");
    mostrarMatriz(g, 2, "TEMPOS (HORAS)");
};


void dijkstra(Grafo &g, int origem, int destino, int criterio){ //Feito com auxilio do material do professor e de ia
    int n = g.paises.size();
    double INF = numeric_limits<double>::infinity();

    vector<double> dist(n, INF);
    vector<int> pai(n, -1);


    priority_queue<pair<double, int>,
        vector<pair<double, int>>,
        greater<pair<double, int>>> fila;

    dist[origem] = 0;
    fila.push({0, origem});

    while (!fila.empty()) {
        int atual = fila.top().second;
        double distanciaAtual = fila.top().first;
        fila.pop();

        if (distanciaAtual > dist[atual]) continue;

        for (Aresta a : g.adj[atual]) {
            double novaDist = dist[atual] + peso(a, criterio);

            if (novaDist < dist[a.destino]) {
                dist[a.destino] = novaDist;
                pai[a.destino] = atual;
                fila.push({novaDist, a.destino});
            }
        }
    }

    if (dist[destino] == INF) {
        cout << "\nDestino inacessivel!\n";
        return;
    }
    
    vector<int> caminho;

    for (int v = destino; v != -1; v = pai[v])
        caminho.push_back(v);

    reverse(caminho.begin(), caminho.end());

    double custo = brasilPortugal.preco;
    double distancia = brasilPortugal.distancia;
    double tempo = brasilPortugal.tempo;

    cout << "\n Menor caminho por ";

    if (criterio == 0) cout << "CUSTO";
    else if (criterio == 1) cout << "DISTANCIA";
    else cout << "TEMPO";

    cout << ":\nBrasil -> ";

    for (int i = 0; i < caminho.size(); i++) {
        cout << g.paises[caminho[i]].nome;

        if (i < caminho.size() - 1) {
            int prox = caminho[i + 1];

            for (Aresta a : g.adj[caminho[i]]) {
                if (a.destino == prox) {
                    custo += a.preco;
                    distancia += a.distancia;
                    tempo += a.tempo;
                    break;
                }
            }

            cout << " -> ";
        }
    }

    if (criterio == 0) {
        cout << "\nCusto total: R$ " << custo;
    } else if (criterio == 1) {
        cout << "\nDistancia total: " << distancia << " km";
    }else if (criterio == 2){
        cout << "\nTempo total: " << tempo << " horas\n";
    }else{
        cout << "Criterio invalido" << endl;
    };
};

void mostrarCaminhos(Grafo &g) {
    cout << "----------- Caminho minimo -------------" << endl;

    dijkstra(g, 0, 7, 0);
    dijkstra(g, 0, 7, 1);
    dijkstra(g, 0, 7, 2);

};


int main(int argc, char const *argv[])
{

    Grafo europa;

    cadastrarPaises(europa);
    cadastrarConexoes(europa);
    dijkstra(europa, 0, 4, 0);
    dijkstra(europa, 0, 4, 1);
    dijkstra(europa, 0, 4, 2);
    mostrarCaminhos(europa);
    //mostrarCaminhos(europa);//
    
    return 0;
}
