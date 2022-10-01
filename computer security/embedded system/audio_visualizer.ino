#include <arduinoFFT.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

MD_MAX72XX disp = MD_MAX72XX(MD_MAX72XX::FC16_HW, 10, 4);
arduinoFFT FFT = arduinoFFT();
double realComponent[64];
double imagComponent[64];

//int spectralHeight[] = {0b00000000,0b10000000,0b11000000,
//                        0b11100000,0b11110000,0b11111000,
//                        0b11111100,0b11111110,0b11111111};
                        
int spectralHeight[] = {0b00000000,0b00000001,0b00000011,
                        0b00000111,0b00001111,0b00011111,
                        0b00111111,0b01111111,0b11111111};
int index, c, value;
void setup()
{
  disp.begin();
  Serial.begin(9600);
}

void loop()
{
  int sensitivity = map(analogRead(A6),0,1023,50,100); //0~1024)->50~100
  //Serial.println (sensitivity);
  for(int i=0; i<64; i++)
  {
    realComponent[i] = analogRead(A7)/sensitivity;
    Serial.println(analogRead(A7));
    imagComponent[i] = 0;
  }
  FFT.Windowing(realComponent, 64, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(realComponent, imagComponent, 64, FFT_FORWARD);
  FFT.ComplexToMagnitude(realComponent, imagComponent, 64);
  for(int i=0; i<32; i++)
  {
    realComponent[i] = constrain(realComponent[i],0,80);  //限制在0~80
    realComponent[i] = map(realComponent[i],0,80,0,8);
    index = realComponent[i];
    value = spectralHeight[index];
//    c = 31 - i;
    disp.setColumn(i, value);
  }
}
