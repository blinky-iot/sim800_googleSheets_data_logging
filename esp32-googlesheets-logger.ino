#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "GardenWhispers";
const char* password = "blink2023?";

const char* scriptURL = "https://script.google.com/macros/s/AKfycbwlS5XQkTyxypw53-NIs2_XSIRcqAyM25jzZY_DRH5nEoSYf865HXBC-gotA8G9MNoe-w/exec";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void loop() {
  float temp = random(200, 350) / 10.0;
  float hum = random(400, 800) / 10.0;

  Serial.printf("Sending -> Temp: %.1f°C, Humidity: %.1f%%\n", temp, hum);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(scriptURL) + "?temp=" + temp + "&hum=" + hum;

    http.begin(url);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);
    } else {
      Serial.println("HTTP Error: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(10000);
}