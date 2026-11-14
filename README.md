# N-Body Particle Simulator & Celestial Dynamics (C++17)

[![C++ CI & Tests](https://github.com/Erratu/Projet_CPP/actions/workflows/ci.yml/badge.svg)](https://github.com/Erratu/Projet_CPP/actions/workflows/ci.yml)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![CMake](https://img.shields.io/badge/CMake-3.16%2B-brightgreen.svg)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Moteur de simulation numérique de dynamique moléculaire et gravitationnelle à $N$ corps développé en C++17 dans le cadre du cursus de Mathématiques Appliquées.

Le projet implémente un intégrateur symplectique d'ordre 2 (**Störmer-Verlet**), le potentiel d'interaction intermoléculaire de **Lennard-Jones**, ainsi qu'une accélération spatiale par **Cell-Lists (Linked-Cell method)** réduisant la complexité algorithmique de $\mathcal{O}(N^2)$ à $\mathcal{O}(N)$.

---

## Points Clés & Fonctionnalités

- **Intégration Numérique Symplectique** : Schéma de Störmer-Verlet (Velocity Verlet) garantissant la conservation de l'énergie et la stabilité temporelle.
- **Potentiel de Lennard-Jones** :
  $$V(r) = 4\varepsilon \left[ \left(\frac{\sigma}{r}\right)^{12} - \left(\frac{\sigma}{r}\right)^6 \right]$$
  avec troncature au rayon de coupure $r_{\text{cut}}$ et calcul efficace des forces sans racine carrée superflue.
- **Accélération Spatiale $\mathcal{O}(N)$** : Partitionnement de l'espace en cellules de taille $r_{\text{cut}}$. Chaque particule n'interagit qu'avec les particules de sa cellule et de ses $3^D - 1$ cellules voisines.
- **Conditions aux Limites Polyvalentes** :
  - `REFLEXION` : Rebond élastique spéculaire aux parois.
  - `ABSORPTION` : Suppression des particules hors domaine.
  - `PERIODIQUE` : Conditions limites toriques / périodiques.
  - `REFLEXION_POTENTIEL` : Répulsion progressive modélisée par potentiel répulsif $r^{-12}$ aux parois.
- **Thermostat Cinétique** : Rééchelonnement des vitesses pour régulation de température / énergie cinétique cible.
- **Architecture Générique** : Classes `Vecteur<D>`, `Particule<D>`, `Univers<D>` templatisées sur la dimension d'espace ($D = 2, 3$).
- **Exports Scientifiques** : Génération de fichiers VTU (format XML Unstructured Grid de VTK) compatibles avec **ParaView** et visualisables via script Python.

---

## Structure du Projet

```text
├── include/           # En-têtes C++ (Vecteur, Particule, Univers, Exceptions)
├── src/               # Implémentations templates (.tpp)
├── demo/              # Scénarios physiques exécutables
│   ├── demo_collision.cpp   # Impact élastique de deux blocs de particules
│   ├── demo_sys_sol.cpp     # Orbites gravitationnelles (Soleil, Terre, Jupiter, Halley)
│   ├── demo_q6.cpp          # Impact sphère sur substrat sous gravité et thermostat
│   └── perfs_insertion.cpp  # Benchmarks de performance
├── test/              # Suite de tests unitaires (GoogleTest)
├── doc/               # Configuration Doxygen et rapport mathématique
├── scripts/           # Visualisation et benchmarks Python
└── .github/workflows/ # Pipeline d'intégration continue (CI)
```

---

## Compilation & Exécution

### Prérequis
- Compilateur compatible C++17 (`g++ >= 9` ou `clang++ >= 10`)
- CMake `>= 3.16`
- Doxygen & Graphviz *(optionnel, pour la documentation)*
- Python 3 + Matplotlib *(optionnel, pour les animations)*

### Instructions de build

```bash
# Cloner le dépôt
git clone https://github.com/Erratu/Projet_CPP.git
cd Projet_CPP

# Configurer et compiler en mode Release (-O3)
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j $(nproc)
```

### Lancement des tests

```bash
ctest --test-dir build --output-on-failure
```

### Lancement des démonstrations

```bash
# Simulation d'un impact de deux corps
./build/demo/demo_collision

# Simulation du système planétaire
./build/demo/demo_sys_sol

# Benchmark de complexité et de conteneurs
./build/demo/perfs_insertion
```

---

## Visualisation & Résultats

Les simulations génèrent des fichiers `.vtu` dans des dossiers dédiés (`output_collision/`, etc.). 

### Option 1 : Via le script Python (Génération de GIF)
```bash
python3 scripts/visualize_simulation.py --dir output_collision --out collision.gif
```

### Option 2 : Via ParaView
1. Ouvrir le groupe de fichiers `output_*.vtu`.
2. Cliquer sur **Apply**.
3. Ajouter un filtre **Glyph** (Sphères).
4. Colorer par le champ de vitesse (`Velocity`) ou de masse (`Masse`).
5. Appuyer sur **Play**.

---

## Analyse de Performances

Le benchmark `perfs_insertion` met en évidence deux concepts critiques :
1. **Conteneurs STL** : Le pré-dimensionnement mémoire avec `std::vector::reserve` surpasse `std::list` en évitant les allocations nœud par nœud et en maximisant la localité spatiale du cache CPU.
2. **Méthode des cellules** : Grâce au maillage spatial indexé, le temps de calcul des forces à chaque pas de temps passe d'une complexité quadratique $\mathcal{O}(N^2)$ à une complexité quasi-linéaire $\mathcal{O}(N)$ lorsque la densité reste bornée.

---

## Licence
Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.