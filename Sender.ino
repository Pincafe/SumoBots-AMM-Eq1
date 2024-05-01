#include <esp_now.h>
#include <WiFi.h>


uint8_t receiverMAC[] = {0xE8,0x6B,0xEA,0xCA,0x55,0xB0};

typedef struct struct_message {
  int jsA;
  int jsB;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println("Data sent");
}

const int JoystickA = 36;
const int JoystickB = 39;

int ValA = 0;
int ValB = 0;

void setup()
{

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if(esp_now_init() != ESP_OK) {
      
      return;
    }

    esp_now_register_send_cb(OnDataSent);

    memcpy(peerInfo.peer_addr, receiverMAC,6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if(esp_now_add_peer(&peerInfo) != ESP_OK) {
      
      return;
    }
}

void loop()
{
  
ValA = analogRead(JoystickA);
ValB = analogRead(JoystickB);
Serial.println(ValA);
  myData.jsA = ValA;
  myData.jsB = ValB;

 


  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *) &myData, sizeof(myData));

  if(result == ESP_OK) {
    Serial.println("Success");
  }
  else {
   Serial.println("not sent");
  }
  
}
