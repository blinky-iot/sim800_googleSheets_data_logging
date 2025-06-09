#define TINY_GSM_MODEM_SIM800

#include <HardwareSerial.h>
#include <TinyGsmClient.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MODEM_RX 16
#define MODEM_TX 17
HardwareSerial sim800(1);
#define SerialMon Serial

const char apn[]  = "safaricom";
const char user[] = "saf";
const char pass[] = "data";

const char* server = "41.90.109.101";
const int   port = 3000;


TinyGsm modem(sim800);
TinyGsmClient client(modem);

void setup() {
  SerialMon.begin(9600);
  delay(10);

  sim800.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  SerialMon.println("Initializing modem...");
  modem.restart();

  SerialMon.print("Connecting to APN: ");
  SerialMon.println(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println("GPRS failed.");
    while (true);
  }
  SerialMon.println("GPRS connected!");

  dht.begin();
}

void loop() {
  float temp = random(200, 350) / 10.0;
  float hum = random(400, 800) / 10.0;

  String url = "/post-data?temp=" + String(temp, 1) +
               "&hum=" + String(hum, 1);

  SerialMon.println("Sending data to server...");
  if (client.connect(server, port)) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");
    SerialMon.println("Request sent.");
  } else {
    SerialMon.println("Server connection failed.");
  }

  unsigned long timeout = millis();
  while (client.connected() && millis() - timeout < 5000) {
    while (client.available()) {
      char c = client.read();
      SerialMon.write(c);
    }
  }
  client.stop();

  delay(20000);
}
