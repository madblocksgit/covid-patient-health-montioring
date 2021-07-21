# covid-patient-health-montioring
Official repo of a project developed for a student from URCET - Temperature Sensor, Pulse Oximeter, Blynk

# Process
1. Create a portable hotspot with username - covid, password - 123456789
2. This program will keep uploading data to Blynk App
3. On Blynk, the data will be visualised and the notifications will be sent on Blynk

# Connections
1. Pulse Oximeter - Arduino (SCL - A5 - Orange, SDA - A4 - Yellow, RED - GND, BROWN - Vin)
2. Wireless Temperature Sensor - ESP32 (SCL - Violet , SDA - White , VCC - Orange, GND - Yellow )
3. Arduino - ESP32 (Arduino - 0, 1 - ESP32 - TXD, RXD)


