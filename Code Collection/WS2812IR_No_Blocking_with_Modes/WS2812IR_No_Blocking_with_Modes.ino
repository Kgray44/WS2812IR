bool testIR = false;//true or false

#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define modeAmount 5
#define hueinc 1000
#define brightinc 20

#define RECV_PIN  3
#define PIN       2
#define NUMPIXELS 180

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

unsigned long hue = 0;

int bright = 127;
int modecount = 0;
bool mode = false;
bool on = true;
bool update = true;
int currentpixel=0;
bool first = true;
int section = 1;
bool flash = false;
int t=1;
int d=1;
int p=1;
unsigned long firstpixelhue=0;

struct structu {
  int value=0;
  int lastm=0;
  int timeb=0;
  int number=0;
  bool rising=true;
};
structu pixelF[15];
int pc=0;

unsigned long lastmillis=0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn();
  irrecv.blink13(true);

  pixels.begin();
}

void loop() {
  listenIR();
  takeStep();
}

void listenIR() {
  if (irrecv.decode()) {
    handleKey();
    irrecv.resume();  // Receive the next value
  }
}

void takeStep(){
  if (on){
    pixels.setBrightness(bright);
    if (!mode){
      if (update){
        pixels.fill(pixels.gamma32(pixels.ColorHSV(hue)),0,NUMPIXELS);
        pixels.show();
        update=false;
      }
    }
    else {
      if (modecount == 0){
        if (millis() - lastmillis > 300){
          if (first){
            currentpixel=currentpixel+6;
            pixels.fill(pixels.gamma32(pixels.ColorHSV(hue)),currentpixel,currentpixel+3);
            pixels.fill(pixels.Color(0,0,0),currentpixel+3,currentpixel+6);
            if (currentpixel >= NUMPIXELS){
              pixels.show();
              currentpixel=0;
              first = false;
              lastmillis = millis();
            }
          }
          else {
            currentpixel=currentpixel+6;
            pixels.fill(pixels.Color(0,0,0),currentpixel,currentpixel+3);
            pixels.fill(pixels.gamma32(pixels.ColorHSV(hue)),currentpixel+3,currentpixel+6);
            if (currentpixel >= NUMPIXELS){
              pixels.show();
              currentpixel=0;
              first = true;
              lastmillis = millis();
            }
          }
        }
      }
      else if (modecount == 1){
        if (millis() - lastmillis > 200){
          if (section == 1){
            currentpixel=currentpixel+3;
            pixels.setPixelColor(currentpixel,pixels.gamma32(pixels.ColorHSV(hue)));
            pixels.setPixelColor(currentpixel-1,pixels.Color(0,0,0));
            if (currentpixel >= NUMPIXELS){
              pixels.show();
              currentpixel=1;
              section = 2;
              lastmillis = millis();
            }
          }
          else if (section == 2){
            currentpixel=currentpixel+3;
            pixels.setPixelColor(currentpixel,pixels.gamma32(pixels.ColorHSV(hue)));
            pixels.setPixelColor(currentpixel-1,pixels.Color(0,0,0));
            if (currentpixel >= NUMPIXELS){
              pixels.show();
              currentpixel=2;
              section = 3;
              lastmillis = millis();
            }
          }
          else {
            currentpixel=currentpixel+3;
            pixels.setPixelColor(currentpixel,pixels.gamma32(pixels.ColorHSV(hue)));
            pixels.setPixelColor(currentpixel-1,pixels.Color(0,0,0));
            if (currentpixel >= NUMPIXELS){
              pixels.show();
              currentpixel=0;
              section = 1;
              lastmillis = millis();
            }
          }
        }
      }
      else if (modecount == 2){
        if (millis() - lastmillis > t && !flash){
          pixels.setPixelColor(p,pixels.Color(255,255,255));
          pixels.show();
          flash = true;
          lastmillis = millis();
        }
        else if (millis() - lastmillis > d && flash){
          pixels.setPixelColor(p,pixels.Color(0,0,0));
          pixels.show();
          flash = false;
          lastmillis = millis();
          t = random(10,500);
          d = random(4,30);
          p = random(0,NUMPIXELS);
        }
      }
      else if (modecount == 3){
        if (millis() - lastmillis > 5){
          currentpixel++;
          int pixelHue = firstpixelhue + (currentpixel * 65536L / NUMPIXELS);
          pixels.setPixelColor(currentpixel,pixels.ColorHSV(pixelHue));
          if (currentpixel >= NUMPIXELS){
            pixels.show();
            currentpixel=0;
            firstpixelhue=firstpixelhue+256;
            lastmillis = millis();
          }
        }
      }
      else if (modecount == 4){
        pc++; if (pc>10){pc=0;}
        if (millis() - pixelF[pc].lastm > pixelF[pc].timeb){
          if (pixelF[pc].rising==true){
            pixelF[pc].value=pixelF[pc].value+10;
            pixels.setPixelColor(pixelF[pc].number, pixels.Color(pixelF[pc].value,pixelF[pc].value,map(pixelF[pc].value,0,255,0,80)));
            pixels.show();
            if (pixelF[pc].value >= 250){
              pixelF[pc].value=250;
              pixels.setPixelColor(pixelF[pc].number, pixels.Color(pixelF[pc].value,pixelF[pc].value,map(pixelF[pc].value,0,255,0,80)));
              pixels.show();
              pixelF[pc].timeb=random(50,1000);
              pixelF[pc].lastm=millis();
              pixelF[pc].rising=false;
            }
          }
          else {
            pixelF[pc].value=pixelF[pc].value-10;
            pixels.setPixelColor(pixelF[pc].number, pixels.Color(pixelF[pc].value,pixelF[pc].value,map(pixelF[pc].value,0,255,0,80)));
            pixels.show();
            if (pixelF[pc].value <= 0){
              pixelF[pc].value=0;
              pixels.setPixelColor(pixelF[pc].number, pixels.Color(0,0,0));
              pixels.show();
              pixelF[pc].timeb=random(1000,14000);
              pixelF[pc].lastm=millis();
              pixelF[pc].rising=true;
              pixelF[pc].number=random(0,NUMPIXELS);
            }
          }
        }
      }
    }
  }
  else {
    if (update){
      clear();
      update=false;
    }
  }
}

void clear(){
  pixels.fill(pixels.Color(0,0,0),0,NUMPIXELS);
  pixels.show();
}

void handleKey() {
  uint16_t command;
  if (irrecv.decodedIRData.protocol == 7 && !testIR){
    command = irrecv.decodedIRData.command;
  }
  if (testIR){
    Serial.println(command);
    return;
  }
  Serial.println("Protocol:" + String(irrecv.decodedIRData.protocol));

  switch (command) {
    case 0:  Serial.println("POWER");  update=true;currentpixel=0;on = !on; break;
    case 1:  Serial.println("VOL+");   update=true;bright+=brightinc;if(bright>255){bright=255;} break;
    case 2:  Serial.println("FUNC.");  update=true;clear();mode = !mode; break;
    case 4:  Serial.println("BACK");   update=true;if (mode){clear();modecount--;if(modecount<0){modecount=modeAmount-1;}}else{hue-=hueinc;if(hue<0){hue=65536;}} break;
    case 5:  Serial.println("PLAY");   break;
    case 6:  Serial.println("NEXT");   update=true;if (mode){clear();modecount++;if(modecount>modeAmount-1){modecount=0;}}else{hue+=hueinc;if(hue>65536){hue=0;}} break;
    case 8:  Serial.println("DOWN");   break;
    case 9:  Serial.println("VOL-");   update=true;bright-=brightinc;if(bright<0){bright=0;} break;
    case 10: Serial.println("UP");     break;
    case 12: Serial.println("num: 0"); break;
    case 13: Serial.println("EQ");     break;
    case 14: Serial.println("REPT.");  break;
    case 16: Serial.println("num: 1"); break;
    case 17: Serial.println("num: 2"); break;
    case 18: Serial.println("num: 3"); break;
    case 20: Serial.println("num: 4"); break;
    case 21: Serial.println("num: 5"); break;
    case 22: Serial.println("num: 6"); break;
    case 24: Serial.println("num: 7"); break;
    case 25: Serial.println("num: 8"); break;
    case 26: Serial.println("num: 9"); break;
    default: Serial.println(command);  break;
  }
}
