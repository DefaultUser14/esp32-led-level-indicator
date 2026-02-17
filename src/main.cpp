#include "Arduino.h"


#define POT_VCC 33
#define POT_SIG 32

const int leds[] = {13,12,14,27,26,25};

const int pot_range = 4095;

const int led_count = 6;
const int intervall = pot_range / led_count;

const int average_count = 5;
int averaged_value = 0;

const int delay_ms = 10;
unsigned long last_time = 0;

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < led_count; i++) {
     pinMode(leds[i], OUTPUT);
  }

  pinMode(POT_VCC, OUTPUT);
  digitalWrite(POT_VCC, HIGH);

}

void loop()
{
  if (millis() - last_time >= delay_ms) {
    int raw_value = analogRead(POT_SIG);

    averaged_value = (averaged_value * (average_count - 1) + raw_value) /average_count;

    int led_on_count = averaged_value / intervall;
    led_on_count = min(led_on_count, led_count - 1);

    int brightness = (averaged_value - (led_on_count * intervall)) * 255 / intervall;

    for (int i = 0; i < led_count; i++){
      analogWrite(leds[i], 0);
    }

    for (int i= 0; i < (led_on_count); i++) {
      analogWrite(leds[i], 255);
    }


    analogWrite(leds[led_on_count], brightness);

    // Serial.println(averaged_value);
    last_time = millis();
  }
}