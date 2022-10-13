#include <SPI.h>      // библиотека для протокола SPI
#include <nRF24L01.h> // библиотека для nRF24L01+
#include <RF24.h>     // библиотека для радио модуля

#define dv_left_forv 2
#define dv_left_back 3
#define dv_right_forv 4
#define dv_right_back 5

const uint64_t pipe = 0xF0F1F2F3F4LL; // идентификатор передачи
RF24 radio(7, 10); // Для MEGA2560 замените на RF24 radio(9,53);

void setup() {
  pinMode(dv_left_back, OUTPUT);
  pinMode(dv_right_back, OUTPUT);
  pinMode(dv_right_forv, OUTPUT);
  pinMode(dv_left_forv, OUTPUT);
  digitalWrite(dv_left_back, LOW);
  digitalWrite(dv_right_back, LOW);
  digitalWrite(dv_right_forv, LOW);
  digitalWrite(dv_left_forv, LOW);
  Serial.begin(115200);  // запускаем последовательный порт
  radio.begin();       // включаем радио модуль
  radio.setChannel(0); // выбираем канал (от 0 до 127)

  // скорость: RF24_250KBPS, RF24_1MBPS или RF24_2MBPS
  radio.setDataRate(RF24_1MBPS);
  // мощность: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM
  radio.setPALevel(RF24_PA_HIGH);

  radio.openReadingPipe(1, pipe);    // открываем первую трубу
  radio.startListening();            // начинаем слушать трубу
}

void loop()
{
  int data;

  if (radio.available())             // проверяем буфер обмена
  {
    radio.read(&data, sizeof(data)); // читаем данные
    // if(data!=0){
    Serial.print("data: ");
    Serial.println(data);            // выводим данные на монитор порта
    // }

    if (data == 1) {
      //   Serial.println("forw");
      digitalWrite (dv_left_forv, HIGH );
      digitalWrite (dv_right_forv, HIGH );
      digitalWrite(dv_right_back, LOW);
      digitalWrite(dv_left_back, LOW);
    }
    if (data == 2) {
      //  Serial.println("back");
      digitalWrite (dv_left_back, HIGH );
      digitalWrite (dv_right_back, HIGH );
      digitalWrite(dv_right_forv, LOW);
      digitalWrite(dv_left_forv, LOW);
    }
    if (data == 3) {
      // Serial.println("left");
      digitalWrite (dv_right_forv, HIGH );
      digitalWrite(dv_right_back, LOW);
      digitalWrite(dv_left_back, LOW);
      digitalWrite (dv_left_forv, LOW);
    }
    if (data == 4) {
      // Serial.println("right");
     digitalWrite (dv_left_forv, HIGH );
      digitalWrite (dv_right_forv, LOW);
      digitalWrite(dv_right_back, LOW);
      digitalWrite(dv_left_back, LOW);
    }
    if (data == 0) {
      digitalWrite(dv_right_forv, LOW);
      digitalWrite(dv_left_forv, LOW);
      digitalWrite(dv_right_back, LOW);
      digitalWrite(dv_left_back, LOW);
    }
  }
  /*
  if (!radio.available()) {
    digitalWrite(dv_right_forv, LOW);
    digitalWrite(dv_left_forv, LOW);
    digitalWrite(dv_right_back, LOW);
    digitalWrite(dv_left_back, LOW);
  }
  */
}
