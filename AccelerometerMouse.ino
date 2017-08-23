
#include <MPU6050.h>
#include <I2Cdev.h>
#include <Mouse.h>
#include <Wire.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
int button1 = 6;
int button2 = 7;
int buttonState1 = 0;
int buttonState2 = 0;

void setup() {

  Serial.begin(9600);
  Wire.begin();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = -(gx + 15) / 150;
  vy = -(gz - 100) / 150;

  Serial.print("gx = ");
  Serial.print(gx);
  Serial.print(" | gz = ");
  Serial.print(gz);

  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy);

  Mouse.move(vy, vx);

  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);

  if (buttonState1 == HIGH) {
    Mouse.press(MOUSE_LEFT);
    delay(50);
    Mouse.release(MOUSE_LEFT);
    delay(50);
  }
  else if (buttonState2 == HIGH) {
    Mouse.press(MOUSE_RIGHT);
    delay(50);
    Mouse.release(MOUSE_RIGHT);
    delay(50);
  }
  delay(60);
}

