#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;



// Para bellman ford un grafo va ser un vector de vertices
struct Eje {
    int origen, destino, peso;
};


void relajar(vector<int> &distancias, Eje grafo) {
    if (distancias[grafo.origen] + grafo.peso < distancias[grafo.destino]) {
        distancias[grafo.destino] = distancias[grafo.origen] + grafo.peso;
    }
}

// A este bellman ford lo tiene que usar una funcion que a partir del grafo de entrada
// otro grafo que tenga un vertice que tenga grado de salida n (ese tiene que va a ser el origen)
// y otro grado de entrada n . Asi se asegura que se pueden encontrar ciclos negativos del grafo .
bool bellmanFord(int origen, vector<Eje> &grafo, int n, int m) {
    int i, j;
    vector<int> distancias;
    for (i = 0; i < n; ++i) {
        distancias.push_back(INT_MAX); // Esto no tengo idea de si hacerlo asi , una distancia invalida
    }
    distancias[origen] = 0;
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < m; ++j) {
            relajar(distancias, grafo[j]);
        }
    }
    for (j = 0; j < m; ++j) {
        if (distancias[grafo[j].origen] + grafo[j].peso < distancias[grafo[j].destino]) return false;
    }

    return true;
}

bool bellmanFordMod(vector<Eje> &grafo, int n, int m, int c) {

//    Agrego un vertice s t que se conectan a todos los nodos

    vector<Eje> grafo_auxiliar;
    for (int j = 0; j < m; ++j) {
        Eje v = {grafo[j].origen, grafo[j].destino, grafo[j].peso - c};
        grafo_auxiliar.push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        Eje s = {n, i, 1};
        Eje t = {i, n + 1, 1};
        grafo_auxiliar.push_back(s);
        grafo_auxiliar.push_back(t);
    }

    return bellmanFord(n, grafo, n + 2, m + n);
}


int minimo(vector<Eje> &vector, int m) {
    int min = INT_MAX;
    for (int i = 0; i < m; ++i) {
        if (vector[i].peso < min) { min = vector[i].peso; }
    }
    return min;
}

int maximo(vector<Eje> &vector, int m) {
    int max = -1;
    for (int i = 0; i < m; ++i) {
        if (vector[i].peso > max) { max = vector[i].peso; }
    }
    return max;
}

int maxima_reduccion(vector<Eje> &grafo, int n, int m) {
    int sup = maximo(grafo, m);
    int inf = minimo(grafo, m);
    int c = sup;

    while (inf < sup) {
        c = ((sup - inf) / 2) + inf;
        if (bellmanFordMod(grafo, n, m, c)) {
            inf = c;
        } else {
            sup = c;
        }
    }
    return c;

}

int main() {
    vector<Eje> provincia;
    Eje ruta_0 = {0, 1, 2};
    Eje ruta_1 = {1, 2, 1};
    Eje ruta_2 = {2, 0, 1};
    provincia.push_back(ruta_0);
    provincia.push_back(ruta_1);
    provincia.push_back(ruta_2);
    int res = maxima_reduccion(provincia, 3, 3);

    cout << res << '\n';
}