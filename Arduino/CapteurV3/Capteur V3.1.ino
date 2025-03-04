// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <SharpIR.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    7

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 24

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
// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(9600);
  Serial.println("Capteur infrarouge Sharp 10-80 cm");
  
}

uint32_t red = (255,0,0);

void LEDdanger_0(){
  if(mesure_0 <= 30){
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    delay(10);
  }
  else{
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
  }
}
void LEDdanger_60(){
  if(mesure_60 <= 30){
    strip.setPixelColor(1, strip.Color(255, 0, 0));
    strip.show();
    delay(10);
  }
  else{
    strip.setPixelColor(1, strip.Color(0, 255, 0));
    strip.show();
  }
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...


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
  LEDdanger_0();
  LEDdanger_60();

}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.



