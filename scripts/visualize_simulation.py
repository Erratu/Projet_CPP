#!/usr/bin/env python3
"""
Script de conversion des snapshots .vtu en animation GIF/PNG
Dépendances : pip install matplotlib numpy
"""

import os
import glob
import xml.etree.ElementTree as ET
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import argparse

def parse_vtu(filepath):
    tree = ET.parse(filepath)
    root = tree.getroot()
    
    positions = []
    velocities = []
    masses = []
    
    for piece in root.iter('Piece'):
        for data_array in piece.iter('DataArray'):
            name = data_array.get('Name')
            text_data = data_array.text.strip().split()
            vals = [float(x) for x in text_data]
            
            if name == 'Position':
                positions = np.array(vals).reshape(-1, 3)
            elif name == 'Velocity':
                velocities = np.array(vals).reshape(-1, 3)
            elif name == 'Masse':
                masses = np.array(vals)
                
    return positions, velocities, masses

def animate_simulation(folder, output_gif="simulation.gif", interval=50):
    files = sorted(glob.glob(os.path.join(folder, "output_*.vtu")))
    if not files:
        print(f"Aucun fichier .vtu trouvé dans '{folder}'")
        return

    print(f"Chargement de {len(files)} snapshots depuis '{folder}'...")
    
    # Premier snapshot pour calibrer les limites du graphe
    pos0, _, _ = parse_vtu(files[0])
    
    fig, ax = plt.subplots(figsize=(8, 6), dpi=100)
    ax.set_facecolor('#0f172a')
    fig.patch.set_facecolor('#0f172a')
    
    # Calcul des bornes globales
    all_x, all_y = [], []
    for f in files[::max(1, len(files)//10)]: # échantillon
        p, _, _ = parse_vtu(f)
        if len(p) > 0:
            all_x.extend(p[:, 0])
            all_y.extend(p[:, 1])
            
    margin_x = (max(all_x) - min(all_x)) * 0.08 if all_x else 10
    margin_y = (max(all_y) - min(all_y)) * 0.08 if all_y else 10
    ax.set_xlim(min(all_x) - margin_x, max(all_x) + margin_x)
    ax.set_ylim(min(all_y) - margin_y, max(all_y) + margin_y)
    
    scatter = ax.scatter([], [], s=12, c=[], cmap='plasma', alpha=0.85, edgecolors='none')
    title = ax.set_title("", color='white', fontsize=12)
    ax.tick_params(colors='white')
    for spine in ax.spines.values():
        spine.set_color('#334155')

    def update(frame_idx):
        pos, vel, mass = parse_vtu(files[frame_idx])
        if len(pos) > 0:
            scatter.set_offsets(pos[:, :2])
            # Coloration par la norme de vitesse
            speed = np.linalg.norm(vel[:, :2], axis=1) if len(vel) > 0 else np.ones(len(pos))
            scatter.set_array(speed)
        title.set_text(f"Snapshot {frame_idx + 1}/{len(files)} - Particules: {len(pos)}")
        return scatter, title

    ani = animation.FuncAnimation(fig, update, frames=len(files), interval=interval, blit=False)
    print(f"Sauvegarde sous {output_gif}...")
    ani.save(output_gif, writer='pillow', fps=1000 // interval)
    plt.close()
    print("Export terminé !")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Animer des sorties .vtu")
    parser.add_argument("--dir", type=str, default="output_collision", help="Dossier contenant les .vtu")
    parser.add_argument("--out", type=str, default="collision.gif", help="Nom du fichier GIF de sortie")
    args = parser.parse_args()
    animate_simulation(args.dir, args.out)