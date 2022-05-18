/****************************************************************************************************************************
  WiFiManager_RTL8720.h
  For RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards

  WiFiManager_RTL8720 (https://github.com/khoih-prog/WiFiManager_RTL8720) is a library 
  for the RTL8720DN, RTL8722DM, RTL8722CSM, etc. boards to enable store Credentials in FlashStorage/SPIFFS/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_RTL8720
  Licensed under MIT license
  
  Version: 1.0.0
   
  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      04/02/2021  Initial coding for RTL8720DN, RTL8722DM, RTL8722CSM, etc.
 *****************************************************************************************************************************/

#pragma once

#ifndef WiFiManager_RTL8720_h
#define WiFiManager_RTL8720_h

#if !defined(CONFIG_PLATFORM_8721D)
  #error Only for Ameba Realtek RTL8720DN, RTL8722DM and RTL8722CSM platform.
#endif

#define RTL8720_WIFIMANAGER_VERSION        "WiFiManager_RTL8720 v1.0.0"

#include <FlashStorage_RTL8720.h>
#include <WiFiWebServer_RTL8720.h>

#ifndef USING_CUSTOMS_STYLE
  #define USING_CUSTOMS_STYLE     false
#endif

#ifndef USING_CUSTOMS_HEAD_ELEMENT
  #define USING_CUSTOMS_HEAD_ELEMENT     false
#endif

#ifndef USING_CORS_FEATURE
  #define USING_CORS_FEATURE     false
#endif

//////////////////////////////////////////////

// New from v1.3.0
// KH, Some minor simplification
#if !defined(SCAN_WIFI_NETWORKS)
  #define SCAN_WIFI_NETWORKS     true     //false
#endif
	
#if SCAN_WIFI_NETWORKS
  #if !defined(MANUAL_SSID_INPUT_ALLOWED)
    #define MANUAL_SSID_INPUT_ALLOWED     true
  #endif

  #if !defined(MAX_SSID_IN_LIST)
    #define MAX_SSID_IN_LIST     6
  #elif (MAX_SSID_IN_LIST < 2)
    #warning Parameter MAX_SSID_IN_LIST defined must be >= 2 - Reset to 6
    #undef MAX_SSID_IN_LIST
    #define MAX_SSID_IN_LIST      6
  #elif (MAX_SSID_IN_LIST > 15)
    #warning Parameter MAX_SSID_IN_LIST defined must be <= 15 - Reset to 6
    #undef MAX_SSID_IN_LIST
    #define MAX_SSID_IN_LIST      6
  #endif
#else
  #warning SCAN_WIFI_NETWORKS disabled	
#endif

///////// NEW for DRD /////////////
// These defines must be put before #include <DoubleResetDetector_Generic.h>
// to select where to store DoubleResetDetector_Generic's variable.
// Otherwise, library will use default FlashStorage storage
#define  DRD_FLAG_DATA_SIZE     4

#ifndef DRD_GENERIC_DEBUG
  #define DRD_GENERIC_DEBUG     false
#endif

#include <DoubleResetDetector_Generic.h>      //https://github.com/khoih-prog/DoubleResetDetector_Generic

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector_Generic to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

///////// NEW for DRD /////////////

//NEW
#define MAX_ID_LEN                5
#define MAX_DISPLAY_NAME_LEN      16

typedef struct
{
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
} MenuItem;
//

#if USE_DYNAMIC_PARAMETERS
  #warning Using Dynamic Parameters
  ///NEW
  extern uint16_t NUM_MENU_ITEMS;
  extern MenuItem myMenuItems [];
  bool *menuItemUpdated = NULL;
#else
  #warning Not using Dynamic Parameters
#endif


#define SSID_MAX_LEN      32
// WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

#define HEADER_MAX_LEN            16
#define BOARD_NAME_MAX_LEN        24

typedef struct Configuration
{
  char header         [HEADER_MAX_LEN];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [BOARD_NAME_MAX_LEN];
  int  checkSum;
} WM_Configuration;

// Currently CONFIG_DATA_SIZE  =   236  = (16 + 96 * 2 + 4 + 24)
uint16_t CONFIG_DATA_SIZE = sizeof(WM_Configuration);

///New from v1.0.4
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern WM_Configuration defaultConfig;

// -- HTML page fragments

const char WM_HTML_HEAD_START[] /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>RTL8720_WM</title>";

const char WM_HTML_HEAD_STYLE[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

const char WM_HTML_HEAD_END[]   /*PROGMEM*/ = "</head><div style='text-align:left;display:inline-block;min-width:260px;'>\
<fieldset><div><label>*WiFi SSID</label><div>[[input_id]]</div></div>\
<div><label>*PWD (8+ chars)</label><input value='[[pw]]' id='pw'><div></div></div>\
<div><label>*WiFi SSID1</label><div>[[input_id1]]</div></div>\
<div><label>*PWD1 (8+ chars)</label><input value='[[pw1]]' id='pw1'><div></div></div></fieldset>\
<fieldset><div><label>Board Name</label><input value='[[nm]]' id='nm'><div></div></div></fieldset>";	// DO NOT CHANGE THIS STRING EVER!!!!

const char WM_HTML_INPUT_ID[]   /*PROGMEM*/ = "<input value='[[id]]' id='id'>";
const char WM_HTML_INPUT_ID1[]  /*PROGMEM*/ = "<input value='[[id1]]' id='id1'>";

const char WM_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char WM_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char WM_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char WM_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";
const char WM_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);\
request.open('GET',url,false);request.send(null);}\
function sv(){udVal('id',document.getElementById('id').value);udVal('pw',document.getElementById('pw').value);\
udVal('id1',document.getElementById('id1').value);udVal('pw1',document.getElementById('pw1').value);\
udVal('nm',document.getElementById('nm').value);";

const char WM_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char WM_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char WM_HTML_END[]          /*PROGMEM*/ = "</html>";

#if SCAN_WIFI_NETWORKS
const char WM_SELECT_START[]      /*PROGMEM*/ = "<select id=";
const char WM_SELECT_END[]        /*PROGMEM*/ = "</select>";
const char WM_DATALIST_START[]    /*PROGMEM*/ = "<datalist id=";
const char WM_DATALIST_END[]      /*PROGMEM*/ = "</datalist>";
const char WM_OPTION_START[]      /*PROGMEM*/ = "<option>";
const char WM_OPTION_END[]        /*PROGMEM*/ = "";			// "</option>"; is not required
const char WM_NO_NETWORKS_FOUND[] /*PROGMEM*/ = "No suitable WiFi networks available!";
#endif

//////////////////////////////////////////

//KH Add repeatedly used const
//KH, from v1.1.0
const char WM_HTTP_HEAD_CL[]         PROGMEM = "Content-Length";
const char WM_HTTP_HEAD_TEXT_HTML[]  PROGMEM = "text/html";
const char WM_HTTP_HEAD_TEXT_PLAIN[] PROGMEM = "text/plain";

const char WM_HTTP_CACHE_CONTROL[]   PROGMEM = "Cache-Control";
const char WM_HTTP_NO_STORE[]        PROGMEM = "no-cache, no-store, must-revalidate";
const char WM_HTTP_PRAGMA[]          PROGMEM = "Pragma";
const char WM_HTTP_NO_CACHE[]        PROGMEM = "no-cache";
const char WM_HTTP_EXPIRES[]         PROGMEM = "Expires";

const char WM_HTTP_CORS[]            PROGMEM = "Access-Control-Allow-Origin";
const char WM_HTTP_CORS_ALLOW_ALL[]  PROGMEM = "*";

//////////////////////////////////////////////

// New from v1.2.0
#if !defined(REQUIRE_ONE_SET_SSID_PW)
  #define REQUIRE_ONE_SET_SSID_PW     false
#endif

#define PASSWORD_MIN_LEN        8

//////////////////////////////////////////////

String IPAddressToString(IPAddress _address)
{
  String str = String(_address[0]);
  str += ".";
  str += String(_address[1]);
  str += ".";
  str += String(_address[2]);
  str += ".";
  str += String(_address[3]);
  return str;
}

class WiFiManager_Generic_Lite
{
    public:
    
    WiFiManager_Generic_Lite()
    {     
      // check for the presence of the shield
#if ( USE_WIFI101 || USE_ESP_AT_SHIELD )
      if (WiFi.status() == WL_NO_SHIELD)
#else
      if (WiFi.status() == WL_NO_MODULE)
#endif      
      {
        WM_LOGERROR(F("NoWiFi"));
      }     
    }

    ~WiFiManager_Generic_Lite()
    {
      if (server)
      {
        delete server;

#if SCAN_WIFI_NETWORKS
        if (indices)
        {
          free(indices); //indices array no longer required so free memory
        }
#endif
      }
    }
        
    bool connectWiFi(const char* ssid, const char* pass)
    {
      WM_LOGERROR1(F("Con2:"), ssid);
      
      setHostname();

      if ( WiFi.begin(ssid, pass) == WL_CONNECTED )  
      {
        displayWiFiData();
      }
      else
      {
        WM_LOGERROR(F("NoW"));
        return false;
      }

      WM_LOGERROR(F("WOK"));

      wifi_connected = true;

      return true;
    }
   
    void begin(const char* ssid,
               const char* pass )
    {
      WM_LOGERROR(F("conW"));
      connectWiFi(ssid, pass);
    }

    void begin(const char *iHostname = "")
    {
      #define RETRY_TIMES_CONNECT_WIFI			3
      
      if (iHostname[0] == 0)
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();
        
        String _hostname = "STM32-WIFI-" + randomNum;
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());
      }
      else
      {
        // Prepare and store the hostname only not NULL
        getRFC952_hostname(iHostname);
      }
      
       WM_LOGERROR1(F("Hostname="), RFC952_hostname);
      //////
      
      //// New DRD ////
      drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
      {
        WM_LOGERROR(F("Double Reset Detected"));
     
        noConfigPortal = false;
      }
      //// New DRD ////
      
      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        WM_LOGERROR(F("======= Start Default Config Data ======="));
        displayConfigData(defaultConfig);
      }
      
      hadConfigData = getConfigData();
      
      isForcedConfigPortal = isForcedCP();
        
      //// New DRD/MRD ////
      //  noConfigPortal when getConfigData() OK and no MRD/DRD'ed
      if (hadConfigData && noConfigPortal && (!isForcedConfigPortal) )
      {
        hadConfigData = true;

        if (connectMultiWiFi(RETRY_TIMES_CONNECT_WIFI))
        {
          WM_LOGERROR(F("b:WOK"));
        }
        else
        {
          WM_LOGERROR(F("b:NoW"));
          // failed to connect to WiFi, will start configuration mode
          startConfigurationMode();
        }
      }
      else
      {      
        WM_LOGERROR(isForcedConfigPortal? F("bg: isForcedConfigPortal = true") : F("bg: isForcedConfigPortal = false"));
                     
        // If not persistent => clear the flag so that after reset. no more CP, even CP not entered and saved
        if (persForcedConfigPortal)
        {
          WM_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
        }
        else
        {
          WM_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-non-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
          clearForcedCP();
        }
          
        //To permit autoreset after timeout if DRD/MRD or non-persistent forced-CP 
        hadConfigData = isForcedConfigPortal ? true : (noConfigPortal ? false : true);
        
        // failed to connect to WiFi, will start configuration mode
        startConfigurationMode();
      }
    }

#ifndef RETRY_TIMES_RECONNECT_WIFI
  #define RETRY_TIMES_RECONNECT_WIFI   2
#else
  // Force range of user-defined RETRY_TIMES_RECONNECT_WIFI between 2-5 times
  #if (RETRY_TIMES_RECONNECT_WIFI < 2)
    #warning RETRY_TIMES_RECONNECT_WIFI too low. Reseting to 2
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   2
  #elif (RETRY_TIMES_RECONNECT_WIFI > 5)
    #warning RETRY_TIMES_RECONNECT_WIFI too high. Reseting to 5
    #undef RETRY_TIMES_RECONNECT_WIFI
    #define RETRY_TIMES_RECONNECT_WIFI   5
  #endif
#endif

#ifndef RESET_IF_CONFIG_TIMEOUT
  #define RESET_IF_CONFIG_TIMEOUT   true
#endif

#ifndef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
  #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET          10
#else
  // Force range of user-defined TIMES_BEFORE_RESET between 2-100
  #if (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET < 2)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too low. Reseting to 2
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   2
  #elif (CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET > 100)
    #warning CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET too high. Resetting to 100
    #undef CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET
    #define CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET   100
  #endif
#endif

    void run()
    {
      static int retryTimes = 0;
      static bool wifiDisconnectedOnce = false;
      
      // Lost connection in running. Give chance to reconfig.
      // Check WiFi status every 5s and update status
      // Check twice to be sure wifi disconnected is real
      static unsigned long checkstatus_timeout = 0;
      #define WIFI_STATUS_CHECK_INTERVAL    5000L
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////
         
      if ( !configuration_mode && (millis() > checkstatus_timeout) )
      {       
        if (WiFi.status() == WL_CONNECTED)
        {
          wifi_connected = true;
        }
        else
        {
          if (wifiDisconnectedOnce)
          {
            wifiDisconnectedOnce = false;
            wifi_connected = false;
            WM_LOGERROR(F("r:Check&WLost"));
          }
          else
          {
            wifiDisconnectedOnce = true;
          }
        }
        
        checkstatus_timeout = millis() + WIFI_STATUS_CHECK_INTERVAL;
      }    

      // Lost connection in running. Give chance to reconfig.
      if ( !wifi_connected )
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect WiFi
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
          retryTimes = 0;

          if (server)
          {
            //WM_LOGDEBUG(F("r:handleClient"));
            server->handleClient();
          }
           
          return;
        }
        else
        {
#if RESET_IF_CONFIG_TIMEOUT
          // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
          // to permit user another chance to config.
          if ( configuration_mode && (configTimeout != 0) )
          {
            if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
            {
              WM_LOGERROR1(F("r:WLost&TOut.ConW.Retry#"), retryTimes);
            }
            else
            {
              resetFunc();  //call reset
            }
          }
#endif

          // Not in config mode, try reconnecting before forcing to config mode
          if ( !wifi_connected )
          {
            WM_LOGERROR(F("r:WLost.ReconW"));
            
            if (connectMultiWiFi(RETRY_TIMES_RECONNECT_WIFI))
            {
              WM_LOGERROR(F("r:WOK"));
            }
          }
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        WM_LOGERROR(F("r:gotWBack"));
      }
    }
    
    //////////////////////////////////////////////
    
    void setHostname()
    {
      if (RFC952_hostname[0] != 0)
      {
#if USE_WIFI101
        WiFi.hostname(RFC952_hostname);
#elif USE_WIFI_NINA    
        WiFi.setHostname(RFC952_hostname);
#endif        
      }
    }
    
    //////////////////////////////////////////////

    void setConfigPortalIP(IPAddress portalIP = IPAddress(192, 168, 4, 1))
    {
      portal_apIP = portalIP;
    }
    
    //////////////////////////////////////////////

    #define MIN_WIFI_CHANNEL      1
    #define MAX_WIFI_CHANNEL      11    // Channel 13 is flaky, because of bad number 13 ;-)

    int setConfigPortalChannel(int channel = 1)
    {
      // If channel < MIN_WIFI_CHANNEL - 1 or channel > MAX_WIFI_CHANNEL => channel = 1
      // If channel == 0 => will use random channel from MIN_WIFI_CHANNEL to MAX_WIFI_CHANNEL
      // If (MIN_WIFI_CHANNEL <= channel <= MAX_WIFI_CHANNEL) => use it
      if ( (channel < MIN_WIFI_CHANNEL - 1) || (channel > MAX_WIFI_CHANNEL) )
        AP_channel = 1;
      else if ( (channel >= MIN_WIFI_CHANNEL - 1) && (channel <= MAX_WIFI_CHANNEL) )
        AP_channel = channel;

      return AP_channel;
    }
    
    //////////////////////////////////////////////
    
    void setConfigPortal(String ssid = "", String pass = "")
    {
      portal_ssid = ssid;
      portal_pass = pass;
    }
    
    //////////////////////////////////////////////

    void setSTAStaticIPConfig(IPAddress ip)
    {
      static_IP = ip;
    }
    
    //////////////////////////////////////////////
    
    String getWiFiSSID(uint8_t index)
    { 
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WM_config.WiFi_Creds[index].wifi_ssid));
    }
    
    //////////////////////////////////////////////

    String getWiFiPW(uint8_t index)
    {
      if (index >= NUM_WIFI_CREDENTIALS)
        return String("");
        
      if (!hadConfigData)
        getConfigData();

      return (String(WM_config.WiFi_Creds[index].wifi_pw));
    }
    
    //////////////////////////////////////////////

    bool getWiFiStatus()
    {
      return wifi_connected;
    }
    
    //////////////////////////////////////////////
    
    WM_Configuration* getFullConfigData(WM_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &WM_config, sizeof(WM_Configuration));

      return (configData);
    }
    
    //////////////////////////////////////////////

    String localIP()
    {
      ipAddress = IPAddressToString(WiFi.localIP());

      return ipAddress;
    }
    
    //////////////////////////////////////////////

    void clearConfigData()
    {
      memset(&WM_config, 0, sizeof(WM_config));
      
#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
#endif

      saveConfigData();
    }
    
    //////////////////////////////////////////////
    
    bool isConfigDataValid()
    {
      return hadConfigData;
    }
    
    //////////////////////////////////////////////
    
    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (FLASHSTORAGE_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////

    void resetFunc()
    {    
      // Initialize the IWDG with 2 seconds timeout.
      // This would cause a CPU reset if the IWDG timer
      // is not reloaded in approximately 2 seconds.
      IWatchdog.begin(2000000);
    }

    //////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
    // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"

#if USING_CUSTOMS_STYLE
    //sets a custom style, such as color
    // "<style>div,input{padding:5px;font-size:1em;}
    // input{width:95%;}body{text-align: center;}
    // button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}
    // fieldset{border-radius:0.3rem;margin:0px;}</style>";
    void setCustomsStyle(const char* CustomsStyle = WM_HTML_HEAD_STYLE) 
    {
      WM_HTML_HEAD_CUSTOMS_STYLE = CustomsStyle;
      WM_LOGDEBUG1(F("Set CustomsStyle to : "), WM_HTML_HEAD_CUSTOMS_STYLE);
    }
    
    const char* getCustomsStyle()
    {
      WM_LOGDEBUG1(F("Get CustomsStyle = "), WM_HTML_HEAD_CUSTOMS_STYLE);
      return WM_HTML_HEAD_CUSTOMS_STYLE;
    }
#endif

#if USING_CUSTOMS_HEAD_ELEMENT    
    //sets a custom element to add to head, like a new style tag
    void setCustomsHeadElement(const char* CustomsHeadElement = NULL) 
    {
      _CustomsHeadElement = CustomsHeadElement;
      WM_LOGDEBUG1(F("Set CustomsHeadElement to : "), _CustomsHeadElement);
    }
    
    const char* getCustomsHeadElement()
    {
      WM_LOGDEBUG1(F("Get CustomsHeadElement = "), _CustomsHeadElement);
      return _CustomsHeadElement;
    }
#endif
    
#if USING_CORS_FEATURE   
    void setCORSHeader(const char* CORSHeaders = NULL)
    {     
      _CORS_Header = CORSHeaders;

      WM_LOGDEBUG1(F("Set CORS Header to : "), _CORS_Header);
    }
    
    const char* getCORSHeader()
    {      
      WM_LOGDEBUG1(F("Get CORS Header = "), _CORS_Header);
      return _CORS_Header;
    }
#endif
          
    //////////////////////////////////////


  private:
    String ipAddress = "0.0.0.0";

    WiFiWebServer* server = NULL;
    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;
    
    bool isForcedConfigPortal   = false;
    bool persForcedConfigPortal = false;

    WM_Configuration WM_config;
    
    uint16_t totalDataSize = 0;

    String macAddress = "";
    bool wifi_connected = false;

    IPAddress portal_apIP = IPAddress(192, 168, 4, 1);
    int AP_channel = 10;

    String portal_ssid = "";
    String portal_pass = "";

    IPAddress static_IP   = IPAddress(0, 0, 0, 0);

    /////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
#if USING_CUSTOMS_STYLE
    const char* WM_HTML_HEAD_CUSTOMS_STYLE = NULL;
#endif
    
#if USING_CUSTOMS_HEAD_ELEMENT
    const char* _CustomsHeadElement = NULL;
#endif
    
#if USING_CORS_FEATURE    
    const char* _CORS_Header        = WM_HTTP_CORS_ALLOW_ALL;   //"*";
#endif
       
    /////////////////////////////////////
    // Add WiFi Scan from v1.3.0
    
#if SCAN_WIFI_NETWORKS
  int WiFiNetworksFound = 0;		// Number of SSIDs found by WiFi scan, including low quality and duplicates
  int *indices;					        // WiFi network data, filled by scan (SSID, BSSID)
  String ListOfSSIDs = "";		  // List of SSIDs found by scan, in HTML <option> format
#endif

    //////////////////////////////////////
    
#define RFC952_HOSTNAME_MAXLEN      24

    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    char* getRFC952_hostname(const char* iHostname)
    {
      memset(RFC952_hostname, 0, sizeof(RFC952_hostname));

      size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);

      size_t j = 0;

      for (size_t i = 0; i < len - 1; i++)
      {
        if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
        {
          RFC952_hostname[j] = iHostname[i];
          j++;
        }
      }
      // no '-' as last char
      if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
        RFC952_hostname[j] = iHostname[len - 1];

      return RFC952_hostname;
    }
    
    void displayConfigData(WM_Configuration configData)
    {
      WM_LOGERROR5(F("Hdr="),   configData.header, F(",SSID="), configData.WiFi_Creds[0].wifi_ssid,
                   F(",PW="),   configData.WiFi_Creds[0].wifi_pw);
      WM_LOGERROR3(F("SSID1="), configData.WiFi_Creds[1].wifi_ssid, F(",PW1="),  configData.WiFi_Creds[1].wifi_pw);     
      WM_LOGERROR1(F("BName="), configData.board_name);     
                 
#if USE_DYNAMIC_PARAMETERS     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        WM_LOGERROR5("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }
#endif               
    }

    void displayWiFiData()
    {
      WM_LOGERROR3(F("SSID="), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
      WM_LOGERROR1(F("IP="), localIP() );
    }

#define WM_BOARD_TYPE   "RTL8720_WM"
#define WM_NO_CONFIG             "blank"

#ifndef FLASHSTORAGE_START
  #define FLASHSTORAGE_START     0
  #warning FLASHSTORAGE_START not defined. Set to 0
#else
  #if (FLASHSTORAGE_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > FLASHSTORAGE_SIZE)
    #error FLASHSTORAGE_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > FLASHSTORAGE_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define CONFIG_FLASHSTORAGE_START    (FLASHSTORAGE_START + DRD_FLAG_DATA_SIZE)

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(WM_config) - sizeof(WM_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &WM_config ) + index);
      }

      return checkSum;
    }
    
    //////////////////////////////////////////////
    
         
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
   
      WM_LOGERROR(isPersistent ? F("setForcedCP Persistent") : F("setForcedCP non-Persistent"));
   
      FlashStorage.put(CONFIG_FLASHSTORAGE_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      FlashStorage.put(CONFIG_FLASHSTORAGE_START + CONFIG_DATA_SIZE, 0);
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
      FlashStorage.get(CONFIG_FLASHSTORAGE_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////
   
#if USE_DYNAMIC_PARAMETERS
   
    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
      
      uint16_t offset = CONFIG_FLASHSTORAGE_START + sizeof(WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                  
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > BUFFER_LEN)
        {
          // Size too large, abort and flag false
          WM_LOGERROR(F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
         
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;
        
        // Prepare buffer, more than enough
        memset(readBuffer, 0, sizeof(readBuffer));
        
        // Read more than necessary, but OK and easier to code
        FlashStorage.get(offset, readBuffer);
        // NULL terminated
        readBuffer[myMenuItems[i].maxlen] = 0;

        WM_LOGDEBUG3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);     
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }   
        
        offset += myMenuItems[i].maxlen;    
      }

      FlashStorage.get(offset, readCheckSum);
           
      WM_LOGERROR3(F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////
    
    bool FLASHSTORAGE_getDynamicData()
    {
      int readCheckSum;
      int checkSum = 0;
      uint16_t offset = CONFIG_FLASHSTORAGE_START + sizeof(WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      totalDataSize = sizeof(WM_config) + sizeof(readCheckSum);
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          *_pointer = FlashStorage.readByte(offset);
          
          checkSum += *_pointer;  
         }       
      }
      
      FlashStorage.get(offset, readCheckSum);
      
      WM_LOGERROR3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////

    void FLASHSTORAGE_putDynamicData()
    {
      int checkSum = 0;
      uint16_t offset = CONFIG_FLASHSTORAGE_START + sizeof(WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        
        //WM_LOGDEBUG3(F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);

        // Must use FlashStorage.commit() to write to FlashStorage
        FlashStorage.setCommitASAP(false);
        
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          FlashStorage.writeByte(offset, *_pointer);
          
          checkSum += *_pointer;     
        }         
      }
      
      FlashStorage.put(offset, checkSum);
      
      FlashStorage.commit();
      
      // Restore CommitASAP to be safe
      FlashStorage.setCommitASAP(true);
      
      WM_LOGERROR1(F("CrCCSum=0x"), String(checkSum, HEX));
    }
#endif    // #if USE_DYNAMIC_PARAMETERS    
    
    //////////////////////////////////////////////
    
    void NULLTerminateConfig()
    {
      //#define HEADER_MAX_LEN      16
      //#define SERVER_MAX_LEN      32
      //#define TOKEN_MAX_LEN       36
      
      // NULL Terminating to be sure
      WM_config.header[HEADER_MAX_LEN - 1] = 0;
      WM_config.WiFi_Creds[0].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      WM_config.WiFi_Creds[0].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      WM_config.WiFi_Creds[1].wifi_ssid[SSID_MAX_LEN - 1] = 0;
      WM_config.WiFi_Creds[1].wifi_pw  [PASS_MAX_LEN - 1] = 0;
      WM_config.board_name[BOARD_NAME_MAX_LEN - 1]  = 0;
    }
       
    //////////////////////////////////////////////
    
    bool isWiFiConfigValid()
    {
      #if REQUIRE_ONE_SET_SSID_PW
      // If SSID ="blank" or NULL, or PWD length < 8 (as required by standard) => return false
      // Only need 1 set of valid SSID/PWD
      if (!( ( ( strncmp(WM_config.WiFi_Creds[0].wifi_ssid, WM_NO_CONFIG, strlen(WM_NO_CONFIG)) && 
                 strlen(WM_config.WiFi_Creds[0].wifi_ssid) >  0 )  &&
             (   strlen(WM_config.WiFi_Creds[0].wifi_pw) >= PASSWORD_MIN_LEN ) ) ||
             ( ( strncmp(WM_config.WiFi_Creds[1].wifi_ssid, WM_NO_CONFIG, strlen(WM_NO_CONFIG)) && 
                 strlen(WM_config.WiFi_Creds[1].wifi_ssid) >  0 )  &&
               ( strlen(WM_config.WiFi_Creds[1].wifi_pw) >= PASSWORD_MIN_LEN ) ) ))
      #else
      // If SSID ="blank" or NULL, or PWD length < 8 (as required by standard) => invalid set
      // Need both sets of valid SSID/PWD
      if ( !strncmp(WM_config.WiFi_Creds[0].wifi_ssid,   WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           !strncmp(WM_config.WiFi_Creds[0].wifi_pw,     WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           !strncmp(WM_config.WiFi_Creds[1].wifi_ssid,   WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           !strncmp(WM_config.WiFi_Creds[1].wifi_pw,     WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
           ( strlen(WM_config.WiFi_Creds[0].wifi_ssid) == 0 ) || 
           ( strlen(WM_config.WiFi_Creds[1].wifi_ssid) == 0 ) ||
           ( strlen(WM_config.WiFi_Creds[0].wifi_pw)   < PASSWORD_MIN_LEN ) ||
           ( strlen(WM_config.WiFi_Creds[1].wifi_pw)   < PASSWORD_MIN_LEN ) )
      #endif     
      {
        // If SSID, PW ="blank" or NULL, set the flag
        WM_LOGERROR(F("Invalid Stored WiFi Config Data"));
        
        // Nullify the invalid data to avoid displaying garbage
        memset(&WM_config, 0, sizeof(WM_config));
        
        hadConfigData = false;
        
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////
    
    bool FLASHSTORAGE_get()
    {
      FlashStorage.get(CONFIG_FLASHSTORAGE_START, WM_config);
      NULLTerminateConfig();
      
      return isWiFiConfigValid();
    }
    
    //////////////////////////////////////////////
    
    void FLASHSTORAGE_put()
    {
      FlashStorage.put(CONFIG_FLASHSTORAGE_START, WM_config);
    }
    
    //////////////////////////////////////////////

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      WM_config.checkSum = calChecksum;
      
      WM_LOGERROR5(F("SaveFlashStorage,Sz="), FlashStorage.length(), F(",DataSz="), totalDataSize, F(",WCSum=0x"), String(calChecksum, HEX));
      
      FLASHSTORAGE_put();
        
#if USE_DYNAMIC_PARAMETERS        
      FLASHSTORAGE_putDynamicData();
#endif        
    }    
    
    //////////////////////////////////////////////
    
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&WM_config, &defaultConfig, sizeof(WM_config));
      strcpy(WM_config.header, WM_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
          
      WM_LOGERROR(F("======= Start Loaded Config Data ======="));
      displayConfigData(WM_config);    
    }
    
    //////////////////////////////////////////////
    
    bool getConfigData()
    {
      bool dynamicDataValid = true;
      int calChecksum;   
      
      hadConfigData = false; 
           
      // Use new LOAD_DEFAULT_CONFIG_DATA logic
      if (LOAD_DEFAULT_CONFIG_DATA)
      {     
        // Load Config Data from Sketch
        loadAndSaveDefaultConfigData();
        
        // Don't need Config Portal anymore
        return true; 
      }
      else
      {   
        // Load stored config data from FlashStorage
        WM_LOGERROR1(F("FlashStoragesz:"), FLASHSTORAGE_SIZE);
        WM_LOGERROR1(F("FlashStorage Length():"), FlashStorage.length());
        
        // Get config data. If "blank" or NULL, set false flag and exit
        if (!FLASHSTORAGE_get())
        {
          return false;
        }
        
        // Verify ChkSum
        calChecksum = calcChecksum();

        WM_LOGERROR3(F("CCSum=0x"), String(calChecksum, HEX),
                   F(",RCSum=0x"), String(WM_config.checkSum, HEX));
        
#if USE_DYNAMIC_PARAMETERS        
        // Load stored dynamic data from LittleFS
        dynamicDataValid = checkDynamicData();
#endif           
                      
        // If checksum = 0 => simulated FlashStorage has been cleared (by uploading new FW, etc) => force to CP
        // If bad checksum = 0 => force to CP
        if ( (calChecksum != 0) && (calChecksum == WM_config.checkSum) )
        {
          if (dynamicDataValid)
          {
  #if USE_DYNAMIC_PARAMETERS        
            FLASHSTORAGE_getDynamicData();
            
            WM_LOGERROR(F("Valid Stored Dynamic Data"));
  #endif
           
            WM_LOGERROR(F("======= Start Stored Config Data ======="));
            displayConfigData(WM_config);
            
            // Don't need Config Portal anymore
            return true;
          }
          else
          {
            // Invalid Stored config data => Config Portal
            WM_LOGERROR(F("Invalid Stored Dynamic Data. Load default from Sketch"));
            
            // Load Default Config Data from Sketch, better than just "blank"
            loadAndSaveDefaultConfigData();
                             
            // Need Config Portal here as data can be just dummy
            // Even if you don't open CP, you're OK on next boot if your default config data is valid 
            return false;
          }
        } 
      }
      
      if ( (strncmp(WM_config.header, WM_BOARD_TYPE, strlen(WM_BOARD_TYPE)) != 0) ||
           (calChecksum != WM_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (WM_config.checkSum == 0) ) )   
      {
        // Including Credentials CSum
        WM_LOGERROR1(F("InitCfgFile,sz="), sizeof(WM_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&WM_config, &defaultConfig, sizeof(WM_config));
        }
        else
        {
          memset(&WM_config, 0, sizeof(WM_config));

#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
#endif
              
          strcpy(WM_config.WiFi_Creds[0].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WM_config.WiFi_Creds[0].wifi_pw,     WM_NO_CONFIG);
          strcpy(WM_config.WiFi_Creds[1].wifi_ssid,   WM_NO_CONFIG);
          strcpy(WM_config.WiFi_Creds[1].wifi_pw,     WM_NO_CONFIG);
          strcpy(WM_config.board_name, WM_NO_CONFIG);
          
#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(WM_config.header, WM_BOARD_TYPE);
        
#if USE_DYNAMIC_PARAMETERS
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          WM_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
#endif
        
        // Don't need
        WM_config.checkSum = 0;

        saveConfigData();
        
        return false;  
      }
      else if ( !isWiFiConfigValid() )
      {
        // If SSID, PW ="blank" or NULL, stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(WM_config);
      }

      return true;
    }
    
    //////////////////////////////////////////////
    
    // New connection logic from v1.2.0
    bool connectMultiWiFi(int retry_time)
    {
      int sleep_time  = 250;
      int index       = 0;
      int new_index   = 0;
      uint8_t status  = WL_IDLE_STATUS;
                       
      static int lastConnectedIndex = 255;

      WM_LOGDEBUG(F("ConMultiWifi"));
      
      if (static_IP != IPAddress(0, 0, 0, 0))
      {
        WM_LOGDEBUG(F("UseStatIP"));
        WiFi.config(static_IP);
      }
      
      if (lastConnectedIndex != 255)
      {
        //  Successive connection, index = ??
        // Checking if new_index is OK
        new_index = (lastConnectedIndex + 1) % NUM_WIFI_CREDENTIALS;
        
        if ( strlen(WM_config.WiFi_Creds[new_index].wifi_pw) >= PASSWORD_MIN_LEN )
        {    
          index = new_index;
          WM_LOGDEBUG3(F("Using index="), index, F(", lastConnectedIndex="), lastConnectedIndex);
        }
        else
        {
          WM_LOGERROR3(F("Ignore invalid WiFi PW : index="), new_index, F(", PW="), WM_config.WiFi_Creds[new_index].wifi_pw);
          
          // Using the previous valid index
          index = lastConnectedIndex;
        }
      }
      else
      {
        //  First connection ever, index = 0
        if ( strlen(WM_config.WiFi_Creds[0].wifi_pw) >= PASSWORD_MIN_LEN )
        {    
          WM_LOGDEBUG(F("First connection, Using index=0"));
        }
        else
        {
          WM_LOGERROR3(F("Ignore invalid WiFi PW : index=0, SSID="), WM_config.WiFi_Creds[0].wifi_ssid,
                       F(", PWD="), WM_config.WiFi_Creds[0].wifi_pw);
          
          // Using the next valid index
          index = 1;
        }
      } 
         
      WM_LOGERROR3(F("con2WF:SSID="), WM_config.WiFi_Creds[index].wifi_ssid,
                   F(",PW="), WM_config.WiFi_Creds[index].wifi_pw);
      
      uint8_t numIndexTried = 0;
      
      while ( !wifi_connected && (numIndexTried++ < NUM_WIFI_CREDENTIALS) )
      {         
        while ( 0 < retry_time )
        {      
          WM_LOGDEBUG1(F("Remaining retry_time="), retry_time);
          
          status = WiFi.begin(WM_config.WiFi_Creds[index].wifi_ssid, WM_config.WiFi_Creds[index].wifi_pw); 
              
          // Need restart WiFi at beginning of each cycle 
          if (status == WL_CONNECTED)
          {
            wifi_connected = true;          
            lastConnectedIndex = index;                                     
            WM_LOGDEBUG1(F("WOK, lastConnectedIndex="), lastConnectedIndex);
            
            break;
          }
          else
          {
            delay(sleep_time);
            retry_time--;
          }         
        }
        
        if (status == WL_CONNECTED)
        {         
          break;
        }
        else
        {        
          if (retry_time <= 0)
          {      
            WM_LOGERROR3(F("Failed using index="), index, F(", retry_time="), retry_time);
            retry_time = RETRY_TIMES_CONNECT_WIFI;  
          }
          
          new_index = (index + 1) % NUM_WIFI_CREDENTIALS;
          
          // only use new index if valid (len >= PASSWORD_MIN_LEN = 8)
          if ( strlen(WM_config.WiFi_Creds[new_index].wifi_pw) >= PASSWORD_MIN_LEN )
          {
            index = new_index;
          }
          
          //WiFi.end();
        }
      }

      if (wifi_connected)
      {
        WM_LOGERROR(F("con2WF:OK"));
        
        WM_LOGERROR1(F("IP="), WiFi.localIP() );
        
        displayWiFiData();
      }
      else
      {
        WM_LOGERROR(F("con2WF:failed"));  
        // Can't connect, so try another index next time. Faking this index is OK and lost
        lastConnectedIndex = index;  
      }

      return wifi_connected;  
    }
    
    //////////////////////////////////////////////
    
    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template  = WM_HTML_HEAD_START;
      
  #if USING_CUSTOMS_STYLE
      // Using Customs style when not NULL
      if (WM_HTML_HEAD_CUSTOMS_STYLE)
        root_html_template  += WM_HTML_HEAD_CUSTOMS_STYLE;
      else
        root_html_template  += WM_HTML_HEAD_STYLE;
  #else     
      root_html_template  += WM_HTML_HEAD_STYLE;
  #endif
      
  #if USING_CUSTOMS_HEAD_ELEMENT
      if (_CustomsHeadElement)
        root_html_template += _CustomsHeadElement;
  #endif          
      
#if SCAN_WIFI_NETWORKS
      WM_LOGDEBUG1(WiFiNetworksFound, F(" SSIDs found, generating HTML now"));
      // Replace HTML <input...> with <select...>, based on WiFi network scan in startConfigurationMode()

      ListOfSSIDs = "";

      for (int i = 0, list_items = 0; (i < WiFiNetworksFound) && (list_items < MAX_SSID_IN_LIST); i++)
      {
        if (indices[i] == -1) 
          continue; 		// skip duplicates and those that are below the required quality
          
        ListOfSSIDs += WM_OPTION_START + String(WiFi.SSID(indices[i])) + WM_OPTION_END;	
        list_items++;		// Count number of suitable, distinct SSIDs to be included in list
      }

      WM_LOGDEBUG(ListOfSSIDs);

      if (ListOfSSIDs == "")		// No SSID found or none was good enough
        ListOfSSIDs = WM_OPTION_START + String(WM_NO_NETWORKS_FOUND) + WM_OPTION_END;

      pitem = String(WM_HTML_HEAD_END);

#if MANUAL_SSID_INPUT_ALLOWED
      pitem.replace("[[input_id]]",  "<input id='id' list='SSIDs'>"  + String(WM_DATALIST_START) + "'SSIDs'>" + ListOfSSIDs + WM_DATALIST_END);
      WM_LOGDEBUG1(F("pitem:"), pitem);
      pitem.replace("[[input_id1]]", "<input id='id1' list='SSIDs'>" + String(WM_DATALIST_START) + "'SSIDs'>" + ListOfSSIDs + WM_DATALIST_END);
      
      WM_LOGDEBUG1(F("pitem:"), pitem);

#else
      pitem.replace("[[input_id]]",  "<select id='id'>"  + ListOfSSIDs + WM_SELECT_END);
      pitem.replace("[[input_id1]]", "<select id='id1'>" + ListOfSSIDs + WM_SELECT_END);
#endif

      root_html_template += pitem + WM_FLDSET_START;

#else

      pitem = String(WM_HTML_HEAD_END);
      pitem.replace("[[input_id]]",  WM_HTML_INPUT_ID);
      pitem.replace("[[input_id1]]", WM_HTML_INPUT_ID1);
      root_html_template += pitem + WM_FLDSET_START;

#endif    // SCAN_WIFI_NETWORKS

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WM_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(WM_FLDSET_END) + WM_HTML_BUTTON + WM_HTML_SCRIPT;     

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(WM_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(WM_HTML_SCRIPT_END) + WM_HTML_END;
      
      return;     
    }
       
    //////////////////////////////////////////////

    void serverSendHeaders()
    {
      WM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CACHE_CONTROL:"), WM_HTTP_CACHE_CONTROL, "=", WM_HTTP_NO_STORE);
      server->sendHeader(WM_HTTP_CACHE_CONTROL, WM_HTTP_NO_STORE);
      
#if USING_CORS_FEATURE
      // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"
      WM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CORS:"), WM_HTTP_CORS, " : ", _CORS_Header);
      server->sendHeader(WM_HTTP_CORS, _CORS_Header);
#endif
     
      WM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_PRAGMA:"), WM_HTTP_PRAGMA, " : ", WM_HTTP_NO_CACHE);
      server->sendHeader(WM_HTTP_PRAGMA, WM_HTTP_NO_CACHE);
      
      WM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_EXPIRES:"), WM_HTTP_EXPIRES, " : ", "-1");
      server->sendHeader(WM_HTTP_EXPIRES, "-1");
    }
       
    //////////////////////////////////////////////

    void handleRequest()
    {
      if (server)
      {        
        String key    = server->arg("key");
        String value  = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          // New from v1.1.0         
          serverSendHeaders();        
          //////
          
          String result;
          createHTML(result);

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;

          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("RTL8720_WM", RFC952_hostname);
          }
          else if ( WM_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("RTL8720_WM", WM_config.board_name);
          }

          if (hadConfigData)
          {
            result.replace("[[id]]",     WM_config.WiFi_Creds[0].wifi_ssid);
            result.replace("[[pw]]",     WM_config.WiFi_Creds[0].wifi_pw);
            result.replace("[[id1]]",    WM_config.WiFi_Creds[1].wifi_ssid);
            result.replace("[[pw1]]",    WM_config.WiFi_Creds[1].wifi_pw);
            result.replace("[[nm]]",     WM_config.board_name);
          }
          else
          {
            result.replace("[[id]]",  "");
            result.replace("[[pw]]",  "");
            result.replace("[[id1]]", "");
            result.replace("[[pw1]]", "");
            result.replace("[[nm]]",  "");
          }
          
#if USE_DYNAMIC_PARAMETERS          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
          }
#endif


          WM_LOGDEBUG1(F("h:HTML page size:"), result.length());
          WM_LOGDEBUG1(F("h:HTML="), result);
          
          server->send(200, WM_HTTP_HEAD_TEXT_HTML, result);

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&WM_config, 0, sizeof(WM_config));
          strcpy(WM_config.header, WM_BOARD_TYPE);
        }

#if USE_DYNAMIC_PARAMETERS
        if (!menuItemUpdated)
        {
          // Don't need to free
          menuItemUpdated = new bool[NUM_MENU_ITEMS];
          
          if (menuItemUpdated)
          {
            for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
            {           
              // To flag item is not yet updated
              menuItemUpdated[i] = false;       
            }
            
            WM_LOGDEBUG1(F("h: Init menuItemUpdated :" ), NUM_MENU_ITEMS);                    
          }
          else
          {
            WM_LOGERROR(F("h: Error can't alloc memory for menuItemUpdated" ));
          }
        }  
#endif

        static bool id_Updated  = false;
        static bool pw_Updated  = false;
        static bool id1_Updated = false;
        static bool pw1_Updated = false;
        static bool nm_Updated  = false;
          
        if (!id_Updated && (key == String("id")))
        {   
          WM_LOGDEBUG(F("h:repl id"));
          id_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WM_config.WiFi_Creds[0].wifi_ssid) - 1)
            strcpy(WM_config.WiFi_Creds[0].wifi_ssid, value.c_str());
          else
            strncpy(WM_config.WiFi_Creds[0].wifi_ssid, value.c_str(), sizeof(WM_config.WiFi_Creds[0].wifi_ssid) - 1);
        }
        else if (!pw_Updated && (key == String("pw")))
        {    
          WM_LOGDEBUG(F("h:repl pw"));
          pw_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WM_config.WiFi_Creds[0].wifi_pw) - 1)
            strcpy(WM_config.WiFi_Creds[0].wifi_pw, value.c_str());
          else
            strncpy(WM_config.WiFi_Creds[0].wifi_pw, value.c_str(), sizeof(WM_config.WiFi_Creds[0].wifi_pw) - 1);
        }
        else if (!id1_Updated && (key == String("id1")))
        {   
          WM_LOGDEBUG(F("h:repl id1"));
          id1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WM_config.WiFi_Creds[1].wifi_ssid) - 1)
            strcpy(WM_config.WiFi_Creds[1].wifi_ssid, value.c_str());
          else
            strncpy(WM_config.WiFi_Creds[1].wifi_ssid, value.c_str(), sizeof(WM_config.WiFi_Creds[1].wifi_ssid) - 1);
        }
        else if (!pw1_Updated && (key == String("pw1")))
        {    
          WM_LOGDEBUG(F("h:repl pw1"));
          pw1_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WM_config.WiFi_Creds[1].wifi_pw) - 1)
            strcpy(WM_config.WiFi_Creds[1].wifi_pw, value.c_str());
          else
            strncpy(WM_config.WiFi_Creds[1].wifi_pw, value.c_str(), sizeof(WM_config.WiFi_Creds[1].wifi_pw) - 1);
        }
        else if (!nm_Updated && (key == String("nm")))
        {
          WM_LOGDEBUG(F("h:repl nm"));
          nm_Updated = true;
          
          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(WM_config.board_name) - 1)
            strcpy(WM_config.board_name, value.c_str());
          else
            strncpy(WM_config.board_name, value.c_str(), sizeof(WM_config.board_name) - 1);
        }
        else
        {
        
#if USE_DYNAMIC_PARAMETERS        
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {           
            if ( !menuItemUpdated[i] && (key == myMenuItems[i].id) )
            {
              WM_LOGDEBUG3(F("h:"), myMenuItems[i].id, F("="), value.c_str() );
              
              menuItemUpdated[i] = true;
              
              number_items_Updated++;

              // Actual size of pdata is [maxlen + 1]
              memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

              if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
                strcpy(myMenuItems[i].pdata, value.c_str());
              else
                strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
                
              break;  
            }
          }
#endif
        }
        
        WM_LOGDEBUG1(F("h:items updated ="), number_items_Updated);
        WM_LOGDEBUG3(F("h:key ="), key, ", value =", value);

        server->send(200, WM_HTTP_HEAD_TEXT_HTML, "OK");

#if USE_DYNAMIC_PARAMETERS        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif 
        {
          WM_LOGERROR(F("h:UpdFlashStorage"));

          saveConfigData();
          
          // Done with CP, Clear CP Flag here if forced
          if (isForcedConfigPortal)
            clearForcedCP();

          WM_LOGERROR(F("h:Rst"));

          // TO DO : what command to reset
          // Delay then reset the board after save data
          delay(1000);
          resetFunc();  //call reset
        }
      }   // if (server)
    }
    
    //////////////////////////////////////////////

#ifndef CONFIG_TIMEOUT
  #warning Default CONFIG_TIMEOUT = 60s
  #define CONFIG_TIMEOUT			60000L
#endif

    void startConfigurationMode()
    {
#if SCAN_WIFI_NETWORKS
	    configTimeout = 0;  // To allow user input in CP
	    
	    WiFiNetworksFound = scanWifiNetworks(&indices);	
#endif
    
      WiFi.config(portal_apIP);

      if ( (portal_ssid == "") || portal_pass == "" )
      {
        String randomNum = String(random(0xFFFFFF), HEX);
        randomNum.toUpperCase();

        portal_ssid = "WM_" + randomNum;
        portal_pass = "MyWM_" + randomNum;
      }
      
      // start access point, AP only, channel 10
           
      uint16_t channel;
     
      // Use random channel if  AP_channel == 0     
      if (AP_channel == 0)
        channel = (millis() % MAX_WIFI_CHANNEL) + 1;
      else
        channel = AP_channel;

      WM_LOGERROR3(F("SSID="), portal_ssid, F(",PW="), portal_pass);
      WM_LOGERROR3(F("IP="), portal_apIP, F(",CH="), channel);

#if USE_ESP_AT_SHIELD
      // start access point, AP only,default channel 10
      WiFi.beginAP(portal_ssid.c_str(), channel, portal_pass.c_str(), ENC_TYPE_WPA2_PSK, true);
#else
      // start access point, AP only,default channel 10
      WiFi.beginAP(portal_ssid.c_str(), portal_pass.c_str(), channel);
#endif
      

      if (!server)
      {
        server = new WiFiWebServer;
      }

      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1

      if (server)
      {
        server->on("/", [this](){ handleRequest(); });
        server->begin();
      }

      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
      {
        configTimeout = millis() + CONFIG_TIMEOUT;
                      
        WM_LOGDEBUG3(F("s:millis() = "), millis(), F(", configTimeout = "), configTimeout);
      }
      else
      {
        configTimeout = 0;
               
        WM_LOGDEBUG(F("s:configTimeout = 0"));    
      }

      configuration_mode = true;
    }
    
#if SCAN_WIFI_NETWORKS

	  // Source code adapted from https://github.com/khoih-prog/ESP_WiFiManager/blob/master/src/ESP_WiFiManager-Impl.h

    int           _paramsCount            = 0;
    int           _minimumQuality         = -1;
    bool          _removeDuplicateAPs     = true;
	
	  //////////////////////////////////////////
    
    void swap(int *thisOne, int *thatOne)
    {
       int tempo;

       tempo    = *thatOne;
       *thatOne = *thisOne;
       *thisOne = tempo;
    }

    //////////////////////////////////////////
	
	  void setMinimumSignalQuality(int quality)
	  {
	    _minimumQuality = quality;
	  }

	  //////////////////////////////////////////

	  //if this is true, remove duplicate Access Points - default true
	  void setRemoveDuplicateAPs(bool removeDuplicates)
	  {
	    _removeDuplicateAPs = removeDuplicates;
	  }

	  //////////////////////////////////////////

	  //Scan for WiFiNetworks in range and sort by signal strength
	  //space for indices array allocated on the heap and should be freed when no longer required  
	  int scanWifiNetworks(int **indicesptr)
	  {
	    WM_LOGDEBUG(F("Scanning Network"));

	    int n = WiFi.scanNetworks();

	    WM_LOGDEBUG1(F("scanWifiNetworks: Done, Scanned Networks n = "), n); 

	    //KH, Terrible bug here. WiFi.scanNetworks() returns n < 0 => malloc( negative == very big ) => crash!!!
	    //In .../esp32/libraries/WiFi/src/WiFiType.h
	    //#define WIFI_SCAN_RUNNING   (-1)
	    //#define WIFI_SCAN_FAILED    (-2)
	    //if (n == 0)
	    if (n <= 0)
	    {
		    WM_LOGDEBUG(F("No network found"));
		    return (0);
	    }
	    else
	    {
		    // Allocate space off the heap for indices array.
		    // This space should be freed when no longer required.
		    int* indices = (int *)malloc(n * sizeof(int));

		    if (indices == NULL)
		    {
		      WM_LOGDEBUG(F("ERROR: Out of memory"));
		      *indicesptr = NULL;
		      return (0);
		    }

		    *indicesptr = indices;
	       
		    //sort networks
		    for (int i = 0; i < n; i++)
		    {
		      indices[i] = i;
		    }

		    WM_LOGDEBUG(F("Sorting"));

		    // RSSI SORT
		    // old sort
		    for (int i = 0; i < n; i++)
		    {
		      for (int j = i + 1; j < n; j++)
		      {
			      if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i]))
			      {
                    //std::swap(indices[i], indices[j]);
                    // Using locally defined swap()
                    swap(&indices[i], &indices[j]);
       			}
		      }
		    }

		    WM_LOGDEBUG(F("Removing Dup"));

		    // remove duplicates ( must be RSSI sorted )
		    if (_removeDuplicateAPs)
		    {
		      String cssid;
		      
		      for (int i = 0; i < n; i++)
		      {
			      if (indices[i] == -1)
			        continue;

			      cssid = WiFi.SSID(indices[i]);
			      
			      for (int j = i + 1; j < n; j++)
			      {
			        if (cssid == WiFi.SSID(indices[j]))
			        {
				        WM_LOGDEBUG1("DUP AP:", WiFi.SSID(indices[j]));
				        indices[j] = -1; // set dup aps to index -1
			        }
			      }
		      }
		    }

		    for (int i = 0; i < n; i++)
		    {
		      if (indices[i] == -1)
			      continue; // skip dups

		      int quality = getRSSIasQuality(WiFi.RSSI(indices[i]));

		      if (!(_minimumQuality == -1 || _minimumQuality < quality))
		      {
			      indices[i] = -1;
			      WM_LOGDEBUG(F("Skipping low quality"));
		      }
		    }

		    WM_LOGDEBUG(F("WiFi networks found:"));
		    
		    for (int i = 0; i < n; i++)
		    {
		      if (indices[i] == -1)
			      continue; // skip dups
		      else
			      WM_LOGDEBUG5(i+1,": ",WiFi.SSID(indices[i]), ", ", WiFi.RSSI(i), "dB");
		    }

		    return (n);
	    }
	  }

	  //////////////////////////////////////////

	  int getRSSIasQuality(int RSSI)
	  {
	    int quality = 0;

	    if (RSSI <= -100)
	    {
		    quality = 0;
	    }
	    else if (RSSI >= -50)
	    {
		    quality = 100;
	    }
	    else
	    {
		    quality = 2 * (RSSI + 100);
	    }

	    return quality;
	  }

  //////////////////////////////////////////

#endif	       
};

#endif    //WiFiManager_RTL8720_h
