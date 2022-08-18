## WiFiManager_RTL8720 (Light Weight Credentials / WiFi Manager for RTL8720DN, RTL8722DM, RTL8722CSM, etc. modules/shields)

[![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_RTL8720.svg?)](https://www.ardu-badge.com/WiFiManager_RTL8720)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WiFiManager_RTL8720.svg)](https://github.com/khoih-prog/WiFiManager_RTL8720/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/WiFiManager_RTL8720/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WiFiManager_RTL8720.svg)](http://github.com/khoih-prog/WiFiManager_RTL8720/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Why do we need this WiFiManager_RTL8720 library](#why-do-we-need-this-WiFiManager_RTL8720-library)
  * [Features](#features)
  * [WiFiMulti_Generic library usage](#WiFiMulti_Generic-library-usage)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For AmebaD boards](#1-for-AmebaD-boards)
* [How It Works](#how-it-works)
* [How to use](#how-to-use)
  * [ 1. Basic usage](#1-basic-usage)
  * [ 2. Add custom parameters](#2-add-custom-parameters)
  * [ 3. Not using custom parameters](#3-not-using-custom-parameters)
  * [ 4. To open Config Portal](#4-to-open-config-portal)
  * [ 5. To use different AP WiFi Channel](#5-to-use-different-ap-wifi-channel)
  * [ 6. To use different static AP IP from default](#6-to-use-different-static-ap-ip-from-default)
  * [ 7. To use custom DHCP HostName](#7-to-use-custom-dhcp-hostname)
  * [ 8. To use custom HTML Style](#8-to-use-custom-html-style)
  * [ 9. To use custom Head Elements](#9-to-use-custom-head-elements)
  * [10. To use CORS Header](#10-to-use-cors-header)
  * [11. To use and input only one set of WiFi SSID and PWD](#11-to-use-and-input-only-one-set-of-wifi-ssid-and-pwd)
    * [11.1 If you need to use and input only one set of WiFi SSID/PWD](#111-if-you-need-to-use-and-input-only-one-set-of-wifi-ssidpwd)
    * [11.2 If you need to use both sets of WiFi SSID/PWD](#112-if-you-need-to-use-both-sets-of-wifi-ssidpwd)
  * [12. To enable auto-scan of WiFi networks for selection in Configuration Portal](#12-to-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [12.1 Enable auto-scan of WiFi networks for selection in Configuration Portal](#121-enable-auto-scan-of-wifi-networks-for-selection-in-configuration-portal)
    * [12.2 Disable manually input SSIDs](#122-disable-manually-input-ssids)
    * [12.3 Select maximum number of SSIDs in the list](#123-select-maximum-number-of-ssids-in-the-list)
  * [13. To avoid blocking in loop when WiFi is lost](#13-To-avoid-blocking-in-loop-when-wifi-is-lost)
    * [13.1 Max times to try WiFi per loop](#131-max-times-to-try-wifi-per-loop)
    * [13.2 Interval between reconnection WiFi if lost](#132-interval-between-reconnection-wifi-if-lost)
  * [14. Not using Board_Name on Config_Portal](#14-Not-using-Board_Name-on-Config_Portal)
  * [15. How to use CONFIG_MODE_LED](#15-How-to-use-CONFIG_MODE_LED)
* [Examples](#examples)
  * [ 1. RTL8720_WiFi](examples/RTL8720_WiFi)
  * [ 2. RTL8720_WiFi_MQTT](examples/RTL8720_WiFi_MQTT) **New**
* [So, how it works?](#so-how-it-works)
  * [1. Without SCAN_WIFI_NETWORKS](#1-without-scan_wifi_networks)
  * [2. With SCAN_WIFI_NETWORKS](#2-with-scan_wifi_networks)
* [Important Configuration Notes](#important-Configuration-notes)
* [How to use default Credentials and have them pre-loaded onto Config Portal](#how-to-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
  * [1. To always load Default Credentials and override Config Portal data](#1-to-always-load-default-credentials-and-override-config-portal-data)
  * [2. To load Default Credentials when there is no valid Credential](#2-to-load-default-credentials-when-there-is-no-valid-credential)
  * [3. Example of Default Credentials](#3-example-of-default-credentials)
* [How to add dynamic parameters from sketch](#how-to-add-dynamic-parameters-from-sketch)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Example RTL8720_WiFi](#example-RTL8720_WiFi)
  * [1. File RTL8720_WiFi.ino](#1-file-RTL8720_WiFiino)
  * [2. File defines.h](#2-file-definesh)
  * [3. File Credentials.h](#3-file-credentialsh)
  * [4. File dynamicParams.h](#4-file-dynamicparamsh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. RTL8720_WiFi on Rtlduino RTL8720DN](#1-RTL8720_WiFi-on-Rtlduino-RTL8720DN) 
    * [1.1 Open Config Portal](#11-open-config-portal)
    * [1.2 Received data from Config Portal](#12-received-data-from-config-portal)
    * [1.3 Got valid Credential from Config Portal, then connected to WiFi](#13-got-valid-credential-from-config-portal-then-connected-to-wifi)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [WiFiManager_RTL8720 library](https://github.com/khoih-prog/WiFiManager_RTL8720)

#### Features

If you have used the full-fledge WiFiManager such as :

1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)
3. [`Khoi Hoang ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)

and have to write **complicated callback functions** to save custom parameters in SPIFFS/LittleFS/EEPROM, you'd appreciate the simplicity of this Light-Weight Credentials / WiFiManager.

This library is a Light Weight Credentials / WiFiManager for , etc. boards

This is a Credentials / WiFi Connection Manager, permitting the addition of custom parameters to be configured in Config Portal. The parameters then will be saved automatically, **without the complicated callback functions** to handle data saving / retrieving.

You can also specify DHCP HostName, static AP and STA IP. Use much less memory compared to full-fledge WiFiManager. Config Portal will be auto-adjusted to match the number of dynamic custom parameters. Credentials are saved in FlashStorage_RTL8720.

The web configuration portal, served from the `RTL8720DN` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

New recent features:

- **MultiWiFi** feature for configuring/auto(re)connecting shields to the available MultiWiFi APs at runtime.
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- **Powerful-yet-simple-to-use feature to enable adding dynamic custom parameters** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
- Optional default **Credentials as well as Dynamic parameters to be optionally autoloaded into Config Portal** to use or change instead of manually input.
- Dynamic custom parameters to be saved **automatically in non-volatile memory, such as FlashStorage_RTL8720**.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are designed to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
- Control Config Portal from software or Virtual Switches
- To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP
- Use new FlashStorage_RTL8720 features
- **Scan WiFi networks** for selection in Configuration Portal

---

#### WiFiMulti_Generic library usage

The usage the new [WiFiMulti_Generic](https://github.com/khoih-prog/WiFiMulti_Generic) library to help connect to the best of **multi-WiFi APs**, with **auto-checking / auto-reconnecting** features when WiFi connection is lost.


---

#### Currently supported Boards

This [**WiFiManager_RTL8720** library](https://github.com/khoih-prog/WiFiManager_RTL8720) currently supports these following boards:

 1. **RTL8720DN, RTL8722DM, RTM8722CSM, etc. boards**


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino AmebaD core 3.1.2+`](https://github.com/ambiot/ambd_arduino) for Realtek RTL8720DN, RTL8722DM and RTM8722CSM. [![GitHub release](https://img.shields.io/github/release/ambiot/ambd_arduino.svg)](https://github.com/ambiot/ambd_arduino/releases/latest)
 3. [`FlashStorage_RTL8720 library v1.1.0+`](https://github.com/khoih-prog/FlashStorage_RTL8720). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_RTL8720.svg)](https://github.com/khoih-prog/FlashStorage_RTL8720/releases/latest)
 4. [`DoubleResetDetector_Generic v1.8.1+`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)
 5. [`MultiResetDetector_Generic v1.8.1+`](https://github.com/khoih-prog/MultiResetDetector_Generic). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/MultiResetDetector_Generic.svg?)](https://www.ardu-badge.com/MultiResetDetector_Generic)
 6. [`WiFiMulti_Generic library v1.1.1+`](https://github.com/khoih-prog/WiFiMulti_Generic) to use WiFiMulti function. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiMulti_Generic.svg?)](https://www.ardu-badge.com/WiFiMulti_Generic). **New**
 7. [`Modified Adafruit_MQTT_Library v2.4.2+`](https://github.com/khoih-prog/Adafruit_MQTT_Library) to use MQTT examples for many boards.

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**WiFiManager_RTL8720**](https://github.com/khoih-prog/WiFiManager_RTL8720), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiManager_RTL8720.svg?)](https://www.ardu-badge.com/WiFiManager_RTL8720) for more detailed instructions.

### Manual Install

1. Navigate to [**WiFiManager_RTL8720**](https://github.com/khoih-prog/WiFiManager_RTL8720) page.
2. Download the latest release `WiFiManager_RTL8720-main.zip`.
3. Extract the zip file to `WiFiManager_RTL8720-main` directory 
4. Copy the whole 
  - `WiFiManager_RTL8720-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**WiFiManager_RTL8720** library](https://registry.platformio.org/libraries/khoih-prog/WiFiManager_RTL8720) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/WiFiManager_RTL8720/installation). Search for **WiFiManager_RTL8720** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For AmebaD boards

 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.2. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


---
---

## How It Works

- The [**RTL8720_WiFi**](examples/RTL8720_WiFi) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of [**RTL8720_WiFi**](examples/RTL8720_WiFi) is that a new `RTL8720` will start a WiFi configuration portal when powered up, but has no valid stored Credentials or can't connect to WiFi APs after a pre-determined time.
- There are 6 more custom parameters added in the sketch which you can use in your program later. In the example, they are: 2 sets of Blynk Servers and Tokens, Blynk Port and MQTT Server.
- Using any WiFi enabled device with a browser (computer, phone, tablet) connect to the newly created AP and type in the configurable AP IP address (default 192.168.4.1). The Config Portal AP channel (default 10) is also configurable to avoid conflict with other APs.
- The Config Portal is **auto-adjusted** to fix the 4 static parameters (WiFi SSIDs/PWDs) as well as 6 more dynamic custom parameters.
- After the custom data entered, and **Save** button pressed, the configuration data will be saved in host's non-volatile memory, then the board reboots.
- If there is valid stored Credentials, it'll go directly to connect to one of the **MultiWiFi APs** without starting / using the Config Portal.
- `AmebaD RTL8720` will try to connect. If successful, the dynamic DHCP and/or configured static IP address will be displayed in the configuration portal. 
- The `AmebaD RTL8720` WiFi Config Portal network and Web Server will shutdown to return control to the sketch code.
- In the operation, if the current WiFi connection is lost because of any reason, the system will **auto(Re)connect** to the remaining WiFi AP.
- **If system can't connect to any of the 2 WiFi APs, the Config Portal will start**, after some pre-determined time, to permit user to update the Credentials.

---

### How to use

#### 1. Basic usage

- Include in your sketch

```cpp
// Must be before #include <WiFiManager_RTL8720.h>
// Start location in EEPROM to store config data. Default 0
// Config data Siz, not including your custom data, currently is 84 bytes)
#define EEPROM_START      0

#include <WiFiManager_RTL8720.h>

WiFiManager_RTL8720* WiFiManager;
```

#### 2. Add custom parameters

- To add custom parameters, just add

```
#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in <WiFiManager_RTL8720.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN + 1]  = "account.duckdns.org";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN + 1]   = "token1";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN + 1]  = "account.ddns.net";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN + 1]   = "token2";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "8080";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt.duckdns.org";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "prt", "Port",          Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mqt", "MQTT Server",   MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS

```

#### 3. Not using custom parameters

- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS      false
```

#### 4. To open Config Portal

- When you want to open a config portal, just add

```cpp
WiFiManager = new WiFiManager_RTL8720();
WiFiManager->begin();
```

#### 5. To use different AP WiFi Channel

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs : 

```cpp
WiFiManager->setConfigPortalChannel(newChannel);
```

- To use random AP WiFi Channel to avoid conflict with other WiFi APs : 

```cpp
WiFiManager->setConfigPortalChannel(0);
```

#### 6. To use different static AP IP from default

- To use different static AP IP (not use default `192.168.4.1`), call

```cpp
WiFiManager->setConfigPortalIP(IPAddress(xxx,xxx,xxx,xxx));
```

#### 7. To use custom DHCP HostName

- To set custom DHCP HostName :
 
```
  // Set customized DHCP HostName
  WiFiManager->begin("SAMD_ABCDEF");
```
 
or just use the default Hostname, for example "SAMD_XXXXXX" for SAMD

```
  //Or use default Hostname "WM_RTL8720"
  //WiFiManager->begin();
```

#### 8. To use custom HTML Style

```
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

...

WiFiManager->setCustomsStyle(NewCustomsStyle);
```

#### 9. To use custom Head Elements


```
WiFiManager->setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
```

#### 10. To use CORS Header

```
WiFiManager->setCORSHeader("Your Access-Control-Allow-Origin");
```

While in AP mode, connect to it using its `SSID` (WM_RTL8720) / `Password` ("MyWM_RTL8720"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then click **Save**. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


Once Credentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.


#### 11. To use and input only one set of WiFi SSID and PWD

#### 11.1 If you need to use and input only one set of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       true
```
But it's always advisable to use and input both sets for reliability.
 
#### 11.2 If you need to use both sets of WiFi SSID/PWD

```
// Permit input only one set of WiFi SSID/PWD. The other can be "NULL or "blank"
// Default is false (if not defined) => must input 2 sets of SSID/PWD
#define REQUIRE_ONE_SET_SSID_PW       false
```

#### 12. To enable auto-scan of WiFi networks for selection in Configuration Portal

#### 12.1 Enable auto-scan of WiFi networks for selection in Configuration Portal


```
#define SCAN_WIFI_NETWORKS                  true
```

The manual input of SSIDs is default enabled, so that users can input arbitrary SSID, not only from the scanned list. This is for the sample use-cases in which users can input the known SSIDs of another place, then send the boards to that place. The boards can connect to WiFi without users entering Config Portal to re-configure.

#### 12.2 Disable manually input SSIDs

```
// To disable manually input SSID, only from a scanned SSID lists
#define MANUAL_SSID_INPUT_ALLOWED           false
```

This is for normal use-cases in which users can only select an SSID from a scanned list of SSIDs to avoid typo mistakes and/or security.

#### 12.3 Select maximum number of SSIDs in the list

The maximum number of SSIDs in the list is selectable from 2 to 15 (for ESP8266/ESP32-AT shields, from 2-6). If invalid number of SSIDs is selected, the default number of 10 will be used.


```
// From 2-15
#define MAX_SSID_IN_LIST                    8
```

#### 13. To avoid blocking in loop when WiFi is lost


#### 13.1 Max times to try WiFi per loop

To define max times to try WiFi per loop() iteration. To avoid blocking issue in loop()

Default is 1 if not defined, and minimum is forced to be 1.

To use, uncomment in `defines.h`. 

Check [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/18#issue-1094004380)

```
#define MAX_NUM_WIFI_RECON_TRIES_PER_LOOP     2
```

#### 13.2 Interval between reconnection WiFi if lost

Default is no interval between reconnection WiFi times if lost WiFi. Max permitted interval will be 10mins.

Uncomment to use. Be careful, WiFi reconnection will be delayed if using this method.

Only use whenever urgent tasks in loop() can't be delayed. But if so, it's better you have to rewrite your code, e.g. using higher priority tasks.

Check [retries block the main loop #18](https://github.com/khoih-prog/WiFiManager_NINA_Lite/issues/18#issuecomment-1006197561)

```
#define WIFI_RECON_INTERVAL                   30000     // 30s
```

#### 14. Not using Board_Name on Config_Portal

Default is `true`. Just change to `false` to Not using `Board_Name` on Config_Portal

```
/////////////////////////////////////////////

// Optional, to use Board Name in Menu
#define USING_BOARD_NAME                    false

/////////////////////////////////////////////
```

#### 15. How to use CONFIG_MODE_LED

Check the examples

https://github.com/khoih-prog/WiFiManager_RTL8720/blob/49c1aff82d2742a2e0b787a24009d2905b76ee3c/examples/RP2040_WiFi/RP2040_WiFi.ino#L22-L30


https://github.com/khoih-prog/WiFiManager_RTL8720/blob/49c1aff82d2742a2e0b787a24009d2905b76ee3c/examples/RP2040_WiFi/defines.h#L191-L208



---
---

### Examples

 1. [RTL8720_WiFi](examples/RTL8720_WiFi)
 2. [RTL8720_WiFi_MQTT](examples/RTL8720_WiFi_MQTT) **New**
 
---
---

## So, how it works?

In `Configuration Portal Mode`, it starts an AP called `WM_RTL8720`. Connect to it using the `configurable password` you can define in the code. For example, `MyWM_RTL8720` (see examples):

After you connected, please, go to http://192.168.4.1 or newly configured AP IP, you'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_RTL8720/blob/main/pics/Main.png">
</p>

Enter your credentials, 

### 1. Without SCAN_WIFI_NETWORKS

<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_RTL8720/blob/main/pics/Input.png">
</p>

### 2. With SCAN_WIFI_NETWORKS


<p align="center">
    <img src="https://github.com/khoih-prog/WiFiManager_RTL8720/blob/main/pics/Input_With_Scan.png">
</p>


---

### Important Configuration Notes

1. Now you can use special chars such as **~, !, @, #, $, %, ^, &, _, -, space,etc.** thanks to [brondolin](https://github.com/brondolin) to provide the amazing fix in [**Blynk_WM**](https://github.com/khoih-prog/Blynk_WM) to permit input special chars such as **%** and **#** into data fields. See [Issue 3](https://github.com/khoih-prog/Blynk_WM/issues/3).
2. The SSIDs, Passwords must be input (or to make them different from **blank**). Otherwise, the Config Portal will re-open until those fields have been changed. If you don't need any field, just input anything or use duplicated data from similar field.
3. WiFi password max length now is 63 chars according to WPA2 standard.

---

### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

#### 1. To always load [Default Credentials](examples/RTL8720_WiFi/Credentials.h) and override Config Portal data

```
// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To load [Default Credentials](examples/RTL8720_WiFi/Credentials.h) when there is no valid Credential.

Config Portal data input will be override DEFAULT_CONFIG_DATA

```
// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

#### 3. Example of [Default Credentials](examples/RTL8720_WiFi/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header, just add board_name 
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [24];
  int  checkSum;
} ESP_WM_LITE_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      false

#if TO_LOAD_DEFAULT_CONFIG_DATA

// This feature is primarily used in development to force a known set of values as Config Data
// It will NOT force the Config Portal to activate. Use DRD or erase Config Data with ESP_WiFiManager.clearConfigData()

// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
//bool LOAD_DEFAULT_CONFIG_DATA = true;

// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;


WM_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "RTL8720",

  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  //char board_name     [24];

  "RTL8720-Control",

  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

WM_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////


#endif    //Credentials_h
```

### How to add dynamic parameters from sketch

Example of [Default dynamicParams](examples/RTL8720_WiFi/dynamicParams.h)

- To add custom parameters, just modify the example below

```
#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_BLYNK_SERVER_LEN      34
#define MAX_BLYNK_TOKEN_LEN       34

char Blynk_Server1 [MAX_BLYNK_SERVER_LEN + 1]  = "account.duckdns.org";
char Blynk_Token1  [MAX_BLYNK_TOKEN_LEN + 1]   = "token1";

char Blynk_Server2 [MAX_BLYNK_SERVER_LEN + 1]  = "account.ddns.net";
char Blynk_Token2  [MAX_BLYNK_TOKEN_LEN + 1]   = "token2";

#define MAX_BLYNK_PORT_LEN        6
char Blynk_Port   [MAX_BLYNK_PORT_LEN + 1]  = "8080";

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt.duckdns.org";

MenuItem myMenuItems [] =
{
  { "sv1", "Blynk Server1", Blynk_Server1,  MAX_BLYNK_SERVER_LEN },
  { "tk1", "Token1",        Blynk_Token1,   MAX_BLYNK_TOKEN_LEN },
  { "sv2", "Blynk Server2", Blynk_Server2,  MAX_BLYNK_SERVER_LEN },
  { "tk2", "Token2",        Blynk_Token2,   MAX_BLYNK_TOKEN_LEN },
  { "prt", "Port",          Blynk_Port,     MAX_BLYNK_PORT_LEN },
  { "mqt", "MQTT Server",   MQTT_Server,    MAX_MQTT_SERVER_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;

#endif    //USE_DYNAMIC_PARAMETERS


#endif      //dynamicParams_h

```
- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS     false
```

or

```
/////////////// Start dynamic Credentials ///////////////

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
/////// // End dynamic Credentials ///////////

```
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"id"    for WiFi SSID
"pw"    for WiFi PW
"id1"   for WiFi1 SSID
"pw1"   for WiFi1 PW
"nm"    for Board Name
```
---
---

### Example [RTL8720_WiFi](examples/RTL8720_WiFi)

Please take a look at other examples, as well.

#### 1. File [RTL8720_WiFi.ino](examples/RTL8720_WiFi/RTL8720_WiFi.ino)

https://github.com/khoih-prog/WiFiManager_RTL8720/blob/1f0b76463cfcf47c582d773a7e8863daf6a38a34/examples/RTL8720_WiFi/RTL8720_WiFi.ino#L14-L150


---

#### 2. File [defines.h](examples/RTL8720_WiFi/defines.h)

https://github.com/khoih-prog/WiFiManager_RTL8720/blob/1f0b76463cfcf47c582d773a7e8863daf6a38a34/examples/RTL8720_WiFi/defines.h#L14-L134


---

#### 3. File [Credentials.h](examples/RTL8720_WiFi/Credentials.h)

https://github.com/khoih-prog/WiFiManager_RTL8720/blob/1f0b76463cfcf47c582d773a7e8863daf6a38a34/examples/RTL8720_WiFi/Credentials.h#L14-L93


---

#### 4. File [dynamicParams.h](examples/RTL8720_WiFi/dynamicParams.h)


https://github.com/khoih-prog/WiFiManager_RTL8720/blob/1f0b76463cfcf47c582d773a7e8863daf6a38a34/examples/RTL8720_WiFi/dynamicParams.h#L14-L74


---
---


### Debug Terminal output Samples

#### 1. RTL8720_WiFi on Rtlduino RTL8720DN

This is the terminal output when running [**RTL8720_WiFi**](examples/RTL8720_WiFi) example on **Rtlduino RTL8720DN**:

#### 1.1 Open Config Portal

```
Starting RTL8720_WiFi on Rtlduino RTL8720DN
WiFiManager_RTL8720 v1.1.0
DoubleResetDetector_Generic v1.8.1
interface 0 is initialized
interface 1 is initialized
Initializing WIFI ...
WIFI initialized
Current Firmware Version = 1.0.0
[WG] Set CustomsStyle to : <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[WG] Set CustomsHeadElement to : <style>html{filter: invert(10%);}</style>
[WG] Set CORS Header to : Your Access-Control-Allow-Origin
[WG] Hostname=RTL8720-Controller
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[WG] Double Reset Detected
[WG] CCSum=0x1115,RCSum=0x1115
[WG] ChkCrR:pdata=OK.duckdns.org,len=34
[WG] ChkCrR:pdata=token1,len=34
[WG] ChkCrR:pdata=OK.ddns.net,len=34
[WG] ChkCrR:pdata=token2,len=34
[WG] ChkCrR:pdata=8080,len=6
[WG] ChkCrR:pdata=mqtt.duckdns.org,len=34
[WG] ChkCrR:CrCCsum=0x14db,CrRCsum=0x14db
[WG] CrCCSum=14db,CrRCSum=14db
[WG] Valid Stored Dynamic Data
[WG] ======= Start Stored Config Data =======
[WG] Hdr=RTL8720_WIFI,SSID=HueNet_5G,PW=12345678
[WG] SSID1=HueNet2_5G,PW1=12345678
[WG] BName=RTL8720
[WG] i=0,id=sv1,data=OK.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=OK.ddns.net
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=prt,data=8080
[WG] i=5,id=mqt,data=mqtt.duckdns.org
[WG] bg: isForcedConfigPortal = false
[WG] bg:Stay forever in CP:DRD/MRD
[WG] Scanning Network
[WG] scanWifiNetworks: Done, Scanned Networks n = 29
[WG] Sorting
[WG] Removing Dup
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] DUP AP:
[WG] WiFi networks found:
[WG] 1: HueNet_5G, -25dB
[WG] 2: HueNetTek, -36dB
[WG] 3: HueNet, -36dB
[WG] 4: HueNet1, -37dB
[WG] 5: HueNet2, -44dB
[WG] 6: HueNet2_5G, -53dB
[WG] 7: SmartRG-02a2, -55dB
[WG] 8: Linksys00043, -72dB
[WG] 9: , -74dB
[WG] 11: DECO-5655, -82dB
[WG] 16: Rogers5651, -83dB
[WG] 17: DECO-5655_EXT, -86dB
[WG] 18: SmartRG-02a2-5G, -86dB
[WG] 19: Rogers 786, -88dB
[WG] 20: BELL627, -89dB
[WG] 24: Waterhome, -93dB
[WG] 27: Jasmine, -94dB
[WG] 29: BELL040_EXT2.4G, -95dB
[WG] SSID=RTL8720_WM_25,PW=MyRTL8720_WM_25
[WG] IP=192.168.4.1,CH=7
IPv4 enabled

LwIP_DHCP: dhcp stop.
Deinitializing WIFI ...
WIFI deinitialized
Initializing WIFI ...
WIFI initialized
Starting AP ...
RTL8720_WM_25 started

[INFO] Listen socket successfully
[INFO] Socket conntect successfully 
[WG] s:millis() = 8667, configTimeout = 128666
RTL8721D[Driver]: +OnAuth: 40:5b:d8:e8:9c:f3
RTL8721D[Driver]: +OnAssocReq
RTL8721D[Driver]: Enter rtw_ap_update_sta_ra_info 
RTL8721D[Driver]: rtw_ap_update_sta_ra_info Before update sta ra info 
RTL8721D[Driver]: rtw_ap_update_sta_ra_info=> mac_id:2 , tx_ra_bitmap:0xfffff, networkType:0x07
RTL8721D[Driver]: set pairwise key to hw: alg:4(WEP40-1 WEP104-5 TKIP-2 AES-4) for 40:5b:d8:e8:9c:f3
RTL8721D[Driver]: set group key to hw: alg:4(WEP40-1 WEP104-5 TKIP-2 AES-4) keyid:1
ip_table[100] = 00,00,00,00,00,00
```

#### 1.2 Received data from Config Portal

```
[INFO] Accept connection successfully
A client connected to this server :
[PORT]: 36668
[IP]:192.168.4.100
[WG] h: Init menuItemUpdated :6
[WG] h:repl id
[WG] h:items updated =1
[WG] h:key =id, value =HueNet_5G
Your stored Credentials :
Blynk Server1 = OK.duckdns.org
Token1 = token1
Blynk Server2 = OK.ddns.net
Token2 = token2
Port = 8080
MQTT Server = mqtt.duckdns.org
[INFO] Accept connection successfully
A client connected to this server :
[PORT]: 36670
[IP]:192.168.4.100
[WG] h:repl pw
[WG] h:items updated =2
[WG] h:key =pw, value =12345678
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36672
[IP]:192.168.4.100
[WG] h:repl id1
[WG] h:items updated =3
[WG] h:key =id1, value =HueNet2_5G
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36674
[IP]:192.168.4.100
[WG] h:repl pw1
[WG] h:items updated =4
[WG] h:key =pw1, value =12345678
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36676
[IP]:192.168.4.100
[WG] h:repl nm
[WG] h:items updated =5
[WG] h:key =nm, value =RTL8720
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36678
[IP]:192.168.4.100
[WG] h:sv1=OK.duckdns.org
[WG] h:items updated =6
[WG] h:key =sv1, value =OK.duckdns.org
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36680
[IP]:192.168.4.100
[WG] h:tk1=token1
[WG] h:items updated =7
[WG] h:key =tk1, value =token1
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36682
[IP]:192.168.4.100
[WG] h:sv2=OK.ddns.net
[WG] h:items updated =8
[WG] h:key =sv2, value =OK.ddns.net
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36684
[IP]:192.168.4.100
[WG] h:tk2=token2
[WG] h:items updated =9
[WG] h:key =tk2, value =token2
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36686
[IP]:192.168.4.100
[WG] h:prt=8080
[WG] h:items updated =10
[WG] h:key =prt, value =8080
[INFO] Accept connection successfully

A client connected to this server :
[PORT]: 36688
[IP]:192.168.4.100
[WG] h:mqt=mqtt.duckdns.org
[WG] h:items updated =11
[WG] h:key =mqt, value =mqtt.duckdns.org
[WG] h:Update FlashStorage
[WG] SaveEEPROM,Sz=4096,DataSz=416,WCSum=0x1115
[WG] pdata=OK.duckdns.org,len=34
[WG] pdata=token1,len=34
[WG] pdata=OK.ddns.net,len=34
[WG] pdata=token2,len=34
[WG] pdata=8080,len=6
[WG] pdata=mqtt.duckdns.org,len=34
[WG] CrCCSum=0x14db
[WG] h:Rst
```

#### 1.3 Got valid Credential from Config Portal, then connected to WiFi

```
Starting RTL8720_WiFi on Rtlduino RTL8720DN
WiFiManager_RTL8720 v1.1.0
DoubleResetDetector_Generic v1.8.1
interface 0 is initialized
interface 1 is initialized
Initializing WIFI ...
WIFI initialized
Current Firmware Version = 1.0.0
[WG] Set CustomsStyle to : <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[WG] Set CustomsHeadElement to : <style>html{filter: invert(10%);}</style>
[WG] Set CORS Header to : Your Access-Control-Allow-Origin
[WG] Hostname=RTL8720-Controller
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[WG] CCSum=0x1115,RCSum=0x1115
[WG] ChkCrR:pdata=OK.duckdns.org,len=34
[WG] ChkCrR:pdata=token1,len=34
[WG] ChkCrR:pdata=OK.ddns.net,len=34
[WG] ChkCrR:pdata=token2,len=34
[WG] ChkCrR:pdata=8080,len=6
[WG] ChkCrR:pdata=mqtt.duckdns.org,len=34
[WG] ChkCrR:CrCCsum=0x14db,CrRCsum=0x14db
[WG] CrCCSum=14db,CrRCSum=14db
[WG] Valid Stored Dynamic Data
[WG] ======= Start Stored Config Data =======
[WG] Hdr=RTL8720_WIFI,SSID=HueNet_5G,PW=12345678
[WG] SSID1=HueNet2_5G,PW1=12345678
[WG] BName=RTL8720
[WG] i=0,id=sv1,data=OK.duckdns.org
[WG] i=1,id=tk1,data=token1
[WG] i=2,id=sv2,data=OK.ddns.net
[WG] i=3,id=tk2,data=token2
[WG] i=4,id=prt,data=8080
[WG] i=5,id=mqt,data=mqtt.duckdns.org
[WG] No WiFi. Trying to scan and reconnect

RTL8721D[Driver]: set ssid [HueNet_5G] 
RTL8721D[Driver]: rtw_set_wpa_ie[1160]: AuthKeyMgmt = 0x2 
RTL8721D[Driver]: rtw_restruct_sec_ie[4225]: no pmksa cached 
RTL8721D[Driver]: start auth to 68:7f:74:94:f4:a5
RTL8721D[Driver]: auth alg = 2
RTL8721D[Driver]: 
OnAuthClient:algthm = 0, seq = 2, status = 0, sae_msg_len = 11
RTL8721D[Driver]: auth success, start assoc
RTL8721D[Driver]: association success(res=1)
RTL8721D[Driver]: ClientSendEAPOL[1624]: no use cache pmksa 
RTL8721D[Driver]: ClientSendEAPOL[1624]: no use cache pmksa 
RTL8721D[Driver]: set pairwise key to hw: alg:4(WEP40-1 WEP104-5 TKIP-2 AES-4)
RTL8721D[Driver]: set group key to hw: alg:2(WEP40-1 WEP104-5 TKIP-2 AES-4) keyid:2

Interface 0 IP address : 192.168.2.132
[WG] WiFi connected after time: 1
[WG] SSID:HueNet_5G,RSSI=-39
[WG] IP address:192.168.2.132
[WG] b:WOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
H
Your stored Credentials :
Blynk Server1 = OK.duckdns.org
Token1 = token1
Blynk Server2 = OK.ddns.net
Token2 = token2
Port = 8080
MQTT Server = mqtt.duckdns.org
H
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
```
  
---
---

#### Debug

Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
#define DEBUG_WIFI_WEBSERVER_PORT     Serial
#define WIFI_GENERIC_DEBUG_OUTPUT     Serial

#define _WIFI_GENERIC_LOGLEVEL_       4

#define DRD_GENERIC_DEBUG             true
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core or this library version.

Sometimes, the library will only work if you update the `AmebaD RTL8720` core to the newer or older version because some function compatibility.

---
---


### Issues

Submit issues to: [WiFiManager_RTL8720 issues](https://github.com/khoih-prog/WiFiManager_RTL8720/issues)

---
---

### TO DO

1. Support more boards, shields and libraries
2. Bug Searching and Killing

---

### DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (SSIDs, Passwords, etc.), entering config portal
 5. Add configurable Config Portal IP, SSID and Password
 6. Change Synch XMLHttpRequest to Async
 7. Add configurable Static IP, GW, Subnet Mask and 2 DNS Servers' IP Addresses.
 8. Add checksums
 9. Add MultiWiFi features with auto(re)connect
10. Easy-to-use **Dynamic Parameters** without the necessity to write complicated ArduinoJSon functions
11. Permit to input special chars such as **%** and **#** into data fields.
12. Default Credentials and dynamic parameters
13. **DoubleDetectDetector** to force Config Portal when double reset is detected within predetermined time, default 10s.
14. Configurable Config Portal Title
15. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
16. Add Table of Contents and Version String
17. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header
18. Add functions to control Config Portal from software or Virtual Switches.
19. Permit optionally inputting one set of WiFi SSID/PWD by using `REQUIRE_ONE_SET_SSID_PW == true`
20. Enforce WiFi Password minimum length of 8 chars
21. Enable **scan of WiFi networks** for selection in Configuration Portal
22. Fix the blocking issue in loop() with configurable `WIFI_RECON_INTERVAL`
23. Optimize code by passing by `reference` instead of `value`
24. Optional `Board_Name` in Config Portal
25. Add optional `CONFIG_MODE_LED` to be `ON` when in Config Portal mode.
26. Add function `isConfigMode()` to signal system is in Config Portal mode
27. Use [WiFiMulti_Generic](https://github.com/khoih-prog/WiFiMulti_Generic) library to connect to the best of **multi-WiFi APs**, with **auto-checking / auto-reconnecting** features when WiFi connection is lost.


---
---
 
### Contributions and Thanks

Please help contribute to this project and add your name here.


---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/WiFiManager_RTL8720/blob/main/LICENSE)

---

### Copyright

Copyright 2022- Khoi Hoang


