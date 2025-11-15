#include <WiFi.h>           // Biblioteca para conexão Wi-Fi no ESP32
#include <PubSubClient.h>   // Biblioteca para comunicação MQTT

// Configurações de Wi-Fi
const char *ssid     = "Wokwi-GUEST";
const char *password = "";

// Configurações do broker MQTT
const char *mqtt_broker = "broker.hivemq.com";
int mqtt_port           = 1883;
const char *client_id   = "ESP32_Guilherme_01";

// Tópicos MQTT para publicar e assinar
String topic_custom_publish   = "guilherme/iot/ldr/pub";
String topic_custom_subscribe = "guilherme/iot/ldr/sub";

// Objetos de rede e cliente MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Configuração do sensor LDR
const int ldrPin = 33;     // Pino analógico onde o LDR está conectado
float ldrValue;            // Variável para armazenar a leitura do LDR
String val_distance_data = "ldr";  // Chave usada no JSON publicado

// Assinaturas de funções
void callback(char *topic2, byte *payload, unsigned int length);
void reconnect();

void setup() {
  pinMode(ldrPin, INPUT);  // Define o pino do LDR como entrada

  Serial.begin(9600);      // Inicia comunicação serial para debug
  delay(1000);

  // Conexão com a rede Wi-Fi
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password, 6);   // Conecta ao Wi-Fi (canal 6 no Wokwi)

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Mostra IP do ESP32

  // Configurações do cliente MQTT
  client.setServer(mqtt_broker, mqtt_port);  // Define broker e porta
  client.setCallback(callback);              // Define função de callback para mensagens recebidas

  // Tenta conectar ao broker MQTT
  while (!client.connected()) {
    Serial.printf("Cliente %s tentando conectar no HiveMQ public broker...\n", client_id);

    if (client.connect(client_id)) {
      Serial.println("Conectado ao HiveMQ Public broker!");
    } else {
      Serial.print("Falha na conexão, estado: ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  // Converte o tópico de subscribe para char[] e realiza inscrição
  char finalsubs[topic_custom_subscribe.length() + 1];
  topic_custom_subscribe.toCharArray(finalsubs, topic_custom_subscribe.length() + 1);
  client.subscribe(finalsubs);
  Serial.print("Inscrito no tópico: ");
  Serial.println(finalsubs);
}

// Função chamada sempre que uma mensagem chega em um tópico assinado
void callback(char *topic2, byte *payload, unsigned int length) {
  Serial.println("==== Mensagem recebida ====");
  Serial.print("Tópico: ");
  Serial.println(topic2);
  Serial.print("Mensagem: ");

  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);   // Mostra o payload recebido caractere a caractere
  }

  Serial.println();
  Serial.println("---------------------------");
}

// Função para reconectar ao broker MQTT em caso de desconexão
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando reconectar ao HiveMQ... ");

    if (client.connect(client_id)) {
      Serial.println("Conectado!");

      // Reinscreve no tópico após reconectar
      char finalsubs[topic_custom_subscribe.length() + 1];
      topic_custom_subscribe.toCharArray(finalsubs, topic_custom_subscribe.length() + 1);
      client.subscribe(finalsubs);
      Serial.print("Reinscrito no tópico: ");
      Serial.println(finalsubs);
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" - tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void loop() {
  // Garante que o cliente MQTT esteja conectado
  if (!client.connected()) {
    reconnect();
  }

  client.loop();  // Mantém a comunicação MQTT ativa

  // Leitura do valor analógico do LDR
  ldrValue = analogRead(ldrPin);
  Serial.print("Leitura LDR: ");
  Serial.println(ldrValue);

  // Monta mensagem em formato JSON para envio via MQTT
  String mensagemJson = "{\"" + val_distance_data + "\":\"" + String(ldrValue, 0) + "\"}";

  // Conversão das Strings para char[] para publicar
  char finalDataChar[mensagemJson.length() + 1];
  char topicChar[topic_custom_publish.length() + 1];

  mensagemJson.toCharArray(finalDataChar, mensagemJson.length() + 1);
  topic_custom_publish.toCharArray(topicChar, topic_custom_publish.length() + 1);

  // Publica a mensagem no tópico definido
  client.publish(topicChar, finalDataChar);
  Serial.print("Publicado no tópico ");
  Serial.print(topicChar);
  Serial.print(": ");
  Serial.println(mensagemJson);

  delay(1000);  // Aguarda 1 segundo entre as leituras/publicações
}