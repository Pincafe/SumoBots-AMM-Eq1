// Se declaran los pines de los motores
const int en_A = 2;  // en_A y en_B representan los pines de la velocidad
const int en_B = 11; // son pines PWM
const int in_1 = 8;  // in_1 a in_4 son los pines de input a los motores
const int in_2 = 9;  // motor A toma in_1 e in_2
const int in_3 = 12; // motor B toma in_3 e in_4
const int in_4 = 13;
const int jsAP = 0;  // Joystick A Pin (jsAP) y Joystick B Pin (jsBP)
const int jsBP = 1;  // Van conectados al eje x de los joysticks para su lectura

void setup() {

  // declaramos los pines como salidas
   pinMode(en_A,OUTPUT);
   pinMode(in_1,OUTPUT);
   pinMode(in_2,OUTPUT);
   pinMode(en_B,OUTPUT);
   pinMode(in_3,OUTPUT);
   pinMode(in_4,OUTPUT);
   Serial.begin(9600);
}


void loop() {
    int jsA, jsB; // valores de los joysticks (eje x)
    int speedA, speedB; // valores de velocidad de ambos motores
 jsA = analogRead(A0); // leemos ambos joysticks
 jsB = analogRead(A1);

 if((jsA>470) && (jsA<540)) { // como los joysticks son imprecisos, establecemos un rango de 470 a 540
  analogWrite(en_A, 0);       // como una posición central y de reposo para mantener el motor en 0s
   }
 if(jsA>550)                               // establecemos que un valor por encima de 550, el motor
   {                                       // se moverá hacia adelante 
     speedA = map(jsA,550,1024,130,255);   // la velocidad se mapea en un rango de 130 (minima para
      forwardA();                          // empezar a girar) y 255 (maximo en PWM)
      analogWrite(en_A, speedA);           // establecemos la velocidad a través del pin en_A

   }
 if(jsA<470)                               // en un valor debajo de 470, el motor se moverá
   {                                       // hacia atrás
     speedA = map(jsA,470,0,130,255);
     backwardA();
      analogWrite(en_A, speedA);


   }

    // Se repite lo mismo para el motor B

if((jsB>470) && (jsB<540)) {
  analogWrite(en_B, 0);
   }
 if(jsB>550)
   {
     speedB = map(jsB,550,1024,130,255);
      forwardB();
      analogWrite(en_B, speedB);

   }
 if(jsB<470)
   {
     speedB = map(jsB,470,0,130,255);
     backwardB();
      analogWrite(en_B, speedB);


   }

}

  // Funciones para el movimiento de los motores

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