import matplotlib.pyplot as plt
import numpy as np


def lire_tableau_depuis_fichier(nom_fichier):
    tableau = []
    with open(nom_fichier, 'r') as fichier:
        lignes = fichier.readlines()
        for ligne in lignes:
            elements = ligne.strip().split(' ')
            elements_float = [float(e) for e in elements]
            tableau.append(elements_float)
    return tableau

# Exemple d'utilisation
nom_fichier = 'data10prct'
tableau = np.array(lire_tableau_depuis_fichier(nom_fichier))


# Générer des données d'exemple
X = tableau[0]
Y = [tableau[1][i]/tableau[5][i] for i in range(len(tableau[3]))]

y1 = [tableau[1][i]/tableau[2][i] for i in range(len(tableau[3]))]
y2 = [tableau[4][i]/tableau[5][i] for i in range(len(tableau[3]))]

# Créer le graphique
fig, ax = plt.subplots(figsize=(7,5))
# Tracer les données
col1 = '#698bc2'
col2 = '#499c69'
col3 = '#f0e173'


ax.plot(tableau[0][:],100*tableau[2][:], label='Picking from Queue', color=col1, linestyle='-', linewidth=2, marker='o', markersize=5, markeredgewidth=1.5)
ax.plot(tableau[0][:], 100*tableau[3][:], label='Traveling neighbors', color=col2, linestyle='-', linewidth=2, marker='o', markersize=5, markeredgewidth=1.5)
ax.plot(tableau[0][:], 100*tableau[4][:], label='Updating Pareto fronts', color=col3, linestyle='-', linewidth=2, marker='o', markersize=5, markeredgewidth=1.5)
ax.set_ylim(0, 100)

#ax.set_yscale('log')
ax.legend(loc='center left', fontsize=13)
ax.tick_params(axis='both', which='major', labelsize=13)
ax.grid(True, which='both', linestyle='--', linewidth=0.5)


# Afficher le graphique
plt.show()
