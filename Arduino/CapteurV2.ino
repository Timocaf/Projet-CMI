// Utiliser la version 2.0.1 de la bibliothque SharpIR
// Port Analogique 0 et 1 inutilisable
#include <SharpIR.h>

int mesure_0;
int mesure_60;
int mesure_120;
int mesure_180;
int mesure_240;
int mesure_300;
int danger;

SharpIR Capteur_1( SharpIR::GP2Y0A21YK0F, A3 );
SharpIR Capteur_2( SharpIR::GP2Y0A21YK0F, A5 );
SharpIR Capteur_3( SharpIR::GP2Y0A21YK0F, A7 );
SharpIR Capteur_4( SharpIR::GP2Y0A21YK0F, A9 );
SharpIR Capteur_5( SharpIR::GP2Y0A21YK0F, A11 );
SharpIR Capteur_6( SharpIR::GP2Y0A21YK0F, A13 );

void setup(){
  Serial.begin(9600);
  Serial.println("Capteur infrarouge Sharp 10-80 cm");
}

int min(int val0, int val1, int val2, int val3, int val4, int val5){
  if(){

  }
}


void loop(){
  delay(100);
  Serial.print("Distance 0° (cm) = ");
  mesure_0 = Capteur_1.getDistance();
  Serial.print(mesure_0);
  Serial.print("\t Distance 60° (cm) = ");
  mesure_60 = Capteur_2.getDistance();
  Serial.print(mesure_60);
  Serial.print("\t Distance 120° (cm) = ");
  mesure_120 = Capteur_3.getDistance();
  Serial.print(mesure_120);
  Serial.print("\t Distance 180° (cm) = ");
  mesure_180 = Capteur_4.getDistance();
  Serial.print(mesure_180);
  Serial.print("\t Distance 240° (cm) = ");
  mesure_240 = Capteur_5.getDistance();
  Serial.print(mesure_240);
  Serial.print("\t Distance 300° (cm) = ");
  mesure_300 = Capteur_6.getDistance();
  Serial.print(mesure_300);
  Serial.print("\t Dianger le plus proche = ");
  danger = min(mesure_0, mesure_60, mesure_120, mesure_180, mesure_240, mesure_300);
  Serial.print(danger);
}