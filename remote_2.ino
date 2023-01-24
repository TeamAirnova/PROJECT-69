#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT

#include <ESP8266WiFi.h>
#include <Servo.h>
#define MIN_SIGNAL 1000 // Minimum pulse length in µs ( Pulses )
#define MAX_SIGNAL 2000 // Maximum pulse length in µs

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_WIFI_SSID "Model_69😎"
#define REMOTEXY_WIFI_PASSWORD "airnova69"
#define REMOTEXY_SERVER_PORT 6377

                                                                               
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 45 bytes
  { 255,3,0,0,0,38,0,16,31,1,1,0,13,42,12,12,121,31,0,1,
  0,41,41,12,12,36,31,0,10,48,25,19,15,15,4,26,31,79,78,0,
  31,79,70,70,0 };
 
// this structure defines all the variables and events of your control interface
struct {

    // input variables
  uint8_t button_1; // =1 if button pressed, else =0
  uint8_t button_2; // =1 if button pressed, else =0
  uint8_t pushSwitch_1; // =1 if state is ON, else =0

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 D0
#define PIN_BUTTON_2 D1
#define PIN_PUSHSWITCH_1 D2

Servo motA, motB, motC, motD; // four motors quad copter
char data;


void setup()
{
  Serial.begin(9600);
 
  RemoteXY_Init ();
 
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode (PIN_BUTTON_2, OUTPUT);
  pinMode (PIN_PUSHSWITCH_1, OUTPUT);

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

 
}

void loop()
{
  RemoteXY_Handler ();
//  Serial.println("hii");
  digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1==0)?LOW:HIGH);
  digitalWrite(PIN_BUTTON_2, (RemoteXY.button_2==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_1, (RemoteXY.pushSwitch_1==0)?LOW:HIGH);
  if(RemoteXY.pushSwitch_1 == HIGH)
  {
     

    int Speed =2000;

    motA.writeMicroseconds(Speed);
    motB.writeMicroseconds(Speed);
    motC.writeMicroseconds(Speed);
    motD.writeMicroseconds(Speed);  
    
  }
  else{
    int Speed =0;
    motA.writeMicroseconds(Speed);
    motB.writeMicroseconds(Speed);
    motC.writeMicroseconds(Speed);
    motD.writeMicroseconds(Speed);  
  }
  }
 
