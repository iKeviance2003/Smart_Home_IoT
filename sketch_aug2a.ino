/*************************************************************
- Chương trình điều khiển bật/tắt các chân D1-D4 trên bo khi tác động
vào switch trên blynk.cloud tương ứng địa chỉ lần lượt là 5-4-0-LED_BUILTIN
- Giám sát trạng thái chân số 14(D5).
- Giám sát giá trị đọc được từ biến trở tại chân A0
- OK ngày 11/11/2023
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL68kvfTMzi"
#define BLYNK_TEMPLATE_NAME "PIR"
#define BLYNK_AUTH_TOKEN "AjbpuK5sbIGkZ3PL0O2EOYSyDQHrjiXN"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// Khai báo các chân kết nối
const int pirPin = 14;  // Cảm biến PIR //D5
const int ledPin = 5;  // LED //D1
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Zone Six 10NTP";
char pass[] = "Camonquykhach";

// Khai báo đối tượng BlynkTimer
BlynkTimer timer;

BLYNK_WRITE(V1) // Hàm này sẽ được gọi mỗi khi trạng thái của Virtual Pin V1 thay đổi
{
  int value = param.asInt(); // Đọc giá trị từ V1
  if (value == 1) {
    digitalWrite(ledPin, HIGH); // Bật LED
  } else {
    digitalWrite(ledPin, LOW);  // Tắt LED
  }
}

void mytimerevent() {
  int pirValue = digitalRead(pirPin); // Đọc giá trị từ cảm biến PIR
  Blynk.virtualWrite(V2, pirValue); // Gửi giá trị cảm biến PIR lên Virtual Pin V2
}

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT); // Cảm biến PIR vào chế độ đầu vào
  pinMode(ledPin, OUTPUT); // LED vào chế độ đầu ra
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, mytimerevent); // Cập nhật giá trị cảm biến PIR mỗi giây
}

void loop()
{
  Blynk.run();
  timer.run();
}