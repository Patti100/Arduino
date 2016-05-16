#include <Adafruit_NeoPixel.h>

#define soundSensorPin 9
#define PIN 6
#define lightCount 20


//Music from speaker
byte button = 2;
byte speaker=11;
//int val =0;
int C = 1047;
int D = 1175;
int E = 1319;
int F = 1397;
int G = 1568;
int A = 1760;
int B = 1976;
int Quarter = 200;
int Half = 450;


//Buton
int buttonOn= 0;
// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

int ONOFFState = 0;
int RunState=0;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(lightCount, PIN, NEO_GRB + NEO_KHZ800);
int vol = 0;
float total = 0;
int fadeCol = 0;
int val[25];
int volLast = 0;
int fadeAmt = 0;
int counter = 0;

void setup()
{
    pinMode(button, INPUT);
    pinMode(speaker, OUTPUT);
    pinMode(soundSensorPin, INPUT);
  
    // Initialize all pixels to 'off'
    strip.begin();
    strip.show(); 

    //set button on off state to off
    ONOFFState = 0;
    RunState=0;
    Serial.begin(9600);

  }

  void loop()
  {
    buttonState = digitalRead(button);
    if (buttonState != lastButtonState) {
         // if the state has changed, increment the counter
         if (buttonState == HIGH) {
           // if the current state is HIGH then the button
           // wend from off to on:
           buttonPushCounter++;
           //Serial.println("on");
           //Serial.print("number of button pushes:  ");
           //Serial.println(buttonPushCounter);

            if(ONOFFState==0){
              ONOFFState=1;
              RunState=0;
              playsong();  //Button is turned on so play song on speaker
              Serial.println("ONOFFState=on");
            }
            else if(ONOFFState==1){
              ONOFFState=0;
               TurnLEDsOFF();
              Serial.println("ONOFFState=off");
            }
         } else {
           // if the current state is LOW then the button
           // wend from on to off:
           //Serial.println("off");
         }
         // Delay a little bit to avoid bouncing
         delay(50);
      }
       // save the current state as the last state,
       //for next time through the loop
       lastButtonState = buttonState;


       //Handle the LEDs
      if(ONOFFState==1){
        handleLEDs();
      }

       
   }
    

  //play the digital tune from the speaker
  void playsong(){
        digitalWrite(speaker, HIGH);
        song();
        digitalWrite(speaker, LOW);
  }


  void note(int frequency, int NoteDuration)
  {
    tone(speaker, frequency);
    delay(NoteDuration);
    noTone(speaker);
    delay(50);
  }

  void song()
  {
  int ScaleNotes[]={C,D,E,F,G,A,B,2*C};
  int NoteLengths[]={Quarter,Quarter,Quarter,Quarter,Quarter,Quarter,Quarter,Half};
  for(int index=0;index<8;index++)
  {
    note(ScaleNotes[index],NoteLengths[index]);
    } 
  }


  //LEDs
  void handleLEDs(){
        fadeCol = 0;
        total = 0;
      
        for (int i = 0; i < 80; i++){
            counter = 0;
         do{
           vol = digitalRead(soundSensorPin);
       
            counter = counter + 1;
            if (counter > 500){
               rainbowCycle(10);
              
            }
          }while (vol == 0);
          
          total = total + vol;
       
        }
        
        vol = total / 80;
               
        vol = map(vol,20,255,0,20);
        
        
        if (volLast > vol) {
          vol = volLast - 4;
        }
        
        volLast = vol;
        fadeAmt = 0;

        int halfLigthcount = lightCount/2;
        for (int i = 0; i<lightCount;i++){
          if (i < vol){ 
               strip.setPixelColor((i+halfLigthcount), strip.Color(0,255,0));
               strip.setPixelColor((halfLigthcount-i), strip.Color(0,255,0));
          }
          else if (i < (vol + 8)) {
               strip.setPixelColor((i+halfLigthcount), strip.Color(255,0,0));
               strip.setPixelColor((halfLigthcount-i), strip.Color(255,0,0));
          }
          else
          {
              strip.setPixelColor((i+halfLigthcount), strip.Color(0,0,255));
               strip.setPixelColor((halfLigthcount-i), strip.Color(0,0,255));
           }
        }
        strip.show();
    
  }

  

  void TurnLEDsOFF(){
 

     for (int i = 0; i<lightCount;i++){
      strip.setPixelColor(i, strip.Color(0,0,0));
      
     }
     strip.show();
  }

  void TurnLEDsON(){
    
  }
  void rainbowCycle(uint8_t wait) {
      uint16_t i, j;
    
      for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        delay(wait);
         vol = analogRead(A0);
         if (vol> 10) {
          return;
         }
      }
}


//Color wheel
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
     return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if(WheelPos < 170) {
      WheelPos -= 85;
     return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
     WheelPos -= 170;
     return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}
 

