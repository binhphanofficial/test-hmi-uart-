#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include "Nextion.h"
float t1,t;
SoftwareSerial HMISerial(10, 11);
NexButton b0 = NexButton(0, 1, "b0");
NexButton b1 = NexButton(0, 2 , "b1");
NexText t0 = NexText(0, 3, "t0");
NexTouch *nex_listen_list[] = {
  &b0,
  &b1,
  NULL
};
void onPopCallback(void *ptr) {
  digitalWrite(13, 1);

}
void offPopCallback(void *ptr) {
  digitalWrite(13, 0);
  static char temperatureCTemp[6];
  dtostrf(t, 6, 2, temperatureCTemp);
  t0.setText(temperatureCTemp);
}
void setup() {
  // put your setup code here, to run once:
 nexInit();
 Serial.begin(9600);
 pinMode(13, OUTPUT);
 digitalWrite(13, 0);
 b0.attachPop(onPopCallback, &b0);
 b1.attachPop(offPopCallback, &b1);
 mlx.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
nexLoop(nex_listen_list);
t1=mlx.readAmbientTempC();
Serial.print("Ambient = "); Serial.print(t1); 
t=mlx.readObjectTempC();
Serial.print("*C\tObject = "); Serial.print(t); Serial.println("*C");
}
