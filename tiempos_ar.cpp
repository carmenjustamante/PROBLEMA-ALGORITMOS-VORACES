#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include "algoritmos_ar.h"

using namespace std;
using namespace std::chrono;

void medir_tiempos_estudio() {
    ofstream archivo("datos_tiempos.csv");
    // Cabecera clara para las gráficas individuales y la comparativa
    archivo << "N,GlobIter_Peor,GlobIter_Mejor,GlobRec_Peor,GlobRec_Mejor,PorTarea_Peor,PorTarea_Mejor\n";

    // BUCLE CON ESPACIADO MULTIPLICATIVO (Requisito del profesor)
    for (int N = 100; N <= 3200; N *= 2) {
        vector<vector<int>> matriz_peor(N, vector<int>(N));
        vector<vector<int>> matriz_mejor(N, vector<int>(N));
        vector<int> cap(N, 1); // Capacidad estándar

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int val = rand() % 100 + 1;
                matriz_peor[i][j] = val; // Peor caso: matriz densa
                matriz_mejor[i][j] = (rand() % 100 < 2) ? val : 0; // Mejor caso: muy dispersa (2%)
            }
        }

        // --- GLOBAL ITERATIVO ---
        auto s = high_resolution_clock::now();
        voraz_global(N, N, matriz_peor, cap);
        auto t_gi_p = duration_cast<microseconds>(high_resolution_clock::now() - s).count();

        s = high_resolution_clock::now();
        voraz_global(N, N, matriz_mejor, cap);
        auto t_gi_m = duration_cast<microseconds>(high_resolution_clock::now() - s).count();

        // --- GLOBAL RECURSIVO ---
        s = high_resolution_clock::now();
        voraz_recursivo(N, N, matriz_peor, cap);
        auto t_gr_p = duration_cast<microseconds>(high_resolution_clock::now() - s).count();

        s = high_resolution_clock::now();
        voraz_recursivo(N, N, matriz_mejor, cap);
        auto t_gr_m = duration_cast<microseconds>(high_resolution_clock::now() - s).count();

        // --- POR TAREA ---
        s = high_resolution_clock::now();
        voraz_por_tarea(N, N, matriz_peor, cap);
        auto t_pt_p = duration_cast<microseconds>(high_resolution_clock::now() - s).count();

        s = high_resolution_clock::now();
        voraz_por_tarea(N, N, matriz_mejor, cap);
        auto t_pt_m = duration_cast<microseconds>(high_resolution_clock::now() - s).count();

        archivo << N << "," << t_gi_p << "," << t_gi_m << "," << t_gr_p << "," 
                << t_gr_m << "," << t_pt_p << "," << t_pt_m << "\n";
        
        cout << "Procesado N=" << N << endl;
    }
    archivo.close();
}

int main() {
    srand(123);
    cout << "Generando datos de rendimiento..." << endl;
    medir_tiempos_estudio();
    cout << "Archivo datos_tiempos.csv generado." << endl;
    return 0;
}