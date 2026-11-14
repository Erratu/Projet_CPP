#!/usr/bin/env python3
"""
Lance les benchmarks C++ et génère les figures pour le README et le notebook
"""
import subprocess
import re
import matplotlib.pyplot as plt

def run_insertion_benchmark():
    cmd = ["./build/demo/perfs_insertion"]
    res = subprocess.run(cmd, capture_output=True, text=True)
    output = res.stdout
    print(output)
    
    # Extraction des temps d'insertion
    t_list = float(re.search(r"Temps \(std::list\) : ([\d\.]+) s", output).group(1))
    t_vec = float(re.search(r"Temps \(std::vector avec reserve\) : ([\d\.]+) s", output).group(1))
    
    # Extraction des k pour l'algo Störmer-Verlet
    k_matches = re.findall(r"Génération de (\d+) particules \(k=(\d+)\)\.\.\. Temps de calcul : ([\d\.]+) s", output)
    n_particules = [int(m[0]) for m in k_matches]
    t_calc = [float(m[2]) for m in k_matches]
    
    # Figure 1 : list vs vector
    plt.figure(figsize=(6, 4))
    plt.bar(["std::list", "std::vector (reserve)"], [t_list, t_vec], color=['#ef4444', '#3b82f6'])
    plt.ylabel("Temps d'exécution (secondes)")
    plt.title("Performance d'insertion (32 768 particules)")
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.savefig("benchmarks_insertion.png", dpi=150)
    plt.close()
    
    # Figure 2 : Complexité de l'algorithme avec cellules
    if n_particules:
        plt.figure(figsize=(7, 4.5))
        plt.plot(n_particules, t_calc, 'o-', color='#10b981', linewidth=2, label="Maillage spatial (Cell-Lists)")
        plt.xlabel("Nombre de particules (N)")
        plt.ylabel("Temps de calcul 1 pas (s)")
        plt.title("Mise à l'échelle de la simulation N-Body")
        plt.xscale('log')
        plt.yscale('log')
        plt.grid(True, which="both", ls="--", alpha=0.5)
        plt.legend()
        plt.tight_layout()
        plt.savefig("benchmarks_scaling.png", dpi=150)
        plt.close()

if __name__ == "__main__":
    run_insertion_benchmark()