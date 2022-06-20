

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
 { 255,5,0,0,0,72,0,16,126,0,1,0,21,11,13,13,131,31,0,1,
  0,9,24,13,13,131,31,0,1,0,33,24,13,13,131,31,0,1,0,21,
  37,13,13,131,31,0,2,0,61,26,33,9,131,2,31,31,66,108,117,101,
  116,111,111,116,104,0,76,105,110,101,70,111,108,108,111,119,101,114,0 };

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  uint8_t button_1; // =1 if button pressed, else =0
  uint8_t button_2; // =1 if button pressed, else =0
  uint8_t button_3; // =1 if button pressed, else =0
  uint8_t button_4; // =1 if button pressed, else =0
  uint8_t switch_1; // =1 if switch ON and =0 if OFF

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
#define in1 3
#define in2 4
#define in3 5
#define in4 6
#define sensorR 7
#define sensorL 8
#define trig 12
#define echo 11
int sr = 0;
int sl = 0;
char readin;
long duration, distance;



void setup()
{
  RemoteXY_Init ();
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(sensorR, INPUT);
  pinMode(sensorL, INPUT);
  pinMode(echo, INPUT);



  // TODO you setup code

}

void loop()
{ if (RemoteXY.switch_1 == 0) {


    Ultrasonic();
    sr = digitalRead(sensorR);
    sl = digitalRead(sensorL);
    if (sl == 0 && sr == 0 && distance > 20) {
      forword();

    }
    else if (sl == 0 && sr == 0 && distance < 20) {
      stoop();

    }
    else if (sl == 0 && sr == 1 && distance > 20) {
      right();

    }
    else if (sl == 0 && sr == 1 && distance < 20) {
      stoop();

    }
    else if (sl == 1 && sr == 0 && distance > 20) {
      left();

    }
    else if (sl == 1 && sr == 0 && distance < 20) {
      stoop();
    }
    else if (sl == 1 && sr == 1) {
      stoop();
    }


  }
  else if (RemoteXY.switch_1 == 1) {
    if (RemoteXY.button_1 == 1) {
      forword();
    }
    else if (RemoteXY.button_2 == 1) {
      left();
    }
    else if (RemoteXY.button_3 == 1) {
      right();
    }
    else if (RemoteXY.button_4 == 1) {
      backword();
    }
    else {
      stoop();
    }
  }
  RemoteXY_Handler ();


  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay()


}  void  Ultrasonic()
{ digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH);
  distance = (duration / 2 ) * 0.0343 ;
}
void forword()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void backword()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void right()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void stoop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
