#include <WiFi.h>  
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <AccelStepper.h>



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
#define dirPin1 12
#define stepPin1 13

#define dirPin2 27
#define stepPin2 14

#define dirPin3 25
#define stepPin3 26

#define dirPin4 32
#define stepPin4 33


  
AccelStepper stepper1(1, stepPin1, dirPin1); // Initialize the stepper library
AccelStepper stepper2(1, stepPin2, dirPin2); 
AccelStepper stepper3(1, stepPin3, dirPin3);
AccelStepper stepper4(1, stepPin4, dirPin4);



void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 // WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password, 6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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
      client.publish("testTopic", "robot is connected!");
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



// called by client.loop() 
// Responsible for receiving mqtt messages. 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String stMessage;

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    stMessage += (char)payload[i];
  }
  Serial.println();

  if(stMessage.charAt(0) == '0'){
      Serial.print("retrieve item from shelf ( ");
      Serial.print(stMessage.substring(1));
      Serial.println(" )");
      if( retrieveAction( stMessage.charAt(1), stMessage.charAt(2) ) ){
        client.publish("testTopic", "1");
      }
    }
}



void rotateClockwise(AccelStepper& stepper, int destination) {
  stepper.moveTo(destination * 10);
  stepper.runToPosition();
  Serial.print("moving ");
}
/*
void rotateAntiClockwise(AccelStepper& stepper, int destination) {
  stepper.moveTo(stepsPerRevolution / 10); // Rotate 36 degrees (10% of a full revolution) anticlockwise
  stepper.run();
}
*/


bool retrieveAction( int locationX, int locationY ){
  // note, this needs more work for actual robot. 
  
  rotateClockwise(stepper1, locationX);
  rotateClockwise(stepper2, locationX);
  rotateClockwise(stepper3, locationY);
  rotateClockwise(stepper4, locationY);
     
  return true; 
}



// Function to move a stepper motor to its target position and return the new position  
/*
long moveToTarget(Stepper& stepper, long targetPosition, long& currentPosition) {  
    long stepsToMove = targetPosition - currentPosition;
    stepsToMove = +stepsToMove;
    if (stepsToMove > 0) {  
        for(int i = 0; i <= stepsToMove; i++){
          stepper.step(1);  
          currentPosition++;
        }
    }   
    return currentPosition;  
} 
*/



void setup() {
  delay(500);
  // When opening the Serial Monitor, select 9600 Baud
  Serial.begin(9600);
  delay(500);

  
  setup_wifi();

  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  

  stepper1.setMaxSpeed(1000); // Adjust the maximum speed of your stepper motor
  stepper1.setAcceleration(500); // Adjust the acceleration of your stepper motor

  stepper2.setMaxSpeed(1000); 
  stepper2.setAcceleration(500);

  stepper3.setMaxSpeed(1000); 
  stepper3.setAcceleration(500);

  stepper4.setMaxSpeed(1000); 
  stepper4.setAcceleration(500);
}



void loop() {
  
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 30000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "I'm alive! #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("testTopic", msg);
  }
  

  delay(1);
}


