/****************************************************************************
 * Este código sume a ThingSpeak, el valor analógico que se encuentra
 * en la entrada del ESP 8266
 * 
 * Placa: MiniWemos
 ****************************************************************************/


#include <ThingSpeak.h>
#include <ESP8266WiFi.h>


char ssid[] = "";     //  your network SSID (name)
char pass[] = "";    // your network password

unsigned long myChannelNumber = 2; //Change for your Channel Number
 
const char * myWriteAPIKey = "";  // Change for your APIKey
  WiFiClient  client;


void setup()
{
  pinMode(D1, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // Conexión a WiFi
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }
  Serial.println("");
  digitalWrite(D1, HIGH);
  
  Serial.println("Se conecto a la Red");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  

  ThingSpeak.begin(client);
  
}

void loop()
{

  int sensorValue =0;
  float voltage = 0;

  // Se muestrea el valor analógico y se convierte a un número entre 0 y 1023
  
    sensorValue = analogRead(A0);            

  // Se convierte el valor obtenido en tensión
  
   voltage = sensorValue * (3.3 / 1023.0);
  
  // Imprimir el valor de tensión obtenido:
  
  Serial.println(voltage);
  
  if(voltage>=2) digitalWrite(D1, HIGH);
  
  else
  digitalWrite(D1,LOW);

  // Se envía la información a ThingSpeak
  
  ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  
  delay(15000); // Cada 15 segundo se envía la información de tensión.
}

