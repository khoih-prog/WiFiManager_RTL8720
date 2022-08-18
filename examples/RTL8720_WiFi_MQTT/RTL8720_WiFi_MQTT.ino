/****************************************************************************************************************************
  RTL8720_WiFi_MQTT.ino
  
  For RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards

  WiFiManager_RTL8720 (https://github.com/khoih-prog/WiFiManager_RTL8720) is a library
  for the RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards to enable store Credentials in FlashStorage/SPIFFS/LittleFS for easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_RTL8720
  Licensed under MIT license
  *****************************************************************************************************************************/
  
//  You have to use forked and modified library https://github.com/khoih-prog/Adafruit_MQTT_Library
 
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#define LOCAL_DEBUG       true  //false

#include "Adafruit_MQTT.h"                //https://github.com/adafruit/Adafruit_MQTT_Library
#include "Adafruit_MQTT_Client.h"         //https://github.com/adafruit/Adafruit_MQTT_Library

// Create a WiFiClient class to connect to the MQTT server
WiFiClient *client                    = NULL;

Adafruit_MQTT_Client    *mqtt         = NULL;
Adafruit_MQTT_Publish   *Temperature  = NULL;
Adafruit_MQTT_Subscribe *LED_Control  = NULL;

// You have to get from a sensor. Here is just an example
uint32_t measuredTemp = 5;

WiFiManager_RTL8720* WiFiManager;

void heartBeatPrint()
{
  static int num = 1;

  if (WiFiManager->isConfigMode())
    Serial.print("C");        // C means in Config Mode
  else
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.print("H");        // H means connected to WiFi
    }
    else
      Serial.print("F");        // F means not connected to WiFi  
  }

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void publishMQTT()
{
  MQTT_connect();

  if (Temperature->publish(measuredTemp))
  {
    //Serial.println(F("Failed to send value to Temperature feed!"));
    Serial.print(F("T"));        // T means publishing OK
  }
  else
  {
    //Serial.println(F("Value to Temperature feed sucessfully sent!"));
    Serial.print(F("F"));        // F means publishing failure
  }
}

void subscribeMQTT()
{
  Adafruit_MQTT_Subscribe *subscription;

  MQTT_connect();

  while ((subscription = mqtt->readSubscription(5000)))
  {
    if (subscription == LED_Control)
    {
      Serial.print(F("\nGot: "));
      Serial.println((char *)LED_Control->lastread);

      if (!strcmp((char*) LED_Control->lastread, "ON"))
      {
        digitalWrite(LED_PIN, HIGH);
      }
      else
      {
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

  //KH
#define HEARTBEAT_INTERVAL    5000L
  // Print WiFi hearbeat, Publish MQTT Topic every HEARTBEAT_INTERVAL (5) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    if ( !WiFiManager->isConfigMode() )
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        // MQTT related jobs
        publishMQTT();
        subscribeMQTT();
      }
    }
    
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

void deleteOldInstances()
{
  // Delete previous instances
  if (mqtt)
  {
    delete mqtt;
    mqtt = NULL;
    Serial.println(F("Deleting old MQTT object"));
  }

  if (Temperature)
  {
    delete Temperature;
    Temperature = NULL;
    Serial.println(F("Deleting old Temperature object"));
  }
}

#define USE_GLOBAL_TOPIC    true

#if USE_GLOBAL_TOPIC
  String completePubTopic;
  String completeSubTopic;
#endif

void createNewInstances()
{
  if (!client)
  {
    client = new WiFiClient;

    if (client)
    {
      Serial.println(F("\nCreating new WiFi client object OK"));
    }
    else
      Serial.println(F("\nCreating new WiFi client object failed"));
  }

  // Create new instances from new data
  if (!mqtt)
  {
    // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
    mqtt = new Adafruit_MQTT_Client(client, AIO_SERVER, atoi(AIO_SERVERPORT), AIO_USERNAME, AIO_KEY);

    if (mqtt)
    {
      Serial.println(F("Creating new MQTT object OK"));
      Serial.print(F("AIO_SERVER = ")); Serial.print(AIO_SERVER); Serial.print(F(", AIO_SERVERPORT = ")); Serial.println(AIO_SERVERPORT);
      Serial.print(F("AIO_USERNAME = ")); Serial.print(AIO_USERNAME); Serial.print(F(", AIO_KEY = ")); Serial.println(AIO_KEY);
    }
    else
      Serial.println(F("Creating new MQTT object failed"));
  }

  if (!Temperature)
  {
#if USE_GLOBAL_TOPIC
    completePubTopic = String(AIO_USERNAME) + String(AIO_PUB_TOPIC);
#else
    // Must be static or global
    static String completePubTopic = String(AIO_USERNAME) + String(AIO_PUB_TOPIC);
#endif

    Temperature = new Adafruit_MQTT_Publish(mqtt, completePubTopic.c_str());
    Serial.print(F("Creating new MQTT_Pub_Topic,  Temperature = ")); Serial.println(completePubTopic);

    if (Temperature)
    {
      Serial.println(F("Creating new Temperature object OK"));
      Serial.print(F("Temperature MQTT_Pub_Topic = ")); Serial.println(completePubTopic);
    }
    else
      Serial.println(F("Creating new Temperature object failed"));
  }

  if (!LED_Control)
  {
#if USE_GLOBAL_TOPIC
    completeSubTopic = String(AIO_USERNAME) + String(AIO_SUB_TOPIC);
#else
    // Must be static or global
    static String completeSubTopic = String(AIO_USERNAME) + String(AIO_SUB_TOPIC);
#endif

    LED_Control = new Adafruit_MQTT_Subscribe(mqtt, completeSubTopic.c_str());

    Serial.print(F("Creating new AIO_SUB_TOPIC, LED_Control = ")); Serial.println(completeSubTopic);

    if (LED_Control)
    {
      Serial.println(F("Creating new LED_Control object OK"));
      Serial.print(F("LED_Control AIO_SUB_TOPIC = ")); Serial.println(completeSubTopic);

      mqtt->subscribe(LED_Control);
    }
    else
      Serial.println(F("Creating new LED_Control object failed"));
  }
}

void MQTT_connect()
{
  int8_t ret;

  createNewInstances();

  // Return if already connected
  if (mqtt->connected())
  {
    return;
  }

#if LOCAL_DEBUG
  Serial.println(F("\nConnecting to WiFi MQTT (3 attempts)..."));
#endif

  uint8_t attempt = 3;

  while ( (ret = mqtt->connect()) )
  {
    // connect will return 0 for connected
    Serial.println(mqtt->connectErrorString(ret));

#if LOCAL_DEBUG
    Serial.println(F("Another attemtpt to connect to MQTT in 5 seconds..."));
#endif

    mqtt->disconnect();
    delay(5000);  // wait 5 seconds
    attempt--;

    if (attempt == 0)
    {
      Serial.println(F("WiFi MQTT connection failed. Continuing with program..."));
      return;
    }
  }

#if LOCAL_DEBUG
  Serial.println(F("WiFi MQTT connection successful!"));
#endif
}

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  delay(200);

  Serial.print(F("\nStart RTL8720_WiFi_MQTT on ")); Serial.println(BOARD_NAME);
  Serial.println(RTL8720_WIFIMANAGER_VERSION);
  Serial.println(DOUBLERESETDETECTOR_GENERIC_VERSION);

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();

  Serial.print("Current Firmware Version = "); Serial.println(fv);
  
  if (fv != LATEST_RTL8720_FIRMWARE) 
  {
    Serial.println("Please upgrade the firmware");
  }

  WiFiManager = new WiFiManager_RTL8720();

  // Optional to change default AP IP(192.168.4.1) and channel(10)
  //WiFiManager->setConfigPortalIP(IPAddress(192, 168, 120, 1));
  WiFiManager->setConfigPortalChannel(0);

#if USING_CUSTOMS_STYLE
  WiFiManager->setCustomsStyle(NewCustomsStyle);
#endif

#if USING_CUSTOMS_HEAD_ELEMENT
  WiFiManager->setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
#endif

#if USING_CORS_FEATURE  
  WiFiManager->setCORSHeader("Your Access-Control-Allow-Origin");
#endif

  // Set customized DHCP HostName
  WiFiManager->begin(HOST_NAME);
  //Or use default Hostname "RTL8720-WIFI-XXXXXX"
  //WiFiManager->begin();
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials()
{
  Serial.println(F("\nYour stored Credentials :"));

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.print(myMenuItems[i].displayName);
    Serial.print(F(" = "));
    Serial.println(myMenuItems[i].pdata);
  }
}

void displayCredentialsInLoop()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
}

#endif

void loop()
{
  WiFiManager->run();
  check_status();

#if USE_DYNAMIC_PARAMETERS
  displayCredentialsInLoop();
#endif  
}
