#include "motors.h"
#include "PS2_controller.h"

void setup()
{
  Serial.begin(115200);
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
  pinMode(39, INPUT);
  pinMode(36, INPUT);
  pinMode(25, INPUT);
  pinMode(32, INPUT);
  delay(10);
}

void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
  
}
