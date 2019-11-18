int espacio = 0;
String comando = "";
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

}

void loop() {
//  if(Serial2.available()){
//    Serial.print("Hay algo\n");
//    char letra = Serial2.read();
//    Serial.print(letra);
//    Serial.print("---------------------------------------------------------------------------------------------");
//    Serial1.print(letra);
//  }
//  else
//  {
//    Serial.print("No hay nada\n");
//    
//    if(espacio==20){
//        Serial1.print(".");
//        Serial1.print("$");
//        Serial1.print("\n"); espacio=0;
//      }
//
//    
//    espacio++;
//  }


  if(Serial.available()){
    char letra = Serial.read();
    //Serial1.print(letra);
    comando+=letra;
  }
  else{
    if(comando != ""){
      Serial1.print(comando);
      comando = "";
    }
  }


  if(Serial1.available()){
    char letra = Serial1.read();
    Serial.print(letra);
  }
    
}
