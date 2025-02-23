#include <SharpIR.h>
#define Sortie A0
#define modele 1080
SharpIR Capteur(Sortie,modele);

void setup(){
    Serial.begin(9600);
    Serial.println("Capteur infrarouge Sharp 10-80 cm")
}

void loop(){
    delay(100);
    Serial.print("distance (cm)= ");
    Serial.println(Capteur.distance());
}