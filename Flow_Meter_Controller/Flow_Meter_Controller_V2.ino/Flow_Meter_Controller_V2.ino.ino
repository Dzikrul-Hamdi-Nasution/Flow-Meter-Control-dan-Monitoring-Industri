#include <Wire.h> // Library komunikasi I2C 
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <EEPROM.h>
int arus, kondisi_memori, kondisi, memori;
int sensorValue = 0;
const int analogInPin = A0;
int fx, rumus, hasil_baca_1, hasil_baca, kalibrasi_ulang, kalibrasi_ulang_2;
int output_arus, merah = 12, hijau = 13;
double volume_flow;
double nilai_waktu = 0.000277778;
void setup()
{
  Serial.begin(9600);
  pinMode(merah, INPUT);
  pinMode(hijau, INPUT);
  pinMode (merah, INPUT_PULLUP);
  pinMode (hijau, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Flow Meter");
  memori = EEPROM.read(0);
  volume_flow = memori;
}
void loop()
{
  sensorValue = analogRead(analogInPin);
  for (int x = 0; x < 20; x++) {
    sensorValue = analogRead(analogInPin);
    hasil_baca = hasil_baca + sensorValue;
    delay(50);
    if (digitalRead(merah) == LOW) {
      volume_flow = 0;
      EEPROM.write(0, volume_flow);
      lcd.clear();
    }

    if (digitalRead(hijau) == LOW) {
      // turn LED on:


    }








  }




  hasil_baca_1 = hasil_baca / 20;
  hasil_baca = 0;

  kalibrasi_ulang = map(hasil_baca_1, 12, 490, 0, 378);
  //kalibrasi_ulang = hasil_baca_1;

  if (kalibrasi_ulang > 0) {
    lcd.setCursor(0, 0);
    lcd.print("Flow : ");
    lcd.print(kalibrasi_ulang);
    lcd.print("     ");
    if (kalibrasi_ulang < 100) {
      lcd.setCursor(9, 0);
      lcd.print(" ");
    }
  }
  else {
    lcd.setCursor(0, 0);
    kalibrasi_ulang = 0;
    lcd.print("Wiring Error");

  }
  rumus_volume();
  memori = EEPROM.read(0);
  lcd.setCursor(0, 1);
  lcd.print("Vol : ");
  lcd.print(memori);






}



void rumus_volume() {
  volume_flow = volume_flow + (kalibrasi_ulang * nilai_waktu);
  EEPROM.write(0, volume_flow);

}
