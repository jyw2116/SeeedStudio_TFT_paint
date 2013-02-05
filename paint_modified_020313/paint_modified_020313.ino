// Paint application - Demonstate both TFT and Touch Screen
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include <stdint.h>
#include <TouchScreen.h> 
#include <TFT.h>

#ifdef SEEEDUINO
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 14   // can be a digital pin, this is A0
  #define XP 17   // can be a digital pin, this is A3 
#endif

#ifdef MEGA
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 54   // can be a digital pin, this is A0
  #define XP 57   // can be a digital pin, this is A3 
#endif 

//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1

#define TS_MINX 140 
#define TS_MAXX 900
#define TS_MINY 120
#define TS_MAXY 940
#define PAL_WIDTH 20

int color = WHITE;  //Paint brush color

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //init TouchScreen port pins

void setup()
{

Tft.init();  //init TFT library
pinMode(0,OUTPUT);

//Draw the pallet
Tft.fillRectangle(0,0,30,PAL_WIDTH,ORANGE); 
Tft.fillRectangle(30,0,30,PAL_WIDTH,RED);
Tft.fillRectangle(60,0,30,PAL_WIDTH,GREEN);
Tft.fillRectangle(90,0,30,PAL_WIDTH,BLUE);
Tft.fillRectangle(120,0,30,PAL_WIDTH,CYAN);
Tft.fillRectangle(150,0,30,PAL_WIDTH,YELLOW);
Tft.fillRectangle(180,0,30,PAL_WIDTH,WHITE);
Tft.fillRectangle(210,0,30,PAL_WIDTH,PINK);

//Draw the CLEAR ALL Button
Tft.fillRectangle(0, 290, 30, 30, WHITE);
//void drawChar(unsigned char ascii,unsigned int poX, unsigned int poY,unsigned int size, unsigned int fgcolor)
Tft.drawChar(88,0,290,4.5,BLACK);  
}


void loop()
{
  
  // a point object holds x y and z coordinates.
  Point p = ts.getPoint();

  //map the ADC value read to into pixel co-ordinates

  p.x = map(p.x, TS_MINX, TS_MAXX, 240, 0);
  p.y = map(p.y, TS_MINY, TS_MAXY, 320, 0);
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > ts.pressureThreshhold) {
  
 
 // Detect paint brush color change
 if(p.y < PAL_WIDTH)
  {
    if(p.x >= 0 && p.x < 30)
    {
      color = ORANGE;
    }
    if(p.x >= 30 && p.x < 60)
    {
      color = RED;
      digitalWrite(0,HIGH);
    }
    if(p.x >= 60 && p.x < 90)
    {
      color = GREEN;
    }
    if(p.x >= 90 && p.x < 110)
    {
      color = BLUE;
      digitalWrite(0,LOW);
    }
    if(p.x >= 120 && p.x < 150)
    {
      color = CYAN;
    }
    if(p.x >= 150 && p.x < 180)
    {
      color = YELLOW;
    }
    if(p.x >= 180 && p.x < 210)
    {
      color = WHITE;
    }
    if(p.x >= 210 && p.x < 240)
    {
      color = PINK;
    }    
  }
  
  else if (p.y >= 290 && p.y <320 && p.x >= 0 && p.x <= 30)
  {
    setup();
  }
  
  else    
  {
      Tft.fillCircle(p.x,p.y,2,color);
  }
     
 }

}
