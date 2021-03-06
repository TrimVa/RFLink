// ************************************* //
// * Arduino Project RFLink-esp        * //
// * https://github.com/couin3/RFLink  * //
// * 2018..2020 Stormteam - Marc RIVES * //
// * More details in RFLink.ino file   * //
// ************************************* //

#ifndef AutoConnect_h
#define AutoConnect_h

#include <Arduino.h>
#include "RFLink.h"

#ifdef AUTOCONNECT_ENABLED

extern String LastMsg;
extern String CmdMsg;

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif // ESP8266

#include <AutoConnect.h>
#ifdef ESP8266
#define GET_CHIPID() (ESP.getChipId())
#elif ESP32
#define GET_CHIPID() ((uint32_t)ESP.getEfuseMac())
#endif //ESP8266

// --------- These labels can be renamed (Need clean-up before re-build) ---------
//  https://hieromon.github.io/AutoConnect/changelabel.html#label-text-replacement-header-file
//  AUTOCONNECT_MENULABEL_CONFIGNEW   "Configure new AP"
//  AUTOCONNECT_MENULABEL_OPENSSIDS   "Open SSIDs"
//  AUTOCONNECT_MENULABEL_DISCONNECT  "Disconnect"
//  AUTOCONNECT_MENULABEL_RESET       "Reset..."
//  AUTOCONNECT_MENULABEL_UPDATE      "Update"
//  AUTOCONNECT_MENULABEL_HOME        "HOME"
//  AUTOCONNECT_MENULABEL_DEVINFO     "Device info"
//  AUTOCONNECT_BUTTONLABEL_RESET     "RESET"
//  AUTOCONNECT_BUTTONLABEL_UPDATE    "UPDATE"

#ifdef AUTOCONNECT_MENULABEL_CONFIGNEW
#undef AUTOCONNECT_MENULABEL_CONFIGNEW
#define AUTOCONNECT_MENULABEL_CONFIGNEW "Configure Wifi"
#endif

#ifdef AUTOCONNECT_MENULABEL_RESET
#undef AUTOCONNECT_MENULABEL_RESET
#define AUTOCONNECT_MENULABEL_RESET "Reboot"
#endif

#ifdef AUTOCONNECT_MENULABEL_OPENSSIDS
#undef AUTOCONNECT_MENULABEL_OPENSSIDS
#define AUTOCONNECT_MENULABEL_OPENSSIDS "Known networks"
#endif

// Adds MQTT tab to Autoconnect
#define PARAM_FILE "/settings.json"
#define PROTOCOL_FILE "/protocols.json"
#define AUX_SETTING_URI "/settings"
#define AUX_SAVE_URI "/settings_save"
//#define AUX_CLEAR_URI "/settings_clear"

void setup_AutoConnect();
void loop_AutoConnect();

void rootPage();
void HandleLastMsg();

// JSON definition of AutoConnectAux.
// Multiple AutoConnectAux can be defined in the JSON array.
// In this example, JSON is hard-coded to make it easier to understand
// the AutoConnectAux API. In practice, it will be an external content
// which separated from the sketch, as the mqtt_RSSI_FS example shows.
static const char AUX_settings[] PROGMEM = R"raw(
  [
    {
      "title": "RFLink settings",
      "uri": "/settings",
      "menu": true,
      "element": [
        {
          "name": "style1",
          "type": "ACStyle",
          "value": "label+input,label+select{position:sticky;left:180px;width:210px!important;box-sizing:border-box;}"
        },
        {
          "name": "header0",
          "type": "ACText",
          "value": "<h2>MQTT settings</h2>",
          "style": "text-align:center;color:#2f4f4f;padding:10px;"
        },
        {
          "name": "caption1",
          "type": "ACText",
          "value": "Connexion",
          "style": "font-family:serif;color:#4682b4;"
        },
        {
          "name": "newline1",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "MQTT_SERVER",
          "type": "ACInput",
          "value": "",
          "label": "Server",
          "pattern": "^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\\-]*[A-Za-z0-9])$",
          "placeholder": "example : 192.168.0.10"
        },
        {
          "name": "MQTT_PORT",
          "type": "ACInput",
          "value": "",
          "label": "Port",
          "placeholder": "default is 1883"
        },
        {
          "name": "MQTT_ID",
          "type": "ACInput",
          "label": "ID",
          "placeholder": "example : RFLink-ESP-xx"
        },
        {
          "name": "MQTT_USER",
          "type": "ACInput",
          "label": "User"
        },
        {
          "name": "MQTT_PSWD",
          "type": "ACInput",
          "label": "Password"
        },
        {
          "name": "caption2",
          "type": "ACText",
          "value": "Messages",
          "style": "font-family:serif;color:#4682b4;"
        },
        {
          "name": "newline2",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "MQTT_TOPIC_OUT",
          "type": "ACInput",
          "label": "Out Topic",
          "pattern": "(.*)[^\/]$",
          "placeholder": "example : /RFLink/msg",
          "value": "/RFLink/msg"
        },
        {
          "name": "MQTT_TOPIC_IN",
          "type": "ACInput",
          "label": "In Topic",
          "pattern": "(.*)[^\/]$",
          "placeholder": "example : /RFLink/cmd",
          "value": "/RFLink/cmd"
        },
        {
          "name": "MQTT_RETAINED",
          "type": "ACCheckbox",
          "value": "unique",
          "labelPosition" : "AC_Infront",
          "post" : "AC_Tag_BR",
          "label": "Retained",
          "checked": false
        },
        {
          "name": "newline3",
          "type": "ACElement",
          "value": "<hr>"
        },
      {
          "name": "style4",
          "type": "ACStyle",
          "value": "label+input,label+select{position:sticky;left:180px;width:210px!important;box-sizing:border-box;}"
        },
        {
          "name": "header4",
          "type": "ACText",
          "value": "<h2>Advanced settings</h2>",
          "style": "text-align:center;color:#2f4f4f;padding:10px;"
        },
        {
          "name": "caption5",
          "type": "ACText",
          "value": "Wifi",
          "style": "font-family:serif;color:#4682b4;"
        },
        {
          "name": "newline5",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "Adv_HostName",
          "type": "ACInput",
          "value": "RFlink-ESP",
          "label": "Hostname"
        },
        {
          "name": "Adv_Power",
          "type": "ACInput",
          "label": "TX Power",
          "placeholder": "default is 20 (max)"
        },
        {
          "name": "newline6",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "style5",
          "type": "ACStyle",
          "value": "label+input,label+select{position:sticky;left:180px;width:210px!important;box-sizing:border-box;}"
        },
        {
          "name": "header5",
          "type": "ACText",
          "value": "<h2>GPIO settings</h2>",
          "style": "text-align:center;color:#2f4f4f;padding:10px;"
        },
        {
          "name": "caption6",
          "type": "ACText",
          "value": "Radio Receiver",
          "style": "font-family:serif;color:#4682b4;"
        },
        {
          "name": "newline7",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "PIN_RF_RX_PMOS",
          "type": "ACInput",
          "label": "RX_PMOS",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_RX_NMOS",
          "type": "ACInput",
          "label": "RX_NMOS",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_RX_VCC",
          "type": "ACInput",
          "label": "RX_VCC",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_RX_GND",
          "type": "ACInput",
          "label": "RX_GND",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_RX_NA",
          "type": "ACInput",
          "label": "RX_NA",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_RX_DATA",
          "type": "ACInput",
          "label": "RX_DATA",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PULLUP_RF_RX_DATA",
          "type": "ACCheckbox",
          "value": "unique",
          "labelPosition" : "AC_Infront",
          "post" : "AC_Tag_BR",
          "label": "Pullup on RX_DATA",
          "checked": false
        },
        {
          "name": "newlineX",
          "type": "ACElement",
          "value": "</br>"
        },
        {
          "name": "caption7",
          "type": "ACText",
          "value": "Radio Emitter",
          "style": "font-family:serif;color:#4682b4;"
        },
        {
          "name": "newline8",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "PIN_RF_TX_PMOS",
          "type": "ACInput",
          "label": "TX_PMOS",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_TX_NMOS",
          "type": "ACInput",
          "label": "TX_NMOS",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_TX_VCC",
          "type": "ACInput",
          "label": "TX_VCC",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_TX_GND",
          "type": "ACInput",
          "label": "TX_GND",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_TX_NA",
          "type": "ACInput",
          "label": "TX_NA",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "PIN_RF_TX_DATA",
          "type": "ACInput",
          "label": "TX_DATA",
          "placeholder": "NOT_A_PIN"
        },
        {
          "name": "newline9",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "save",
          "type": "ACSubmit",
          "value": "Save",
          "uri": "/settings_save"
        },
        {
          "name": "discard",
          "type": "ACSubmit",
          "value": "Discard",
          "uri": "/settings"
        }
      ]
    },
    {
      "title": "RFlink ESP settings",
      "uri": "/settings_save",
      "menu": false,
      "element": [
        {
          "name": "caption",
          "type": "ACText",
          "value": "<h4>Saved values</h4>",
          "style": "text-align:center;color:#2f4f4f;padding:10px;"
        },
        {
          "name": "parameters",
          "type": "ACText"
        },
        {
          "name": "newline",
          "type": "ACElement",
          "value": "<hr>"
        },
        {
          "name": "clear",
          "type": "ACSubmit",
          "value": "OK",
          "uri": "/settings"
        }
      ]
    }
  ]
  )raw";

#endif // AUTOCONNECT_ENABLED
#endif // AutoConnect_h