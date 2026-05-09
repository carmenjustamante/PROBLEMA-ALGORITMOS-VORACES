import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

def generar_graficas():
    try:
        df = pd.read_csv("datos_tiempos.csv")
    except FileNotFoundError:
        print("Error: No se encuentra datos_tiempos.csv")
        return

    # Reemplazamos los ceros absolutos por un valor diminuto
    # para que la escala logarítmica no dé error
    df = df.replace(0, 0.0001)
    N = df['N']

    # ==========================================================
    # BLOQUE 1: Estudio Mejor vs Peor
    # ==========================================================

    # 1. GLOBAL ITERATIVO: Mejor vs Peor
    plt.figure(figsize=(8, 5))
    plt.plot(N, df['GlobIter_Peor'], 'r-o', label='Peor Caso (Densa)')
    plt.plot(N, df['GlobIter_Mejor'], 'g-s', label='Mejor Caso (Dispersa)')
    plt.title("Algoritmo Global Iterativo: Mejor vs Peor Caso")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.legend()
    plt.grid(True)
    plt.savefig("1_Global_Iterativo_Mejor_Peor.png")

    # 2. GLOBAL RECURSIVO: Mejor vs Peor
    plt.figure(figsize=(8, 5))
    plt.plot(N, df['GlobRec_Peor'], 'r-o', label='Peor Caso (Densa)')
    plt.plot(N, df['GlobRec_Mejor'], 'g-s', label='Mejor Caso (Dispersa)')
    plt.title("Algoritmo Global Recursivo: Mejor vs Peor Caso")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.legend()
    plt.grid(True)
    plt.savefig("2_Global_Recursivo_Mejor_Peor.png")

    # 3. POR TAREA: Mejor vs Peor
    plt.figure(figsize=(8, 5))
    plt.plot(N, df['PorTarea_Peor'], 'r-o', label='Peor Caso (Densa)')
    plt.plot(N, df['PorTarea_Mejor'], 'g-s', label='Mejor Caso (Dispersa)')
    plt.title("Algoritmo Por Tarea: Mejor vs Peor Caso")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.legend()
    plt.grid(True)
    plt.savefig("3_Por_Tarea_Mejor_Peor.png")

    # ==========================================================
    # BLOQUE 2: COMPARATIVAS Y EFECTOS ESTRUCTURALES
    # ==========================================================

    # 4. COMPARATIVA DE LOS TRES (Lineal)
    plt.figure(figsize=(8, 5))
    plt.plot(N, df['GlobIter_Peor'], label='Global Iterativo', linewidth=2, marker='o')
    plt.plot(N, df['GlobRec_Peor'], label='Global Recursivo', linewidth=2, marker='s')
    plt.plot(N, df['PorTarea_Peor'], label='Por Tarea (Búsqueda Local)', linewidth=2, marker='^')
    plt.title("Comparativa: Los 3 Algoritmos (Peor Caso) - Escala LINEAL")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.legend()
    plt.grid(True)
    plt.savefig("4_Comparativa_Triple_Lineal.png")

    # 5. COMPARATIVA DE LOS TRES (Logarítmica)
    plt.figure(figsize=(8, 5))
    plt.plot(N, df['GlobIter_Peor'], label='Global Iterativo', linewidth=2, marker='o')
    plt.plot(N, df['GlobRec_Peor'], label='Global Recursivo', linewidth=2, marker='s')
    plt.plot(N, df['PorTarea_Peor'], label='Por Tarea', linewidth=2, marker='^')
    plt.title("Comparativa: Los 3 Algoritmos (Peor Caso) - Escala LOGARÍTMICA")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.yscale('log') # Escala logarítmica activada
    plt.legend()
    plt.grid(True)
    plt.savefig("5_Comparativa_Triple_Log.png")

    # 6. EL COSTE DE LA RECURSIVIDAD
    plt.figure(figsize=(8, 5))
    plt.plot(N, df['GlobIter_Peor'], 'b-o', label='Global Iterativo')
    plt.plot(N, df['GlobRec_Peor'], 'r-s', label='Global Recursivo')
    plt.title("Iterativo vs. Recursivo")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.yscale('log')
    plt.legend()
    plt.grid(True)
    plt.savefig("6_Coste_Recursividad_Log.png")

    # 7. FOTO FINISH (Gráfico de Barras para el caso más grande)
    plt.figure(figsize=(8, 5))
    ultima_fila = df.iloc[-1]
    N_max = int(ultima_fila['N'])
    tiempos_finales = [
        ultima_fila['GlobIter_Peor'],
        ultima_fila['GlobRec_Peor'],
        ultima_fila['PorTarea_Peor']
    ]
    etiquetas = ['Global Iterativo', 'Global Recursivo', 'Por Tarea']
    colores = ['blue', 'red', 'green']
   
    plt.bar(etiquetas, tiempos_finales, color=colores)
    plt.title(f"Rendimiento Absoluto para el caso más grande (N = {N_max})")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.savefig("7_Barras_Comparativa_Max.png")
   

    # ==========================================================
    # BLOQUE 3: REGRESIÓN MATEMÁTICA Y CONTRASTE (MODIFICADO)
    # ==========================================================

    n_vals = N.values

    # 1. Regresión Global Iterativo Peor -> O(N^2 log N)
    t_gi_peor = df['GlobIter_Peor'].values
    x_n2_logn = (n_vals**2) * np.log2(n_vals) # Transformación teórica
   
    res_gi = linregress(x_n2_logn, t_gi_peor)
    r2_gi = res_gi.rvalue ** 2
    pred_gi = res_gi.intercept + res_gi.slope * x_n2_logn

    plt.figure(figsize=(8, 5))
    plt.plot(n_vals, t_gi_peor, 'bx', label='Experimental (Global Iterativo)')
    plt.plot(n_vals, pred_gi, 'orange', label=f'Ajuste O(N² log N) | R² = {r2_gi:.4f}')
    plt.title("Contraste Teórico-Experimental: Global Iterativo")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.legend()
    plt.grid(True)
    plt.savefig("8a_Contraste_GlobIter.png")

    # 2. Regresión Global Recursivo Peor -> O(N^2 log N)
    t_gr_peor = df['GlobRec_Peor'].values
    res_gr = linregress(x_n2_logn, t_gr_peor)
    r2_gr = res_gr.rvalue ** 2
    pred_gr = res_gr.intercept + res_gr.slope * x_n2_logn

    plt.figure(figsize=(8, 5))
    plt.plot(n_vals, t_gr_peor, 'rx', label='Experimental (Global Recursivo)')
    plt.plot(n_vals, pred_gr, 'green', label=f'Ajuste O(N² log N) | R² = {r2_gr:.4f}')
    plt.title("Contraste Teórico-Experimental: Global Recursivo")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.legend()
    plt.grid(True)
    plt.savefig("8b_Contraste_GlobRec.png")

    # 3. Regresión Por Tarea Peor -> O(N^2)
    # Explicación: Por Tarea anida dos bucles de N, por tanto es cuadrático puro.
    t_pt_peor = df['PorTarea_Peor'].values
    x_n2 = n_vals**2
    res_pt = linregress(x_n2, t_pt_peor)
    r2_pt = res_pt.rvalue ** 2
    pred_pt = res_pt.intercept + res_pt.slope * x_n2

    plt.figure(figsize=(8, 5))
    plt.plot(n_vals, t_pt_peor, 'gx', label='Experimental (Por Tarea)')
    plt.plot(n_vals, pred_pt, 'red', label=f'Ajuste O(N²) | R² = {r2_pt:.4f}')
    plt.title("Contraste Teórico-Experimental: Por Tarea")
    plt.xlabel("N (Trabajadores/Tareas)")
    plt.ylabel("Tiempo (Microsegundos)")
    plt.legend()
    plt.grid(True)
    plt.savefig("8c_Contraste_PorTarea.png")

    print("\n--- RESULTADOS DE LAS REGRESIONES ---")
    print(f"R^2 Global Iterativo (Ajuste N^2 log N): {r2_gi:.4f}")
    print(f"R^2 Global Recursivo (Ajuste N^2 log N): {r2_gr:.4f}")
    print(f"R^2 Por Tarea        (Ajuste N^2):       {r2_pt:.4f}")
    print("-------------------------------------\n")

if __name__ == "__main__":
    generar_graficas()