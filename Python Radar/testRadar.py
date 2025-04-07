import serial
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg')
import numpy as np

# Définir le port série et la vitesse (vérifie ton port !)
port = "/dev/ttyACM0"  # Linux/Mac : /dev/ttyUSB0 ou /dev/ttyACM0 | Windows : COM3, COM4...
baud_rate = 9600  # Doit correspondre à Serial.begin(9600)
loop=True

plt.show()

nombreCapteurs = 6;
tabMesures = [0 for i in range(6)]
cycle = 0
print(tabMesures)

try:
    # Ouvrir la connexion série
    ser = serial.Serial(port, baudrate=baud_rate, timeout=1)
    print(f"Connexion établie sur {port}")

    while loop==True:
        # Lire une ligne depuis l'Arduino
        line = ser.readline().decode('utf-8').strip()
        if line:  # Vérifie si la ligne n'est pas vide
            if line == 0:
                cycle = 0
            else :
                if cycle == 6:
                    cycle = 0
                tabMesures[cycle] = int(line)
                print(f"Donnée reçue : {line}")
                print(cycle)
                print(tabMesures)
                if cycle <= 5:
                    cycle += 1

except serial.SerialException as e:
    print(f"Erreur de connexion : {e}")

except KeyboardInterrupt:
    print("\nProgramme interrompu par l'utilisateur.")

finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Port série fermé.")

