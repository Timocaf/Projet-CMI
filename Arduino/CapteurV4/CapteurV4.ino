// Utiliser la version 2.0.1 de la bibliothque SharpIR
// Port Analogique 0 et 1 inutilisable
#include <SharpIR.h>
#include <SoftwareSerial.h>

#define RX_BT 15
#define TX_BT 14

int mesure_0 = 0;
int mesure_60 = 0;
int mesure_120 = 0;
int mesure_180 = 0;
int mesure_240 = 0;
int mesure_300 = 0;
int nombreCapteurs = 6;
int * tabMesures = new int[nombreCapteurs]{mesure_0, mesure_60, mesure_120, mesure_180, mesure_240, mesure_300};
int danger;
int bluetooth_value = 0;


SharpIR Capteur_0( SharpIR::GP2Y0A21YK0F, A3 );
SharpIR Capteur_60( SharpIR::GP2Y0A21YK0F, A5 );
SharpIR Capteur_120( SharpIR::GP2Y0A21YK0F, A7 );
SharpIR Capteur_180( SharpIR::GP2Y0A21YK0F, A9 );
SharpIR Capteur_240( SharpIR::GP2Y0A21YK0F, A11 );
SharpIR Capteur_300( SharpIR::GP2Y0A21YK0F, A13 );

SoftwareSerial BTSerial(RX_BT, TX_BT);

int minVal(int tab[], int taille){
  int valMin = tab[0];
  for (int i = 1; i < taille; i++){
    if(valMin > tab[i]){
      valMin = tab[i];
    }
  }
  return valMin;
}

void afficheTableau(int tab[]){
  for(int i = 0; i < nombreCapteurs; i++){
    delay(100);
    Serial.println(tab[i]);
  }
}

int puissance(int exposant, int valeur){
  int result = 1;
  if(exposant == 0){
    return 1;
  }
  for(int i = 0; i < exposant; i++){
    result *= valeur;
  }
  return result;
}

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(500);
  for(int i = 0; i < nombreCapteurs; i++){
    delay(100);
    Serial.println(i);
  }
}

void loop(){
  delay(250);
  //Serial.print("Distance 0° (cm) = ");
  mesure_0 = Capteur_0.getDistance();
  //Serial.print(mesure_0);
  //Serial.print("\t Distance 60° (cm) = ");
  mesure_60 = Capteur_60.getDistance();
  //Serial.print(mesure_60);
  //Serial.print("\t Distance 120° (cm) = ");
  mesure_120 = Capteur_120.getDistance();
  //Serial.print(mesure_120);
  //Serial.print("\t Distance 180° (cm) = ");
  mesure_180 = Capteur_180.getDistance();
  //Serial.print(mesure_180);
  //Serial.print("\t Distance 240° (cm) = ");
  mesure_240 = Capteur_240.getDistance();
  //Serial.print(mesure_240);
  //Serial.print("\t Distance 300° (cm) = ");
  mesure_300 = Capteur_300.getDistance();
  //Serial.print(mesure_300);
  tabMesures [0] = mesure_0;
  tabMesures [1] = mesure_60;
  tabMesures [2] = mesure_120;
  tabMesures [3] = mesure_180;
  tabMesures [4] = mesure_240;
  tabMesures [5] = mesure_300;
  //Serial.print("\t Danger le plus proche = ");

  int danger = minVal(tabMesures, nombreCapteurs);
  //afficheTableau(tabMesures);

  // Bluetooth (si ça marche pas faut taper Ewan)

  bluetooth_value= 0;
  for(int i = 0; i < nombreCapteurs; i++){
    if(11 <= tabMesures[i]){
      bluetooth_value += puissance(i,2);
    }
  }
  if (bluetooth_value < 10){
    BTSerial.print("00"+String(bluetooth_value));  // Pour assurer un retour avec 3 chiffres pour les valeurs en dessous de 100
  }
  else if (bluetooth_value < 100){
    BTSerial.print("0"+String(bluetooth_value));
  }
  else{
     BTSerial.print(bluetooth_value);
  }
 
  Serial.println(bluetooth_value);
}
