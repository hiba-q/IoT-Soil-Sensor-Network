// CO2 sensor variables
int co2_sensor_port = A1;
int co2_sensor_value = 0;
float co2_concentration_ppm = 0;

// pH sensor variables
int ph_sensor_port = A0;
int ph_sensor_value = 0;
float pH = 0;

//WIFI module variables
String ssid     = "Simulator Wifi";  // SSID to connect to
String password = "";   //virtual wifi has no password 
String host     = "api.thingspeak.com"; // Open Weather Map API
const int httpPort   = 80;
String url     = "/update?api_key=KT57ADAG6851ZYHU&field1="; //ThingSpeak Channel A

//setting up the wifi module
void setupESP8266(void)    
{
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Baud rate
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);          	// Wait a little for the ESP to respond
 
  if (Serial.find("OK"))
	Serial.println("ESP8266 OK!!!");  // Connect to Simulator Wifi
 
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\""); //AT+CWLAP – list nearby available WiFi networks
  delay(10);                     	// Wait a little for the ESP to respond
 
  if (Serial.find("OK"))
	Serial.println("Connected to WiFi!!!"); 	// Open TCP connection to the host:
 
  //ESP8266 connects to the server as a TCP client.
 
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);                               	// Wait a little for the ESP to respond
 
  if (Serial.find("OK"))
   Serial.println("ESP8266 Connected to server!!!") ;
}

//Sends data to Thingspeak
void send_data(void)
{
  // Construct HTTP call
  String httpPacket = "GET " + url + String(co2_concentration_ppm) + "&field2=" + String(pH) +  + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10);    	// Wait a little for the ESP to respond if (!Serial.find(">")) return -1;
  // Send our http request
  Serial.print(httpPacket);
  delay(10);   	// Wait a little for the ESP to respond
  if (Serial.find("SEND OK\r\n"))
	Serial.println("ESP8266 sends data to the server");
}

void setup()
{
  pinMode(A1, INPUT); 	//gas sensor analog input
  pinMode(A0, INPUT); 	//potentiometer analog input
  setupESP8266();
 
}

void loop() {
   // For CO2 sensor 
  int co2_sensor_value = analogRead(co2_sensor_port);
  float co2_voltage = co2_sensor_value * (5.0 / 1023.0); // Convert analog value to voltage

  // Assuming a linear conversion formula for CO2 concentration
  float co2_concentration_ppm = co2_voltage * 1000.0; // Assuming linear relationship, check datasheet for actual formula
  
  Serial.println("CO2 sensor value: " + String(co2_concentration_ppm));

   // For pH sensor measurement
  ph_sensor_value = analogRead(ph_sensor_port);
  float ph_voltage = ph_sensor_value * (5.0 / 1023.0); // Convert analog value to voltage
  float pH = 7.0 - (ph_voltage - 2.5) / 0.59; // Convert voltage to pH value
  Serial.println("pH value: " + String(pH));
  
  //-----------------------------------------------------------------------------------------------------
  // Send data to ThingSpeak
  send_data();
  
  delay(15000); // Wait for 15 seconds before repeating the loop
};
