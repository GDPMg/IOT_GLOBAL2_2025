# 📡 Projeto IoT com ESP32 – Medição de Luminosidade via MQTT (LDR + HiveMQ)

Este projeto demonstra uma solução IoT utilizando **ESP32**, **sensor LDR** e comunicação **MQTT** para enviar medições de luminosidade em tempo real.  
A aplicação foi desenvolvida como parte de um trabalho acadêmico, explorando automação, sensores e o futuro do trabalho conectado. Nosso projeto 
apresenta uma solução IoT capaz de monitorar continuamente a luminosidade e oferecer recomendações em tempo real para melhorar o conforto e a ergonomia do ambiente.

---

## 🚨 Problema

Ambientes modernos exigem monitoramento contínuo de luminosidade para automação, ergonomia e segurança.  
O desafio é permitir que um dispositivo simples colete essas informações e envie para outra aplicação de forma leve, eficiente e confiável.

---

## 💡 Solução Criada

A solução utiliza:

- ESP32 como dispositivo principal  
- Sensor LDR (resistor dependente de luz)  
- Envio dos dados via MQTT para o HiveMQ Public Broker  
- Visualização e análise no Node-RED  
- Simulação completa no Wokwi  

O ESP32 lê o valor do LDR, gera um JSON e publica em um tópico MQTT.  
O Node-RED recebe esses dados e exibe em gráficos e gauges.

---

## 🔧 Tecnologias Utilizadas

- **ESP32**
- **LDR + resistor**
- **MQTT (HiveMQ Public Broker)**
- **Node-RED**
- **Arduino IDE**
- **Wokwi (simulação online)**

---

## 🧪 Funcionamento Geral

1. O ESP32 conecta ao Wi-Fi.
2. Lê continuamente o valor do LDR.
3. Gera um JSON como:
   ```json
   {"ldr":"1234"}
4. Publica no tópico MQTT definido.
5. O Node-RED processa e exibe em dashboards.
6. O ESP32 também pode receber comandos via subscribe.

---

## 📡 Tópicos MQTT Utilizados

Tópico de publicação:
- guilherme/iot/ldr/pub

Tópico de assinatura:
- guilherme/iot/ldr/sub

Broker utilizado:
- broker.hivemq.com
- Porta: 1883

---

## 🛠️ Dependências

Bibliotecas utilizadas

- #include <WiFi.h>
- #include <PubSubClient.h>

Instale via Library Manager no Arduino IDE.

Placa

- ESP32 Dev Module (instalar via Boards Manager)

---

## ▶️ Como Executar o Projeto

1. Clonar o repositório
- git clone https://github.com/SEU-USUARIO/SEU-REPO.git

2. Abrir o código no Arduino IDE
3. Instalar as bibliotecas necessárias
4. Selecionar a placa ESP32 e a porta correta
5. Fazer upload para o ESP32
6. No Node-RED:
- Criar fluxo MQTT-IN → Gauge/Chart/Debug
- Configurar com o mesmo broker e tópicos

---

## 🔗 Link da simulação no Wokwi
- https://wokwi.com/projects/447712083002777601I

## 🔗 Link Youtube
- https://youtu.be/f6DmKOWooxY?si=fBDmx725Y0ycrukB

---

## 📸 Imagem do circuito
<img width="1088" height="359" alt="image" src="https://github.com/user-attachments/assets/b29ce941-97cd-4df5-9e5b-e5379b6848c7" />

---

## 📸 Imagem do Dashboard
<img width="1249" height="748" alt="image" src="https://github.com/user-attachments/assets/c007e0e2-2571-48c8-91d7-c9ea8c2fd744" />

---

## 📊 Resultado Esperado

- Leitura contínua da luminosidade
- Publicação confiável via MQTT
- Dashboard em tempo real no Node-RED
- Comunicação bidirecional ESP32 ↔️ MQTT
