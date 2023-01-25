// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>
#include <Servo.h>
#define MIN_SIGNAL 1000 // Minimum pulse length in µs ( Pulses )
#define MAX_SIGNAL 2000 // Maximum pulse length in µs
#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 35 bytes
  { 255,2,0,0,0,28,0,16,31,0,2,0,37,11,22,11,2,26,31,31,
  79,78,0,79,70,70,0,4,128,6,32,88,9,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  int8_t slider_1; // =0..100 slider position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 D0
#define SLIDER_1 D1
Servo motA, motB, motC, motD; // four motors quad copter
char data;


void setup() 
{
  Serial.begin(9600);
  RemoteXY_Init (); 
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode (SLIDER_1 , OUTPUT);
  
  delay(1000);
  Serial.println("Starting..");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
  motA.attach(14);
  motB.attach(12);
  motC.attach(0);
  motD.attach(13);
  
  Serial.print("Maximum output in uS : " );
  Serial.print(MAX_SIGNAL);
  Serial.print("\n");

  motA.writeMicroseconds(MAX_SIGNAL);
  motA.writeMicroseconds(MIN_SIGNAL);
  delay(1500);
  motB.writeMicroseconds(MAX_SIGNAL);
  motB.writeMicroseconds(MIN_SIGNAL);
  delay(1500);
  motC.writeMicroseconds(MAX_SIGNAL);
  motC.writeMicroseconds(MIN_SIGNAL);
  delay(1500);
  motD.writeMicroseconds(MAX_SIGNAL);
  motD.writeMicroseconds(MIN_SIGNAL);
  
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();

  Serial.println("hii");
  digitalWrite(PIN_BUTTON_1, (RemoteXY.switch_1==0)?LOW:HIGH);
//  digitalWrite(PIN_PUSHSWITCH_1, (RemoteXY.pushSwitch_1==0)?LOW:HIGH);
   if(RemoteXY.slider_1 > 0 )
  {
     

    int Speed =10*RemoteXY.slider_1+1000;

    motA.writeMicroseconds(Speed);
    motB.writeMicroseconds(Speed);
    motC.writeMicroseconds(Speed);
    motD.writeMicroseconds(Speed);  
    
  }
   else
  {
    Serial.print("code is in else loop") 
    int Speed=0;

    motA.writeMicroseconds(Speed);
    motB.writeMicroseconds(Speed);
    motC.writeMicroseconds(Speed);
    motD.writeMicroseconds(Speed);  
    
  }

 

  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
