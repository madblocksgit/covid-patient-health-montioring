#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "BK2aSuufEMsJX6OcWcqMkJrMfUL2JZpJ";             // You should get Auth Token in the Blynk App.
char ssid[] = "covid";                                     // Your WiFi credentials.
char pass[] = "123456789";

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#define REPORTING_PERIOD_MS 1000
String bpm,spo2;
void onBeatDetected()
{
  Serial.println("Beat!");
}
void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing pulse oximeter..");
  Blynk.begin(auth, ssid, pass);
  mlx.begin();
}
 
void loop()
{
  Blynk.run();
  while(Serial.available()>0)
  {
    String ch=Serial.readStringUntil('\r');
    if(ch!="")
    {
      int comma=ch.indexOf(",");//72.4,98
      bpm=ch.substring(1,comma);
      spo2=ch.substring(comma+1);
    }
    float temp=checkBodyTemperature();
    Serial.print("BPM:");
    Serial.print(bpm);
    Serial.print("\t SPO2:");
    Serial.print(spo2);
    Serial.print("\tTemp:");
    Serial.println(temp); 
    Blynk.virtualWrite(V0, temp);
    if(bpm.toInt()>40 && spo2.toInt()>40)
    {
      Blynk.virtualWrite(V3, bpm);
      Blynk.virtualWrite(V4, spo2);
      Blynk.virtualWrite(V0, temp);
      if(temp>102)
      {
        Blynk.notify("Temperature is High");
        delay(5000);
      }
      if(spo2.toInt()>80 && spo2.toInt()<90)
      {
        Blynk.notify("Oxygen Level is LOW");
        delay(5000);
      }
      if((bpm.toInt()>40 && bpm.toInt()<50)||(bpm.toInt()>90 && bpm.toInt()<120))
      {
        Blynk.notify("ABNORMAL PULSE");
        delay(5000);
      }
    }
  }
}
float checkBodyTemperature(void)
{
  float sum=0;
  for(int i=0;i<4;i++)
  {
    sum+=mlx.readObjectTempF();
  }
  sum=sum/4;
  if(sum>91)
    sum+=4.2;
  return(sum);
}
