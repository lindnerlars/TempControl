/**************************************************************************************************
 * Wifi.ino
 *
 * Created: 07/06/2020
 * Author: Lars Lindner
 *
 *
***************************************************************************************************/

WiFiServer server(80);
WiFiClient client;

const char* ssid = "INFINITUM7271_2.4";							// Wifi name
const char* password = "MODEM08042020";							// Wifi Password

String tmp_str = "";											// String that contains the command and the value extracted from the http string


void setupWifi()
{
	// Connect to WiFi network
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	
	WiFi.begin(ssid, password);
	IPAddress ip(192,168,1,67);
	IPAddress gateway(192,168,1,254);
	IPAddress subnet(255,255,255,0);
	WiFi.config(ip, gateway, subnet);
	
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	
	// Start the Server
	server.begin();
	Serial.println("Server started");
	
	// Print the IP address
	Serial.println(WiFi.localIP());
}


void wifiConnect()
{
	// Check if a client has connected
	client = server.available();
	if (client)
	{
		Serial.println("Client connected");
	}
	
	// If connected and has data, then read data, process and respond
	if (client)
	{
		wifiRead();
		wifiHttpResponse();
	}
}


void wifiRead()
{
	// The complete string from the http request is read
	String cmpl_str = client.readStringUntil('\r');

	// The command and the value is extracted from the http string
	tmp_str = cmpl_str.substring(cmpl_str.indexOf("/") + 1);
	tmp_str.remove(tmp_str.indexOf(" "));
	String cmd_str = tmp_str;
	cmd_str.remove(cmd_str.indexOf("/"));
	int cmd_int = tmp_str.substring(tmp_str.indexOf("/") + 1).toInt();

	// 	if (cmd_int == 0)
	// 	{
	// 		digitalWrite(LED_BUILTIN, HIGH);
	// 	}
	// 	else if (cmd_int == 1)
	// 	{
	// 		digitalWrite(LED_BUILTIN, LOW);
	// 	}
	// 	else
	// 	{
	// 		Serial.println("invalid request");
	// 		client.stop();
	// 		return;
	// 	}
}


void wifiHttpResponse()
{
	// HTTP response
	client.flush();
	String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nData Received ";
	s +=  tmp_str;
	s += " </html>";
	client.println(s);
	
}




