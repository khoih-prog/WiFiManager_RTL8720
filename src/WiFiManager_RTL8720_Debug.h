/****************************************************************************************************************************
  WiFiManager_RT8720_Debug.h
  For RTL8720DN, RTL8722DM, RTM8722CSM, etc. boards

  WiFiManager_RT8720 (https://github.com/khoih-prog/WiFiManager_RT8720) is a library 
  for the RTL8720DN, RTL8722DM, RTM8722CSM, etc. boards to enable store Credentials in EEPROM/SPIFFS/LittleFS for easy 
  configuration/reconfiguration and autoconnect/autoreconnect of WiFi and other services without Hardcoding.

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiManager_RT8720
  Licensed under MIT license
  
  Version: 1.0.0
   
  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      04/02/2021  Initial coding for RTL8720DN, RTL8722DM, RTM8722CSM, etc.
 *****************************************************************************************************************************/

#ifndef WiFiManager_RT8720_Debug_h
#define WiFiManager_RT8720_Debug_h

#ifdef RT8720_DEBUG_OUTPUT
  #define DBG_PORT_RT8720       RT8720_DEBUG_OUTPUT
#else
  #define DBG_PORT_RT8720       Serial
#endif

// Change _WM_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _WM_LOGLEVEL_
  #define _WM_LOGLEVEL_       0
#endif

const char RT8720_MARK[] = "[WML] ";

#define RT8720_PRINT_MARK   DBG_PORT_RT8720.print(RT8720_MARK)

#define RT8720_PRINT        DBG_PORT_RT8720.print
#define RT8720_PRINTLN      DBG_PORT_RT8720.println


///////////////////////////////////////////

#define WM_LOGERROR0(x)     if(_WM_LOGLEVEL_>0) { RT8720_PRINT(x); }
#define WM_LOGERROR(x)      if(_WM_LOGLEVEL_>0) { RT8720_PRINT_MARK; RT8720_PRINTLN(x); }
#define WM_LOGERROR1(x,y)   if(_WM_LOGLEVEL_>0) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINTLN(y); }
#define WM_LOGERROR2(x,y,z) if(_WM_LOGLEVEL_>0) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINTLN(z); }
#define WM_LOGERROR3(x,y,z,w) if(_WM_LOGLEVEL_>0) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINTLN(w); }
#define WM_LOGERROR5(x,y,z,w,xx,yy) if(_WM_LOGLEVEL_>0) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINT(w); RT8720_PRINT(xx); RT8720_PRINTLN(yy); }

///////////////////////////////////////////

#define WM_LOGWARN0(x)     if(_WM_LOGLEVEL_>1) { RT8720_PRINT(x); }
#define WM_LOGWARN(x)      if(_WM_LOGLEVEL_>1) { RT8720_PRINT_MARK; RT8720_PRINTLN(x); }
#define WM_LOGWARN1(x,y)   if(_WM_LOGLEVEL_>1) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINTLN(y); }
#define WM_LOGWARN2(x,y,z) if(_WM_LOGLEVEL_>1) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINTLN(z); }
#define WM_LOGWARN3(x,y,z,w) if(_WM_LOGLEVEL_>1) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINTLN(w); }
#define WM_LOGWARN5(x,y,z,w,xx,yy) if(_WM_LOGLEVEL_>1) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINT(w); RT8720_PRINT(xx); RT8720_PRINTLN(yy); }

///////////////////////////////////////////

#define WM_LOGINFO0(x)     if(_WM_LOGLEVEL_>2) { RT8720_PRINT(x); }
#define WM_LOGINFO(x)      if(_WM_LOGLEVEL_>2) { RT8720_PRINT_MARK; RT8720_PRINTLN(x); }
#define WM_LOGINFO1(x,y)   if(_WM_LOGLEVEL_>2) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINTLN(y); }
#define WM_LOGINFO2(x,y,z) if(_WM_LOGLEVEL_>3) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINTLN(z); }
#define WM_LOGINFO3(x,y,z,w) if(_WM_LOGLEVEL_>3) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINTLN(w); }
#define WM_LOGINFO5(x,y,z,w,xx,yy) if(_WM_LOGLEVEL_>2) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINT(w); RT8720_PRINT(xx); RT8720_PRINTLN(yy); }

///////////////////////////////////////////

#define WM_LOGDEBUG0(x)     if(_WM_LOGLEVEL_>3) { RT8720_PRINT(x); }
#define WM_LOGDEBUG(x)      if(_WM_LOGLEVEL_>3) { RT8720_PRINT_MARK; RT8720_PRINTLN(x); }
#define WM_LOGDEBUG1(x,y)   if(_WM_LOGLEVEL_>3) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINTLN(y); }
#define WM_LOGDEBUG2(x,y,z) if(_WM_LOGLEVEL_>3) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINTLN(z); }
#define WM_LOGDEBUG3(x,y,z,w) if(_WM_LOGLEVEL_>3) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINTLN(w); }
#define WM_LOGDEBUG5(x,y,z,w,xx,yy) if(_WM_LOGLEVEL_>3) { RT8720_PRINT_MARK; RT8720_PRINT(x); RT8720_PRINT(y); RT8720_PRINT(z); RT8720_PRINT(w); RT8720_PRINT(xx); RT8720_PRINTLN(yy); }

///////////////////////////////////////////

#endif    //WiFiManager_RT8720_Debug_h
