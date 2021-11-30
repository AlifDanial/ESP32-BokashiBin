#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4        // dht input pin
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

int sensorpin=36;   //Analog pin for soil moisture sensor
//int sensorpin2=25;   //setting the sensor pin
int outputpin=33;   //output pin for soil moisture sensor
int moisture;  //the variable to control
int motion;  //the variable to control
String moist_s;
float h;
float t;

//ENTER_GOOGLE_DEPLOYMENT_ID
const char * ssid = "The Matrix";
const char * password = "Wsdhuj78+";
String GOOGLE_SCRIPT_ID = "AKfycbzhRMQ3aSHcwetqvBapeA3NQ9dvROV8WUy6-nxgnm93cSNpUmprwD0MlHixFeWegUbQCw";
//---------------------------------------------------------------------

const int sendInterval = 2000;
DHT dht(DHTPIN,DHTTYPE);

 void setup() {
  //--------------------------------------------
  Serial.begin(115200);
  //start serial communication with Serial Monitor
  pinMode(sensorpin,INPUT);    //setting sensor pin to be input
  pinMode(outputpin,OUTPUT);   //setting output pin to be output
  pinMode(DHTPIN, INPUT);
  
  delay(10);
  //--------------------------------------------
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("OK");
  //--------------------------------------------

  dht.begin();
}

void loop() {

  moisture=analogRead(sensorpin);  //read the value from sensor pin
//  motion=analogRead(sensorpin2);

  
  Serial.println(motion);
  Serial.println(moisture);  //show the value receive in serial monitor  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

   // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  if(moisture<=600){                //the criticall value to trigger the solenoid
    digitalWrite(outputpin,LOW);}   
  
  else{
    digitalWrite(outputpin,HIGH);} 

//  delay(sendInterval);
  print_speed();

}


void print_speed()
{
    String param;
//    param  = "tag=Moisture";
    param = "humid="+String(h);
    param += "&moist="+String(moisture);
    param += "&temp="+String(t);
//    param += "&ph="+String(t);
    Serial.println(param);
    write_to_google_sheet(param);
}

void write_to_google_sheet(String params) {
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
   //Serial.print(url);
    Serial.println("Postring data to Google Sheet");
    //---------------------------------------------------------------------
    //starts posting data to google sheet
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();  
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    //getting response from google sheet
    String payload;
    if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload: "+payload);     
    }
    //---------------------------------------------------------------------
    http.end();
}
