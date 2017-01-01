#include <dht.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Wire.h>


dht DHT;

#define DHT21_PIN 6
static const char               topic_temp[] = "garage/temp1";
static const char               topic_hum[] = "garage/humidity1";
char  message[] = "00.00";  //initialise
int i;
String  gtemp;
String  ghum;

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 202);
IPAddress server(192, 168, 0, 3);
EthernetClient ethClient;
PubSubClient client(ethClient);



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
 Serial.print("DHT21, \t");
 int chk = DHT.read21(DHT21_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;

  }


 // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);

  
  gtemp = DHT.temperature;
 
  Serial.print(gtemp);
  Serial.print(",");
  Serial.println(ghum);
    for ( i = 0; i < gtemp.length(); i++ ) {
        message[i]= gtemp.charAt(i);       
    }
  //message[i] = '\0';
  client.publish(topic_temp, message);
  
   ghum = DHT.humidity;
  for ( i = 0; i < ghum.length(); i++ ) {
        message[i]= ghum.charAt(i);
    }
  // message[i] = '\0';
   Serial.println(message);
     
   client.publish(topic_hum, message);
  
}





void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
     // client.publish("outTopic","hello world");

     
  Serial.print("DHT21, \t");
 int chk = DHT.read21(DHT21_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;

  }


 // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);
  gtemp = DHT.temperature;
  Serial.print(gtemp);
  Serial.print(",");
 // Serial.println(gtemp.length());
  Serial.println(ghum);
  for ( i = 0; i < gtemp.length(); i++ ) {
        message[i]= gtemp.charAt(i);
    }
//message[i] = '\0';
     
            client.publish(topic_temp, message);
   ghum = DHT.humidity;
  for ( i = 0; i < ghum.length(); i++ ) {
        message[i]= ghum.charAt(i);
    }
   //message[i] = '\0';
   Serial.println(message);
     
   client.publish(topic_hum, message);



      // ... and resubscribe
      client.subscribe("garage/gettemp1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}




void setup()
{
  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);


  
}

void loop()
{



    // READ DATA
  Serial.print("DHT21, \t");
 int chk = DHT.read21(DHT21_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;

  }


 // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);
  gtemp = DHT.temperature;
  Serial.print(gtemp);
  Serial.print(",");
 // Serial.println(gtemp.length());
  Serial.println(ghum);

  
  for ( i = 0; i < gtemp.length(); i++ ) {
        message[i]= gtemp.charAt(i);
    }
  //message[i] = '\0';
     
  client.publish(topic_temp, message);

   ghum = DHT.humidity;
  for ( i = 0; i < ghum.length(); i++ ) {
        message[i]= ghum.charAt(i);
    }
   //message[i] = '\0';
   Serial.println(message);
     
   client.publish(topic_hum, message);
            
  delay(300000);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();




  
}
//
// END OF FILE
//
