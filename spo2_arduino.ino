#include "MAX30100_PulseOximeter.h" 
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
float BPM, SpO2;
uint32_t tsLastReport = 0; 
void onBeatDetected()
{
    digitalWrite(13,HIGH);
    //Serial.println("Beat Detected!");
}
 
void setup()
{
    pinMode(13,OUTPUT);
    Serial.begin(9600);
    if (!pox.begin())
    {
         for(;;);
    }
    else
    {
         pox.setOnBeatDetectedCallback(onBeatDetected);
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}
 
void loop()
{
    pox.update();
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        digitalWrite(13,LOW);
        Serial.print(BPM);
        Serial.print(",");
        Serial.println(SpO2);
        tsLastReport = millis();
    }
}
