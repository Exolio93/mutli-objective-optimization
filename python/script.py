import matplotlib.pyplot as plt
import numpy as np
import time as t

epsilon = 1

def read_map(graph_path_1, dim):
    # Lire le fichier
    with open(graph_path_1, 'r') as fichier:
        lignes = fichier.readlines()
    
    # Lire N et val_max
    N = int(lignes[0].strip())
    val_max = float(lignes[1].strip())
    
    # Initialiser les tableaux X et Y
    X = np.zeros(N)
    Y = np.zeros(N)
    pX = np.zeros(dim-1)
    pY = np.zeros(dim-1)
    
    # Lire les valeurs dans X et Y
    for i in range(2, 2 + N):
        index, x_val, y_val = lignes[i].strip().split()
        index = int(index)
        X[index] = float(x_val)
        Y[index] = float(y_val)
        
    for i in range(2+N, 2+N+dim-1):
        index, x_val, y_val = lignes[i].strip().split()
        index = int(index)
        pX[index] = float(x_val)
        pY[index] = float(y_val)
    
    
    
    
    return N, val_max, X, Y, pX, pY


def read_solution(solution_path):
    with open(solution_path, 'r') as fichier:
        lignes = fichier.readlines()
    
    # Lire la première ligne pour obtenir la valeur de N
    N = int(lignes[0].strip())
    
    # Initialiser une liste pour stocker les blocs
    blocs = []
    
    # Lire chaque bloc
    bloc = []
    for ligne in lignes[1:]:
        ligne = ligne.strip()
        if ligne == '*':
            
            blocs.append(bloc)
            bloc = []
        else:
            # Ajouter les triplets (float, float, int) au bloc actuel
            valeurs = ligne.split()
            triplet = (float(valeurs[0]), float(valeurs[1]), int(valeurs[2]))
            bloc.append(triplet)
    
    # Ajouter le dernier bloc s'il n'est pas vide
    if bloc:
        blocs.append(bloc)
    
    # Convertir la liste de listes en un tableau numpy d'objets
    result = np.array(blocs, dtype=object)
    
    return result

def read_arcs(arcs_path):
    with open(arcs_path, 'r') as fichier:
        lignes = fichier.readlines()
    
    # Lire la première ligne pour obtenir la valeur de N
    N = int(lignes[0].strip())
    dim = int(lignes[1].strip())
    Ax = np.zeros((N,N))
    Ay = np.zeros((N,N))
    # Initialiser une liste pour stocker les tuples
    arcs = []
    
    # Lire les lignes suivantes après la deuxième ligne
    for ligne in lignes[2:]:
        valeurs = ligne.strip().split()
        Ax[int(valeurs[0])][int(valeurs[1])] = float(valeurs[2])
        Ay[int(valeurs[0])][int(valeurs[1])] = float(valeurs[3])
    
    return dim, Ax,Ay



# Exemple d'utilisation

graph_path_1 = "save/test/map"
graph_path_2 = "save/test/solution"
graph_path_3 = "save/test/2_20_20"


dim, Ax,Ay = read_arcs(graph_path_3)
N, val_max, X, Y, pX, pY = read_map(graph_path_1,dim)
sets = read_solution(graph_path_2)


plt.figure(figsize=(10, 6))

def plot_path(i):
    global N
    point = sets[-1][i]
    ind = N-1
    restart = True
    while(restart):

        if (point[2] == 0):
            restart = False
        plt.plot([X[ind], X[point[2]]], [Y[ind], Y[point[2]]], 'b')

        
        for elt in sets[point[2]]:
            if(abs(elt[0] + Ax[point[2]][ind] - point[0]) <epsilon and abs(elt[1] + Ay[point[2]][ind]-point[1])<epsilon):
                
                ind = point[2]
                point = elt
                break

        
        
        


# PLOT OF ALL ARCS

for i in range(N):
    for j in range(N):
        if (Ax[i][j]!=0 or Ay[i][j]!=0):
            plt.plot([X[i], X[j]], [Y[i], Y[j]], 'r--')


# num_graphs = len(sets[-1])

# # Déterminez le nombre de lignes et de colonnes pour les subplots
# ncols = 3  # Par exemple, 3 colonnes
# nrows = (num_graphs + ncols - 1) // ncols  # Calcul du nombre de lignes nécessaires

# # Créez une figure et les subplots
# fig, axes = plt.subplots(nrows, ncols, figsize=(15, nrows * 5))
# if nrows == 1:
#     axes = axes[np.newaxis, :]
# if ncols == 1:
#     axes = axes[:, np.newaxis]

# # Tracer chaque graphique dans son subplot respectif
# for i in range(num_graphs):
#     row = i // ncols
#     col = i % ncols
#     ax = axes[row, col]
    
#     plt.sca(axes[row, col])  # Définir le subplot actif
#     plot_path(i)  # Tracer le graphique numéro i
#     plt.scatter(X, Y, c='red', marker='o')
#     ax.set_aspect('equal')
    
# # Ajustez l'espacement entre les subplots
# plt.tight_layout()
# plt.show()

plt.scatter(X, Y, c='blue', marker='o')
plt.scatter(pX, pY, c='red', marker='X')
plt.title('Graph of Points')
plt.xlabel('X values')
plt.ylabel('Y values')
plt.grid(True)
plt.show()

