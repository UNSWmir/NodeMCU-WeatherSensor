#include "DHT.h"
#include <readiness_io.h>
#include <Ticker.h>
#include "config.h"

const int       LED_PIN          =  0;   // The pin connecting the LED (D3)
const byte      INTERRUPT_PIN    = 12;   // The pin connect the test button (D6)

volatile byte interrupt = 0;

#define DHTPIN 4                // The Digital Pin the sensor is connected too (D2)
#define DHTTYPE DHT22           // Designated the type of DHT Sensor

DHT dht(DHTPIN, DHTTYPE);
readiness_io client(CHANNEL_ID, TOPIC, SENSOR_ID, VERSION, FORMAT);
Ticker timer;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.setTimeout(2000);
  while(!Serial) { } // Wait for serial to initialize.
  Serial.println("Device Started");

  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  client.wifiConnection(WIFI_SSID, WIFI_PASS);

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), buttonInterrupt, FALLING);
  timer.attach(UPDATE_RATE, writeToServer);

  client.testConnection();
}

void buttonInterrupt() {
  interrupt++;
}

/* Interrupt timer for sending data to the Readiness.io server */
void writeToServer(){
  interrupt++;
}

void loop() {
  if(interrupt>0){

    /* Read from the DHT22 Sensor */
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    /* Write data to a json string and send to the server. */
    String weather = "\"humidity\":"  + String(h) + ",";
    weather += "\"temperature\":"   + String(t) ;

    /* Publish data to the readiness_io network */
    client.publishCustom(weather);
    /* Reset the interrupt variable until the timer interrupt or push button sets it off */
    interrupt=0;

  }

}
