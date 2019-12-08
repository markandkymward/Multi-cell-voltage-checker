/*
OLED connections
GND - GND
VCC - VCC
SDA - Arduino pin A4
SCL - Arduino pin A5 
*/

#include "U8glib.h"
#include <Adafruit_MCP3008.h>

Adafruit_MCP3008 adc1;
Adafruit_MCP3008 adc2;



U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC  // Fast I2C / TWI


#define MOVING_AVERAGE_COUNT 16

unsigned int samples0[MOVING_AVERAGE_COUNT];
unsigned int samples1[MOVING_AVERAGE_COUNT];
unsigned int samples2[MOVING_AVERAGE_COUNT];
unsigned int samples3[MOVING_AVERAGE_COUNT];
unsigned int samples4[MOVING_AVERAGE_COUNT];
unsigned int samples5[MOVING_AVERAGE_COUNT];
unsigned int samples6[MOVING_AVERAGE_COUNT];
unsigned int samples7[MOVING_AVERAGE_COUNT];
unsigned int samples8[MOVING_AVERAGE_COUNT];
unsigned int samples9[MOVING_AVERAGE_COUNT];

int maIndex0 = 0;
int maIndex1 = 0;
int maIndex2 = 0;
int maIndex3 = 0;
int maIndex4 = 0;
int maIndex5 = 0;
int maIndex6 = 0;
int maIndex7 = 0;
int maIndex8 = 0;
int maIndex9 = 0;

int total0 = 0;
int total1 = 0;
int total2 = 0;
int total3 = 0;
int total4 = 0;
int total5 = 0;
int total6 = 0;
int total7 = 0;
int total8 = 0;
int total9 = 0;

void setup() 
{ 
  Serial.begin(9600);
  adc1.begin(4);
  adc2.begin(5);
//  // not really necessary
//  pinMode(A0, INPUT);
//  pinMode(A1, INPUT);
//  pinMode(A2, INPUT);
//  pinMode(A3, INPUT);
  
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_fixed_v0);
  
  memset(samples0, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples1, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples2, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples3, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples4, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples5, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples6, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples7, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples8, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  memset(samples9, 0, MOVING_AVERAGE_COUNT * sizeof(unsigned int));
  
  // fill the moving average buffer before displaying anything, 
  // otherwise numbers will take a few seconds to settle
  for (int i = 0; i < MOVING_AVERAGE_COUNT; i++)
    sample();
}

char vbuf0[16];
char vbuf1[16];
char vbuf2[16];
char vbuf3[16];
char vbuf4[16];
char vbuf5[16];
char vbuf6[16];
char vbuf7[16];
char vbuf8[16];
char vbuf9[16];

void draw10() {
  u8g.setFont(u8g_font_tpssb);
  u8g.drawStr(30,12,"CELL VOLTS");
  u8g.setFont(u8g_font_fixed_v0);
  int base = 26;
  int offset = 9;
  u8g.drawStr( 2, base, vbuf0);
  u8g.drawStr( 2, base+(1*offset), vbuf1);
  u8g.drawStr( 2, base+(2*offset), vbuf2);
  u8g.drawStr( 2, base+(3*offset), vbuf3);
  u8g.drawStr( 2, base+(4*offset), vbuf4); 
  u8g.drawStr( 66, base+(0*offset), vbuf5);
  u8g.drawStr( 66, base+(1*offset), vbuf6);
  u8g.drawStr( 66, base+(2*offset), vbuf7);
  u8g.drawStr( 66, base+(3*offset), vbuf8);
  u8g.drawStr( 66, base+(4*offset), vbuf9);
}

void draw9() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
  u8g.drawStr( 2, 36, vbuf2);
  u8g.drawStr( 2, 48, vbuf3);
  u8g.drawStr( 2, 60, vbuf4); 
  u8g.drawStr( 66, 12, vbuf5);
  u8g.drawStr( 66, 24, vbuf6);
  u8g.drawStr( 66, 36, vbuf7);
  u8g.drawStr( 66, 48, vbuf8);
}
void draw8() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
  u8g.drawStr( 2, 36, vbuf2);
  u8g.drawStr( 2, 48, vbuf3);
  u8g.drawStr( 2, 60, vbuf4); 
  u8g.drawStr( 66, 12, vbuf5);
  u8g.drawStr( 66, 24, vbuf6);
  u8g.drawStr( 66, 36, vbuf7);
}

void draw7() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
  u8g.drawStr( 2, 36, vbuf2);
  u8g.drawStr( 2, 48, vbuf3);
  u8g.drawStr( 2, 60, vbuf4); 
  u8g.drawStr( 66, 12, vbuf5);
  u8g.drawStr( 66, 24, vbuf6);
}
void draw6() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
  u8g.drawStr( 2, 36, vbuf2);
  u8g.drawStr( 2, 48, vbuf3);
  u8g.drawStr( 2, 60, vbuf4); 
  u8g.drawStr( 66, 12, vbuf5);
}

void draw5() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
  u8g.drawStr( 2, 36, vbuf2);
  u8g.drawStr( 2, 48, vbuf3);
  u8g.drawStr( 2, 60, vbuf4); 
}
void draw4() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
  u8g.drawStr( 2, 36, vbuf2);
  u8g.drawStr( 2, 48, vbuf3);
}

void draw3() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
  u8g.drawStr( 2, 36, vbuf2);
}

void draw2() {
  u8g.drawStr( 2, 12, vbuf0);
  u8g.drawStr( 2, 24, vbuf1);
}

unsigned long lastScreenUpdate = 0;

#define DO_MOVING_AVERAGE(which)\
  total##which -= samples##which[ maIndex##which ];\
  samples##which[ maIndex##which ] = adc1.readADC(which);\
  total##which += samples##which[ maIndex##which ];\
  maIndex##which = (maIndex##which + 1) % MOVING_AVERAGE_COUNT;

#define DO_MOVING_AVERAGE_2(which)\
  total##which -= samples##which[ maIndex##which ];\
  samples##which[ maIndex##which ] = adc2.readADC(which-8);\
  total##which += samples##which[ maIndex##which ];\
  Serial.println(samples##which[ maIndex##which ]);\
  maIndex##which = (maIndex##which + 1) % MOVING_AVERAGE_COUNT;

void sample()
{  
  DO_MOVING_AVERAGE(0)
  DO_MOVING_AVERAGE(1)
  DO_MOVING_AVERAGE(2)
  DO_MOVING_AVERAGE(3)
  DO_MOVING_AVERAGE(4)
  DO_MOVING_AVERAGE(5)
  DO_MOVING_AVERAGE(6)
  DO_MOVING_AVERAGE(7)
  DO_MOVING_AVERAGE_2(8)
  DO_MOVING_AVERAGE_2(9)
}

void updateScreen() 
{
  unsigned long now = millis();
  if ( now - lastScreenUpdate < 300 )
    return;
    
  sample();
    
  float v0 = 5 * (total0 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v1 = 5 * (total1 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v2 = 5 * (total2 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v3 = 5 * (total3 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v4 = 5 * (total4 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v5 = 5 * (total5 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v6 = 5 * (total6 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v7 = 5 * (total7 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v8 = 5 * (total8 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  float v9 = 5 * (total9 / (float)MOVING_AVERAGE_COUNT) / 1023.0f;
  
  //Serial.println(total2) ; 
  // set these to your resistor actual values
  float r11 =  1006;
  float r12 =  998;
  float r21 =  1950;
  float r22 = 1005;
  float r31 =  2970;
  float r32 = 1003;
  float r41 =  4710;
  float r42 =  1199;
  float r51 =  14920;
  float r52 =  2980;
  float r61 =  17930;
  float r62 =  2960;
  float r71 =  75500;
  float r72 =  9860;
  float r81 =  81800;
  float r82 =  9870;
  float r91 =  29900;
  float r92 =  3000;
  
    
  v0 *= 1;
  v1 *= (r11 + r12) / r12;
  v2 *= (r21 + r22) / r22;
  v3 *= (r31 + r32) / r32;
  v4 *= (r41 + r42) / r42;
  v5 *= (r51 + r52) / r52;
  v6 *= (r61 + r62) / r62;
  v7 *= (r71 + r72) / r72;
  v8 *= (r81 + r82) / r82;
  v9 *= (r91 + r92) / r92;
  
  // adjust to match your voltmeter results
  v0 *= .9914;
  v1 *= .9872;
  v2 *= .9895;
  v3 *= .9900;
  v4 *= .9880;
  v5 *= .9886;
  v6 *= .9854;
  v7 *= .9932;
  v8 *= .9892;
  v9 *= .9869;
  
//  
  v9 -= v8;
  v8 -= v7;
  v7 -= v6;
  v6 -= v5;
  v5 -= v4;
  v4 -= v3;
  v3 -= v2;
  v2 -= v1;
  v1 -= v0;
    
  int whole0 = (int)v0;
  int whole1 = (int)v1;
  int whole2 = (int)v2;
  int whole3 = (int)v3;
  int whole4 = (int)v4;
  int whole5 = (int)v5;
  int whole6 = (int)v6;
  int whole7 = (int)v7;
  int whole8 = (int)v8;
  int whole9 = (int)v9;
  
  int fraction0 = (v0 * 100) - (whole0 * 100);
  int fraction1 = (v1 * 100) - (whole1 * 100);
  int fraction2 = (v2 * 100) - (whole2 * 100);
  int fraction3 = (v3 * 100) - (whole3 * 100);
  int fraction4 = (v4 * 100) - (whole4 * 100);
  int fraction5 = (v5 * 100) - (whole5 * 100);
  int fraction6 = (v6 * 100) - (whole6 * 100);
  int fraction7 = (v7 * 100) - (whole7 * 100);
  int fraction8 = (v8 * 100) - (whole8 * 100);
  int fraction9 = (v9 * 100) - (whole9 * 100);
  
  sprintf(vbuf0, "v0: %d.%02d", whole0, fraction0);
  sprintf(vbuf1, "v1: %d.%02d", whole1, fraction1);
  sprintf(vbuf2, "v2: %d.%02d", whole2, fraction2);
  sprintf(vbuf3, "v3: %d.%02d", whole3, fraction3);
  sprintf(vbuf4, "v4: %d.%02d", whole4, fraction4);
  sprintf(vbuf5, "v5: %d.%02d", whole5, fraction5);
  sprintf(vbuf6, "v6: %d.%02d", whole6, fraction6);
  sprintf(vbuf7, "v7: %d.%02d", whole7, fraction7);
  sprintf(vbuf8, "v8: %d.%02d", whole8, fraction8);
  sprintf(vbuf9, "v9: %d.%02d", whole9, fraction9);

//  Serial.println("\rv0:" + String(v0));
//  Serial.println("\rv1:" + String(v1));
//  Serial.println("\rv2:" + String(v2));
//  Serial.println("\rv3:" + String(v3));

  u8g.firstPage();
  
do{
  draw10();
}
  while(u8g.nextPage());
//  if ( v3 >= 0 && v2 >= 0 ) {
//    do {
//      draw4();
//    } 
//    while( u8g.nextPage() );
//  }
//  else if ( v2 >= 0 ) {
//    do {
//      draw3();
//    } 
//    while( u8g.nextPage() );
//  }
//  else {
//    do {
//      draw2();
//    } 
//    while( u8g.nextPage() );
//  }
//  
//  lastScreenUpdate = millis();  
//
//
}

void loop()
{
  updateScreen();
}
