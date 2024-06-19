import matplotlib.pyplot as plt
import numpy as np
import time as t
def read_map(graph_path_1):
    # Lire le fichier
    with open(graph_path_1, 'r') as fichier:
        lignes = fichier.readlines()
    
    # Lire N et val_max
    N = int(lignes[0].strip())
    val_max = float(lignes[1].strip())
    
    # Initialiser les tableaux X et Y
    X = np.zeros(N)
    Y = np.zeros(N)
    
    # Lire les valeurs dans X et Y
    for i in range(2, 2 + N):
        index, x_val, y_val = lignes[i].strip().split()
        index = int(index)
        X[index] = float(x_val)
        Y[index] = float(y_val)
    
    return N, val_max, X, Y


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
            if bloc:  # Ajouter le bloc précédent à la liste des blocs
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
    Ax = np.zeros((N,N))
    Ay = np.zeros((N,N))
    # Initialiser une liste pour stocker les tuples
    arcs = []
    
    # Lire les lignes suivantes après la deuxième ligne
    for ligne in lignes[2:]:
        valeurs = ligne.strip().split()
        Ax[int(valeurs[0])][int(valeurs[1])] = float(valeurs[2])
        Ay[int(valeurs[0])][int(valeurs[1])] = float(valeurs[3])
    
    return Ax,Ay



# Exemple d'utilisation

graph_path_1 = "save/graph_to_plot/map"
graph_path_2 = "save/graph_to_plot/solution"
graph_path_3 = "save/graph_to_plot/2_20_50"




N, val_max, X, Y = read_map(graph_path_1)
sets = read_solution(graph_path_2)
Ax,Ay = read_arcs(graph_path_3)

plt.figure(figsize=(10, 6))

def plot_path(i):
    global N
    point = sets[-1][i]
    ind = N-1
    while(True):
        
        plt.plot([X[ind], X[point[2]]], [Y[ind], Y[point[2]]], 'b')
        for elt in sets[point[2]]:
            
            if(elt[0] + Ax[point[2]][ind] == point[0] and elt[1] + Ay[point[2]][ind] == point[1]):
                print(point, elt)
                t.sleep(1)
                point = elt
                break
            else : 
                print("ok")
            
        print("looop")
        
        
        if (point[2] == 0):
            break
        


# # PLOT OF ALL ARCS
# for k in range(len(arcs)):
#     i = int(arcs[k][0])
#     j = int(arcs[k][1])
#     xx = []
#     plt.plot([X[i], X[j]], [Y[i], Y[j]], 'r--')


plt.scatter(X, Y, c='blue', marker='o')
plot_path(1)
plt.title('Graph of Points')
plt.xlabel('X values')
plt.ylabel('Y values')
plt.grid(True)
plt.show()