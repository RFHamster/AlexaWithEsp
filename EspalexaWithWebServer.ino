#include <bits/stdc++.h>
#include <Espalexa.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

// Funções
boolean connectWifi();
void inicializarD1();
void firstLightChanged(uint8_t brightness);
void adicionarDispositivo(String nome, String porta, int tipo);

// Rede
const char* ssid = "Anisio-Vivo";
const char* password = "fernandesmontes";

boolean wifiConnected = false;
Espalexa espalexa;
ESP8266WebServer server(80);
std::map<String,int> portaValorD1;

void setup()
{
  // Inicializando Sistema
  Serial.begin(115200);
  wifiConnected = connectWifi();
  inicializarD1();
  
  if(wifiConnected){
    //recuperarPortas();
    //Configurando EndPoints
    server.on("/", HTTP_GET, [](){
      server.send(200, "text/plain", "Fununciando.");
      Serial.println("Funciona!");
    });

    server.on("/cadastrar", HTTP_GET, [](){
      String nome = server.arg("nome");
      String porta = server.arg("porta");
      String tipo = server.arg("tipo");

      Serial.println(nome);
      Serial.println(porta);
      Serial.println(tipo);

      if(nome == "" || porta == "" || tipo == ""){
        server.send(400, "text/plain", "Bad Request");
      }else{
        char c = tipo[0];
        int t = c - '0';
        adicionarDispositivo(nome, porta, t);
        Serial.println("Cadastrou");
        server.send(200, "application/json", "{\"request\": 1}");
      }

    });
    server.onNotFound([](){
      if (!espalexa.handleAlexaApiCall(server.uri(),server.arg(0)))
      {
        server.send(404, "text/plain", "Not found");
      }
    });

    espalexa.begin(&server);
  } else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
  espalexa.loop();
  delay(1);
}

void adicionarDispositivo(String nome, String porta, int tipo){
  int valor = portaValorD1[porta];
  if(tipo == 0){
    pinMode(valor,INPUT);
  }else{
    pinMode(valor,OUTPUT);
  }
  
  digitalWrite(valor,0);

  espalexa.addDevice(nome, [nome,valor](uint8_t brightness){
    Serial.print(nome);
    Serial.print(" mudou para ");

    if (brightness) {
      Serial.println("ON");
      digitalWrite(valor,1);
    }
    else  {
      digitalWrite(valor,0);
      Serial.println("OFF");
    }
  });

}

void inicializarD1(){
  portaValorD1["0"] = D0;
  portaValorD1["1"] = D1;
  portaValorD1["2"] = D2;
  portaValorD1["3"] = D3;
  portaValorD1["4"] = D4;
  portaValorD1["5"] = D5;
  portaValorD1["6"] = D6;
  portaValorD1["7"] = D7;
  portaValorD1["8"] = D8;
  portaValorD1["9"] = D9;
}

void recuperarPortas(){
  JsonDocument doc;
  String serverName = "http://adequate-engaged-calf.ngrok-free.app/chassi/1";
  HTTPClient http;
  WiFiClient client;
  String resposta;
  http.begin(client, serverName.c_str());
  int httpCode = http.GET();
  if (httpCode > 0) {
    resposta = http.getString();
    Serial.println(resposta);
  }else {
    Serial.print("Error code: ");
    return;
  }
  Serial.println(httpCode);
  http.end();
  DeserializationError error = deserializeJson(doc, resposta);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  std::map<String,String> aux;
  // Itera sobre todos os elementos do array JSON
  for (JsonVariant element : doc.as<JsonArray>()) {
    for (JsonPair kv : element.as<JsonObject>()) {
      aux[kv.key().c_str()] = kv.value().as<String>();
    }
  }
  int tipo = aux["tipo"][0] - '0';
  adicionarDispositivo(aux["nome"],aux["porta"],tipo);
}

boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  delay(100);
  return state;
}
