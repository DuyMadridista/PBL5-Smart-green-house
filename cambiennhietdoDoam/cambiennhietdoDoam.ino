#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define DHTPIN D2      // Chân GPIO kết nối với cảm biến DHT11
#define DHTTYPE DHT11 // Loại cảm biến DHT11
#define RELAY_PIN D1
#define SOIL_MOISTURE_PIN A0 // Chân GPIO kết nối với cảm biến độ ẩm đất
// #define LIGHT_SENSOR_PIN D7   // Chân GPIO kết nối với cảm biến ánh sáng
int value, realValue;

const char* ssid = "Redmi";     // Tên WiFi
const char* password = "12345678"; // Mật khẩu WiFi
const char* serverAddress = "http://192.168.107.79:3001/sensor-data"; // Địa chỉ endpoint Flask
const char* serverAddressPlum = "http://192.168.107.79:3001/getPlum";
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  delay(1000);
  dht.begin();
  connectToWiFi();
  
}

void loop() {
  for(int i = 0; i <= 9; i++) {
    realValue += analogRead(SOIL_MOISTURE_PIN);
  }
  value = realValue / 10;
  realValue = 0;
  int percentMoisture = map(value, 350, 1024, 0, 100);
  percentMoisture = 100 - percentMoisture;

  // Đọc dữ liệu từ cảm biến DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Đọc dữ liệu từ cảm biến ánh sáng
  // int lightIntensity = analogRead(LIGHT_SENSOR_PIN);

  // Kiểm tra nếu đọc dữ liệu thành công từ cảm biến DHT11 và cảm biến độ ẩm đất
  // if (isnan(humidity) || isnan(temperature)) {
  //   Serial.println("Failed to read from DHT sensor!");
  //   return;
  // }
  
  // In dữ liệu đo được ra Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  
  Serial.print("Soil Moisture: ");
  Serial.print(percentMoisture);
  Serial.println("%");
  int isPlum = getPlumData();
  if(percentMoisture < 50 || isPlum==1) {
    Serial.println(isPlum);
    digitalWrite(RELAY_PIN, LOW); // Bật máy bơm nước
    Serial.println("Water pump activated!"); // In ra thông điệp
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Tắt máy bơm nước
  }
  // Serial.print("Light Intensity: ");
  // Serial.println(lightIntensity);

  // Gửi dữ liệu đến endpoint trên server Flask
  sendSensorData(temperature, humidity, percentMoisture);
  
  delay(2000);
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendSensorData(float temperature, float humidity, int soilMoisture) {
  HTTPClient http;

  // Tạo đối tượng WiFiClient
  WiFiClient client;

  // Tạo URL của endpoint
  String url = String(serverAddress);

  // Tạo JSON object
  StaticJsonDocument<200> jsonDocument;
  jsonDocument["temperature"] = temperature;
  jsonDocument["humidity"] = humidity;
  jsonDocument["soil_moisture"] = soilMoisture;
  // jsonDocument["light_intensity"] = lightIntensity;

  // Chuyển đổi JSON object thành chuỗi
  String jsonString;
  serializeJson(jsonDocument, jsonString);

  Serial.print("Sending data to: ");
  Serial.println(url);

  // Gửi request POST đến server Flask
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);
  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error sending HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
int getPlumData() {
  HTTPClient http;

  // Tạo đối tượng WiFiClient
  WiFiClient client;

  // Tạo URL của endpoint
  String url = "http://192.168.107.79:3001/getPlum";

  // Gửi yêu cầu GET đến URL
  http.begin(client, url); // Sử dụng client đã được khởi tạo trong setup()
  int httpResponseCode = http.GET();

  int isPlum = 0; // Mặc định không bật máy bơm
  
  if (httpResponseCode == 200) {
    // Đọc dữ liệu JSON từ phản hồi
    String payload = http.getString();
    DynamicJsonDocument jsonDocument(200);
    deserializeJson(jsonDocument, payload);

    // Lấy giá trị của isPlum
    isPlum = jsonDocument["isPlum"];
    Serial.print("isPlum: ");
    Serial.println(isPlum);
  } else {
    Serial.print("Error getting Plum data: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  
  return isPlum;
}



