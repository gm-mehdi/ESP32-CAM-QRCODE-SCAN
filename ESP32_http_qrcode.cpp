#include <Arduino.h>

#include <WiFi.h>

#include <HTTPClient.h>

#include <ESP32QRCodeReader.h>

#include <ESP32CameraPins.h>

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"
#define CHECK_STATUS "https://YOUR_URL.com/api/check.php"
#define CHANGE_STATUS "https://YOUR_URL.com/api/statutchange.php"

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

struct QRCodeData qrCodeData;
bool isConnected = false;

bool connectWifi() {
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int maxRetries = 10;
  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
    maxRetries--;
    if (maxRetries <= 0) {
      return false;
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  return true;
}

void callWebhook(String code) {
  HTTPClient http;
  http.begin(String(CHECK_STATUS) + "?id=" + code);
  int httpCode = http.GET();
  String statut = http.getString();
  if (statut == "true") {
    Serial.println("OK");

    http.begin(String(CHANGE_STATUS) + "?id=" + code);
    int httpCode = http.GET();

    // for test 
    // http.begin(String(CHECK_STATUS) + "?id=" + code);
    // Serial.println(statut);
    // digitalWrite(12,LOW);
    // delay(5000);
    // digitalWrite(12,HIGH);
  } else if (statut == "false") {
    Serial.println("Utilisé");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  //  pinMode(12, OUTPUT);
  //    digitalWrite(12,HIGH);
  reader.setup();
  //reader.setDebug(true);
  Serial.println("Setup QRCode Reader");

  reader.begin();
  Serial.println("Begin QR Code reader");

  delay(1000);
}

void loop() {

  bool connected = connectWifi();
  if (isConnected != connected) {
    isConnected = connected;
  }
  if (reader.receiveQrCode( & qrCodeData, 100)) {
    Serial.println("Found QRCode");
    if (qrCodeData.valid) {
      Serial.print("Payload: ");
      Serial.println((const char * ) qrCodeData.payload);
      callWebhook(String((const char * ) qrCodeData.payload));

    } else {

      Serial.print("Invalid: ");
      Serial.println((const char * ) qrCodeData.payload);
    }
  }
  delay(300);
}
