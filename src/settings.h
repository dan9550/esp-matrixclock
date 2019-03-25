// Timezone
#define timeZone 10  // AEST

// DST parameters
// When Daylight Savings time starts
#define DSTStartMonth 9
#define DSTStartDay 30
#define DSTStartHour 2
// TODO: This only accounts for sundays!
//#define DSTStartSunday nextSunday //nextSunday or previousSunday

// When Daylight Savings time ends
#define DSTEndMonth 3
#define DSTEndDay 31
// TODO: This only accounts for sundays!
//#define DSTEndSunday nextSunday //nextSunday or previousSunday

// How often weather data is polled
#define WEATHER_POLL_INTERVAL 300   // Seconds

// Button to be used for configuration reset
#define CONFIGRESETBUTTON D5    // D5 - GPIO 14 on nodemcu hw

// Serial baud rate
#define serialBuadRate 9600

// NTP server
#define NTPServer "au.pool.ntp.org"

// Swap timeout
#define swapTimeout 40

// Old matrix type
#define OLDTYPE_MATRIX

// OpenWeatherMap details
//char cityid[CITYID_LEN] = "City_ID";
//char apitoken[APITOKEN_LEN] = "API_token";

// Weather units
// Default: Kelvin, Metric: Celsius, Imperial: Fahrenheit.
// Don't use Kelvin :)
#define units "metric"

// Display brightness
#define displayBrightness 0 // 0 - 10
