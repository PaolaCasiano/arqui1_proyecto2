String comando = "";
String comando2 = "";
bool verbose = true;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  if(Serial.available()){
    char letra = Serial.read();
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
    if(verbose){
      switch(letra){
        case 'C':
          //llamar cono
          break;
        case 'S':
          //llamar esfera
          break;
        case 'P':
          //llamar plano
          break;
        case 'B':
          //llamar paraboloide
          break;
        case 'H':
          //llamar hiperboloide1
          break;
        case 'L':
          //llamar hiperboloide1
          break;
        case '[':
          verbose = false;
          //activar para enviar palabras
          break;
        case '#':
        default:
          Serial.print(letra);
          break;
      }
    }
    else{
      comando2+=letra;
    }
  }
  else{
    if(comando2 != ""){
      //llamar a imprimir cadena
      comando = "";
      verbose = true;
    }
  }
}
