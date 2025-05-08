import serial
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg')
import numpy as np

# Définir le port série et la vitesse (vérifie ton port !)
port = "/dev/ttyACM0"  # Linux/Mac : /dev/ttyUSB0 ou /dev/ttyACM0 | Windows : COM3, COM4...
baud_rate = 9600  # Doit correspondre à Serial.begin(9600)
loop = True

nombreCapteurs = 6
cycle = 0
# Labels des axes
labels = ['3', '2', '1', '6', '5', '4']
num_vars = len(labels)
angles = np.linspace(0, 2 * np.pi, num_vars, endpoint=False)

# Initialisation de la figure
fig, ax = plt.subplots(figsize=(7, 7), subplot_kw=dict(polar=True))

# Réglages de l'apparence
ax.set_thetagrids(np.degrees(angles), labels)
ax.set_ylim(0, 90)
ax.grid(True, linestyle='--', alpha=0.4)
ax.set_title("Données Dynamiques en Temps Réel", size=16, pad=20)

# Fonction pour mettre à jour les points avec des données simulées
def update_points(tabMesures):
    ax.cla()  # Effacer le contenu précédent du graphique
    ax.set_thetagrids(np.degrees(angles), labels)
    ax.set_ylim(0, 90)
    ax.grid(True, linestyle='--', alpha=0.4)
    ax.set_title("Données Dynamiques en Temps Réel", size=16, pad=20)

    # Fermer la boucle pour relier les points
    values = np.append(tabMesures, tabMesures[0])  # Reprendre le premier point à la fin
    angle_vals = np.append(angles, angles[0])

    # Tracer la ligne polygonale
    ax.plot(angle_vals, values, color='royalblue', linewidth=2)

    # Remplir la surface sous la courbe (optionnel)
    ax.fill(angle_vals, values, color='royalblue', alpha=0.25)
    
    plt.draw()  # Re-dessiner le graphique
    plt.pause(0.1) # Pause pour actualiser tous les 1 seconde

# Affichage de la figure
plt.show(block=False)

try:
    # Ouvrir la connexion série
    ser = serial.Serial(port, baudrate=baud_rate, timeout=1)
    print(f"Connexion établie sur {port}")

    while loop==True:
        # Lire une ligne depuis l'Arduino
        line = ser.readline().decode('utf-8').strip()
        if line:  # Vérifie si la ligne n'est pas vide
            tabMesures = line.split(',')
            print(f"Donnée reçue : {line}")
            if len(tabMesures) >= 6:
                tabMesures = [int(x) for x in tabMesures]
                print(tabMesures)
                update_points(tabMesures)

        
except serial.SerialException as e:
    print(f"Erreur de connexion : {e}")

except KeyboardInterrupt:
    plt.close('all')
    print("\nProgramme interrompu par l'utilisateur.")
    loop=False



