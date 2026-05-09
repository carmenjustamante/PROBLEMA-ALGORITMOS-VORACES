#include <iostream>
#include <vector>
#include <cassert>
#include "algoritmos_ar.h"

using namespace std;

void run_test_1() {
    int nw = 5, nt = 5;
    vector<vector<int>> matriz = {
        {0, 2, 0, 0, 0},
        {0, 0, 0, 2, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1}
    };
    vector<int> cap = {1, 2, 2, 2, 1};

    auto res = voraz_global(nw, nt, matriz, cap);
    assert(res.first == 0); // No se pueden asignar todos los trabajos
    cout << "Test 1 superado (Beneficio = 0)." << endl;
}

void run_test_2() {
    int nw = 8, nt = 6;
    vector<vector<int>> matriz = {
        {4, 0, 0, 0, 0, 0},
        {4, 5, 0, 0, 0, 0},
        {0, 4, 0, 0, 0, 0},
        {2, 0, 0, 3, 2, 0},
        {0, 0, 0, 4, 2, 0},
        {5, 5, 2, 0, 2, 3},
        {0, 0, 2, 2, 2, 2},
        {0, 2, 0, 0, 2, 5}
    };
    vector<int> cap = {1, 1, 1, 1, 1, 1, 1, 1};

    auto res = voraz_global(nw, nt, matriz, cap);
    // El beneficio esperado aproximado según tu ejemplo es 23
    assert(res.first == 23); 
    cout << "Test 2 superado (Beneficio = 23)." << endl;
}

int main() {
    cout << "Iniciando tests unitarios estáticos..." << endl;
    run_test_1();
    run_test_2();
    cout << "Todos los tests unitarios superados con éxito." << endl;
    return 0;
}