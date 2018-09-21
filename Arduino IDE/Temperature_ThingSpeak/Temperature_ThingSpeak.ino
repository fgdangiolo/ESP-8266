/**************************************************************************************
 * Este código toma la temperatura desde dos sensores distintos: 1) LM 35 y 2) Ds18b20
 * Nota: Error de medidicón: 1) LM35: 0,2°C  2) Ds18b20: 0,0625°C
 * Placa: Mini Wemos
 *********************************************************************************** */

#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int pin_ds18b20 = D4;  // Pin donde se conectará el sensor (1-Wire)

OneWire sensor_one_wire(pin_ds18b20);                // Se instancia a las clases OneWire y DallasTemperature    
DallasTemperature sensor_ds18b20(&sensor_one_wire);

char ssid[] = "Your SSID";   //  Nombre de la RED
char pass[] = "Your Pass";   //  Clave de la RED

unsigned long myChannelNumber = 2;  // Cambiar por el número de Canal
const char * myWriteAPIKey = " ";
unsigned int dataFieldOne = 1;    // Campo donde se escribirá el dato de Temperatura
unsigned int dataFieldTwo = 2;    // Campo donde se escribirá el dato de Temperatura

  WiFiClient  client;

void setup()
{
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  sensor_ds18b20.begin(); // Se inicializa el bus 1-Wire

  // Conexión a WiFi
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }
  
  Serial.println("");
  digitalWrite(D3, LOW);
  
  Serial.println("Se conecto a la Red");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  

  ThingSpeak.begin(client);
  
}

void loop()
{

  // LM 35

  int entrada = 0;
  float tension = 0;
  float temperatura_LM35 = 0;
  float temperatura_Ds18b20;
  
  int sensorValue = analogRead(A0);  // Devuelve un entero entre 0 y 1023
  
  tension  = (3.3 / 1024.0) * sensorValue; // Se convierte el valor en °C a V
  
  temperatura_LM35 = tension / 0.01;       // Se convierte la tensión a grados celsius
 
    Serial.print("Temperatura LM 35: ");
    Serial.print(temperatura_LM35);  
    Serial.println(" °C");
  
  if(temperatura_LM35>=35) digitalWrite(D1, HIGH);
  else
  digitalWrite(D1,LOW);

  // Ds18b20

    sensor_ds18b20.requestTemperatures();                         // Envío de comandos al sensor
    temperatura_Ds18b20 = sensor_ds18b20.getTempCByIndex(0);     //  Obtención de la temperatura
 
    Serial.print("Temperatura Ds18b20: ");
    Serial.print(temperatura_Ds18b20);  
    Serial.println(" °C");

write2TSData(myChannelNumber, dataFieldOne, temperatura_LM35, dataFieldTwo, temperatura_Ds18b20);      

}
 
 int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, myWriteAPIKey );
 
   
  delay(15000); // A ThingSpeak solo se puede enviar datos cada 15 segundos.
  
   return writeSuccess;
}

