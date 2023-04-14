// inslude the SPI library:
#include <SPI.h>

int CS = 10;
int Contador=0;
// * CS - to digital pin 10  (SS pin)
//  * SDI - to digital pin 11 (MOSI pin)
//  * CLK - to digital pin 13 (SCK pin)

void setup() {
 pinMode (CS, OUTPUT);
 pinMode (2, OUTPUT);pinMode (3, OUTPUT);pinMode (4, OUTPUT);
 pinMode (5, OUTPUT);pinMode (6, OUTPUT);pinMode (7, OUTPUT);
// SE MANDA LAS TIERRAS DE LA MATRIZ A ALTO 
 digitalWrite(2,1);digitalWrite(3,1);digitalWrite(4,1);
 
 /* C O M I E N Z A R U T I N A  C O N C U B O */
 SPI.begin(); 
 SPI.setClockDivider(0x07);
 transfer16bitsSPI(0x04, 0x01); //0x0F, 0x55
 transfer16bitsSPI(0x06, 0xFF); //0x0F, 0x55
 transfer16bitsSPI(0x0B,0x55); //0x0B, 0x55
 transfer16bitsSPI(0x0C,0x55); //0x0C, 0x55
 transfer16bitsSPI(0x0D,0x55); //0x0D, 0x55
 transfer16bitsSPI(0x0E,0x55); //0x0E, 0x55
 transfer16bitsSPI(0x0F,0x55); //0x0F, 0x55
 // Endemos todos los leds
 Clearpines();
}

void loop()
{
 
 int retraso=100;
 for(int k=0; k<=3; k++){
    for(int i=0; i<=15; i++){
        writeCube(i,k, 1);
        delay(50);
    }//for i=0:15
 }//for k=0:3
Minicube();
for(int k=0; k<=3; k++){
  int CAPA;
 transfer16bitsSPI(0x54,0xFF);
 transfer16bitsSPI(0x4C,0xFF);
 CAPA=k+0x3C;
 transfer16bitsSPI(0x5C,0x0F);
 transfer16bitsSPI(CAPA,0x00);
delay(retraso);
}
 Minicube();
 transfer16bitsSPI(0x5C,0x00);
 transfer16bitsSPI(0x54,0x00);
 transfer16bitsSPI(0x4C,0x00);
 
 
 transfer16bitsSPI(0x4C,0x0F);
 delay(retraso);
 transfer16bitsSPI(0x4C,0x00);
 Minicube();
 transfer16bitsSPI(0x4C,0xF0);
 delay(retraso);
 transfer16bitsSPI(0x4C,0x00);
  Minicube();
 transfer16bitsSPI(0x54,0x0F);
 delay(retraso);
 transfer16bitsSPI(0x54,0x00);
  
 transfer16bitsSPI(0x54,0xF0);
 delay(retraso);
 transfer16bitsSPI(0x54,0x00);
 Minicube();
// SECUENCIA 4

 for(int i;i <= 100;i++){
   for (int k=0;k<=3;k++){
    int CAPA;
    transfer16bitsSPI(0x54,0xFF);
    transfer16bitsSPI(0x4C,0xFF);
    //delayMicroseconds(800);
    delay(1);
    CAPA=k+0x3C;
    transfer16bitsSPI(0x5C,0x0F);
    transfer16bitsSPI(CAPA,0x00);
   } 
 }

Minicube();
}// Loop

//  -----------  SUBRUTINAS    --------------------------------

void writeCube(int LED, int CAPA, boolean EDO){
  CAPA=CAPA+0x3C;
 transfer16bitsSPI(0x5C,0x0F);
  //if(LED >= 0 && LED <= 7)
 transfer16bitsSPI(0x4C,0x00);
 //if(LED >= 8 && LED <= 15)
 transfer16bitsSPI(0x54,0x00);
 //Cambio de led
 transfer16bitsSPI(CAPA,0x00);
 writepinExt(LED,EDO);
}

//Esta funcion recibe las siguientes restricciones
// Valor del pin de 1 a 20
// Valor de Edo "0" o "1"
void writepinExt(int Pin,boolean Edo)
{
Pin=Pin+0x2C;
if (Pin <= 0x3F)
{transfer16bitsSPI(Pin,Edo);}
else
{transfer16bitsSPI(0x4C,0x55);}
}
//  ------------ LIMPIA LOS PINES LOS MANDA TODOS A CERO  ----------------
void Clearpines(){
transfer16bitsSPI(0x4C,0x00); 
transfer16bitsSPI(0x54,0x00);
transfer16bitsSPI(0x5C,0x00);
}

//-----------------------  Escribe en el IC MAX7301 por SPI  -------------
void transfer16bitsSPI(int commandbyte,int databyte)
{
 digitalWrite(CS,LOW);
 SPI.transfer(commandbyte);
 SPI.transfer(databyte);
 digitalWrite(CS,HIGH);
 }


void Minicube(){
switch(Contador){
  case 0:
  digitalWrite(2,0);digitalWrite(3,1);digitalWrite(4,1);
  digitalWrite(5,1);digitalWrite(6,1);digitalWrite(7,1);
  break; 
  case 1:
  digitalWrite(2,1);digitalWrite(3,0);digitalWrite(4,1);
  digitalWrite(5,1);digitalWrite(6,1);digitalWrite(7,1);
  break; 
  case 2:
  digitalWrite(2,1);digitalWrite(3,1);digitalWrite(4,0);
  digitalWrite(5,1);digitalWrite(6,1);digitalWrite(7,1);
  break; 
  case 3:
  digitalWrite(2,0);digitalWrite(3,1);digitalWrite(4,0);
  digitalWrite(5,1);digitalWrite(6,1);digitalWrite(7,1);
  break; 
  case 4:
  digitalWrite(2,1);digitalWrite(3,0);digitalWrite(4,0);
  digitalWrite(5,1);digitalWrite(6,0);digitalWrite(7,0);
  break; 
  case 5:
  digitalWrite(2,0);digitalWrite(3,1);digitalWrite(4,0);
  digitalWrite(5,0);digitalWrite(6,1);digitalWrite(7,0);
  break; 
  case 6 :
  digitalWrite(2,0);digitalWrite(3,1);digitalWrite(4,0);
  digitalWrite(5,0);digitalWrite(6,1);digitalWrite(7,0);
  break;  
  default:
  digitalWrite(2,0);digitalWrite(3,1);digitalWrite(4,0);
  digitalWrite(5,0);digitalWrite(6,1);digitalWrite(7,0);
}
Contador=Contador+1;
if (Contador >=7)
{Contador=0;}

}
  
  


