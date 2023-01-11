#include <Arduino.h>
#include <SPI.h> 
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define SS_PIN 21
#define RST_PIN 22

// Replace with your network credentials
const char* ssid     = "R.Basman";
const char* password = "satusampaisepuluh";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://akbariot.000webhostapp.com/test.php?";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() 
{

  Serial.begin(115200);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  Serial.println();
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
}

void sendToServer(String nama, String no_kartu, String tanggal, String jam_masuk){
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&nama=" + nama + "&tanggal=" + tanggal
                          + "&no_kartu=" + no_kartu + "&jam_masuk=" + jam_masuk + "";
    //String httpRequestData = "api_key=" + apiKeyValue + "&nama=" + nama + "&tanggal=" + tanggal + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    //http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(3000);
}

void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID Tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  if (content == " a9 1f fd b3"){
    Serial.print("Sudah terdeteksi bolo");
    sendToServer("akbar", "0000", "12-08-2022", "07:00");
  }
  else if (content == " 04 1a 78 7a 92 61 80"){
    Serial.print("Sudah terdeteksi bolo");
    sendToServer("dewi", "0001", "12-08-2022", "07:00");
  }
  else if (content == " 04 7d 2d b2 80 61 80"){
    Serial.print("Sudah terdeteksi bolo");
    sendToServer("bambang", "0002", "12-08-2022", "07:00");
  }
  Serial.println();
  delay(2000);
}