// Bilbiotecas

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <bits/stdc++.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

//Variaveis Globais
 
const char* ssid = "Anisio-Vivo";
const char* password = "fernandesmontes";
WiFiClient client;
int ledPin = D5;
int relePin = D4;
int vermelhoPin = D3;

std::map<String,int> PortasValor;

String serverName = "adequate-engaged-calf.ngrok-free.app";

void startPortas(){
  String resposta = "bab";
  String req = serverName + "";
  JsonDocument doc;
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(relePin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(vermelhoPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  HTTPClient http;
  WiFiClient cliente;
  
  http.begin(cliente, req.c_str());
  int httpCode = http.GET();
  if (httpCode > 0) {
    resposta = http.getString();
    Serial.println(resposta);
  }else {
    Serial.print("Error code: ");
  }
  Serial.println(httpCode);
  http.end();
}

int defineEstadoPorta(String nome, String valor){
  valor.toLowerCase();
  nome.toLowerCase();

  if (PortasValor.find(nome) == PortasValor.end()) {
    return 404;
  }
  int value = 0;
  if(valor.equals("ligado") || valor.equals("ligar")){
    value = 1;
  }
  digitalWrite(PortasValor[nome],value);
  return 200;
}

void definePorta(String nome, int porta, String tipo){
  nome.toLowerCase();
  PortasValor[nome] = porta;
  tipo.toLowerCase();
  if(tipo.equals("input")){
    pinMode(porta, INPUT);
    return;
  }
  pinMode(porta, OUTPUT);
}

WiFiServer server(8082);

void setup() {
  Serial.begin(9600);
  delay(10);
 
  // Conecta a sua Rede WIFI e Mostra na Porta Serial
  Serial.println();
  Serial.println();
  Serial.print("Conectando a rede ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //startPortas();
  Serial.println("");
  Serial.println("WiFi conectado");
 
  // Inicia o Servidor no qual iremos ver no navegador e poder acionar o Relé
  server.begin();
  Serial.println("Servidor Iniciado");
 
  // Retorna o Valor do IP que estará nosso servidor na Rede.
  Serial.print("Usar essa URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

void mandar404(){
  client.println("HTTP/1.1 404 Not Found");
  client.println("Content-Type: text/html");
  client.println(""); // Deixei em branco para indicar o fim do cabeçalho HTTP
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>404 Not Found</title></head>");
  client.println("<body>");
  client.println("<h1>404 Not Found</h1>");
  client.println("<p>O recurso solicitado não foi encontrado no servidor.</p>");
  client.println("</body>");
  client.println("</html>");
}

void mandar400(){
  client.println("HTTP/1.1 400 Bad Request");
  client.println("Content-Type: text/html");
  client.println(""); // Deixei em branco para indicar o fim do cabeçalho HTTP
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>400 Bad Request</title></head>");
  client.println("<body>");
  client.println("<h1>400 Bad Request</h1>");
  client.println("<p>Seu pedido não pôde ser compreendido pelo servidor.</p>");
  client.println("</body>");
  client.println("</html>");
}

std::map<String,String> lerGet(String url){
  std::map<String,String> mapa;
  int inicioGet = url.indexOf("?");
   if(inicioGet == -1){
    return mapa;
  }
  
  String key = "";
  String value = "";
  bool i = false;
  url = url.substring(inicioGet);
  url = url.substring(1,url.indexOf(" "));
  if(url.indexOf("/") != -1){
    mandar404();
    return mapa;
  }
  Serial.println("MyURL = " + url);
  for(char c : url){
    if(c == '&'){
      mapa[key] = value;
      i = !i;
      key = "";
      value = "";
      continue;
    }
    if(c == '='){
      i = !i;
      continue;
    }
    if(!i){
      key += c;
      continue;
    }
    value += c;
  }
  mapa[key] = value;
  return mapa;
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
  }
  // Monitora se existe Cliente( alguém) usando o navegador. Pode ser acompanhado pela porta COM
  client = server.available();
  if (!client) {
    return;
  }
 
  // Servidor fica em estado de espera para alguém enviar o comando( Dados)
  Serial.println("Embarcado");

  // AQUI COMEÇA O CÓDIGO HTML junto com a chamada HTTP>>>>>>
  
  // Faz a leitura da chamada HTTP e mostra os valores baseado no programa acima no VOID SETUP. 
  // Lembrando que aqui não é o programa que subimos( void setup()) e sim, a parte HTML que será enviado para o servidor.
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Compara o pedido de Chamada HTTP e verifica se bate com o programa que fizemos.
  std::map<String,String>::iterator it;
  std::map<String,String> chavesValor = lerGet(request);
  std::vector<String> chaves = {"led","rele","vermelho"};
  
  if(!chavesValor.empty()){

    for(it = chavesValor.begin();it!=chavesValor.end();++it){
      if(std::find(chaves.begin(),chaves.end(),it->first) == chaves.end()){
        mandar400();
        return;
      }
      if(it->second != String("ligado") && it->second != String("desligado")){
        mandar400();
        return;
      }
    }
  }

  std::map<String,int> aux;
  aux["ligado"] = 1;
  aux["desligado"] = 0;

    for(auto it = chavesValor.begin(); it != chavesValor.end(); ++it) {
      if (it->first == "led") {
        digitalWrite(ledPin, aux[it->second]);
        continue;
      } 
      if (it->first == "rele") {
        digitalWrite(relePin, aux[it->second]);
        continue;
      }
      digitalWrite(vermelhoPin, aux[it->second]);
    }

  String jeySon = "{";
  jeySon += "\"led\":\"";
  if(digitalRead(ledPin) == HIGH){
    jeySon += String("ligado") + String("\",");
  }else{
    jeySon += String("desligado") + String("\",");
  }

  jeySon += " \"rele\":\"";
  if(digitalRead(relePin) == HIGH){
    jeySon += String("ligado") + String("\",");
  }else{
    jeySon += String("desligado") + String("\",");
  }

  jeySon += " \"vermelho\":\"";
  if(digitalRead(vermelhoPin) == HIGH){
    jeySon += String("ligado") + String("\"");
  }else{
    jeySon += String("desligado")+ String("\"");
  }
  jeySon += "}";
  //Serial.println(jeySon);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println(""); // Deixei em branco para quem adivinhar o que faz aqui. Não afeta o código, mas gera algo interessante (:
  client.println(jeySon);

  delay(1);
  Serial.println("Embarcado saiu (: ");
  Serial.println("");
}