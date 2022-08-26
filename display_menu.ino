#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <FastLED.h>

#define OLED_SDA 21
#define OLED_SCL 22
#define BUTTON_PIN 36 // GIOP21 pin connected to button


int lastState = HIGH; // the previous state from the input pin
int currentState;     // the current reading from the input pin

volatile unsigned long counter=0;
volatile unsigned long previousMillis_tempAQI = 0;        
const long interval_tempAQI = 3000;
int tempAQI_state=0;


volatile int adelay=0;
short dis_flag=1;

volatile short modes=1;

Adafruit_SH1106 display(21, 22);






void purifier(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,25);
  display.println("PURIFIER");
  display.display();
  }
  
void autos(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(35,25);
  display.println("AUTOS");
  display.display();
  }
  
void silent(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,25);
  display.println("SILENT");
  display.display();  
  
  }
  
void standby(){
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,25);
  display.println("STANDBY");
  display.display();
  }




//************************************



//menu 
void menu(void){
while(adelay<=50){
adelay++;
if( button()==1)
{
display.clearDisplay();
adelay=0;
modes++;
if(modes>4)
{
modes=1;
} 
//write(6,modes);
}
switch (modes){
case 1:purifier();
break;
case 2: autos();
break;
case 3:silent();
break;
case 4: standby();
break;  
}
}
display.clearDisplay();
tempAQI_state=0;
dis_flag=1;
}
//************************************


void corsa(void){
adelay=0;
if(button()==1)
{
dis_flag=2; 
display.clearDisplay();
}
switch (dis_flag){
case 1: device_home();
adelay=0;
break;
case 2: menu();
break;
}
}






//####################################################################
int button(){
  
    currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH){
    lastState = currentState;
    return(1);
     // save the last state
  
  }
else{
  lastState = currentState;
 return(0);
}
  // save the last state
  //lastState = currentState;
  
  }
//####################################################################



void AQI(){


  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(28,25);
  display.println("AQI:24");
  display.display();
  display.clearDisplay();
  
  }



void TEMP(){


  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25,25);
  display.println("TEMP:30");
  display.display();
  display.clearDisplay();
  
  }



  

void setup()   {                
  Serial.begin(115200);
  /* initialize OLED with I2C address 0x3C */
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();

   pinMode(BUTTON_PIN, INPUT_PULLUP);

}
void loop() { 

corsa();

}








void device_home(void){
volatile unsigned long currentMillis_tempAQI = millis();
if (currentMillis_tempAQI - previousMillis_tempAQI >= interval_tempAQI) {
previousMillis_tempAQI = currentMillis_tempAQI;
if (tempAQI_state == 0){
 display.clearDisplay();
AQI();

tempAQI_state = 1;
}
else{
TEMP();

tempAQI_state = 0;
}
}
}
