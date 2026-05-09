#include "algoritmos_ar.h"
#include <algorithm>

// -------------------------------------------------------------------------
// ESTRATEGIA 1: VORAZ GLOBAL (ITERATIVO)
// -------------------------------------------------------------------------
pair<long long, vector<int>> voraz_global(int nw, int nt, const vector<vector<int>>& matriz, vector<int> cap) {
    vector<Candidato> C;
    
    // Paso 1: Generar el conjunto de candidatos (todas las celdas con beneficio > 0)
    for (int i = 0; i < nw; ++i) {
        for (int j = 0; j < nt; ++j) {
            if (matriz[i][j] > 0) {
                C.push_back({i, j, matriz[i][j]});
            }
        }
    }

    // Paso 2: Función de selección. Ordenamos por beneficio de mayor a menor.
    // Al haber definido el operador < con "mayor que", sort lo ordena descendente.
    sort(C.begin(), C.end());

    vector<int> sol(nt, -1);
    long long beneficioTotal = 0;
    int asignadas = 0;

    // Paso 3: Construcción de la solución
    for (size_t i = 0; i < C.size(); ++i) {
        const Candidato& c = C[i];
        // Factibilidad: ¿La tarea está libre y el trabajador tiene capacidad?
        if (sol[c.tarea] == -1 && cap[c.trabajador] > 0) {
            sol[c.tarea] = c.trabajador;
            cap[c.trabajador]--;
            beneficioTotal += c.beneficio;
            asignadas++;
            if (asignadas == nt) break; // Objetivo alcanzado
        }
    }

    // Según el enunciado: si no se asignan todas las tareas, el beneficio es 0
    if (asignadas < nt) beneficioTotal = 0;
    return {beneficioTotal, sol};
}

// -------------------------------------------------------------------------
// ESTRATEGIA 2: VORAZ GLOBAL (RECURSIVO)
// -------------------------------------------------------------------------
void recursivo_aux(int idx, const vector<Candidato>& C, vector<int>& sol, vector<int>& cap, int& asignadas, long long& total, int nt) {
    // Caso base: fin de candidatos o todas las tareas asignadas
    if (idx == (int)C.size() || asignadas == nt) return;

    const Candidato& c = C[idx];
    // Selección y Factibilidad
    if (sol[c.tarea] == -1 && cap[c.trabajador] > 0) {
        sol[c.tarea] = c.trabajador;
        cap[c.trabajador]--;
        total += c.beneficio;
        asignadas++;
    }
    // Avance rápido: pasamos al siguiente candidato sin vuelta atrás
    recursivo_aux(idx + 1, C, sol, cap, asignadas, total, nt);
}

pair<long long, vector<int>> voraz_recursivo(int nw, int nt, const vector<vector<int>>& matriz, vector<int> cap) {
    vector<Candidato> C;
    for (int i = 0; i < nw; ++i) {
        for (int j = 0; j < nt; ++j) {
            if (matriz[i][j] > 0) C.push_back({i, j, matriz[i][j]});
        }
    }

    sort(C.begin(), C.end());

    vector<int> sol(nt, -1);
    long long beneficioTotal = 0;
    int asignadas = 0;

    recursivo_aux(0, C, sol, cap, asignadas, beneficioTotal, nt);

    if (asignadas < nt) beneficioTotal = 0;
    return {beneficioTotal, sol};
}

// -------------------------------------------------------------------------
// ESTRATEGIA 3: VORAZ POR TAREA
// -------------------------------------------------------------------------
pair<long long, vector<int>> voraz_por_tarea(int nw, int nt, const vector<vector<int>>& matriz, vector<int> cap) {
    vector<int> sol(nt, -1);
    long long beneficioTotal = 0;
    int asignadas = 0;

    // Se recorre cada tarea y se toma la mejor decisión local inmediata
    for (int j = 0; j < nt; ++j) {
        int mejorW = -1;
        int maxB = -1;
        
        for (int i = 0; i < nw; ++i) {
            // Buscamos el trabajador con más beneficio para esta tarea específica
            if (cap[i] > 0 && matriz[i][j] > maxB && matriz[i][j] > 0) {
                maxB = matriz[i][j];
                mejorW = i;
            }
        }
        
        if (mejorW != -1) {
            sol[j] = mejorW;
            cap[mejorW]--;
            beneficioTotal += maxB;
            asignadas++;
        }
    }

    if (asignadas < nt) beneficioTotal = 0;
    return {beneficioTotal, sol};
}