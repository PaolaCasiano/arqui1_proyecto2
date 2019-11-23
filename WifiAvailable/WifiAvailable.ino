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
/*
  modo movil 
    D  = desactivado
    A  = activado
    el flujo normal tiene el modo movil desactivado, asi que va una d
    si el modo movil esta desactivado, solo va a buscar si cambia el estado
    si esta activado, busca si hay ecuaciones o letras que graficar
*/


int estado = 0;
String modo_movil = "D";//////////////////////////////////////////////////////////////la cagamos aqui creemos que es a antes Dv... no la cagaron XD

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
      //Serial.println(datos);
      if(datos.charAt(0) == 'v'){
          GET2D(datos.charAt(1)); 
      }else if(datos == "3D"){
        GET3D();
      }else{
        //Serial.print("debe postear");
        //Serial.print(datos);
        //Serial.println("-");
        POSTEAR(datos);
        //Serial.print("ya posteo");
      }
         
    }else{
      /*if(estado == 1){
        estado = 0;
        delay(1);
      }else if(estado == 0){*/
         GETESTADO();  
         //if(modo_movil == "A"){
            GETTEXTO();
            delay(10000);   
         //}
      //}      
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

    
    HTTPClient http;
    String metodo = "guardar_funcion?eq="+cadena;
    //Serial.print('-');
    //Serial.print(url+metodo);
    //Serial.println('-');
    http.begin(url+metodo);
          
    http.addHeader("Content-Type", "text/plain");
    char char_array[cadena.length()+1];
    strcpy(char_array,cadena.c_str());
    int httpCode = http.GET();
    //Serial.println(httpCode);
    payload = http.getString();
    //Serial.println(payload);
    http.end();  //Close connection
    delay(1000);
}


void GET3D(){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    String metodo = "getEcuacionActual3D";
    HTTPClient http; 
    http.begin(url+metodo); 
    int httpCode = http.GET(); 
    if (httpCode > 0) { 
      payload = http.getString();   //Get the request response payload
      if(payload != "E"){
        Serial.println( payload);  //si cambia de estado, envia el caracter A o D para que lo envie a assembler
      }
    }
    http.end(); 

  }
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
      payload = "";
      payload = http.getString();   //Get the request response payload
      if(payload !="E" &&  payload != ""){
        Serial.println( http.getString()+"$"); //devuelve los puntos de la ecuacion
        //yield();
      } 
      else{
        Serial.println('$');
      }
      delay(1); 

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
        Serial.println( "#");  //si cambia de estado, envia el caracter A o D para que lo envie a assembler
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
      payload = "";
      payload = http.getString(); 
      if(payload != ""){
        Serial.println( http.getString()); 
        delay(15000);
      }
    }
    http.end();   

  }
}
