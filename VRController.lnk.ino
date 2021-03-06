/*
Really crappy code not recommended to copy. 

A0 = x accel1
A1 = y accel1
A2 = z accel1
A4 = x accel2
A5 = y accel2
13 = sleep accel2
accel 2 11 && 12 && 3v not connected to save kabel space
*/

//Accel 2 parameters
#include <AcceleroMMA7361.h>

AcceleroMMA7361 accelero;
int x;
int y;
int z;

// accel 1 parameters
#define ADC_ref 2.56
#define zero_x 1.569
#define zero_y 1.569
#define zero_z 1.569
#define sensitivity_x 0.3
#define sensitivity_y 0.3
#define sensitivity_z 0.3

unsigned int value_x;
unsigned int value_y;
unsigned int value_z;

float xv;
float yv;
float zv;

float angle_x;
float angle_y;
float angle_z;

void setup()
{
  Serial.begin(9600);
  setupAccel1();
  setupAccel2();

  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  
    
  digitalWrite(1, HIGH);
}

void setupAccel2() {
  accelero.begin(13, 12, 11, 10, A4, A5, A6);
  accelero.setARefVoltage(5);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(HIGH);                   //sets the sensitivity to +/-6G
  accelero.calibrate();
}

void setupAccel1() {
  analogReference(INTERNAL2V56);
}

void accel1() {
value_x = analogRead(0);
value_y = analogRead(1);
value_z = analogRead(2);

xv=(value_x/1024.0*ADC_ref-zero_x)/sensitivity_x;

Serial.print ("x= ");
Serial.print (xv);
Serial.print(" g ");

yv=(value_y/1024.0*ADC_ref-zero_y)/sensitivity_y;

Serial.print ("y= ");
Serial.print (yv);
Serial.print(" g ");

zv=(value_z/1024.0*ADC_ref-zero_z)/sensitivity_z;

Serial.print ("z= ");
Serial.print (zv);
Serial.print(" g ");

Serial.print("\n");

Serial.print("Rotation ");

Serial.print("x= ");

angle_x =atan2(-yv,-zv)*57.2957795+180;

Serial.print(angle_x);
Serial.print(" deg");
Serial.print(" ");

Serial.print("y= ");

angle_y =atan2(-xv,-zv)*57.2957795+180;

Serial.print(angle_y);
Serial.print(" deg");
Serial.print(" ");

Serial.print("z= ");

angle_z =atan2(-yv,-xv)*57.2957795+180;

Serial.print(angle_z);
Serial.print(" deg");
Serial.print("\n");


Joystick.button(1, 1);
Joystick.X(value_x - 148); // 148 to correct for faulty accelerometer
Joystick.Y(value_y - 148); // 148 to correct for faulty accelerometer
Serial.println(value_x);
Serial.println("break");
Serial.println(value_y);
/*
if(value_x > 700) {
  digitalWrite(0, HIGH);
  Keyboard.release('w');
  Keyboard.press('a');
  Keyboard.release('s');
  Keyboard.release('d');
} else if(value_x < 570) {
  digitalWrite(0, HIGH);
  Keyboard.release('w');
  Keyboard.release('a');
  Keyboard.release('s');
  Keyboard.press('d');
} else if(value_y > 720) {
  digitalWrite(0, HIGH);
  Keyboard.release('w');
  Keyboard.release('a');
  Keyboard.press('s');
  Keyboard.release('d');
} else if(value_y < 570) {
  digitalWrite(0, HIGH);
  Keyboard.press('w');
  Keyboard.release('a');
  Keyboard.release('s');
  Keyboard.release('d');
} else {
  digitalWrite(0, LOW);
  Keyboard.release('w');
  Keyboard.release('a');
  Keyboard.release('s');
  Keyboard.release('d');
}*/
}

void accel2() {
  x = accelero.getXRaw();
  y = accelero.getYRaw();
  z = accelero.getZRaw();
  Serial.print("\nx: ");
  Serial.print(x);
  Serial.print("\ty: ");
  Serial.print(y);
  Serial.print("\tz: ");
  Serial.print(z);
  
  
if(x > 450) {
  digitalWrite(1, HIGH);
  Keyboard.release('h');
  Keyboard.press('b');
  Keyboard.release('n');
  Keyboard.release('m');
} else if(x < 260) {
  digitalWrite(1, HIGH);
  Keyboard.release('h');
  Keyboard.release('b');
  Keyboard.release('n');
  Keyboard.press('m');
} else if(y > 470) {
  digitalWrite(1, HIGH);
  Keyboard.release('h');
  Keyboard.release('b');
  Keyboard.press('n');
  Keyboard.release('m');
} else if(y < 270) {
  digitalWrite(1, HIGH);
  Keyboard.press('h');
  Keyboard.release('b');
  Keyboard.release('n');
  Keyboard.release('m');
} else {
  digitalWrite(1, LOW);
  Keyboard.release('h');
  Keyboard.release('b');
  Keyboard.release('n');
  Keyboard.release('m');
}
  
  if(x > 450 || x < 260 || y > 470 || y < 270) {
  //digitalWrite(1, LOW);
} else {
 // digitalWrite(1, LOW);
}
}

void loop() {
  accel1();
  accel2();
  delay(0);
}


