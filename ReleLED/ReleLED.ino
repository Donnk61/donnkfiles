#include <WiFi.h>
#include <ArduinoOTA.h>
#include <WebServer.h>

int pinoRELE = 22;
int pinoBUTTON = 23;

//python3 espota.py -i 192.168.1.117 -p 3232 --auth=larsis@larsis --file ReleLED.ino.bin

const char *ssid = "LARSIS_ROBOS";
const char *password = "larsis@larsis";

String releState="off";
String buttonState="off";

WebServer server(80);

void OTASETUP(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
  Serial.println(WiFi.localIP());

  // Inicializa o OTA
  ArduinoOTA.setHostname("nome-da-sua-esp");
  ArduinoOTA.setPassword("larsis@larsis"); // A mesma usada com --auth

  ArduinoOTA.onStart([]() {
    Serial.println("Iniciando OTA");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA Finalizada");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progresso: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erro [%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Falha de autenticação");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Erro ao começar");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Erro de conexão");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Erro de recepção");
    else if (error == OTA_END_ERROR) Serial.println("Erro ao finalizar");
  });

  ArduinoOTA.begin();
    pinMode(2, OUTPUT);
  Serial.println("Pronto para OTA");
}

/*void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  html += ".button2 { background-color: #f44336; }</style></head>";
  html += "<body><h1>TITANS VSSS LED CAMPO</h1>";

  // pinRELE controle
  html += "<p>RELE(22) - State " + releState + "</p>";
  if (releState == "on") {
    html += "<p><a href=\"/off\"><button class=\"button\">OFF</button></a></p>";
  } else {
    html += "<p><a href=\"/on\"><button class=\"button button2\">ON</button></a></p>";
  }
  
  html += "</body></html>";
  server.send(200, "text/html", html);
}*/

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="pt-br">
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <link rel="icon" href="data:,">
      <title>VSSS LED CAMPO</title>
      <style>
        body {
          background: linear-gradient(135deg, #232526 0%, #414345 100%);
          color: #fff;
          font-family: 'Segoe UI', Helvetica, Arial, sans-serif;
          display: flex;
          flex-direction: column;
          align-items: center;
          justify-content: center;
          min-height: 100vh;
          margin: 0;
        }
        .container {
          background: rgba(30, 30, 30, 0.95);
          padding: 40px 30px 30px 30px;
          border-radius: 18px;
          box-shadow: 0 8px 32px 0 rgba(135, 31, 31, 0.37);
          text-align: center;
        }
        h1 {
          margin-bottom: 18px;
          font-size: 2.2em;
          letter-spacing: 2px;
        }
        .state {
          font-size: 1.3em;
          margin-bottom: 30px;
        }
        .button {
          background: linear-gradient(90deg, #4CAF50 0%, #43e97b 100%);
          border: none;
          color: white;
          padding: 18px 50px;
          font-size: 1.3em;
          border-radius: 8px;
          cursor: pointer;
          margin: 10px 0;
          box-shadow: 0 4px 14px 0 rgba(76,175,80,0.25);
          transition: background 0.3s, transform 0.2s;
        }
        .button2 {
          background: linear-gradient(90deg, #f44336 0%, #ff6a00 100%);
          box-shadow: 0 4px 14px 0 rgba(244,67,54,0.25);
        }
        .button:hover {
          transform: scale(1.05);
          opacity: 0.92;
        }
        @media (max-width: 600px) {
          .container { padding: 20px 5vw; }
          h1 { font-size: 1.3em; }
          .button { font-size: 1em; padding: 14px 30px; }
        }
      </style>
    </head>
    <body>
      <div class="container">
        <img src="https://i.imgur.com/ZY24p57.png" alt="Logo" style="width:120px;margin:20px 0;">
        <h1>VSSS LED CAMPO</h1>
        <div class="state">Estado do RELE: <b>%STATE%</b></div>
        %BUTTON%
      </div>
    </body>
    </html>
  )rawliteral";

  String button, button2;
  if (releState == "on" && buttonState == "off") {
    button = "<a href=\"/off\"><button class=\"button button2\">DESLIGAR</button></a>";
  } else if(releState == "off" && buttonState == "off") {
    button = "<a href=\"/on\"><button class=\"button\">LIGAR</button></a>";
  }
  else {
    button = "<a href=\"/\"><button class=\"button\">USANDO SWITCH</button></a>";
  }

  if (buttonState == "on") {
    button2 = "<a href=\"/boff\"><button2 class=\"button button2\">SWITCH ON</button></a>";
  } else{
    button2 = "<a href=\"/bon\"><button2 class=\"button\">SWITCH OFF</button></a>";
  }


  html.replace("%STATE%", releState == "on" ? "Ligado" : "Desligado");
  html.replace("%BUTTON%", button + "<br><br>" + button2);

  server.send(200, "text/html", html);
}

void releon(){
  if(buttonState=="off"){
    digitalWrite(pinoRELE, HIGH);
    releState = "on";
    handleRoot();
  }
  else{
    handleRoot();
  }
}


void releoff(){
  if(buttonState=="off"){
    digitalWrite(pinoRELE, LOW);
    releState = "off";
    handleRoot();
  }
  else{
    handleRoot();
  }
}


void bon(){
  buttonState = "on";
  handleRoot();
}

void boff(){
  buttonState = "off";
  handleRoot();
}

void setup(){
  Serial.begin(115200);

  OTASETUP();
  pinMode(pinoRELE, OUTPUT);
  server.on("/", handleRoot);
  server.on("/on", releon);
  server.on("/off", releoff);

  server.on("/bon", bon);
  server.on("/boff", boff);

  server.begin();
}

void loop() {
  // otasetup
  ArduinoOTA.handle();
  // otasetup
  server.handleClient();
}
