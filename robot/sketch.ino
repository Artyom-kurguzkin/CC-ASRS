#include <WiFi.h>  
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <Stepper.h> 



//---------------------------------------
//---- WiFi settings
//---------------------------------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";



//---------------------------------------
//---- HiveMQ Cloud (mqtt) Broker settings
//---------------------------------------
const char* mqtt_server = "06ea4fbd57d348d0931b9543624acafa.s1.eu.hivemq.cloud"; // replace with your HiveMQ Cluster URL
const char* mqtt_username = "kurg0002"; // replace with your Username
const char* mqtt_password = "9y83jy89L"; // replace with your Password
const int mqtt_port = 8883;

WiFiClientSecure espClient;  
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (500)
char msg[MSG_BUFFER_SIZE];
int value = 0;

// HiveMQ Cloud Let's Encrypt CA certificate
static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";



//---------------------------------------
// Step motor settigns
//---------------------------------------
float stepmax = 600;  
  
// control pins on the board for each of the step-motors  
Stepper Stepper1(stepmax, 12, 14, 27, 26);  
Stepper Stepper2(stepmax, 21,19, 18, 5);  
Stepper Stepper3(stepmax, 23,22, 4, 2);  
Stepper Stepper4(stepmax, 33,32, 35, 34);  
  
long currentPosition1 = 0;  
long currentPosition2 = 0;  
long currentPosition3 = 0;  
long currentPosition4 = 0;  
  
long targetPosition1 = 500;  
long targetPosition2 = 400;  
long targetPosition3 = 300;  
long targetPosition4 = 200;  
  
float speed1 = 50;  
float speed2 = 40;  
float speed3 = 30;  
float speed4 = 20; 



void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}



void reconnect() {
  // Loop until we’re reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection… ");
    String clientId = "ESP32Client";
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected!");
      // Once connected, publish an announcement…
      client.publish("testTopic", "Hello World!");
      // … and resubscribe
      client.subscribe("testTopic");
    } else {
      Serial.print("failed, rc = ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



// Function to move a stepper motor to its target position and return the new position  
long moveToTarget(Stepper& stepper, long targetPosition, long& currentPosition) {  
    long stepsToMove = targetPosition - currentPosition;  
    if (stepsToMove > 0) {  
        stepper.step(1);  
        currentPosition++;  
    } else if (stepsToMove < 0) {  
        stepper.step(-1);  
        currentPosition--;  
    }  
    return currentPosition;  
} 



void setup() {
  delay(500);
  // When opening the Serial Monitor, select 9600 Baud
  Serial.begin(9600);
  delay(500);

  setup_wifi();

  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  Stepper1.setSpeed(speed1);  
  Stepper2.setSpeed(speed2);  
  Stepper3.setSpeed(speed3);  
  Stepper4.setSpeed(speed4);
}



void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "Hello World! #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("testTopic", msg);
  }

  //currentPosition1 = moveToTarget(Stepper1, targetPosition1, currentPosition1);  
  //currentPosition2 = moveToTarget(Stepper2, targetPosition2, currentPosition2);    
  //currentPosition3 = moveToTarget(Stepper3, targetPosition3, currentPosition3);    
  //currentPosition4 = moveToTarget(Stepper4, targetPosition4, currentPosition4); 

  delay(1);
}


