#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>


// Wi-Fi credentials
const char* ssid = "ssid_of_your_net";
const char* password = "password_to_your_network";
// end of wifi credent...
#define DHTPIN 19          // GPIO where DHT11 is connected
#define DHTTYPE DHT11      // Type of DHT in my case DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 23, 4, 15, 2);
Adafruit_BMP085 bmp;
int contrastValue = 60; // Default Contrast Value
const int adcPin = 34;
int adcValue = 0;


WebServer server(80); //port of webserver

void ondisplay() {
  float tc = dht.readTemperature(); // getting data from DHT
  float tf = dht.readTemperature(true); // getting data from DHT
  float hum = dht.readHumidity(); // getting data from DHT

  // Nastavení displeje
  display.clearDisplay();
  display.setContrast(60); // volitelně uprav kontrast
  display.setTextSize(1);
  display.setTextColor(BLACK);

  // Zobrazení teploty v °C
  display.setCursor(0, 0);
  display.println(".:DATA:.");
  display.setCursor(0, 10);
  display.print("Celsia : ");
  display.println(tc, 1);

  // Zobrazení teploty ve °F
  display.setCursor(0, 20);
  display.print("Fahren : ");
  display.println(tf, 1);

  // Zobrazení vlhkosti
  display.setCursor(0, 30);
  display.print("Vlhkost: ");
  display.println(hum, 1);
  
  display.display();   // Show  data on display
  delay(3000); // prodloužený čas pro čtení
}

String forecastFromPressure(float pressure_hPa) {
  if (pressure_hPa > 1030) return "☀️ Jasno a slunečno";
  else if (pressure_hPa > 1020) return "🌤 Převážně jasno";
  else if (pressure_hPa > 1010) return "⛅ Proměnlivé počasí";
  else if (pressure_hPa > 1000) return "🌦 Možnost přeháněk";
  else if (pressure_hPa > 990)  return "🌧 Déšť a oblačno";
  else return "⛈ Bouřky nebo silný vítr";
}

void handleRoot() {
  // DHT data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float tempfaht = dht.readTemperature(true);

  // BMP180 data
  float tcbmp = bmp.readTemperature();
  float bpress = bmp.readPressure(); // Pa
  float altt = bmp.readAltitude(101325); // m.n.m.
  float seapress = bpress / pow(1.0 - (altt / 44330.0), 5.255); // Pa

  // Přepočet na hPa
  float r_bpress = bpress / 100.0;
  float r_seapress = seapress / 100.0;
  float t_sum = temperature + tcbmp;
  float t_avg = t_sum / 2;

  // Předpověď počasí
  String forecast = forecastFromPressure(r_seapress);

  // HTML výstup
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>ESP32 Dashboard</title>";
  html += "<style>";
  html += "body { font-family: Arial; background: #f4f4f4; color: #333; padding: 20px; }";
  html += "h1 { color: #0077cc; }";
  html += "table { border-collapse: collapse; width: 100%; background: #fff; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }";
  html += "th, td { border: 1px solid #ccc; padding: 10px; text-align: left; }";
  html += "th { background-color: #0077cc; color: white; }";
  html += "tr:nth-child(even) { background-color: #f9f9f9; }";
  html += ".sensor-box { background: #fff; border-radius: 8px; padding: 15px; margin-top: 20px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }";
  html += "</style></head><body>";

  html += "<h1>📡 ESP32 Sensors Dashboard</h1>";
  html += "<div style='margin-bottom: 20px;'>";
  html += "<button onclick='resetPressure()'>Resetovat tlakový graf</button> ";
  html += "<button onclick='resetTemperature()'>Resetovat teplotní graf</button> ";
  html += "<button onclick='refreshForecast()'>Aktualizovat předpověď</button>";
  html += "</div>";
  if (isnan(temperature) || isnan(humidity) || isnan(tempfaht)) {
    html += "<p style='color:red;'>❌ Nelze číst DHT senzor!</p>";
  } else {
    html += "<table>";
    html += "<tr><th>Senzor</th><th>Parametr</th><th>Hodnota</th><th>Jednotka</th></tr>";
    html += "<tr><td>DHT11</td><td>Teplota</td><td>" + String(temperature, 1) + "</td><td>°C</td></tr>";
    html += "<tr><td>DHT11</td><td>Vlhkost</td><td>" + String(humidity, 1) + "</td><td>%</td></tr>";
    html += "<tr><td>DHT11</td><td>Teplota (F)</td><td>" + String(tempfaht, 1) + "</td><td>°F</td></tr>";
    html += "<tr><td>BMP180</td><td>Teplota</td><td>" + String(tcbmp, 1) + "</td><td>°C</td></tr>";
    html += "<tr><td>BMP180</td><td>Tlak</td><td>" + String(bpress, 1) + "</td><td>Pa</td></tr>";
    html += "<tr><td>BMP180</td><td>Nadm. výška</td><td>" + String(altt, 1) + "</td><td>m.n.m.</td></tr>";
    html += "<tr><td>BMP180</td><td>Tlak u moře</td><td>" + String(seapress, 1) + "</td><td>Pa</td></tr>";
    html += "<tr><td>BMP180</td><td>Tlak (hPa)</td><td>" + String(r_bpress, 1) + "</td><td>hPa</td></tr>";
    html += "<tr><td>BMP180</td><td>Tlak u moře (hPa)</td><td>" + String(r_seapress, 1) + "</td><td>hPa</td></tr>";
    html += "<tr><td>COUNTED</td><td>Teplota Průměr</td><td>" + String(t_avg, 1) + "</td><td>°C</td></tr>";
    html += "</table>";

    html += "<div class='sensor-box'>";
    html += "<h2>📍 Automatická předpověď</h2>";
    html += "<p style='font-size: 20px;'>" + forecast + "</p>";
    html += "</div>";

    html += "<canvas id='pressureChart' width='400' height='200'></canvas>";
    html += "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script>";
    html += "<script>";
    html += "let pressure = " + String(r_bpress, 1) + ";";
    html += "let history = JSON.parse(localStorage.getItem('pressureHistory')) || [];";
    html += "history.push({ time: new Date().toLocaleTimeString('cs-CZ', { hour: '2-digit', minute: '2-digit', second: '2-digit', hour12: false }), value: pressure });";
    html += "if (history.length > 720) history.shift();";
    html += "localStorage.setItem('pressureHistory', JSON.stringify(history));";

    html += "let ctx = document.getElementById('pressureChart').getContext('2d');";
    html += "new Chart(ctx, { type: 'line', data: { labels: history.map(p => p.time), datasets: [{ label: 'Tlak (hPa)', data: history.map(p => p.value), borderColor: 'blue', fill: false }] }, options: { scales: { y: { beginAtZero: false } } } });";
    html += "</script>";
    html += "<canvas id='tempChart' width='400' height='200'></canvas>";
    html += "<script>";
    html += "let tempAvg = " + String(t_avg, 1) + ";";
    html += "let tempHistory = JSON.parse(localStorage.getItem('tempHistory')) || [];";
    html += "tempHistory.push({ time: new Date().toLocaleTimeString('cs-CZ', { hour: '2-digit', minute: '2-digit', second: '2-digit', hour12: false }), value: tempAvg });";
    html += "if (tempHistory.length > 360) tempHistory.shift();";
    html += "localStorage.setItem('tempHistory', JSON.stringify(tempHistory));";

    html += "let ctx2 = document.getElementById('tempChart').getContext('2d');";
    html += "new Chart(ctx2, { type: 'line', data: { labels: tempHistory.map(p => p.time), datasets: [{ label: 'Průměrná teplota (°C)', data: tempHistory.map(p => p.value), borderColor: 'red', fill: false }] }, options: { scales: { y: { beginAtZero: false } } } });";
    html += "</script>";
  }

  html += "<p><em>🔄 Automatické obnovení za 5 sekund</em></p>";
  html += "<script>setTimeout(()=>{location.reload()},5000);</script>";
  html += "<script>";
  html += "function resetPressure() { localStorage.removeItem('pressureHistory'); location.reload(); }";
  html += "function resetTemperature() { localStorage.removeItem('tempHistory'); location.reload(); }";
  html += "function refreshForecast() { location.reload(); }";
  html += "</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
  
}



void setup() {
  Serial.begin(115200);
  Serial.println("---------------------------");
  Serial.println("HW INIT ver: 1.2");
  Serial.println("---------------------------");
  Serial.println("inicializuji DHT11...");
  dht.begin();
  Serial.println("inicializuji Dislplay...");
  display.begin();
  Serial.println("inicializuji BMP180...");
  if (!bmp.begin()) {
	Serial.println("nelze nalezt BMP085/BMP180 sensor, zkontroluj pripojeni");
  }
  Serial.println("inicializuji WI-FI");
  WiFi.begin(ssid, password);
  Serial.print("pripojuji k Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\npripojeno!");
  Serial.print("IP Adresa: ");
  Serial.println(WiFi.localIP());
  Serial.print("SSID site: ");
  Serial.println(WiFi.SSID());
  Serial.println("inicializuji server...");
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server bezi");
  String url= "http://";
  url += WiFi.localIP().toString();
  Serial.println("---------------------------");
  Serial.println(url);
  Serial.println("---------------------------");
}

void loop() {
  server.handleClient(); // call function of webserver.
  ondisplay();
}
