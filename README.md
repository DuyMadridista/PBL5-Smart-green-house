# Đồ Án: Xây Dựng Nhà Kính Thông Minh

## Mô tả
Dự án "Xây dựng nhà kính thông minh" nhằm mục đích tạo ra một hệ thống nhà kính tự động, sử dụng các công nghệ hiện đại để giám sát và điều khiển các yếu tố môi trường như nhiệt độ, độ ẩm và ánh sáng. Hệ thống bao gồm một server Flask, Node.js và các phần cứng như ESP8266 và ESP32.

## Cấu trúc dự án

### 1. Phần cứng
- **ESP8266 và ESP32**: Các vi điều khiển này sẽ được sử dụng để thu thập dữ liệu từ các cảm biến (nhiệt độ, độ ẩm, ánh sáng, v.v.) và gửi dữ liệu đến server.
- **Cảm biến**: Các cảm biến nhiệt độ, độ ẩm, ánh sáng và các cảm biến khác được kết nối với ESP8266 và ESP32.

### 2. Phần mềm
- **Server Flask**: Được sử dụng để xử lý dữ liệu từ các thiết bị phần cứng và cung cấp API cho ứng dụng web.
- **Node.js**: Sử dụng để xây dựng ứng dụng web thời gian thực, giúp người dùng có thể giám sát và điều khiển nhà kính từ xa.

## Hướng dẫn cài đặt

### 1. Cài đặt phần cứng
- **ESP8266 và ESP32**: Kết nối các cảm biến với ESP8266 và ESP32 theo sơ đồ mạch.
- Nạp firmware cho ESP8266 và ESP32 để thu thập và gửi dữ liệu.

### 2. Cài đặt phần mềm
- **Yêu cầu hệ thống**:
  - Python 3.x
  - Node.js
  - npm (Node Package Manager)

#### a. Server Flask
1. Cài đặt các thư viện cần thiết:
    ```bash
    pip install flask
    pip install flask-restful
    pip install flask-cors
    ```
2. Chạy server Flask:
    ```bash
    python server.py
    ```

#### b. Ứng dụng Node.js
1. Cài đặt các gói cần thiết:
    ```bash
    npm install
    ```
2. Chạy ứng dụng:
    ```bash
    npm start
    ```

## Cấu trúc thư mục
smart-greenhouse/
│
├── hardware/
│ ├── esp8266/
│ │ ├── firmware/
│ │ └── connections/
│ └── esp32/
│ ├── firmware/
│ └── connections/
│
├── server/
│ ├── app/
│ │ ├── init.py
│ │ ├── routes.py
│ │ └── models.py
│ ├── server.py
│ └── requirements.txt
│
├── web/
│ ├── public/
│ ├── src/
│ ├── package.json
│ └── server.js
│
└── README.md

## Cách sử dụng
1. Khởi động các thiết bị ESP8266 và ESP32, đảm bảo chúng kết nối thành công với mạng WiFi và server.
2. Chạy server Flask để xử lý dữ liệu.
3. Khởi động ứng dụng Node.js để cung cấp giao diện web.
4. Truy cập ứng dụng web qua trình duyệt để giám sát và điều khiển nhà kính.

## Tài liệu tham khảo
- [Flask Documentation](https://flask.palletsprojects.com/)
- [Node.js Documentation](https://nodejs.org/en/docs/)
- [ESP8266 Documentation](https://www.espressif.com/en/products/socs/esp8266)
- [ESP32 Documentation](https://www.espressif.com/en/products/socs/esp32)

## Liên hệ
Nếu có bất kỳ câu hỏi hoặc góp ý nào, vui lòng liên hệ:
- Email: vanduyluu432003@gmail.com.com
- Số điện thoại: (+84) 819 682 458

---
