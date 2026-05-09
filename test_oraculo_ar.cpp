#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "algoritmos_ar.h"

using namespace std;

void test_oraculo(int iteraciones) {
    srand(time(NULL));
    int aciertos = 0;

    for (int i = 0; i < iteraciones; ++i) {
        int nw = rand() % 20 + 5;
        int nt = rand() % 20 + 5;
        
        vector<vector<int>> matriz(nw, vector<int>(nt));
        for (int w = 0; w < nw; ++w) {
            for (int t = 0; t < nt; ++t) {
                // 30% de probabilidad de no saber hacer la tarea (0)
                matriz[w][t] = (rand() % 10 < 3) ? 0 : rand() % 100 + 1;
            }
        }
        
        vector<int> cap(nw);
        for (int w = 0; w < nw; ++w) {
            cap[w] = rand() % 5 + 1;
        }

        auto res_global = voraz_global(nw, nt, matriz, cap);
        auto res_recursivo = voraz_recursivo(nw, nt, matriz, cap);

        // Ambas implementaciones globales deben ser estrictamente idénticas
        if (res_global == res_recursivo) {
            aciertos++;
        } else {
            cout << "Discrepancia detectada en la iteracion " << i << endl;
        }
    }
    cout << "Test oraculo finalizado: " << aciertos << "/" << iteraciones << " aciertos." << endl;
}

int main() {
    cout << "Ejecutando oraculo (Voraz Iterativo vs Voraz Recursivo)..." << endl;
    test_oraculo(100);
    return 0;
}