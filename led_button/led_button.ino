#include <SPI.h>
#include <Ethernet.h>


//http://arduino.stackexchange.com/questions/10410/how-to-call-url-with-arduino-ethernet-shield


const int LED_OK = 9;
const int LED_FAIL = 8;
const int BUTTON = 2;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "http://preview.0z2r73ssb57b9tnkmu0xmmr7r2j4iv8nrlkofoyo80k9.box.codeanywhere.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;


void setup() {
  pinMode(LED_OK, OUTPUT);
  pinMode(LED_FAIL, OUTPUT);
  pinMode(BUTTON, INPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  get_requests("Conexion%20inicial%20arduino");
}


void get_requests(String msg) {
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make your API request:
    client.println("GET http://preview.0z2r73ssb57b9tnkmu0xmmr7r2j4iv8nrlkofoyo80k9.box.codeanywhere.com/?api=6MJN4Y6qRsz2g5Zp8QeumkPyb7kY6j9&msg=" + msg + " HTTP/1.1");
    client.println("Host: preview.0z2r73ssb57b9tnkmu0xmmr7r2j4iv8nrlkofoyo80k9.box.codeanywhere.com");
    client.println("Connection: close");
    client.println();
    //client.stop();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}


boolean debug() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
  //
}


void loop() {
  //debug();
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(LED_OK, LOW);
  }
  else {
    digitalWrite(LED_OK, HIGH);
    get_requests("Envio%desde%20Arduino");
    if (debug());
      delay(2000);
  }
}
