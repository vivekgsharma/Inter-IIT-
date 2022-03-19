
#include <ESP8266WiFi.h>
#include <espnow.h>

// C4:5B:BE:63:19:BA    Sever IP Address

uint8_t broadcastAddress[] = {0xC4, 0x5B, 0xBE, 0x63, 0x19, 0xBA};

#define BOARD_ID 1

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    int id;
    int x;
    int y;
} struct_message;


struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;


void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } 

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  
  esp_now_register_send_cb(OnDataSent);
  
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    myData.id = BOARD_ID;
    myData.x = random(1, 50);
    myData.y = random(1, 50);

       esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
    lastTime = millis();
  }
}