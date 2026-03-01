#include <Arduino.h>
#include "DHT.h"

// Định nghĩa chân cảm biến
#define DHTPIN 4
#define DHTTYPE DHT11
#define LIGHT_SENSOR_PIN 5

// Định nghĩa chân 3 LED
#define LED_TEMP 2    // LED báo nóng (> 30°C)
#define LED_HUMID 22  // LED báo độ ẩm cao (> 90%)
#define LED_LIGHT 18  // LED báo tối

// Định nghĩa ngưỡng cảnh báo
#define TEMP_THRESHOLD 30.0
#define HUMID_THRESHOLD 90.0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  // Khai báo chân Input
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  
  // Khai báo chân Output cho 3 LED
  pinMode(LED_TEMP, OUTPUT);
  pinMode(LED_HUMID, OUTPUT);
  pinMode(LED_LIGHT, OUTPUT);
  
  dht.begin();
  Serial.println("He thong giam sat Nhiet do - Do am - Anh sang da san sang!");
}

void loop() {
  delay(2000); // Đợi 2 giây giữa các lần đọc

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int isDark = digitalRead(LIGHT_SENSOR_PIN);

  // Kiểm tra lỗi cảm biến DHT
  if (isnan(t) || isnan(h)) {
    Serial.println("Loi: Khong doc duoc tu DHT11!");
    return;
  }

  // 1. Xử lý LED Nhiệt độ (> 30°C)
  if (t > TEMP_THRESHOLD) {
    digitalWrite(LED_TEMP, HIGH);
  } else {
    digitalWrite(LED_TEMP, LOW);
  }

  // 2. Xử lý LED Độ ẩm (> 90%)
  if (h > HUMID_THRESHOLD) {
    digitalWrite(LED_HUMID, HIGH);
  } else {
    digitalWrite(LED_HUMID, LOW);
  }

  // 3. Xử lý LED Ánh sáng (Trời tối thì bật LED)
  // Lưu ý: Tùy loại module quang trở, có loại xuất HIGH khi tối, có loại xuất LOW. 
  // Bạn kiểm tra nếu ngược thì đổi HIGH thành LOW ở dòng dưới.
  if (isDark == HIGH) {
    digitalWrite(LED_LIGHT, HIGH);
  } else {
    digitalWrite(LED_LIGHT, LOW);
  }

  // In thông số ra Serial Monitor để kiểm tra
  Serial.print("Nhiet do: "); Serial.print(t); Serial.print("°C | ");
  Serial.print("Do am: "); Serial.print(h); Serial.print("% | ");
  Serial.print("Trang thai anh sang: "); Serial.println(isDark == HIGH ? "TOI" : "SANG");
  Serial.println("---------------------------------------------------------");
}