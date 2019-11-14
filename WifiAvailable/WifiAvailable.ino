#include <ESP8266LLMNR.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include<SoftwareSerial.h> 
#include<Arduino.h>

#define LED_BUILTIN 2
const char* ssid = "CBW383G2N-1E51-G";
const char* password = "a2e7a62cc5f26";

//const char* ssid = "Holi:3";
//const char* password = "amfj46571";

int estado = 0;
String modo_movil = "D";

std::string data_;
std::string data_pantalla;
String payload = "";

String datos;
//String url = "http://arqui1api.herokuapp.com/";
String url = "http://192.168.0.33:8000/";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid,password);   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    //Serial.println("Waiting for connection");
  }
}


void loop() {

 
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    //se suponen que enviaran ecuacion;xi,xs;yi,ys;zi,zs
    if(Serial.available() >0){
      datos = Serial.readString();
      if(datos.charAt(0) == 'v'){
          GET2D(datos.charAt(1)); 
      }else{
        Serial.print("-");
        Serial.print(datos);
        Serial.println("-");
        POSTEAR(datos);
      }
         
    }else{
      if(estado == 1){
        estado = 0;
        delay(1);
      }else if(estado == 0){
         GETESTADO();  
         if(modo_movil == "A"){
            GETTEXTO();
            delay(10000);   
         }
      }      
    }
  }
}

void POSTEAR(String cadena){
    //Serial.println("has entrado a postear");

    cadena.replace("+", "%2B");
    cadena.replace("\n","");
    cadena.replace("\r\n","");
    cadena.replace("\r","");
    cadena.replace(" ","");
    cadena.replace("$","");
    Serial.println(cadena);

    
    HTTPClient http;
    String metodo = "guardar_funcion?eq="+cadena;
    Serial.print('-');
    Serial.print(url+metodo);
    Serial.println('-');
    http.begin(url+metodo);
          
    http.addHeader("Content-Type", "text/plain");
    char char_array[cadena.length()+1];
    strcpy(char_array,cadena.c_str());
    int httpCode = http.GET();
    Serial.println(httpCode);
    payload = http.getString();
    Serial.println(payload);
    http.end();  //Close connection
    delay(1000);
}


void GET2D(char numero){
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    String ejes = "";
    switch(numero){
      case '1':
        ejes = "x-y";
        break;
      case '2':
        ejes = "x-z" ;
        break;
      case '3':
        ejes = "y-z";
        break;
    }
    String metodo = "getUltimaEcuacion2D?ejes="+ejes;
    http.begin(url+metodo); 
    int httpCode = http.GET();
    if (httpCode > 0) { 
      payload = http.getString();   //Get the request response payload
      if(payload !="E" &&  payload != ""){
        Serial.println( http.getString()+"$"); //devuelve los puntos de la ecuacion
      }  

    }
    http.end();   //Close connection
  }
}


void GETESTADO(){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    String metodo = "get_estado";
    HTTPClient http; 
    http.begin(url+metodo); 
    int httpCode = http.GET(); 
    if (httpCode > 0) { 
      payload = http.getString();   //Get the request response payload
      if(payload != modo_movil){
        modo_movil = payload;
        Serial.println( payload+"$");  //si cambia de estado, envia el caracter A o D para que lo envie a assembler
      }
    }
    http.end(); 

  }
}

void GETTEXTO(){
  if (WiFi.status() == WL_CONNECTED) { 
    String metodo = "getUltimoTexto";
    
    HTTPClient http;  
    http.begin(url+metodo);
    int httpCode = http.GET();
    if (httpCode > 0) {
      payload = http.getString(); 
      if(payload != ""){
        Serial.println( http.getString()+"$"); 
      }
    }
    http.end();   

  }
}
