/****************************************************************************************************************************
  RTL8720_WiFi.ino
  
  For RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards

  WiFiManager_RTL8720 (https://github.com/khoih-prog/WiFiManager_RTL8720) is a library
  for the RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards to enable store Credentials in FlashStorage/SPIFFS/LittleFS for easy
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_RTL8720
  Licensed under MIT license
  *****************************************************************************************************************************/

#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

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

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

  //KH
#define HEARTBEAT_INTERVAL    20000L
  // Print hearbeat every HEARTBEAT_INTERVAL (20) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
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

  Serial.print(F("\nStarting RTL8720_WiFi on ")); Serial.println(BOARD_NAME);
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
