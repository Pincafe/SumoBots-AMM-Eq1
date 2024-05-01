#include <esp_now.h>
#include <WiFi.h>

const int en_A = 22;
const int in_1 = 16;
const int in_2 = 17;
const int en_B = 23;
const int in_3 = 18;
const int in_4 = 19;

const int freq = 3000;
const int pwmchA = 4;
const int pwmchB = 5;
const int resolution = 8;

int valA, valB; // valores de los joysticks (eje x)


typedef struct struct_message {
  int jsA;
  int jsB;
} struct_message;

struct_message myData;


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("A:");
  Serial.println(valA;
  Serial.print("B:");
  Serial.println(valB);

   valA = myData.jsA
   valB = myData.jsB
}
 
void setup() {

  Serial.begin(115200);

  pinMode(en_A, OUTPUT);
  pinMode(in_1, OUTPUT);
  pinMode(in_2, OUTPUT);
  pinMode(en_B, OUTPUT);
  pinMode(in_3, OUTPUT);
  pinMode(in_4, OUTPUT);

  ledcSetup(pwmchA,freq,resolution);
  ledcAttachPin(en_A,pwmchA);
  ledcSetup(pwmchB,freq,resolution);
  ledcAttachPin(en_B,pwmchB);

  
  
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {


  int speedA, speedB; // valores de velocidad de ambos motores

  if((valA>1930) && (valA<2030)) { // como los joysticks son imprecisos, establecemos un rango de 470 a 540
  ledcWrite(pwmchA, 0);    // como una posición central y de reposo para mantener el motor en 0s
   }
  if(valA>550)                               // establecemos que un valor por encima de 550, el motor
   {                                       // se moverá hacia adelante 
     speedA = map(valA,2030,4095,130,255);   // la velocidad se mapea en un rango de 130 (minima para
      forwardA();                          // empezar a girar) y 255 (maximo en PWM)
      ledcWrite(pwmchA, speedA);          // establecemos la velocidad a través del pin en_A

   }
  if(jsA<1930)                               // en un valor debajo de 470, el motor se moverá
   {                                       // hacia atrás
     speedA = map(valA,1930,0,130,255);
     backwardA();
     ledcWrite(pwmchA, speedA);


   }

    // Se repite lo mismo para el motor B

  if((valB>1930) && (valB<2030)) {
  ledcWrite(pwmchB, 0);
   }
  if(valB>2030)
   {
     speedB = map(valB,2030,4095,130,255);
      forwardB();
     ledcWrite(pwmchB, speedB);

   }
  if(valB<1930)
   {
     speedB = map(valB,1930,0,130,255);
     backwardB();
      ledcWrite(pwmchB, speedB);


   }

}

void forwardA() {
  digitalWrite(in_1,HIGH);
  digitalWrite(in_2,LOW);
}

void forwardB() {
  digitalWrite(in_3,HIGH);
  digitalWrite(in_4,LOW);
}
void brakeA() {
   digitalWrite(in_1,LOW);
   digitalWrite(in_2,LOW);
}

void brakeB() {
   digitalWrite(in_3,LOW);
   digitalWrite(in_4,LOW);
}
void backwardA() {
  digitalWrite(in_1,LOW);
  digitalWrite(in_2,HIGH);
}

void backwardB() {
   digitalWrite(in_3,LOW);
   digitalWrite(in_4,HIGH);
}