const String    CHANNEL_ID    = "XXXXXXX"; // The Readiness.io channel ID
const String    SENSOR_ID     = "XXXXXXX"; // Your AgriWebb or made up sensor ID
const String    TOPIC         = "weather"; // The type of sensor or name of the data your sending
const String    VERSION       = "1";
const String    FORMAT        = ""; // leave this blank unless there is a specific readiness format you need.
                                    // i.e. agriwebb

const char*      WIFI_SSID     = "XXXXXXXX"; // Your WiFi SSID / name
const char*      WIFI_PASS     = "XXXXXXXX"; // Your WiFi password

const uint16_t  UPDATE_RATE     = 600; // How long to wait between sending data back (in seconds)
const uint8_t   TIMEZONE_OFFSET = 10; // The timezone the sensor is located in (eg. 10 for GMT)
