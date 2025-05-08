// Utiliser la version 2.0.1 de la bibliothque SharpIR
// Port Analogique 0 et 1 inutilisable
#include <Wire.h>
#include <SharpIR.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    7

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 35

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


#define RX_BT 15
#define TX_BT 14

int mesure_0 = 0;
int mesure_45 = 0;
int mesure_90 = 0;
int mesure_135 = 0;
int mesure_180 = 0;
int mesure_225 = 0;
int mesure_270 = 0;
int mesure_315 = 0;
const int nombreCapteurs = 8;
int * tabMesures = new int[nombreCapteurs]{mesure_0, mesure_45, mesure_90, mesure_135, mesure_180, mesure_225, mesure_270, mesure_315};
/*int tab_save_last_value[nombreCapteurs]{0};   ancien système pour les valeurs bluetooth
int tab_save_last_value2[nombreCapteurs]{0};
int tabMesures_with_average[nombreCapteurs]{0};
*/
int danger;
int bluetooth_value = 0;
uint8_t tabForWheel[nombreCapteurs]{0};
unsigned long currentMillis;
unsigned long  previousMillis;
unsigned long interval = 500;


SharpIR Capteur_0( SharpIR::GP2Y0A21YK0F, A1 );
SharpIR Capteur_45( SharpIR::GP2Y0A21YK0F, A3 );
SharpIR Capteur_90( SharpIR::GP2Y0A21YK0F, A5 );
SharpIR Capteur_135( SharpIR::GP2Y0A21YK0F, A7 );
SharpIR Capteur_180( SharpIR::GP2Y0A21YK0F, A9 );
SharpIR Capteur_225( SharpIR::GP2Y0A21YK0F, A11 );
SharpIR Capteur_270( SharpIR::GP2Y0A21YK0F, A13 );
SharpIR Capteur_315( SharpIR::GP2Y0A21YK0F, A15 );

SoftwareSerial BTSerial(RX_BT, TX_BT);

/*int minVal(int tab[], int taille){    obselete
  int valMin = tab[0];
  for (int i = 1; i < taille; i++){
    if(valMin > tab[i]){
      valMin = tab[i];
    }
  }
  return valMin;
}*/

void afficheTableau(int tab[]){
  for(int i = 0; i < nombreCapteurs; i++){
    Serial.print(tab[i]);
    if(i+1 < nombreCapteurs){
      Serial.print(",");
    }
  }
  Serial.println();
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

/*void calculAverage(int* tab1, int* tab2, int* tab3, int* destination, int nombreCapteurs) {       ancien système bluetooth
  for (int i = 0; i < nombreCapteurs; i++) {
    destination[i] = (tab1[i] + tab2[i] + tab3[i]) / 3;
    tab1[i] = tab2[i];
    tab2[i] = tab3[i];
  }
}*/

void calculArrayWheel(int TabInt[], uint8_t TabForWheel[], int nombreCapteurs){
  for(uint8_t i = 0; i < nombreCapteurs; i++){
    TabForWheel[i] = (uint8_t)TabInt[i];
  }
}

void onI2CRequest() {
  calculArrayWheel(tabMesures,tabForWheel,nombreCapteurs);
  Wire.write(tabForWheel, nombreCapteurs);
}

void LEDdanger(int * tab, int nb_cap){
  int tab_pix_start[nb_cap] = {0,6,12,16,20,24,28};
  int tab_pix_neon[nb_cap] = {6,6,4,4,4,4,4,6}
 for(int i = 0; i < nb_cap; i++){
   if(tab[i] <= 30){
     for(int j = 0; j < tab_pix_neon[i]; j++){
       strip.setPixelColor(j + tab_pix_start[i], strip.Color(255, 0, 0));
       strip.show();
       delay(10);
     }
   }
   else{
     for(int j = 0; j < tab_pix_neon[i]; j++){
       strip.setPixelColor(j + tab_pix_start[i], strip.Color(0, 255, 0));
       strip.show();
     }
   }
 }
}

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(500);
  for(int i = 0; i < nombreCapteurs; i++){
    delay(100);
    Serial.println(i);
  Wire.begin(0x42);
  Wire.onRequest(onI2CRequest);
  }
}

void loop(){
  mesure_0 = Capteur_0.getDistance();
  mesure_45 = Capteur_45.getDistance();
  mesure_90 = Capteur_90.getDistance();
  mesure_135 = Capteur_135.getDistance();
  mesure_180 = Capteur_180.getDistance();
  mesure_225 = Capteur_225.getDistance();
  mesure_270 = Capteur_270.getDistance();
  mesure_315 = Capteur_315.getDistance();
  tabMesures [0] = mesure_0;
  tabMesures [1] = mesure_45;
  tabMesures [2] = mesure_90;
  tabMesures [3] = mesure_135;
  tabMesures [4] = mesure_180;
  tabMesures [5] = mesure_225;
  tabMesures [6] = mesure_270;
  tabMesures [7] = mesure_315;

  //int danger = minVal(tabMesures, nombreCapteurs); obselete
  afficheTableau(tabMesures);
  LEDdanger(tabMesures, nombreCapteurs);

  // Bluetooth (si ça marche pas faut taper Ewan)
  //calculAverage(tab_save_last_value, tab_save_last_value2, tabMesures, tabMesures_with_average, nombreCapteurs);    ancien système bluetooth

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      bluetooth_value = 0;
      for(int i = 0; i < nombreCapteurs; i++){
        if(tabMesures[i] < 30){                 //30 représente le seuil de distance pour la partie roue du projet
          bluetooth_value += puissance(i,2);    //chaque capteur est associé à une puissance de 2 dans l'application bluetooth
        }
      }
      if (bluetooth_value < 10){
        BTSerial.print("00"+String(bluetooth_value));  // Pour assurer un retour avec 3 chiffres pour les valeurs en dessous de 100
      }
      else if (bluetooth_value < 100){
        BTSerial.print("0"+String(bluetooth_value));  //same
      }
      else{
        BTSerial.print(bluetooth_value);
      }
      previousMillis = currentMillis;
  }
}
