import matplotlib.pyplot as plt

# Définir les listes x et y
x = [50, 100, 200, 500]
y = [0.11, 0.37, 0.95, 3.90]

# Créer le plot
plt.plot(x, y, 'o')  # 'o' indique que nous voulons tracer des points

# Ajouter des labels et un titre
plt.xlabel('Number of nodes ')
plt.ylabel('passage in while loop')

# Afficher le graphique
plt.show()