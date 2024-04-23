#include <ArduinoJson.h>

String jsonData = R"([
  {
    "title": "sunt aut facere repellat provident occaecati excepturi optio reprehenderit",
    "body": "quia et suscipit\nsuscipit recusandae consequuntur expedita et cum\nreprehenderit molestiae ut ut quas totam\nnostrum rerum est autem sunt rem eveniet architecto"
  },
  {
    "title": "qui est esse",
    "body": "est rerum tempore vitae\nsequi sint nihil reprehenderit dolor beatae ea dolores neque\nfugiat blanditiis voluptate porro vel nihil molestiae ut reiciendis\nqui aperiam non debitis possimus qui neque nisi nulla"
  },
  {
    "title": "ea molestias quasi exercitationem repellat qui ipsa sit aut",
    "body": "et iusto sed quo iure\nvoluptatem occaecati omnis eligendi aut ad\nvoluptatem doloribus vel accusantium quis pariatur\nmolestiae porro eius odio et labore et velit aut"
  }
])";

void setup() {
  Serial.begin(9600);
  Serial.println(jsonData);
  // Parsing do JSON
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, jsonData);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  // Itera sobre todos os elementos do array JSON
  for (JsonVariant element : doc.as<JsonArray>()) {
    // Para cada elemento, itera sobre todas as chaves
    for (JsonPair kv : element.as<JsonObject>()) {
      Serial.print("Key: ");
      Serial.print(kv.key().c_str());
      Serial.print(", Value: ");
      Serial.println(kv.value().as<String>());
    }
    Serial.println(); // Adiciona uma linha em branco entre os elementos
  }
}

void loop() {
  // Nada aqui por enquanto
}
