// Источник: роботехника18.рф

#include <SPI.h>      // библиотека для протокола SPI
#include <nRF24L01.h> // библиотека для nRF24L01+
#include <RF24.h>     // библиотека для радио модуля

const uint64_t pipe = 0xF0F1F2F3F4LL; // идентификатор передачи
RF24 radio(7, 10); // Для MEGA2560 замените на RF24 radio(9,53);
int data [2];
#define forw_but 2
#define back_but 3
#define left_but 4
#define right_but 5

void setup() {
  pinMode(forw_but, INPUT_PULLUP);
  pinMode(back_but, INPUT_PULLUP);
  pinMode(left_but, INPUT_PULLUP);
  pinMode(right_but, INPUT_PULLUP);
  Serial.begin(115200);  // запускаем последовательный порт
  radio.begin();       // включаем радио модуль
  radio.setChannel(0); // выбираем канал (от 0 до 127)

  // скорость: RF24_250KBPS, RF24_1MBPS или RF24_2MBPS
  radio.setDataRate(RF24_1MBPS);
  // мощность: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM
  radio.setPALevel(RF24_PA_HIGH);

  radio.openWritingPipe(pipe);      // открываем трубу на передачу
  radio.stopListening();
}

void loop() {
  data[0]=0;
  data[1]=0;
  if (digitalRead(forw_but) == LOW) {
  data[1] = 6;
}
if (digitalRead(back_but) == LOW) {
  data[1] = -6;
}
if (digitalRead(left_but) == LOW) {
  data[0] = -6;
}
if (digitalRead(right_but) == LOW) {
  data[0] = 6;
}
radio.write(&data, sizeof(data)); // отправляем данные и указываем байты

Serial.print("x");
Serial.println(data[0]);             // выводим данные на монитор порта
Serial.print("y");
Serial.println(data[1]); 
//delay(1000);
}
