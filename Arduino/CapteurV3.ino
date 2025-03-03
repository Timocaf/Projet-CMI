// Utiliser la version 2.0.1 de la bibliothque SharpIR
// Port Analogique 0 et 1 inutilisable
#include <SharpIR.h>

int mesure_0 ;
int mesure_60;
int mesure_120;
int mesure_180;
int mesure_240;
int mesure_300;
int nombreCapteurs = 6;
int * tabMesures = new int[nombreCapteurs]{mesure_0, mesure_60, mesure_120, mesure_180, mesure_240, mesure_300};
int danger;

SharpIR Capteur_0( SharpIR::GP2Y0A21YK0F, A3 );
SharpIR Capteur_60( SharpIR::GP2Y0A21YK0F, A5 );
SharpIR Capteur_120( SharpIR::GP2Y0A21YK0F, A7 );
SharpIR Capteur_180( SharpIR::GP2Y0A21YK0F, A9 );
SharpIR Capteur_240( SharpIR::GP2Y0A21YK0F, A11 );
SharpIR Capteur_300( SharpIR::GP2Y0A21YK0F, A13 );

int minVal(int tab[], int taille){
  int valMin = tab[0];
  for (int i = 1; i < taille; i++){
    if(valMin > tab[i]){
      valMin = tab[i];
    }
  }
  return valMin;
}

void setup(){
  Serial.begin(9600);
  Serial.println("Capteur infrarouge Sharp 10-80 cm");
}

void loop(){
  delay(100);
  Serial.print("Distance 0° (cm) = ");
  mesure_0 = Capteur_0.getDistance();
  Serial.print(mesure_0);
  Serial.print("\t Distance 60° (cm) = ");
  mesure_60 = Capteur_60.getDistance();
  Serial.print(mesure_60);
  Serial.print("\t Distance 120° (cm) = ");
  mesure_120 = Capteur_120.getDistance();
  Serial.print(mesure_120);
  Serial.print("\t Distance 180° (cm) = ");
  mesure_180 = Capteur_180.getDistance();
  Serial.print(mesure_180);
  Serial.print("\t Distance 240° (cm) = ");
  mesure_240 = Capteur_240.getDistance();
  Serial.print(mesure_240);
  Serial.print("\t Distance 300° (cm) = ");
  mesure_300 = Capteur_300.getDistance();
  Serial.print(mesure_300);
  tabMesures [0] = mesure_0;
  tabMesures [1] = mesure_60;
  tabMesures [2] = mesure_120;
  tabMesures [3] = mesure_180;
  tabMesures [4] = mesure_240;
  tabMesures [5] = mesure_300;
  Serial.print("\t Dianger le plus proche = ");

  int danger = minVal(tabMesures, nombreCapteurs);
  Serial.println(danger);
}