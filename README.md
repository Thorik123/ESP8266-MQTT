## ESP8266 MQTT

Pada project ini, saya menggunakan layanan MQTT dari [EMQX](https://www.emqx.io/)

MQTT merupakan protokol pengiriman pesan terbuka yang ringan dan dikhususkan untuk protokol jaringan dengan bandwidth terbatas atau perangkat IoT dengan latensi sangat tinggi.

Karena MQTT dikhususkan untuk komunikasi pada bandwidth rendah atau lingkungan berlatensi tinggi, maka dari itu menjadi protokol yang ideal untuk komunikasi mesin-ke-mesin (M2M).

MQTT adalah singkatan dari Message Queuing Telemetry Transport, sebuah protokol jaringan yang menjadi penghubung komunikasi mesin ke mesin.

---

## Komponen MQTT

Setidaknya ada 4 komponen dalam protokol MQTTT yang akan dijelaskan pada point-point berikut ini:

- **Pesan**
  Pesan adalah data yang dibawa keluar oleh protokol ke seluruh jaringan. Ketika pesan ditransmisikan melalui jaringan, maka pesan tersebut berisi parameter berikut:

  - `Payload`
  - `Quality of Service (QoS)`
  - `Property collection`
  - `Nama Topik`
  - `Klien`

- **Klien**

  - Perangkat dikatakan sebagai klien jika membuka koneksi jaringan ke server, melakukan publish pesan yang ingin dilihat klien lain, melakukan subscribe pada pesan yang ingin diterima, berhenti subscibe pesan yang tidak ingin diterima, dan menutup koneksi jaringan ke server.
    Di MQTT, klien melakukan dua operasi, yakni:

  - `Publish`: Saat klien mengirim data ke server
  - `Subscribe`: Ketika klien menerima data dari server

- **Broker/Server**

  - Server atau broker pada MQTT adalah perangkat atau program yang memungkinkan klien untuk subscribe pesan dan publish pesan. Server menerima koneksi jaringan dari klien, menerima pesan dari klien, memproses permintaan subscribe dan berhenti subscribe, meneruskan pesan aplikasi ke klien, dan menutup koneksi jaringan dari klien.

- **Topic**
  - Dalam MQTT dikenal istilah topik yaitu berupa UTF-8 string yang perannya hampir sama seperti topik pada chat hanya saja lebih sederhana dan berfungsi sebagai filter untuk broker atau server dalam mengirimkan pesan ke tiap klien yang terhubung. Dengan kata lain, topik adalah kanal bagi klien untuk subscribe.

---

## Konfigurasi

Sebelum melalukan proses upload ke mikrokontroller, harap memperhatikan beberapa parameter berikut:

- WiFi Parameter

```cpp
const char *wifi_ssid = "xxxxxxxxxxxxx";  // Enter your WiFi name
const char *wifi_pass = "xxxxxxxxxxxxx";  // Enter WiFi password
```

Ganti/ubah SSID dan Password WiFi yang digunakan. Ini penting agar device(ESP) bisa terkoneksi dengan internet dan terhubung ke server/broker.

- MQTT Parameter

Secara default parameter dari dokumentasi **EMQX** adalah sebagai berikut:

```cpp
const char *mqtt_broker = "broker.emqx.io";  // broker address
const char *mqtt_topic = "esp8266/test";     // define topic
const char *mqtt_username = "emqx";          // username for authentication
const char *mqtt_password = "public";        // password for authentication
const int mqtt_port = 1883;                  // port of MQTT over TCP
```

Ubah atau ganti untuk parameter topic `esp8266/test`. Seperti yang sudah dijelaskan sebelumnya bahwa ini yang menjadi kanal atau alamat dari setiap data yang dikirim/diterima. Silahkan ganri dengan yang lebih spesifik dan unik, contoh bisa diambil dari MAC Address atau CHIP-ID perangkat.

Dan untuk parameter yang lain biarkan saja.

---

## Preference

- **Board**

  - ESP8266 3.1.2 by ESP8266 Community
    `https://arduino.esp8266.com/stable/package_esp8266com_index.json`

- **Library**
  - `PubSubClient at version 2.7` [Documentation](https://pubsubclient.knolleary.net/)

---

Selengkapnya bisa baca dokumentasi dari [EMQX](https://docs.emqx.com/en/cloud/latest/connect_to_deployments/esp8266.html)

---
