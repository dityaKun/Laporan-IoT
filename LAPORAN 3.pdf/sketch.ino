#define BLYNK_DEVICE_NAME "Esp32IoT"
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_NAME "Praktek3"
#define BLYNK_AUTH_TOKEN "tx3ikpJ0EgRKIevhaJHnX288aQ_LFhU1"
#define BLYNK_TEMPLATE_ID "TMPL65IBPXVXd"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h>
#include <LiquidCrystal_I2C.h> 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

const int DHT_PIN = 15;

int value0, value1, value2, value3, value6;

byte LED_R = 26;
byte LED_Y = 27;
byte LED_G = 14;
byte LED_B = 12;

DHTesp dht;
BlynkTimer timer;

// Inisialisasi LCD I2C alamat 0x27, 16 kolom, 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Fungsi untuk mengirim data sensor
void sendSensor()
{
  TempAndHumidity data = dht.getTempAndHumidity();

  // Menampilkan di Serial Monitor
  Serial.print("% Temperature: ");
  Serial.print(data.temperature);
  Serial.println("C ");
  Serial.print("% Kelembaban: ");
  Serial.print(data.humidity);
  Serial.println("% ");

  // Mengirim ke Blynk
  Blynk.virtualWrite(V0, data.temperature);
  Blynk.virtualWrite(V1, data.humidity);

  // Menampilkan di LCD
  lcd.setCursor(0, 0); // baris pertama
  lcd.print("Temp: ");
  lcd.print(data.temperature, 1); // satu angka desimal
  lcd.print((char)223); // simbol derajat
  lcd.print("C     "); // spasi untuk hapus sisa karakter lama

  lcd.setCursor(0, 1); // baris kedua
  lcd.print("Humi: ");
  lcd.print(data.humidity, 1);
  lcd.print("%     ");
}

BLYNK_WRITE(V2)
{
  int nilaiBacaIO = param.asInt();
  digitalWrite(LED_R, nilaiBacaIO);
  Blynk.virtualWrite(V3, nilaiBacaIO);
}

void setup()
{
  Serial.begin(115200);
  dht.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(LED_R, OUTPUT);

  lcd.init();         // Inisialisasi LCD
  lcd.backlight();    // Nyalakan lampu belakang LCD
  lcd.setCursor(0, 0);
  lcd.print("Monitoring...");

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
