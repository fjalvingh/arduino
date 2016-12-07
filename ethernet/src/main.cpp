#include <SPI.h>
#include <EtherCard.h>

byte mac[] = {0xde, 0xad, 0xbe, 0xef, 0xa8, 0x0b};
byte ip[] = {192, 168, 1, 123};

byte Ethernet::buffer[500];

static byte myip[] = { 192,168,1,200 };
static byte gwip[] = { 192,168,1,1 };
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

const char page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head><title>"
    "Hello World!"
  "</title></head>"
  "<body>"
    "<h3>Hello World! This is your Arduino speaking!</h3>"
  "</body>"
"</html>";

void setup() {
  Serial.begin(57600);
  Serial.println("\n[Hello World]");

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");
  else {
    ether.dhcpSetup();
//    ether.staticSetup(myip, gwip);

    ether.printIp("IP:  ", ether.myip);
    ether.printIp("GW:  ", ether.gwip);
    ether.printIp("DNS: ", ether.dnsip);
  }
}

void loop() {
  // wait for an incoming TCP packet, but ignore its contents
  if (ether.packetLoop(ether.packetReceive())) {
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
}
