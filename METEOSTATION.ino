/*
  Метеостанция на датчиках DHT
  Написал код M_A_Production
  Сайт maprod.ru
*/
//Библиотека датчика температуры
#include "DHT.h"
//Библиотеки дисплейного модуля
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Настройка датчика температуры
#define DHTPIN 2 //Digital пин

//Выберите свой датчик, надо раскоментировать подходящую модель
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
//Настройка дисплейного модуля по шине I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
 /*
 pinMode(3,INPUT_PULLUP);
 digitalWrite(3, HIGH);
 */
  //Запуск дисплейного модуля
  lcd.init();
  lcd.init();
  lcd.backlight();

  //Запуск датчика температуры
  dht.begin();
}

void loop() {
  /*
  //Включение и выключение дисплейного модуля с кнопки
  if(digitalRead(3)==LOW){
    lcd.noDisplay();
  }
  else{
    lcd.display();
  }
  */
  //Запись значений с датчика в переменные
  float h = dht.readHumidity(); //Влажность
  float t = dht.readTemperature(); //Темпратура
  float f = dht.readTemperature(true);

  //Вывод ошибки чтения данных с датчика
  if (isnan(h) || isnan(t)) {
    lcd.print(F("Failed to read from DHT sensor!"));
    delay(100);
    return;
  }

  //Подсчет температуры которую чувствует человек
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  //Вывод значений на экран

  //Вывод влажности
  lcd.setCursor(0, 0);
  lcd.print("Hum:");
  lcd.print(int(h));
  
  //Вывод температуры
  lcd.setCursor(7, 0);
  lcd.print("Temp:");
  lcd.print(int(t));
  if(t>=0 || t<10){
     lcd.setCursor(14, 0);
  }
  else{
     lcd.setCursor(15, 0);
  }
 
  lcd.print("C");

  //Вывод температуры которую чувствет человек
  lcd.setCursor(0, 1);
  lcd.print("Heat Index:");
  lcd.setCursor(12, 1);
  lcd.print(int(hic));
  lcd.print(" C");

  //обновление экрана
  delay(2000);
  lcd.clear();


}
