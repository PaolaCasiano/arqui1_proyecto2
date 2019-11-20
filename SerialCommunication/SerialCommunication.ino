String comando = "";
String comando2 = "";
bool verbose = true;
int tierra[8] = {23,25,27,29,31,33,35,37}; //NEGROS
int dato[8] = {39,41,43,45,47,49,51,53}; //AZULES
unsigned long time;
int checkpoint=0;
int clock[8] = {38,40,42,44,46,48,50,52}; //ROJOS
#define in 36
char letra1[8][8];
char letra2[8][8];
char letra3[8][8];
char letra4[8][8];

char cubo_letra[8][512];
char cubo_letra_corrida[512];

char areglo_piramide[512];
char areglo_cilindro[512];
char areglo_corazon[512];
char areglo_prueba[512];
char areglo_circulo[512];
char areglo_planor[512];
char areglo_planoi[512];
char areglo_elipsoide[512];
char areglo_paraboloide[512];
char areglo_hiperboloide1[512];
char areglo_hiperboloide2[512];
char areglo_cono[512];

unsigned long currentMillis;
unsigned long startMillis;
#define velocidad_letras 100
#define velocidad_formas 5000

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(in, OUTPUT);
  for(int i = 0; i< 8; i++)
    {
        pinMode(dato[i],OUTPUT);
        digitalWrite(dato[i],LOW);
        
        pinMode(tierra[i],OUTPUT);
        digitalWrite(tierra[i],LOW);

        pinMode(clock[i],OUTPUT);
        digitalWrite(clock[i],HIGH);
        digitalWrite(clock[i],LOW);
    }
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
    String  texto = Serial1.readString();
    //char letra = Serial1.read();
    char letra = texto.charAt(0);
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
        case '~':
          //verbose = false;
          texto_3d(texto, 3);
          break;
        case '#':
          //ENVIAR A ASSEMBLER EL CAMBIAR DE MODO
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
void cubo(){
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 1; i < 7; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 1; j < 7; j++)//FILAS
        {  
            for(int k = 1; k < 7; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],HIGH);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
    }
    //APAGAMOS LA ULTIMAS CAPA
    digitalWrite(tierra[6],LOW);
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
    digitalWrite(tierra[6],LOW);
    digitalWrite(tierra[7],LOW);
}
void piramide(){
  cubo_piramide();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_piramide[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
    }
    //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
}
void corazon(){
  cubo_corazon();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_corazon[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
    }
    //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
}
void cilindro(){
  cubo_cilindro();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_cilindro[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
    }
    //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
}
//METODO QUE MUESTRA LOS CUBOS
void texto_3d(String t, int sentido){
  String txt=t;
  char ch1;
  char ch2;
    
    switch (sentido)
    {
        case 1:
                  for(int p = 0; p < txt.length(); p++)
                  {
                    ch1 = txt[p];
                    armar_letra(ch1);
                    startMillis = millis();
                    for(int l = 7; l >= 0; l--)
                    {
                    int point=0;
                    for(int i = 0; i < 8; i++)//CAPAS
                    {
                        //ACTIVAMOS ALTA IMPEDANCIA
                        digitalWrite(in,HIGH);
                        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
                        digitalWrite(tierra[i-1],LOW);
                    
                        for(int j = 0; j < 8; j++)//FILAS
                        {  
                            for(int k = 0; k < 8; k++)//DATOS
                            {
                                //CARGAMOS EL DATO EN LA LINEA K
                                digitalWrite(dato[k],cubo_letra[l][point]);
                                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                                point++;
                            }
                            //PULSO PARA CADA FLIP-FLOP
                            digitalWrite(clock[j],HIGH);
                            digitalWrite(clock[j],LOW);
                        }

                        //QUITAMOS ALTA IMPEDANCIA
                        digitalWrite(in,LOW);
                        //ACTIVAMOS LA TIERRA DE LA CAPA
                        digitalWrite(tierra[i],HIGH);
                        //delayMicroseconds(1600);
                        delay(1);
                    }
                    //APAGAMOS LA ULTIMA CAPA
                    digitalWrite(tierra[7],LOW);
                    if (millis() - startMillis >= velocidad_letras)  //test whether the period has elapsed
                    {
                        l--;
                        startMillis = millis();
                    }
                    l++;
                    }
                  }
            
            break;
        case 2:
                  for(int p = 0; p < txt.length(); p++)
                  {
                    ch1 = txt[p];
                    armar_letra(ch1);
                    startMillis = millis();
                    for(int l = 0; l < 8; l++)
                    {
                    int point=0;
                    for(int i = 0; i < 8; i++)//CAPAS
                    {
                        //ACTIVAMOS ALTA IMPEDANCIA
                        digitalWrite(in,HIGH);
                        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
                        digitalWrite(tierra[i-1],LOW);
                    
                        for(int j = 0; j < 8; j++)//FILAS
                        {  
                            for(int k = 0; k < 8; k++)//DATOS
                            {
                                //CARGAMOS EL DATO EN LA LINEA K
                                digitalWrite(dato[k],cubo_letra[l][point]);
                                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                                point++;
                            }
                            //PULSO PARA CADA FLIP-FLOP
                            digitalWrite(clock[j],HIGH);
                            digitalWrite(clock[j],LOW);
                        }

                        //QUITAMOS ALTA IMPEDANCIA
                        digitalWrite(in,LOW);
                        //ACTIVAMOS LA TIERRA DE LA CAPA
                        digitalWrite(tierra[i],HIGH);
                        //delayMicroseconds(1600);
                        delay(1);
                    }
                    //APAGAMOS LA ULTIMA CAPA
                    digitalWrite(tierra[7],LOW);
                    if (millis() - startMillis >= velocidad_letras)  //test whether the period has elapsed
                    {
                        l++;
                        startMillis = millis();
                    }
                    l--;
                    }
                  }
            break;
        case 3:        
                  txt =" "+t+" ";
                  for(int p = 0; p < txt.length(); p++)
                  {    
                  ch1 = txt[p];
                  ch2 = txt[p+1];    
                  armar_cubo_corrido(ch1,ch2,0);
                  startMillis = millis();
                    for(int l = 1; l <= 8; l++)
                    {
                      int point=0;
                      for(int i = 0; i < 8; i++)//CAPAS
                      {
                          //ACTIVAMOS ALTA IMPEDANCIA
                          digitalWrite(in,HIGH);
                          //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
                          digitalWrite(tierra[i-1],LOW);
                      
                          for(int j = 0; j < 8; j++)//FILAS
                          {  
                              for(int k = 0; k < 8; k++)//DATOS
                              {
                                  //CARGAMOS EL DATO EN LA LINEA K
                                  digitalWrite(dato[k],cubo_letra_corrida[point]);
                                  //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                                  point++;
                              }
                              //PULSO PARA CADA FLIP-FLOP
                              digitalWrite(clock[j],HIGH);
                              digitalWrite(clock[j],LOW);
                          }
                          //QUITAMOS ALTA IMPEDANCIA
                          digitalWrite(in,LOW);
                          //ACTIVAMOS LA TIERRA DE LA CAPA
                          digitalWrite(tierra[i],HIGH);
                          //delayMicroseconds(1600);
                          delay(1);
                      }
                      //APAGAMOS LA ULTIMA CAPA
                      digitalWrite(tierra[7],LOW);
                      if (millis() - startMillis >= velocidad_letras)  //test whether the period has elapsed
                      {
                        armar_cubo_corrido(ch1,ch2,l);
                        l++;
                        startMillis = millis();
                      }
                      l--;
                    }
                  }
            break;
    }
        
}
//CORRIMIENTO PARA SENTIDO 3(DERECHA A IZQUIERDA)DE 0-8 0=C1 8=C2
void armar_cubo_corrido(char cu,char cd,int corr){ 
    for(int i = 0; i < 512; i++)
    {
        cubo_letra_corrida[i]=0;
    }
    int point=0;
    char matrix1[8][8];
    matriz_letra(cu);
    for(int j = 0; j < 8; j++)
      {
          for(int k = 0; k < 8; k++)
          {
              matrix1[k][j]=letra1[k][j];
          }
      }
    char matrix2[8][8];
    matriz_letra(cd);
    for(int j = 0; j < 8; j++)
      {
          for(int k = 0; k < 8; k++)
          {
              matrix2[k][j]=letra1[k][j];
          }
      }
      for(int j = 0; j < 8; j++)
      {
          for(int k = 0; k < 8; k++)
          {

              if (k<(8-corr)) 
              {
                cubo_letra_corrida[point]=matrix1[k+corr][j];
                cubo_letra_corrida[point+8]=matrix1[k+corr][j];  
              }
              else 
              {
                  cubo_letra_corrida[point]=matrix2[corr-(8-k)][j];
                  cubo_letra_corrida[point+8]=matrix2[corr-(8-k)][j];
              }
              point++;
          }
      point=point+56;
      }             
}
//METODO QUE ARMA LOS CURBOS
void armar_letra(char c){

    matriz_letra(c);
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 512; j++)
        {
        cubo_letra[i][j]=0;
        }
    }
    
    int point=0;

    for(int j = 0; j < 8; j++)
    {
        for(int k = 0; k < 8; k++)
        {           
            cubo_letra[0][point]=   letra1[k][j];
            cubo_letra[1][point+8]= letra1[k][j];

            cubo_letra[2][point+16]=letra2[k][j];
            cubo_letra[3][point+24]=letra2[k][j];

            cubo_letra[4][point+32]=letra3[k][j];
            cubo_letra[5][point+40]=letra3[k][j];

            cubo_letra[6][point+48]=letra4[k][j];
            cubo_letra[7][point+56]=letra4[k][j];
            point++;
        }
        point=point+56;
    }

    

}



















//  metodo que imprime en un arreglo el cilindro
  void cubo_piramide(){
    //limpio
    for(int x=0; x<=511;x++){ areglo_piramide[x]=0; }
    //pinto
    for(int x=0; x<=127;x++)  { areglo_piramide[x]=1; }
    
    for(int x=137; x<=142;x++)  { areglo_piramide[x]=1; }
    for(int x=145; x<=150;x++)  { areglo_piramide[x]=1; }
    for(int x=153; x<=158;x++)  { areglo_piramide[x]=1; }
    for(int x=161; x<=166;x++)  { areglo_piramide[x]=1; }
    for(int x=169; x<=174;x++)  { areglo_piramide[x]=1; }
    for(int x=177; x<=182;x++)  { areglo_piramide[x]=1; }
    
    for(int x=241; x<=246;x++)  { areglo_piramide[x]=1; }
    for(int x=233; x<=238;x++)  { areglo_piramide[x]=1; }
    for(int x=225; x<=230;x++)  { areglo_piramide[x]=1; }
    for(int x=217; x<=222;x++)  { areglo_piramide[x]=1; }
    for(int x=209; x<=214;x++)  { areglo_piramide[x]=1; }
    for(int x=201; x<=206;x++)  { areglo_piramide[x]=1; }
    
    for(int x=298; x<=301;x++)  { areglo_piramide[x]=1; }
    for(int x=290; x<=293;x++)  { areglo_piramide[x]=1; }
    for(int x=282; x<=285;x++)  { areglo_piramide[x]=1; }
    for(int x=274; x<=277;x++)  { areglo_piramide[x]=1; }
    
    for(int x=362; x<=365;x++)  { areglo_piramide[x]=1; }
    for(int x=354; x<=357;x++)  { areglo_piramide[x]=1; }
    for(int x=346; x<=349;x++)  { areglo_piramide[x]=1; }
    for(int x=338; x<=341;x++)  { areglo_piramide[x]=1; }
    
    for(int x=419; x<=420;x++)  { areglo_piramide[x]=1; }
    for(int x=411; x<=412;x++)  { areglo_piramide[x]=1; }
    
    for(int x=483; x<=484;x++)  { areglo_piramide[x]=1; }
    for(int x=475; x<=476;x++)  { areglo_piramide[x]=1; }
  }

  void cubo_cilindro(){
    //limpio
    for(int x=0; x<=511;x++){ areglo_cilindro[x]=0; }
    //pinto
    for(int x=50; x<=53;x++){ areglo_cilindro[x]=1; }
    for(int x=41; x<=46;x++){ areglo_cilindro[x]=1; }
    for(int x=33; x<=38;x++){ areglo_cilindro[x]=1; }
    for(int x=25; x<=30;x++){ areglo_cilindro[x]=1; }
    for(int x=17; x<=22;x++){ areglo_cilindro[x]=1; }
    for(int x=10; x<=13;x++){ areglo_cilindro[x]=1; }
    //2
    for(int x=114; x<=117;x++){ areglo_cilindro[x]=1; }
    for(int x=105; x<=110;x++){ areglo_cilindro[x]=1; }
    for(int x=97; x<=102;x++){ areglo_cilindro[x]=1; }
    for(int x=89; x<=94;x++){ areglo_cilindro[x]=1; }
    for(int x=81; x<=86;x++){ areglo_cilindro[x]=1; }
    for(int x=74; x<=77;x++){ areglo_cilindro[x]=1; }
    //3
    for(int x=178; x<=181;x++){ areglo_cilindro[x]=1; }
    for(int x=169; x<=174;x++){ areglo_cilindro[x]=1; }
    for(int x=161; x<=166;x++){ areglo_cilindro[x]=1; }
    for(int x=153; x<=158;x++){ areglo_cilindro[x]=1; }
    for(int x=145; x<=150;x++){ areglo_cilindro[x]=1; }
    for(int x=138; x<=141;x++){ areglo_cilindro[x]=1; }
    //4
    for(int x=242; x<=245;x++){ areglo_cilindro[x]=1; }
    for(int x=233; x<=238;x++){ areglo_cilindro[x]=1; }
    for(int x=225; x<=230;x++){ areglo_cilindro[x]=1; }
    for(int x=217; x<=222;x++){ areglo_cilindro[x]=1; }
    for(int x=209; x<=214;x++){ areglo_cilindro[x]=1; }
    for(int x=202; x<=205;x++){ areglo_cilindro[x]=1; }
    //5
    for(int x=306; x<=309;x++){ areglo_cilindro[x]=1; }
    for(int x=297; x<=302;x++){ areglo_cilindro[x]=1; }
    for(int x=289; x<=294;x++){ areglo_cilindro[x]=1; }
    for(int x=281; x<=286;x++){ areglo_cilindro[x]=1; }
    for(int x=273; x<=278;x++){ areglo_cilindro[x]=1; }
    for(int x=266; x<=269;x++){ areglo_cilindro[x]=1; }
    //6
    for(int x=370; x<=373;x++){ areglo_cilindro[x]=1; }
    for(int x=361; x<=366;x++){ areglo_cilindro[x]=1; }
    for(int x=353; x<=358;x++){ areglo_cilindro[x]=1; }
    for(int x=345; x<=350;x++){ areglo_cilindro[x]=1; }
    for(int x=337; x<=342;x++){ areglo_cilindro[x]=1; }
    for(int x=330; x<=333;x++){ areglo_cilindro[x]=1; }
    //7
    for(int x=434; x<=437;x++){ areglo_cilindro[x]=1; }
    for(int x=425; x<=430;x++){ areglo_cilindro[x]=1; }
    for(int x=417; x<=422;x++){ areglo_cilindro[x]=1; }
    for(int x=409; x<=414;x++){ areglo_cilindro[x]=1; }
    for(int x=401; x<=406;x++){ areglo_cilindro[x]=1; }
    for(int x=394; x<=397;x++){ areglo_cilindro[x]=1; }
    //8
    for(int x=498; x<=501;x++){ areglo_cilindro[x]=1; }
    for(int x=489; x<=494;x++){ areglo_cilindro[x]=1; }
    for(int x=481; x<=486;x++){ areglo_cilindro[x]=1; }
    for(int x=473; x<=478;x++){ areglo_cilindro[x]=1; }
    for(int x=465; x<=470;x++){ areglo_cilindro[x]=1; }
    for(int x=458; x<=461;x++){ areglo_cilindro[x]=1; }
    
  }

  void cubo_corazon(){
    //limpio
    for(int x=0; x<=511;x++){ areglo_corazon[x]=0; }
    //pinto
    for(int x=35; x<=36;x++){ areglo_corazon[x]=1; }
    for(int x=27; x<=28;x++){ areglo_corazon[x]=1; }
    //2
    for(int x=107; x<=108;x++){ areglo_corazon[x]=1; }
    for(int x=98; x<=101;x++){ areglo_corazon[x]=1; }
    for(int x=90; x<=93;x++){ areglo_corazon[x]=1; }
    for(int x=83; x<=84;x++){ areglo_corazon[x]=1; }
    //3
    for(int x=179; x<=180;x++){ areglo_corazon[x]=1; }
    for(int x=170; x<=173;x++){ areglo_corazon[x]=1; }
    for(int x=161; x<=166;x++){ areglo_corazon[x]=1; }
    for(int x=153; x<=158;x++){ areglo_corazon[x]=1; }
    for(int x=146; x<=149;x++){ areglo_corazon[x]=1; }
    for(int x=139; x<=140;x++){ areglo_corazon[x]=1; }
    //4
    for(int x=242; x<=245;x++){ areglo_corazon[x]=1; }
    for(int x=233; x<=238;x++){ areglo_corazon[x]=1; }
    for(int x=224; x<=231;x++){ areglo_corazon[x]=1; }
    for(int x=216; x<=223;x++){ areglo_corazon[x]=1; }
    for(int x=209; x<=214;x++){ areglo_corazon[x]=1; }
    for(int x=202; x<=205;x++){ areglo_corazon[x]=1; }
    //5
    for(int x=306; x<=309;x++){ areglo_corazon[x]=1; }
    for(int x=297; x<=302;x++){ areglo_corazon[x]=1; }
    for(int x=288; x<=295;x++){ areglo_corazon[x]=1; }
    for(int x=280; x<=287;x++){ areglo_corazon[x]=1; }
    for(int x=273; x<=278;x++){ areglo_corazon[x]=1; }
    for(int x=266; x<=269;x++){ areglo_corazon[x]=1; }
    //6
    for(int x=361; x<=366;x++){ areglo_corazon[x]=1; }
    for(int x=352; x<=359;x++){ areglo_corazon[x]=1; }
    for(int x=344; x<=351;x++){ areglo_corazon[x]=1; }
    for(int x=337; x<=342;x++){ areglo_corazon[x]=1; }
    areglo_corazon[330]=1;
    areglo_corazon[333]=1;
    areglo_corazon[370]=1;
    areglo_corazon[373]=1;
    //7    
    for(int x=417; x<=422;x++){ areglo_corazon[x]=1; }
    for(int x=409; x<=414;x++){ areglo_corazon[x]=1; }
    areglo_corazon[402]=1;
    areglo_corazon[405]=1;
    areglo_corazon[426]=1;
    areglo_corazon[429]=1;
    //8
    areglo_corazon[474]=1;
    areglo_corazon[477]=1;
    areglo_corazon[482]=1;
    areglo_corazon[485]=1;        
  }
void matriz_letra(char letra){
    switch(letra){
    case ' ':
        blanco();
    break;
      case 'a':
        letra_A1();
        letra_A2();
        letra_A3();
        letra_A4();
        break;
      case 'b':
        letra_B1();
        letra_B2();
        letra_B3();
        letra_B4();
        break;
      case 'c':
        letra_C1();
        letra_C2();
        letra_C3();
        letra_C4();
        break;
      case 'd':
        letra_D1();
        letra_D2();
        letra_D3();
        letra_D4();
        break;
      case 'e':
        letra_E1();
        letra_E2();
        letra_E3();
        letra_E4();
        break;
      case 'f':
        letra_F1();
        letra_F2();
        letra_F3();
        letra_F4();
        break;
      case 'g':
        letra_G1();
        letra_G2();
        letra_G3();
        letra_G4();
        break;
      case 'h':
        letra_H1();
        letra_H2();
        letra_H3();
        letra_H4();
        break;
      case 'i':
        letra_I1();
        letra_I2();
        letra_I3();
        letra_I4();
        break;
      case 'j':
        letra_J1();
        letra_J2();
        letra_J3();
        letra_J4();
        break;
      case 'k':
        letra_K1();
        letra_K2();
        letra_K3();
        letra_K4();
        break;
      case 'l':
        letra_L1();
        letra_L2();
        letra_L3();
        letra_L4();
        break;
      case 'm':
        letra_M1();
        letra_M2();
        letra_M3();
        letra_M4();
        break;
      case 'n':
        letra_N1();
        letra_N2();
        letra_N3();
        letra_N4();
        break;
      case 'ñ':
        egne();
        break;
      case 'o':
        letra_O1();
        letra_O2();
        letra_O3();
        letra_O4();
        break;
      case 'p':
        letra_P1();
        letra_P2();
        letra_P3();
        letra_P4();
        break;
      case 'q':
        letra_Q1();
        letra_Q2();
        letra_Q3();
        letra_Q4();
        break;
      case 'r':
        letra_R1();
        letra_R2();
        letra_R3();
        letra_R4();
        break;
      case 's':
        letra_S1();
        letra_S2();
        letra_S3();
        letra_S4();
        break;
      case 't':
        letra_T1();
        letra_T2();
        letra_T3();
        letra_T4();
        break;
      case 'u':
        letra_U1();
        letra_U2();
        letra_U3();
        letra_U4();
        break;
      case 'v':
        letra_V1();
        letra_V2();
        letra_V3();
        letra_V4();
        break;
      case 'w':
        letra_W1();
        letra_W2();
        letra_W3();
        letra_W4();
        break;
      case 'x':
        letra_X1();
        letra_X2();
        letra_X3();
        letra_X4();
        break;
      case 'y':
        letra_Y1();
        letra_Y2();
        letra_Y3();
        letra_Y4();
        break;
      case 'z':
        letra_Z1();
        letra_Z2();
        letra_Z3();
        letra_Z4();
        break;
      case '1':
        numero_11();
        numero_12();
        numero_13();
        numero_14();
        break;
      case '2':
        numero_21();
        numero_22();
        numero_23();
        numero_24();
        break;
      case '3':
        numero_31();
        numero_32();
        numero_33();
        numero_34();
        break;
      case '4':
        numero_41();
        numero_42();
        numero_43();
        numero_44();
        break;
      case '5':
        numero_51();
        numero_52();
        numero_53();
        numero_54();
        break;
      case '6':
        numero_61();
        numero_62();
        numero_63();
        numero_64();
        break;
      case '7':
        numero_71();
        numero_72();
        numero_73();
        numero_74();
        break;
      case '8':
        numero_81();
        numero_82();
        numero_83();
        numero_84();
        break;
      case '9':
        numero_91();
        numero_92();
        numero_93();
        numero_94();
        break;
      case '0':
        numero_01();
        numero_02();
        numero_03();
        numero_04();
        break;
      case '@':
        arroba();
        limpiar_letra2();
        limpiar_letra3();
        limpiar_letra4();
        break;
      case '$':
        dolar();
        limpiar_letra2();
        limpiar_letra3();
        limpiar_letra4();
        break;
      case '#':
        numeral();
        limpiar_letra2();
        limpiar_letra3();
        limpiar_letra4();
        break;
      case '_':
        guionbajo();
        break;
      case '&':
        ampersand();
        break;
      case '-':
        guion();
        break;
      case '+':
        suma();
        break;
      case '(':
        parabre();
        break;
      case ')':
        parcierra();
        break;
      case '/':
        barra();
        break;
      case '*':
        asterisco();
        break;
      case '\"':
        barra();
        break;
      case '\'':
        comilla();
        break;
      case ':':
        dospuntos();
        break;
      case ';' :
        puntocoma();
        break;
      case '!':
        exclamacion();
        break;
      case '?':
        interrogacion();
        break;
      case '.':
        punto();
        break;
      case ',':
        coma();
        break;
      case '~':
        egne();
        break;
      default:
        //egne();
        break;
    }
  }
// espacio en blanco
  void blanco(){
    limpiar_letra1();
    limpiar_letra2();
    limpiar_letra3();
    limpiar_letra4();
  }

// letra A
  void letra_A1(){
    limpiar_letra1();
    
    //fila_7
    letra1[2][7]=1; letra1[3][7]=1; letra1[4][7]=1; letra1[5][7]=1;
    //fila_6
    letra1[1][6]=1; letra1[6][6]=1;
    //fila_5
    letra1[1][5]=1; letra1[6][5]=1;
    //fila_4
    letra1[1][4]=1; letra1[6][4]=1;
    //fila_3
    letra1[1][3]=1; letra1[2][3]=1; letra1[3][3]=1; letra1[4][3]=1; letra1[5][3]=1;letra1[6][3]=1;
    //fila_2
    letra1[1][2]=1; letra1[6][2]=1;
    //fila_1
    letra1[1][1]=1; letra1[6][1]=1;
    //fila_0
    letra1[1][0]=1; letra1[6][0]=1;
  }

  void letra_A2(){
    limpiar_letra2();
    
    //fila_7
    //fila_6
    letra2[3][6]=1; letra2[4][6]=1;
    //fila_5
    letra2[2][5]=1; letra2[5][5]=1;
    //fila_4
    letra2[2][4]=1; letra2[5][4]=1;
    //fila_3
    letra2[2][3]=1; letra2[3][3]=1; letra2[4][3]=1; letra2[5][3]=1;
    //fila_2
    letra2[2][2]=1; letra2[5][2]=1;
    //fila_1
    letra2[2][1]=1; letra2[5][1]=1;
    //fila_0
  }

  void letra_A3(){
    limpiar_letra3();
    
    //fila_7
    //fila_6
    //fila_5
    letra3[3][5]=1; letra3[4][5]=1;
    //fila_4
    letra3[2][4]=1; letra3[5][4]=1;
    //fila_3
    letra3[2][3]=1; letra3[3][3]=1; letra3[4][3]=1; letra3[5][3]=1;
    //fila_2
    letra3[2][2]=1; letra3[5][2]=1;
    //fila_1
    letra3[2][1]=1; letra3[5][1]=1;
    //fila_0
  }

  void letra_A4(){
    limpiar_letra4();
    
    //fila_7
    //fila_6
    //fila_5
    letra4[3][5]=1; letra4[4][5]=1;
    //fila_4
    letra4[2][4]=1; letra4[5][4]=1;
    //fila_3
    letra4[2][3]=1; letra4[3][3]=1; letra4[4][3]=1; letra4[5][3]=1;
    //fila_2
    letra4[2][2]=1; letra4[5][2]=1;
    //fila_1
    //fila_0
  }

// letra B
  void letra_B1(){
    limpiar_letra1();
    
    //fila_7
    letra1[1][7]=1; letra1[2][7]=1; letra1[3][7]=1; letra1[4][7]=1; letra1[5][7]=1;
    //fila_6
    letra1[1][6]=1; letra1[6][6]=1;
    //fila_5
    letra1[1][5]=1; letra1[6][5]=1;
    //fila_4
    letra1[1][4]=1; letra1[2][4]=1; letra1[3][4]=1; letra1[4][4]=1; letra1[5][4]=1;
    //fila_3
    letra1[1][3]=1; letra1[2][3]=1; letra1[3][3]=1; letra1[4][3]=1; letra1[5][3]=1;
    //fila_2
    letra1[1][2]=1; letra1[6][2]=1;
    //fila_1
    letra1[1][1]=1; letra1[6][1]=1;
    //fila_0
    letra1[1][0]=1; letra1[2][0]=1; letra1[3][0]=1; letra1[4][0]=1; letra1[5][0]=1;
  }

  void letra_B2(){
    limpiar_letra2();
    
    //fila_7
    //fila_6
    letra2[1][6]=1; letra2[2][6]=1; letra2[3][6]=1; letra2[4][6]=1;
    //fila_5
    letra2[1][5]=1; letra2[5][5]=1;
    //fila_4
    letra2[1][4]=1; letra2[2][4]=1; letra2[3][4]=1; letra2[4][4]=1;
    //fila_3
    letra2[1][3]=1; letra2[2][3]=1; letra2[3][3]=1; letra2[4][3]=1;
    //fila_2
    letra2[1][2]=1; letra2[5][2]=1;
    //fila_1
    letra2[1][1]=1; letra2[2][1]=1; letra2[3][1]=1; letra2[4][1]=1;
    //fila_0
  }

  void letra_B3(){
    limpiar_letra3();
    
    //fila_7
    //fila_6
    letra3[2][6]=1; letra3[3][6]=1; letra3[4][6]=1;
    //fila_5
    letra3[2][5]=1; letra3[5][5]=1;
    //fila_4
    letra3[2][4]=1; letra3[3][4]=1; letra3[4][4]=1;
    //fila_3
    letra3[2][3]=1; letra3[3][3]=1; letra3[4][3]=1;
    //fila_2
    letra3[2][2]=1; letra3[5][2]=1;
    //fila_1
    letra3[2][1]=1; letra3[3][1]=1; letra3[4][1]=1;
    //fila_0
  }

  void letra_B4(){
    limpiar_letra4();
    
    //fila_7
    //fila_6
    letra4[2][6]=1; letra4[3][6]=1;
    //fila_5
    letra4[2][5]=1; letra4[4][5]=1;
    //fila_4
    letra4[2][4]=1; letra4[3][4]=1;
    //fila_3
    letra4[2][3]=1; letra4[4][3]=1;
    //fila_2
    letra4[2][2]=1; letra4[3][2]=1;
    //fila_1
    //fila_0
  }

// letra C
  void letra_C1(){
    limpiar_letra1();    
    //fila_7
    letra1[2][7]=1; letra1[3][7]=1; letra1[4][7]=1; letra1[5][7]=1; letra1[6][7]=1;
    //fila_6
    letra1[1][6]=1;
    //fila_5
    letra1[1][5]=1;
    //fila_4
    letra1[1][4]=1; 
    //fila_3
    letra1[1][3]=1;
    //fila_2
    letra1[1][2]=1; 
    //fila_1
    letra1[1][1]=1;
    //fila_0
    letra1[2][0]=1; letra1[3][0]=1; letra1[4][0]=1; letra1[5][0]=1; letra1[6][0]=1;
  }

  void letra_C2(){
    limpiar_letra2();    
    //fila_7
    //fila_6
    letra2[2][6]=1; letra2[3][6]=1; letra2[4][6]=1; letra2[5][6]=1;
    //fila_5
    letra2[1][5]=1;
    //fila_4
    letra2[1][4]=1; 
    //fila_3
    letra2[1][3]=1;
    //fila_2
    letra2[1][2]=1; 
    //fila_1
    letra2[2][1]=1; letra2[3][1]=1; letra2[4][1]=1; letra2[5][1]=1;
    //fila_0
  }

  void letra_C3(){
    limpiar_letra3();    
    //fila_7
    //fila_6
    //fila_5
    letra3[3][5]=1; letra3[4][5]=1; letra3[5][5]=1;
    //fila_4
    letra3[2][4]=1; 
    //fila_3
    letra3[2][3]=1;
    //fila_2
    letra3[2][2]=1; 
    //fila_1
    letra3[3][1]=1; letra3[4][1]=1; letra3[5][1]=1;
    //fila_0
  }

  void letra_C4(){
    limpiar_letra4();    
    //fila_7
    //fila_6
    //fila_5
    letra4[3][5]=1; letra4[4][5]=1;
    //fila_4
    letra4[2][4]=1;
    //fila_3
    letra4[2][3]=1;
    //fila_2
    letra4[3][2]=1; letra4[4][2]=1; 
    //fila_1
    //fila_0
  }

// letra D
  void letra_D1(){
    limpiar_letra1();
    
    //fila_7
    letra1[1][7]=1; letra1[2][7]=1; letra1[3][7]=1; letra1[4][7]=1; letra1[5][7]=1;
    //fila_6
    letra1[1][6]=1; letra1[6][6]=1;
    //fila_5
    letra1[1][5]=1; letra1[6][5]=1;
    //fila_4
    letra1[1][4]=1; letra1[6][4]=1;
    //fila_3
    letra1[1][3]=1; letra1[6][3]=1;
    //fila_2
    letra1[1][2]=1; letra1[6][2]=1;
    //fila_1
    letra1[1][1]=1; letra1[6][1]=1;
    //fila_0
    letra1[1][0]=1; letra1[2][0]=1; letra1[3][0]=1; letra1[4][0]=1; letra1[5][0]=1;
  }

  void letra_D2(){
    limpiar_letra2();
    
    //fila_7
    //fila_6
    letra2[1][6]=1; letra2[2][6]=1; letra2[3][6]=1; letra2[4][6]=1;
    //fila_5
    letra2[1][5]=1; letra2[5][5]=1;
    //fila_4
    letra2[1][4]=1; letra2[5][4]=1;
    //fila_3
    letra2[1][3]=1; letra2[5][3]=1;
    //fila_2
    letra2[1][2]=1; letra2[5][2]=1;
    //fila_1
    letra2[1][1]=1; letra2[2][1]=1; letra2[3][1]=1; letra2[4][1]=1;
    //fila_0
  }

  void letra_D3(){
    limpiar_letra3();
    
    //fila_7
    //fila_6
    //fila_5
    letra3[2][5]=1; letra3[3][5]=1; letra3[4][5]=1;
    //fila_4
    letra3[2][4]=1; letra3[5][4]=1;
    //fila_3
    letra3[2][3]=1; letra3[5][3]=1;
    //fila_2
    letra3[2][2]=1; letra3[5][2]=1;
    //fila_1
    letra3[2][1]=1; letra3[3][1]=1; letra3[4][1]=1;
    //fila_0
  }

  void letra_D4(){
    limpiar_letra4();
    
    //fila_7
    //fila_6
    //fila_5
    //fila_4
    letra4[2][4]=1; letra4[3][4]=1;
    //fila_3
    letra4[2][3]=1; letra4[4][3]=1;
    //fila_2
    letra4[2][2]=1; letra4[3][2]=1;
    //fila_1
    //fila_0
  }

// letra E
  void letra_E1(){
    limpiar_letra1();
    
    //fila_7
    for(int x=0; x<8; x++){ letra1[x][7]=1; }
    //fila_6
    letra1[0][6]=1;
    //fila_5
    letra1[0][5]=1;
    //fila_4
    for(int x=0; x<8; x++){ letra1[x][4]=1; }
    //fila_3
    letra1[0][3]=1;
    //fila_2
    letra1[0][2]=1;
    //fila_1
    letra1[0][1]=1;
    //fila_0
    for(int x=0; x<8; x++){ letra1[x][0]=1; }
  }

  void letra_E2(){
    limpiar_letra2();
    
    //fila_7
    //fila_6
    for(int x=1; x<=6; x++){ letra2[x][6]=1; }
    //fila_5
    letra2[1][5]=1;
    //fila_4
    for(int x=1; x<=6; x++){ letra2[x][4]=1; }
    //fila_3
    letra2[1][3]=1;
    //fila_2
    letra2[1][2]=1;
    //fila_1
    for(int x=1; x<=6; x++){ letra2[x][1]=1; }
    //fila_0
  }

  void letra_E3(){
    limpiar_letra3();
    
    //fila_7
    //fila_6
    //fila_5
    for(int x=2; x<=5; x++){ letra3[x][5]=1; }
    //fila_4
    letra3[2][4]=1;
    //fila_3
    for(int x=2; x<=5; x++){ letra3[x][3]=1; }
    //fila_2
    letra3[2][2]=1;
    //fila_1
    for(int x=2; x<=5; x++){ letra3[x][1]=1; }
    //fila_0
  }

  void letra_E4(){
    limpiar_letra4();
    
    //fila_7
    //fila_6
    //fila_5
    letra4[3][5]=1; letra4[4][5]=1;
    //fila_4
    letra4[3][4]=1;
    //fila_3
    letra4[3][3]=1; letra4[4][3]=1;
    //fila_2
    letra4[3][2]=1;
    //fila_1
    letra4[3][1]=1; letra4[4][1]=1;
    //fila_0
  }

// letra F
  void letra_F1(){
    limpiar_letra1();
    
    //fila_7
    for(int x=0; x<=7; x++){ letra1[x][7]=1; }
    //fila_6
    letra1[0][6]=1;
    //fila_5
    letra1[0][5]=1;
    //fila_4
    for(int x=0; x<=7; x++){ letra1[x][4]=1; }
    //fila_3
    letra1[0][3]=1;
    //fila_2
    letra1[0][2]=1;
    //fila_1
    letra1[0][1]=1;
    //fila_0
    letra1[0][0]=1;
  }

  void letra_F2(){
    limpiar_letra2();
    
    //fila_7
    //fila_6
    for(int x=1; x<=6; x++){ letra2[x][6]=1; }
    //fila_5
    letra2[1][5]=1;
    //fila_4
    for(int x=1; x<=6; x++){ letra2[x][4]=1; }
    //fila_3
    letra2[1][3]=1;
    //fila_2
    letra2[1][2]=1;
    //fila_1
    letra1[1][1]=1;
    //fila_0
  }

  void letra_F3(){
    limpiar_letra3();
    
    //fila_7
    //fila_6
    //fila_5
    for(int x=2; x<=5; x++){ letra3[x][5]=1; }
    //fila_4
    letra3[2][4]=1;
    //fila_3
    for(int x=2; x<=5; x++){ letra3[x][3]=1; }
    //fila_2
    letra3[2][2]=1;
    //fila_1
    letra3[2][1]=1;
    //fila_0
  }

  void letra_F4(){
    limpiar_letra4();
    
    //fila_7
    //fila_6
    //fila_5
    letra4[3][5]=1; letra4[4][5]=1;
    //fila_4
    letra4[3][4]=1;
    //fila_3
    letra4[3][3]=1; letra4[4][3]=1;
    //fila_2
    letra4[3][2]=1;
    //fila_1
    //fila_0
  }

// letra G
  void letra_G1(){
    limpiar_letra1();    
    //fila_7
    for(int x=1; x<=7;x++){ letra1[x][7]=1;}
    //fila_6
    letra1[0][6]=1;
    //fila_5
    letra1[0][5]=1;
    //fila_4
    letra1[0][4]=1; 
    //fila_3
    letra1[0][3]=1; for(int x=3; x<=7;x++){ letra1[x][3]=1;}
    //fila_2
    letra1[0][2]=1; letra1[7][2]=1; 
    //fila_1
    letra1[0][1]=1; letra1[7][1]=1;
    //fila_0
    for(int x=1; x<=7;x++){ letra1[x][0]=1;}
  }

  void letra_G2(){
    limpiar_letra2();    
    //fila_7
    //fila_6
    for(int x=2; x<=6;x++){ letra2[x][6]=1;}
    //fila_5
    letra2[1][5]=1;
    //fila_4
    letra2[1][4]=1; 
    //fila_3
    letra2[1][3]=1; for(int x=4; x<=6;x++){ letra2[x][3]=1;}
    //fila_2
    letra2[1][2]=1; letra2[6][2]=1; 
    //fila_1
    for(int x=2; x<=6;x++){ letra2[x][1]=1;}
    //fila_0
  }

  void letra_G3(){
    limpiar_letra3();    
    //fila_7
    //fila_6
    //fila_5
    letra3[3][5]=1; letra3[4][5]=1; letra3[5][5]=1;
    //fila_4
    letra3[2][4]=1; 
    //fila_3
    letra3[2][3]=1; letra3[4][3]=1; letra3[5][3]=1;
    //fila_2
    letra3[2][2]=1;  letra3[5][2]=1;
    //fila_1
    letra3[3][1]=1; letra3[4][1]=1; letra3[5][1]=1;
    //fila_0
  }

  void letra_G4(){
    limpiar_letra4();    
    //fila_7
    //fila_6
    //fila_5
    letra4[3][5]=1; letra4[4][5]=1;
    //fila_4
    letra4[2][4]=1;
    //fila_3
    letra4[2][3]=1; letra4[4][3]=1;
    //fila_2
    letra4[3][2]=1; letra4[4][2]=1; 
    //fila_1
    //fila_0
  }

// letra H
  void letra_H1(){
    limpiar_letra1();

    //columnas
    for(int x=0; x<=7; x++){ letra1[0][x]=1; }
    for(int x=0; x<=7; x++){ letra1[7][x]=1; }

    //fila
    for(int x=0; x<=7; x++){ letra1[x][3]=1; }
  }

  void letra_H2(){
    limpiar_letra2();

    //columnas
    for(int x=1; x<=6; x++){ letra2[1][x]=1; }
    for(int x=1; x<=6; x++){ letra2[6][x]=1; }

    //fila
    for(int x=1; x<=6; x++){ letra2[x][3]=1; }
  }

  void letra_H3(){
    limpiar_letra3();

    //columnas
    for(int x=1; x<=5; x++){ letra3[2][x]=1; }
    for(int x=1; x<=5; x++){ letra3[5][x]=1; }

    //fila
    for(int x=2; x<=5; x++){ letra3[x][3]=1; }
  }

  void letra_H4(){
    limpiar_letra4();

    //columnas
    for(int x=2; x<=5; x++){ letra4[2][x]=1; }
    for(int x=2; x<=5; x++){ letra4[4][x]=1; }

    //fila
    for(int x=2; x<=4; x++){ letra4[x][3]=1; }
  }

// letra I
  void letra_I1(){
    limpiar_letra1();

    //filas
    for(int x=0; x<=7; x++){ letra1[x][7]=1; }
    for(int x=0; x<=7; x++){ letra1[x][0]=1; }

    //columna
    for(int x=0; x<=7; x++){ letra1[3][x]=1; }
  }

  void letra_I2(){
    limpiar_letra2();

    //filas
    for(int x=1; x<=6; x++){ letra2[x][6]=1; }
    for(int x=1; x<=6; x++){ letra2[x][1]=1; }

    //columna
    for(int x=1; x<=6; x++){ letra2[3][x]=1; }
  }

  void letra_I3(){
    limpiar_letra3();

    //filas
    for(int x=2; x<=5; x++){ letra3[x][5]=1; }
    for(int x=2; x<=5; x++){ letra3[x][1]=1; }

    //columna
    for(int x=1; x<=5; x++){ letra3[3][x]=1; }
  }

  void letra_I4(){
    limpiar_letra4();

    //filas
    for(int x=2; x<=4; x++){ letra4[x][5]=1; }
    for(int x=2; x<=4; x++){ letra4[x][2]=1; }

    //columnas
    for(int x=2; x<=5; x++){ letra4[3][x]=1; }
  }

// letra J
  void letra_J1(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7; x++){ letra1[x][7]=1; }
    for(int x=2; x<=4; x++){ letra1[x][0]=1; }
    //columnas
    for(int x=1; x<=7; x++){ letra1[5][x]=1; }
    letra1[1][1]=1;
    letra1[1][2]=1;
  }

  void letra_J2(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6; x++){ letra2[x][6]=1; }
    for(int x=2; x<=3; x++){ letra2[x][1]=1; }
    //columnas
    for(int x=2; x<=6; x++){ letra2[4][x]=1; }
    letra2[1][2]=1;
  }

  void letra_J3(){
    limpiar_letra3();

    for(int x=2; x<=5; x++){ letra3[x][5]=1; }
    for(int x=2; x<=5; x++){ letra3[4][x]=1; }
    
    letra3[2][2]=1;
    //fila_1
    letra3[3][1]=1;
  }

  void letra_J4(){
    limpiar_letra4();
    
    //fila_5
    letra4[2][5]=1; letra4[3][5]=1; letra4[4][5]=1;
    //fila_4
    letra4[3][4]=1;
    //fila_3
    letra4[3][3]=1; 
    //fila_2
    letra4[2][2]=1;
  }

// letra K
  void letra_K1(){
    limpiar_letra1();
    //columna 
    for(int x=0; x<=7; x++){ letra1[0][x]=1;}
    //fila
    for(int x=0; x<=4; x++){ letra1[x][3]=1;}
    //diagonal
    for(int x=4; x<=7; x++){ letra1[x][x]=1;}
    
    letra1[4][2]=1; letra1[5][1]=1; letra1[6][0]=1;
  }

  void letra_K2(){
    limpiar_letra2();
    //columna 
    for(int x=1; x<=6; x++){ letra2[1][x]=1;}
    //fila
    for(int x=1; x<=4; x++){ letra2[x][3]=1;}
    //diagonal
    for(int x=4; x<=6; x++){ letra2[x][x]=1;}
    
    letra2[4][2]=1; letra2[5][1]=1;
  }

  void letra_K3(){
    limpiar_letra3();
    //columna 
    for(int x=1; x<=5; x++){ letra3[2][x]=1;}

    //diagonal
    for(int x=3; x<=5; x++){ letra3[x][x]=1;}
    
    letra3[4][2]=1; letra3[5][1]=1;
  }

  void letra_K4(){
    limpiar_letra4();
    //columna 
    for(int x=2; x<=5; x++){ letra4[2][x]=1;}

    //diagonal
    for(int x=3; x<=5; x++){ letra4[x][x]=1;}
    
    letra4[4][2]=1; 
  }

// letra L
  void letra_L1(){
    limpiar_letra1();
    
    for(int x=0; x<=7; x++){ letra1[0][x]=1; }
    for(int x=0; x<=7; x++){ letra1[x][0]=1; }
  }

  void letra_L2(){
    limpiar_letra2();
    
    for(int x=1; x<=6; x++){ letra2[1][x]=1; }
    for(int x=1; x<=6; x++){ letra2[x][1]=1; }
  }

  void letra_L3(){
    limpiar_letra3();
    
    for(int x=1; x<=5; x++){ letra3[2][x]=1; }
    for(int x=2; x<=5; x++){ letra3[x][1]=1; }
  }

  void letra_L4(){
    limpiar_letra4();
    
    for(int x=2; x<=5; x++){ letra4[3][x]=1; }
    for(int x=3; x<=4; x++){ letra4[x][2]=1; }
  }

// letra M
  void letra_M1(){
    limpiar_letra1();

    //columnas
    for(int x=0; x<=7; x++){ letra1[0][x]=1; }
    for(int x=0; x<=7; x++){ letra1[7][x]=1; }

    for(int x=4; x<=7; x++){ letra1[x][x]=1; }
    for(int x=7; x>=4; x--){ letra1[7-x][x]=1; }
  }

  void letra_M2(){
    limpiar_letra2();

    //columnas
    for(int x=1; x<=6; x++){ letra2[1][x]=1; }
    for(int x=1; x<=6; x++){ letra2[6][x]=1; }

    for(int x=4; x<=6; x++){ letra2[x][x]=1; }
    for(int x=6; x>=4; x--){ letra2[7-x][x]=1; }
  }

  void letra_M3(){
    limpiar_letra3();

    //columnas
    for(int x=1; x<=5; x++){ letra3[2][x]=1; }
    for(int x=1; x<=5; x++){ letra3[5][x]=1; }

    for(int x=4; x<=5; x++){ letra3[x][x]=1; }
    for(int x=5; x>=4; x--){ letra3[7-x][x]=1; }
  }

  void letra_M4(){
    limpiar_letra4();

    //columnas
    for(int x=2; x<=5; x++){ letra4[2][x]=1; }
    for(int x=2; x<=5; x++){ letra4[5][x]=1; }

    for(int x=4; x<=5; x++){ letra4[x][x]=1; }
    for(int x=5; x>=4; x--){ letra4[7-x][x]=1; }
  }

// letra N
  void letra_N1(){
    limpiar_letra1();

    //columnas
    for(int x=0; x<=7; x++){ letra1[0][x]=1; }
    for(int x=0; x<=7; x++){ letra1[7][x]=1; }

    for(int x=7; x>=0; x--){ letra1[7-x][x]=1; }
  }

  void letra_N2(){
    limpiar_letra2();

    //columnas
    for(int x=1; x<=6; x++){ letra2[1][x]=1; }
    for(int x=1; x<=6; x++){ letra2[6][x]=1; }

    for(int x=6; x>=1; x--){ letra2[7-x][x]=1; }
  }

  void letra_N3(){
    limpiar_letra3();

    //columnas
    for(int x=1; x<=5; x++){ letra3[2][x]=1; }
    for(int x=1; x<=5; x++){ letra3[5][x]=1; }

    for(int x=4; x>=4; x--){ letra3[6-x][x]=1; }
  }

  void letra_N4(){
    limpiar_letra4();

    //columnas
    for(int x=2; x<=5; x++){ letra4[2][x]=1; }
    for(int x=2; x<=5; x++){ letra4[5][x]=1; }

    for(int x=5; x>=2; x--){ letra4[7-x][x]=1; }
  }
// letra Ñ
  void egne(){
    limpiar_letra1();
    for(int i=0;i<7;i++){
      letra1[1][i]=1;
    }
    for(int i=1;i<7;i++){
      letra1[i][5]=1;
    }
    for(int i=2;i<6;i++){
      letra1[i][7]=1;
    }
    for(int i=0;i<6;i++){
      letra1[6][i]=1;
    }

  }  

// letra O
  void letra_O1(){
    limpiar_letra1();

    //columnas
    for(int x=1; x<=6; x++){ letra1[0][x]=1; }
    for(int x=1; x<=6; x++){ letra1[7][x]=1; }
    //filas
    for(int x=1; x<=6; x++){ letra1[x][7]=1; }
    for(int x=1; x<=6; x++){ letra1[x][0]=1; }
  }

  void letra_O2(){
    limpiar_letra2();

    //columnas
    for(int x=2; x<=5; x++){ letra2[1][x]=1; }
    for(int x=2; x<=5; x++){ letra2[6][x]=1; }
    //filas
    for(int x=2; x<=5; x++){ letra2[x][6]=1; }
    for(int x=2; x<=5; x++){ letra2[x][1]=1; }
  }

  void letra_O3(){
    limpiar_letra3();

    //fila 5
    letra3[3][5]=1; letra3[4][5]=1;
    //fila 4
    letra3[2][4]=1; letra3[5][4]=1;
    //fila 3
    letra3[2][3]=1; letra3[5][3]=1;
    //fila 2
    letra3[2][2]=1; letra3[5][2]=1;
    //fila 1
    letra3[3][1]=1; letra3[4][1]=1;
  }

  void letra_O4(){
    limpiar_letra4();

    for(int x=3; x<=4; x++){ letra4[2][x]=1; }
    for(int x=3; x<=4; x++){ letra4[5][x]=1; }
    //filas
    for(int x=3; x<=4; x++){ letra4[x][2]=1; }
    for(int x=3; x<=4; x++){ letra4[x][5]=1; }
  }

// letra P
  void letra_P1(){
    limpiar_letra1();

    //columnas
    for(int x=0; x<=7; x++){ letra1[0][x]=1; }
    for(int x=4; x<=6; x++){ letra1[7][x]=1; }
    //filas
    for(int x=0; x<=6; x++){ letra1[x][7]=1; }
    for(int x=0; x<=6; x++){ letra1[x][3]=1; }
  }

  void letra_P2(){
    limpiar_letra2();

    //columnas
    for(int x=1; x<=6; x++){ letra2[1][x]=1; }
    for(int x=4; x<=5; x++){ letra2[6][x]=1; }
    //filas
    for(int x=1; x<=5; x++){ letra2[x][6]=1; }
    for(int x=1; x<=5; x++){ letra2[x][3]=1; }
  }

  void letra_P3(){
    limpiar_letra3();

    for(int x=1; x<=5; x++){ letra3[2][x]=1; }
    letra3[5][4]=1;
    //filas
    for(int x=2; x<=4; x++){ letra3[x][5]=1; }
    for(int x=2; x<=4; x++){ letra3[x][3]=1; }
  }

  void letra_P4(){
    limpiar_letra4();

    for(int x=2; x<=5; x++){ letra4[2][x]=1; }
    letra4[4][4]=1;
    //filas
    for(int x=2; x<=3; x++){ letra4[x][3]=1; }
    for(int x=2; x<=3; x++){ letra4[x][5]=1; }
  }

// letra Q
  void letra_Q1(){
    limpiar_letra1();

    //columnas
    for(int x=1; x<=6; x++){ letra1[0][x]=1; }
    for(int x=1; x<=6; x++){ letra1[7][x]=1; }
    //filas
    for(int x=1; x<=6; x++){ letra1[x][7]=1; }
    for(int x=1; x<=7; x++){ letra1[x][0]=1; }
    letra1[6][1]=1;
    letra1[5][2]=1;
    
  }

  void letra_Q2(){
    limpiar_letra2();

    //columnas
    for(int x=2; x<=5; x++){ letra2[1][x]=1; }
    for(int x=2; x<=5; x++){ letra2[6][x]=1; }
    //filas
    for(int x=2; x<=5; x++){ letra2[x][6]=1; }
    for(int x=2; x<=6; x++){ letra2[x][1]=1; }
    letra2[5][2]=1;
    letra2[4][3]=1;
  }

  void letra_Q3(){
    limpiar_letra3();

    //fila 5
    letra3[3][5]=1; letra3[4][5]=1;
    //fila 4
    letra3[2][4]=1; letra3[5][4]=1;
    //fila 3
    letra3[2][3]=1; letra3[5][3]=1;
    //fila 2
    letra3[2][2]=1; letra3[5][2]=1;
    //fila 1
    letra3[3][1]=1; letra3[4][1]=1; letra3[5][1]=1;
    letra3[4][2]=1;    
  }

  void letra_Q4(){
    limpiar_letra4();

    for(int x=3; x<=4; x++){ letra4[2][x]=1; }
    for(int x=3; x<=4; x++){ letra4[5][x]=1; }
    //filas
    for(int x=3; x<=4; x++){ letra4[x][5]=1; }
    for(int x=3; x<=5; x++){ letra4[x][2]=1; }
    letra4[4][3]=1;
  }

//letra R 
  void letra_R1(){
    limpiar_letra1();

    //columnas
    for(int x=0; x<=7; x++){ letra1[0][x]=1; }
    for(int x=4; x<=6; x++){ letra1[7][x]=1; }
    //filas
    for(int x=0; x<=6; x++){ letra1[x][7]=1; }
    for(int x=0; x<=6; x++){ letra1[x][3]=1; }

    for(int x=3; x>=0; x--){ letra1[6-x][x]=1; }
  }

  void letra_R2(){
    limpiar_letra2();

    //columnas
    for(int x=1; x<=6; x++){ letra2[1][x]=1; }
    for(int x=4; x<=5; x++){ letra2[6][x]=1; }
    //filas
    for(int x=1; x<=5; x++){ letra2[x][6]=1; }
    for(int x=1; x<=5; x++){ letra2[x][3]=1; }
    
    for(int x=3; x>=1; x--){ letra2[6-x][x]=1; }
  }

  void letra_R3(){
    limpiar_letra3();

    for(int x=1; x<=5; x++){ letra3[2][x]=1; }
    letra3[5][4]=1;
    //filas
    for(int x=2; x<=4; x++){ letra3[x][5]=1; }
    for(int x=2; x<=4; x++){ letra3[x][3]=1; }

    letra3[3][2]=1;
    letra3[4][1]=1;
  }

  void letra_R4(){
    limpiar_letra4();

    for(int x=2; x<=5; x++){ letra4[2][x]=1; }
    letra4[4][4]=1;
    letra4[4][2]=1;
    //filas
    for(int x=2; x<=3; x++){ letra4[x][3]=1; }
    for(int x=2; x<=3; x++){ letra4[x][5]=1; }
  }

//letra S
  void letra_S1(){
    limpiar_letra1();

    //fila
    for(int x=1; x<=7; x++){ letra1[x][7]=1; }
    for(int x=1; x<=6; x++){ letra1[x][3]=1; }
    for(int x=0; x<=6; x++){ letra1[x][0]=1; }
    //columnas
    for(int x=4; x<=6; x++){ letra1[0][x]=1; }
    for(int x=1; x<=2; x++){ letra1[7][x]=1; }
  }

  void letra_S2(){
    limpiar_letra2();

    for(int x=2; x<=6; x++){ letra2[x][6]=1; }
    for(int x=2; x<=5; x++){ letra2[x][3]=1; }
    for(int x=1; x<=5; x++){ letra2[x][1]=1; }
    //columnas
    for(int x=4; x<=5; x++){ letra2[1][x]=1; }
    letra2[6][2]=1;
  }

  void letra_S3(){
    limpiar_letra3();

    for(int x=3; x<=5; x++){ letra3[x][5]=1; }
    for(int x=3; x<=4; x++){ letra3[x][3]=1; }
    for(int x=2; x<=4; x++){ letra3[x][1]=1; }
    //columnas
    letra3[2][4]=1;
    letra3[5][2]=1;
  }

  void letra_S4(){
    limpiar_letra4();

    for(int x=3; x<=4; x++){ letra4[x][5]=1; }
    for(int x=4; x>=2; x--){ letra4[6-x][x]=1; }
    for(int x=2; x<=3; x++){ letra4[x][1]=1; }
  }

// letra T
  void letra_T1(){
    limpiar_letra1();

    for(int x=0; x<=7; x++){ letra1[x][7]=1; }
    for(int x=0; x<=7; x++){ letra1[3][x]=1; }
  }

  void letra_T2(){
    limpiar_letra2();

    for(int x=1; x<=6; x++){ letra2[x][6]=1; }
    for(int x=1; x<=6; x++){ letra2[3][x]=1; }
  }

  void letra_T3(){
    limpiar_letra3();

    for(int x=2; x<=5; x++){ letra3[x][5]=1; }
    for(int x=1; x<=5; x++){ letra3[3][x]=1; }
  }

  void letra_T4(){
    limpiar_letra4();

    for(int x=2; x<=4; x++){ letra4[x][5]=1; }
    for(int x=2; x<=5; x++){ letra4[3][x]=1; }
  }

// letra U
  void letra_U1(){
    limpiar_letra1();

    for(int x=1; x<=7; x++){ letra1[0][x]=1; }
    for(int x=1; x<=7; x++){ letra1[7][x]=1; }

    for(int x=1; x<=6; x++){ letra1[x][0]=1; }
  }

  void letra_U2(){
    limpiar_letra2();

    for(int x=2; x<=6; x++){ letra2[1][x]=1; }
    for(int x=2; x<=6; x++){ letra2[6][x]=1; }

    for(int x=2; x<=5; x++){ letra2[x][1]=1; }
  }

  void letra_U3(){
    limpiar_letra3();

    for(int x=2; x<=5; x++){ letra3[2][x]=1; }
    for(int x=2; x<=5; x++){ letra3[5][x]=1; }

    for(int x=3; x<=4; x++){ letra3[x][1]=1; }
  }

  void letra_U4(){
    limpiar_letra4();

    for(int x=3; x<=5; x++){ letra4[2][x]=1; }
    for(int x=3; x<=5; x++){ letra4[4][x]=1; }

    letra4[3][2]=1;
  }

// letra V
  void letra_V1(){
    limpiar_letra1();

    for(int x=3; x<=7;x++){ letra1[0][x]=1; }
    for(int x=3; x<=7;x++){ letra1[7][x]=1; }
    letra1[1][2]=1; letra1[6][2]=1;
    letra1[2][1]=1; letra1[5][1]=1;
    letra1[3][0]=1; letra1[4][0]=1;
  }

  void letra_V2(){
    limpiar_letra2();

    for(int x=4; x<=6;x++){ letra2[0][x]=1; }
    for(int x=4; x<=6;x++){ letra2[7][x]=1; }
    letra2[1][3]=1; letra2[6][3]=1;
    letra2[2][2]=1; letra2[5][2]=1;
    letra2[3][1]=1; letra2[4][1]=1;
  }

  void letra_V3(){
    limpiar_letra3();

    for(int x=3; x<=5;x++){ letra3[1][x]=1; }
    for(int x=3; x<=5;x++){ letra3[6][x]=1; }
    letra3[2][2]=1; letra3[5][2]=1;
    letra3[3][1]=1; letra3[4][1]=1;
  }

  void letra_V4(){
    limpiar_letra4();

    for(int x=4; x<=5;x++){ letra4[1][x]=1; }
    for(int x=4; x<=5;x++){ letra4[6][x]=1; }
    letra4[2][3]=1; letra4[5][3]=1;
    letra4[3][2]=1; letra4[4][2]=1;
  }

// letra W
  void letra_W1(){
    limpiar_letra1();

    for(int x=0; x<=7;x++){ letra1[0][x]=1; letra1[7][x]=1; }
    
    for(int x=0; x<=3;x++){ letra1[x][x]=1; }
    
    for(int x=3; x>=0;x--){ letra1[7-x][x]=1; }
  }

  void letra_W2(){
    limpiar_letra2();

    for(int x=1; x<=6;x++){ letra2[1][x]=1; letra2[6][x]=1; }
    
    for(int x=1; x<=3;x++){ letra2[x][x]=1; }
    
    for(int x=3; x>=1;x--){ letra2[7-x][x]=1; }
  }

  void letra_W3(){
    limpiar_letra3();

    for(int x=1; x<=5;x++){ letra3[1][x]=1; letra3[6][x]=1; }
    
    for(int x=1; x<=3;x++){ letra3[x][x]=1; }
    
    for(int x=3; x>=1;x--){ letra3[7-x][x]=1; }
  }

  void letra_W4(){
    limpiar_letra4();
    
    for(int x=2; x<=5;x++){ letra4[2][x]=1; letra4[5][x]=1; }
    
    for(int x=2; x<=3;x++){ letra4[x][x]=1; }
    
    for(int x=3; x>=2;x--){ letra4[7-x][x]=1; }
  }

// letra X
  void letra_X1(){
    limpiar_letra1();

    for(int x=0; x<=7;x++){ letra1[x][x]=1; }
    for(int x=7; x>=0;x--){ letra1[7-x][x]=1; }  
  }

  void letra_X2(){
    limpiar_letra2();

    for(int x=1; x<=6;x++){ letra2[x][x]=1; }
    for(int x=6; x>=1;x--){ letra2[7-x][x]=1; }  
  }

  void letra_X3(){
    limpiar_letra3();

    for(int x=2; x<=5;x++){ letra3[x][x]=1; }
    for(int x=5; x>=2;x--){ letra3[7-x][x]=1; }  
  }

  void letra_X4(){
    limpiar_letra4();

    for(int x=3; x<=4;x++){ letra4[x][x]=1; }
    for(int x=4; x>=3;x--){ letra4[7-x][x]=1; }  
  }

// letra Y
  void letra_Y1(){
    limpiar_letra1();

    for(int x=3; x<=7;x++){ letra1[x][x]=1; }
    for(int x=7; x>=4;x--){ letra1[7-x][x]=1; }

    for(int x=0; x<=4;x++){ letra1[3][x]=1; }
  }

  void letra_Y2(){
    limpiar_letra2();

    for(int x=3; x<=6;x++){ letra2[x][x]=1; }
    for(int x=6; x>=4;x--){ letra2[7-x][x]=1; }

    for(int x=1; x<=4;x++){ letra2[3][x]=1; }
  }

  void letra_Y3(){
    limpiar_letra3();

    for(int x=3; x<=5;x++){ letra3[x][x]=1; }
    for(int x=5; x>=4;x--){ letra3[7-x][x]=1; }

    for(int x=1; x<=4;x++){ letra3[3][x]=1; }
  }

  void letra_Y4(){
    limpiar_letra4();

    letra4[2][5]=1; letra4[4][5]=1;
    for(int x=2; x<=4;x++){ letra4[3][x]=1; }
  }

// letra Z
  void letra_Z1(){
    limpiar_letra1();

    for(int x=0; x<=7; x++){
      letra1[x][7]=1;
      letra1[x][x]=1;
      letra1[x][0]=1;  
    }    
  }

  void letra_Z2(){
    limpiar_letra2();

    for(int x=1; x<=6; x++){
      letra2[x][6]=1;
      letra2[x][x]=1;
      letra2[x][1]=1;  
    }    
  }

  void letra_Z3(){
    limpiar_letra3();

    for(int x=2; x<=5; x++){
      letra3[x][5]=1;
      letra3[x][x]=1;
      letra3[x][2]=1;  
    }    
  }

  void letra_Z4(){
    limpiar_letra4();

    for(int x=2; x<=4; x++){
      letra4[x][4]=1;
      letra4[x][x]=1;
      letra4[x][2]=1;  
    }    
  }

// numero 0
  void numero_01(){
    limpiar_letra1();
    for(int x=0; x<=7;x++){ 
      letra1[x][7]=1; 
      letra1[x][0]=1; 
      letra1[0][x]=1; 
      letra1[7][x]=1;
    }  
  }

  void numero_02(){
    limpiar_letra2();
    for(int x=1; x<=6;x++){ 
      letra2[x][6]=1; 
      letra2[x][1]=1; 
      letra2[1][x]=1; 
      letra2[6][x]=1;
    }  
  }

  void numero_03(){
    limpiar_letra3();
    for(int x=2; x<=5;x++){ 
      letra3[x][5]=1; 
      letra3[x][2]=1; 
      letra3[2][x]=1; 
      letra3[5][x]=1;
    }  
  }
  
  void numero_04(){
    limpiar_letra4();
    for(int x=2; x<=4;x++){ 
      letra4[x][4]=1; 
      letra4[x][2]=1; 
      letra4[2][x]=1; 
      letra4[4][x]=1;
    }  
  }

// numero 1
  void numero_11(){
    limpiar_letra1();
    for(int x=0; x<=7;x++){ letra1[x][0]=1;}
    for(int x=0; x<=7;x++){ letra1[4][x]=1;}
    for(int x=0; x<=3;x++){ letra1[x][x+4]=1;}
  }

  void numero_12(){
    limpiar_letra2();
    for(int x=1; x<=6;x++){ letra2[x][1]=1;}
    for(int x=1; x<=6;x++){ letra2[4][x]=1;}
    for(int x=1; x<=3;x++){ letra2[x][x+3]=1;}
  }

  void numero_13(){
    limpiar_letra3();
    for(int x=2; x<=5;x++){ letra3[x][2]=1;}
    for(int x=2; x<=5;x++){ letra3[4][x]=1;}
    letra3[2][4]=1;
    letra3[3][5]=1;
  }

  void numero_14(){
    limpiar_letra4();
    for(int x=3; x<=5;x++){ letra4[x][2]=1;}
    for(int x=2; x<=4;x++){ letra4[4][x]=1;}
    letra4[3][4]=1;
  }

// numero 2
  void numero_21(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7;x++){ letra1[x][7]=1; letra1[x][4]=1; letra1[x][0]=1; }  
    //columnas
    for(int x=0; x<=4;x++){ letra1[0][x]=1;}
    for(int x=4; x<=7;x++){ letra1[7][x]=1;}  
  }

  void numero_22(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6;x++){ letra2[x][6]=1; letra2[x][4]=1; letra2[x][1]=1; }  
    //columnas
    for(int x=1; x<=4;x++){ letra2[1][x]=1;}
    for(int x=4; x<=6;x++){ letra2[6][x]=1;}  
  }

  void numero_23(){
    limpiar_letra3();
    //filas
    for(int x=2; x<=5;x++){ letra3[x][6]=1; letra3[x][4]=1; letra3[x][1]=1; }  
    //columnas
    for(int x=1; x<=4;x++){ letra3[2][x]=1;}
    for(int x=4; x<=6;x++){ letra3[5][x]=1;}  
  }

  void numero_24(){
    limpiar_letra4();
    //filas
    for(int x=3; x<=4;x++){ letra4[x][6]=1; letra4[x][4]=1; letra4[x][2]=1; }  
    //columnas
    letra4[4][5]=1;
    letra4[3][3]=1;  
  }


// numero 3
  void numero_31(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7;x++){ letra1[x][7]=1; letra1[x][4]=1; letra1[x][0]=1; }  
    //columnas
    for(int x=0; x<=7;x++){ letra1[7][x]=1;}  
  }

  void numero_32(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6;x++){ letra2[x][6]=1; letra2[x][3]=1; letra2[x][1]=1; }  
    //columnas
    for(int x=1; x<=6;x++){ letra2[6][x]=1;}  
  }

  void numero_33(){
    limpiar_letra3();
    //filas
    for(int x=2; x<=5;x++){ letra3[x][6]=1; letra3[x][3]=1; letra3[x][1]=1; }  
    //columnas
    for(int x=1; x<=6;x++){ letra3[5][x]=1;}  
  }

  void numero_34(){
    limpiar_letra4();
    //filas
    for(int x=3; x<=4;x++){ letra4[x][6]=1; letra4[x][4]=1; letra4[x][2]=1; }  
    //columnas
    for(int x=2; x<=6;x++){ letra4[4][x]=1;}  
  }

// numero 4
  void numero_41(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7;x++){ letra1[x][4]=1; }  
    //columnas
    for(int x=4; x<=7;x++){ letra1[0][x]=1;}
    for(int x=0; x<=7;x++){ letra1[7][x]=1;}  
  }

  void numero_42(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6;x++){ letra2[x][4]=1;}  
    //columnas
    for(int x=4; x<=6;x++){ letra2[1][x]=1;}
    for(int x=1; x<=6;x++){ letra2[6][x]=1;}  
  }

  void numero_43(){
    limpiar_letra3();
    //filas
    for(int x=2; x<=5;x++){ letra3[x][3]=1;}  
    //columnas
    for(int x=3; x<=5;x++){ letra3[2][x]=1;}
    for(int x=1; x<=5;x++){ letra3[5][x]=1;}  
  }

  void numero_44(){
    limpiar_letra4();
    //filas
    for(int x=2; x<=4;x++){ letra4[x][4]=1;}  
    //columnas
    for(int x=4; x<=5;x++){ letra4[2][x]=1;}
    for(int x=2; x<=5;x++){ letra4[4][x]=1;}  
  }
  
// numero 5
  void numero_51(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7;x++){ letra1[x][7]=1; letra1[x][4]=1; letra1[x][0]=1; }  
    //columnas
    for(int x=4; x<=7;x++){ letra1[0][x]=1;}
    for(int x=0; x<=4;x++){ letra1[7][x]=1;}  
  }

  void numero_52(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6;x++){ letra2[x][6]=1; letra2[x][3]=1; letra2[x][1]=1; }  
    //columnas
    for(int x=3; x<=6;x++){ letra2[1][x]=1;}
    for(int x=1; x<=3;x++){ letra2[6][x]=1;}  
  }

  void numero_53(){
    limpiar_letra3();
    //filas
    for(int x=2; x<=5;x++){ letra3[x][5]=1; letra3[x][3]=1; letra3[x][1]=1; }  
    //columnas
    for(int x=3; x<=5;x++){ letra3[2][x]=1;}
    for(int x=1; x<=3;x++){ letra3[5][x]=1;}  
  }

  void numero_54(){
    limpiar_letra4();
    //filas
    for(int x=3; x<=4;x++){ letra4[x][6]=1; letra4[x][4]=1; letra4[x][2]=1; }  
    //columnas
    for(int x=4; x<=6;x++){ letra4[3][x]=1;}
    for(int x=2; x<=4;x++){ letra4[4][x]=1;}  
  }

// numero 6
  void numero_61(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7;x++){ letra1[x][7]=1; letra1[x][4]=1; letra1[x][0]=1; }  
    //columnas
    for(int x=0; x<=7;x++){ letra1[0][x]=1;}
    for(int x=0; x<=4;x++){ letra1[7][x]=1;}  
  }

  void numero_62(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6;x++){ letra2[x][6]=1; letra2[x][3]=1; letra2[x][1]=1; }  
    //columnas
    for(int x=1; x<=6;x++){ letra2[1][x]=1;}
    for(int x=1; x<=3;x++){ letra2[6][x]=1;}  
  }

  void numero_63(){
    limpiar_letra3();
    //filas
    for(int x=2; x<=5;x++){ letra3[x][5]=1; letra3[x][3]=1; letra3[x][1]=1; }  
    //columnas
    for(int x=1; x<=5;x++){ letra3[2][x]=1;}
    for(int x=1; x<=3;x++){ letra3[5][x]=1;}  
  }

  void numero_64(){
    limpiar_letra4();
    //filas
    for(int x=2; x<=4;x++){ letra4[x][6]=1; letra4[x][4]=1; letra4[x][2]=1; }  
    //columnas
    for(int x=2; x<=6;x++){ letra4[2][x]=1;}
    for(int x=2; x<=4;x++){ letra4[4][x]=1;}  
  }
  
// numero 7
  void numero_71(){
    limpiar_letra1();
    for(int x=0; x<=7;x++){ letra1[x][7]=1; letra1[7][x]=1;}
  }

  void numero_72(){
    limpiar_letra2();
    for(int x=1; x<=6;x++){ letra2[x][6]=1; letra2[6][x]=1;}
  }

  void numero_73(){
    limpiar_letra3();
    for(int x=2; x<=5;x++){ letra3[x][5]=1; letra3[5][x]=1;}
  }

  void numero_74(){
    limpiar_letra4();
    for(int x=2; x<=5;x++){ letra4[4][x]=1;}
    letra4[3][5]=1;
  }

// numero 8
  void numero_81(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7;x++){ letra1[x][7]=1; letra1[x][4]=1; letra1[x][0]=1; }
    //columnas  
    for(int x=0; x<=7;x++){ letra1[0][x]=1; letra1[7][x]=1;}
  }

  void numero_82(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6;x++){ letra2[x][6]=1; letra2[x][3]=1; letra2[x][1]=1; }
    //columnas  
    for(int x=1; x<=6;x++){ letra2[1][x]=1; letra2[6][x]=1;}
  }

  void numero_83(){
    limpiar_letra3();
    //filas
    for(int x=2; x<=5;x++){ letra3[x][5]=1; letra3[x][3]=1; letra3[x][1]=1; }
    //columnas  
    for(int x=1; x<=5;x++){ letra3[2][x]=1; letra3[5][x]=1;}
  }

  void numero_84(){
    limpiar_letra4();
    //filas
    for(int x=2; x<=4;x++){ letra4[x][6]=1; letra4[x][4]=1; letra4[x][2]=1; }
    //columnas  
    for(int x=2; x<=6;x++){ letra4[2][x]=1; letra4[4][x]=1;}
  }

// numero 9
  void numero_91(){
    limpiar_letra1();
    //filas
    for(int x=0; x<=7;x++){ letra1[x][4]=1; letra1[x][7]=1;}  
    //columnas
    for(int x=4; x<=7;x++){ letra1[0][x]=1;}
    for(int x=0; x<=7;x++){ letra1[7][x]=1;}  
  }

  void numero_92(){
    limpiar_letra2();
    //filas
    for(int x=1; x<=6;x++){ letra2[x][4]=1; letra2[x][6]=1;}  
    //columnas
    for(int x=4; x<=6;x++){ letra2[1][x]=1;}
    for(int x=1; x<=6;x++){ letra2[6][x]=1;}  
  }

  void numero_93(){
    limpiar_letra3();
    //filas
    for(int x=2; x<=5;x++){ letra3[x][3]=1; letra3[x][5]=1;}  
    //columnas
    for(int x=3; x<=5;x++){ letra3[2][x]=1;}
    for(int x=1; x<=5;x++){ letra3[5][x]=1;}  
  }

  void numero_94(){
    limpiar_letra4();
    //filas
    for(int x=2; x<=4;x++){ letra4[x][3]=1; letra4[x][5]=1;}  
    //columnas
    for(int x=3; x<=5;x++){ letra4[2][x]=1;}
    for(int x=2; x<=5;x++){ letra4[4][x]=1;}  
  }
  
  void limpiar_letra1(){
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
          letra1[x][y] = 0;
      }     
    }
  }

  void limpiar_letra2(){
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
          letra2[x][y] = 0;
      }     
    }
  }

  void limpiar_letra3(){
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
          letra3[x][y] = 0;
      }     
    }
  }

  void limpiar_letra4(){
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
          letra4[x][y] = 0;
      }     
    }
  }
  void capa1(){
    if(checkpoint<512){
      for(int i=0;i<checkpoint;i++){
      areglo_prueba[i]=0;
      }

      areglo_prueba[checkpoint]=1;
      for(int i=checkpoint+1;i<512;i++){
      areglo_prueba[i]=0;
      }
      checkpoint++;
      Serial.println(checkpoint);
    }
    
  }
// @
  void arroba(){
  limpiar_letra1();
  for(int i=0;i<8;i++){
    letra1[0][i]=1;
  }
  for(int i=1;i<8;i++){
    letra1[i][0]=1;
  }
  for(int i=2;i<8;i++){
    letra1[i][2]=1;
  }
  for(int i=2;i<6;i++){
    letra1[2][i]=1;
  }
  for(int i=2;i<6;i++){
    letra1[5][i]=1;
  }
  for(int i=2;i<8;i++){
    letra1[7][i]=1;
  }
  for(int i=2;i<6;i++){
    letra1[i][5]=1;
  }
  for(int i=0;i<8;i++){
    letra1[i][7]=1;
  }
  }
// #
  void numeral(){
    limpiar_letra1();
    for(int i=0;i<8;i++){
      letra1[2][i]=1;
    }
    for(int i=0;i<8;i++){
      letra1[5][i]=1;
    }
    for(int i=0;i<8;i++){
      letra1[i][2]=1;
    }
    for(int i=0;i<8;i++){
      letra1[i][5]=1;
    }
  }
//$
  void dolar(){
    limpiar_letra1();
    for(int i=0;i<8;i++){
      letra1[i][1]=1;
      letra1[i][4]=1;
      letra1[i][6]=1;
      letra1[2][i]=1;
      letra1[4][i]=1;
    }
    letra1[7][2]=1;
    letra1[7][3]=1;
    
  }
//_ 
  void guionbajo(){
    limpiar_letra1();
    for(int i=0;i<8;i++){
      letra1[i][0]=1;
    }
  }
//&
  void ampersand(){
    limpiar_letra1();
    letra1[0][1]=1;
    letra1[0][5]=1;
    letra1[0][6]=1;
    letra1[1][2]=1;
    letra1[1][4]=1;
    letra1[2][3]=1;
    letra1[3][2]=1;
    letra1[4][1]=1;
    letra1[5][0]=1;
    letra1[5][2]=1;
    letra1[6][3]=1;
    for(int i=1;i<4;i++){
      letra1[i][0]=1;
    }
    for(int i=1;i<4;i++){
      letra1[i][7]=1;
    }
    for(int i=5;i<7;i++){
      letra1[5][i]=1;
    }
  }
//-
  void guion(){
    limpiar_letra1();
    for(int i=1;i<7;i++){
      letra1[i][3]=1;
      letra1[i][4]=1;
    }
  }
//+
  void suma(){
    limpiar_letra1();
    for(int i=0;i<8;i++){
        letra1[3][i]=1;
        letra1[4][i]=1;
        letra1[i][3]=1;
        letra1[i][4]=1;
    }
  }
//(
    void parabre(){
      limpiar_letra1();
      letra1[0][3]=1;
      letra1[0][4]=1;
      letra1[1][2]=1;
      letra1[1][5]=1;
      letra1[2][1]=1;
      letra1[2][6]=1;
      letra1[3][0]=1;
      letra1[3][7]=1;
    }
//)
  void parcierra(){
    limpiar_letra1();
    letra1[7][3]=1;
    letra1[7][4]=1;
    letra1[6][2]=1;
    letra1[6][5]=1;
    letra1[5][1]=1;
    letra1[5][6]=1;
    letra1[4][0]=1;
    letra1[4][7]=1;
  }
// "/"
  void barra(){
      limpiar_letra1();
      letra1[0][0]=1;
      letra1[1][1]=1;
      letra1[2][2]=1;
      letra1[3][3]=1;
      letra1[4][4]=1;
      letra1[5][5]=1;
      letra1[6][6]=1;
      letra1[7][7]=1;
  }
//*
  void asterisco(){
    limpiar_letra1();
    letra1[0][0]=1;
    letra1[0][7]=1;
    letra1[1][6]=1;
    letra1[1][6]=1;
    letra1[6][1]=1;
    letra1[6][6]=1;
    letra1[7][0]=1;
    letra1[7][7]=1;
    for(int i=0;i<8;i++){
      letra1[i][3]=1;
      letra1[i][4]=1;
      letra1[3][i]=1;
      letra1[4][i]=1;
    }
    letra1[2][2]=1;
    letra1[2][5]=1;
    letra1[5][2]=1;
    letra1[5][5]=1;
  }
//"
  void comillas(){
    limpiar_letra1();
    for(int i=4;i<8;i++){
      letra1[2][i]=1;
      letra1[4][i]=1;
    }
  }
//'
  void comilla(){
    limpiar_letra1();
    for(int i=4;i<8;i++){
      letra1[4][i]=1;
    }
  }
//:
  void dospuntos(){
    limpiar_letra1();
    for(int i=3;i<5;i++){
      letra1[i][1]=1;
      letra1[i][2]=1;
      letra1[i][5]=1;
      letra1[i][6]=1;

    }
  }
//;
  void puntocoma(){
    limpiar_letra1();
    for(int i=3;i<5;i++){
      letra1[i][5]=1;
      letra1[i][6]=1;
    }
   letra1[2][1]=1;
   letra1[3][2]=1;
  }
//!
  void exclamacion(){
    limpiar_letra1();
    for(int i=3;i<5;i++){
      letra1[i][0]=1;
      letra1[i][1]=1;
      letra1[i][3]=1;
      letra1[i][4]=1;
      letra1[i][5]=1;
      letra1[i][6]=1;
      letra1[i][7]=1;
      
    }
  }
//?
  void interrogacion(){
    limpiar_letra1();
    for(int i=3;i<5;i++){
      letra1[i][0]=1;
      letra1[i][1]=1;
      letra1[i][3]=1;
      letra1[i][4]=1;
    }
    for(int i=5;i<7;i++){
      letra1[i][5]=1;
      letra1[i][6]=1;
    }
    for(int i=5;i<8;i++){
      letra1[0][i]=1;
    }
    for(int i=0;i<5;i++){
      letra1[i][7]=1;
    }

  }
// .
  void punto(){
    limpiar_letra1();
    for(int i=0;i<2;i++){
      letra1[3][i]=1;
      letra1[4][i]=1;
    }
  }
// ,
  void coma(){
    limpiar_letra1();
    letra1[3][0]=1;
    letra1[4][1]=1;
    letra1[5][2]=1;
    
  }
















void imprimir_esfera(){
  esfera();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_circulo[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
}
  //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
  
  
}
void esfera(){
  //Circulo grande , centro
  for(int i=0;i<512;i++){
    areglo_circulo[i]=0;
  }

  for(int i=258;i<262;i++){
    areglo_circulo[i]=1;
  }

  for(int i=265;i<271;i++){
    areglo_circulo[i]=1;
  }

  for(int i=272;i<304;i++){
    areglo_circulo[i]=1;
  }
  
  for(int i=305;i<311;i++){
    areglo_circulo[i]=1;
  }
  
  for(int i=314;i<318;i++){
    areglo_circulo[i]=1;
  }
 
  //
  for(int i=258-64;i<262-64;i++){
    areglo_circulo[i]=1;
  }

  for(int i=265-64;i<271-64;i++){
    areglo_circulo[i]=1;
  }

  for(int i=272-64;i<304-64;i++){
    areglo_circulo[i]=1;
  }
  
  for(int i=305-64;i<311-64;i++){
    areglo_circulo[i]=1;
  }
  
  for(int i=314-64;i<318-64;i++){
    areglo_circulo[i]=1;
  }
  // Circulo mediano semi-orillas

  areglo_circulo[139]=1;
  areglo_circulo[140]=1;
  for(int i=146;i<150;i++){
    areglo_circulo[i]=1;
  }
  for(int i=129+24;i<135+24;i++){
    areglo_circulo[i]=1;
  }
  for(int i=129+32;i<135+32;i++){
    areglo_circulo[i]=1;
  }
  for(int i=146+24;i<150+24;i++){
    areglo_circulo[i]=1;
  }
  areglo_circulo[139+40]=1;
  areglo_circulo[140+40]=1;
  //

  areglo_circulo[139+192]=1;
  areglo_circulo[140+192]=1;
  for(int i=146+192;i<150+192;i++){
    areglo_circulo[i]=1;
  }
  for(int i=129+24+192;i<135+24+192;i++){
    areglo_circulo[i]=1;
  }
  for(int i=129+32+192;i<135+32+192;i++){
    areglo_circulo[i]=1;
  }
  for(int i=146+24+192;i<150+24+192;i++){
    areglo_circulo[i]=1;
  }
  areglo_circulo[139+40+192]=1;
  areglo_circulo[140+40+192]=1;
  //Circulo pequeño - orillas
  areglo_circulo[67+16]=1;
  areglo_circulo[68+16]=1;
  for(int i=66+24;i<70+24;i++){
    areglo_circulo[i]=1;
  }
  for(int i=66+32;i<70+32;i++){
    areglo_circulo[i]=1;
  }
  areglo_circulo[67+32+320]=1;
  areglo_circulo[68+32+320]=1;
  //
  areglo_circulo[67+16+320]=1;
  areglo_circulo[68+16+320]=1;
  for(int i=66+24+320;i<70+24+320;i++){
    areglo_circulo[i]=1;
  }
  for(int i=66+32+320;i<70+32+320;i++){
    areglo_circulo[i]=1;
  }
  areglo_circulo[67+32+320]=1;
  areglo_circulo[68+32+320]=1;

}
void plano_recto(){
  for(int i=0;i<512;i++){
    areglo_planor[i]=0;
  }
  for(int i=256;i<256+64;i++){
    areglo_planor[i]=1;
  }
}
void plano_inclinado(){
  for(int i=0;i<512;i++){
    areglo_planoi[i]=0;
  }
  //
  for(int i=0;i<8;i++){
    areglo_planoi[8*i]=1;
  }
  for(int i=0;i<8;i++){
    areglo_planoi[8*i+65]=1;
  }
  for(int i=0;i<8;i++){
    areglo_planoi[8*i+130]=1;
  }
  for(int i=0;i<8;i++){
    areglo_planoi[8*i+195]=1;
  }
  for(int i=0;i<8;i++){
    areglo_planoi[8*i+260]=1;
  }
  for(int i=0;i<8;i++){
    areglo_planoi[8*i+325]=1;
  }
  for(int i=0;i<8;i++){
    areglo_planoi[8*i+390]=1;
  }
  for(int i=0;i<8;i++){
    areglo_planoi[8*i+455]=1;
  }
}
void cono(){
  //Vaciamos
  for(int i=0;i<512;i++){
    areglo_circulo[i]=0;
  }
  //Base nivel 1
  for(int i=2;i<6;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+8;i<7+8;i++){
    areglo_cono[i]=1;
  }
  for(int i=0+16;i<0+48;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+56;i<6+56;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+8+40;i<7+8+40;i++){
    areglo_cono[i]=1;
  }
  //Base nivel 2
  for(int i=3+64;i<5+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+8+64;i<7+8+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+16+64;i<7+16+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=0+24+64;i<0+40+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=3+56+64;i<5+56+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+40+64;i<7+40+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+48+64;i<7+48+64;i++){
    areglo_cono[i]=1;
  }
  //Base nivel 3
  
  for(int i=1+8+128;i<7+8+128;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+16+128;i<7+16+128;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+24+128;i<7+24+128;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+32+128;i<7+32+128;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+40+128;i<7+40+128;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+48+128;i<7+48+128;i++){
    areglo_cono[i]=1;
  }
  //Base nivel 4
  for(int i=2+8+128+64;i<6+8+128+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+16+128+64;i<7+16+128+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+24+128+64;i<7+24+128+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+32+128+64;i<7+32+128+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=1+40+128+64;i<7+40+128+64;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+48+128+64;i<6+48+128+64;i++){
    areglo_cono[i]=1;
  }
  // Base nivel 5
  for(int i=2+16+64*4;i<6+16+4*64;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+24+64*4;i<6+24+4*64;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+32+64*4;i<6+32+4*64;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+40+64*4;i<6+40+4*64;i++){
    areglo_cono[i]=1;
  }
  // Base nivel 6
  for(int i=2+16+64*5;i<6+16+5*64;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+24+64*5;i<6+24+5*64;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+32+64*5;i<6+32+5*64;i++){
    areglo_cono[i]=1;
  }
  for(int i=2+40+64*5;i<6+40+5*64;i++){
    areglo_cono[i]=1;
  }
  // Base nivel 7
    areglo_cono[3+24+64*6]=1;
    areglo_cono[4+24+64*6]=1;
    areglo_cono[3+32+64*6]=1;
    areglo_cono[4+32+64*6]=1;
  //Base nivel 8
    areglo_cono[3+24+64*7]=1;
    areglo_cono[4+24+64*7]=1;
    areglo_cono[3+32+64*7]=1;
    areglo_cono[4+32+64*7]=1;


}
void elipsoide(){
  //Vaciamos
  for(int i=0;i<512;i++){
    areglo_elipsoide[i]=0;
  }
  //Capa 1 y 8
  areglo_elipsoide[3+16]=1;
  areglo_elipsoide[4+16]=1;
  for(int i=2+24;i<6+24;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=2+32;i<6+32;i++){
    areglo_elipsoide[i]=1;
  }
  areglo_elipsoide[3+40]=1;
  areglo_elipsoide[4+40]=1;
  
  areglo_elipsoide[3+16+64*7]=1;
  areglo_elipsoide[4+16+64*7]=1;
  for(int i=2+24+64*7;i<6+24+64*7;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=2+32+64*7;i<6+32+64*7;i++){
    areglo_elipsoide[i]=1;
  }
  areglo_elipsoide[3+40+64*7]=1;
  areglo_elipsoide[4+40+64*7]=1;
  //Capas 2 y 7
  for(int i=2+16+64;i<6+16+64;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+24+64;i<7+24+64;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+32+64;i<7+32+64;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=2+40+64;i<6+40+64;i++){
    areglo_elipsoide[i]=1;
  }

  for(int i=2+16+64*6;i<6+16+64*6;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+24+64*6;i<7+24+64*6;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+32+64*6;i<7+32+64*6;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=2+40+64*6;i<6+40+64*6;i++){
    areglo_elipsoide[i]=1;
  }
  //Capas 3 y 6
  for(int i=2+8+64*2;i<6+8+64*2;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+16+64*2;i<7+16+64*2;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=0+24+64*2;i<0+40+64*2;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=2+48+64*2;i<6+48+64*2;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+40+64*2;i<7+40+64*2;i++){
    areglo_elipsoide[i]=1;
  }

  for(int i=2+8+64*5;i<6+8+64*5;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+16+64*5;i<7+16+64*5;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=0+24+64*5;i<0+40+64*5;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=2+48+64*5;i<6+48+64*5;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=1+40+64*5;i<7+40+64*5;i++){
    areglo_elipsoide[i]=1;
  }
  //Capas 4 y 5
  areglo_elipsoide[3+64*3]=1;
  areglo_elipsoide[4+64*3]=1;
  for(int i=1+8+64*3;i<7+8+64*3;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=0+16+64*3;i<0+48+64*3;i++){
    areglo_elipsoide[i]=1;
  }
  areglo_elipsoide[3+54+64*3]=1;
  areglo_elipsoide[4+54+64*3]=1;
  for(int i=1+48+64*3;i<7+48+64*3;i++){
    areglo_elipsoide[i]=1;
  }

  areglo_elipsoide[3+64*4]=1;
  areglo_elipsoide[4+64*4]=1;
  for(int i=1+8+64*4;i<7+8+64*4;i++){
    areglo_elipsoide[i]=1;
  }
  for(int i=0+16+64*4;i<0+48+64*4;i++){
    areglo_elipsoide[i]=1;
  }
  areglo_elipsoide[3+54+64*4]=1;
  areglo_elipsoide[4+54+64*4]=1;
  for(int i=1+48+64*4;i<7+48+64*4;i++){
    areglo_elipsoide[i]=1;
  }

}
void paraboloide(){
  //Vaciamos
 for(int i=0;i<512;i++){
   areglo_paraboloide[i]=0;
 }
 
 //Nivel 1
 areglo_paraboloide[3+24]=1;
 areglo_paraboloide[4+24]=1;
 areglo_paraboloide[3+32]=1;
 areglo_paraboloide[4+32]=1;
 
 //Nivel 2
 areglo_paraboloide[3+16]=1;
 areglo_paraboloide[4+16]=1;
 for(int i=2+24+64;i<6+24+64;i++){
   areglo_paraboloide[i]=1;
 }
 for(int i=2+32+64;i<6+32+64;i++){
   areglo_paraboloide[i]=1;
 }
 areglo_paraboloide[3+40+64]=1;
 areglo_paraboloide[4+40+64]=1;
 //Nivel 3
 areglo_paraboloide[3+8+64*2]=1;
 areglo_paraboloide[4+8+64*2]=1;
 for(int i=2+16+64*2;i<6+16+64*2;i++){
   areglo_paraboloide[i]=1;
 }
 for(int i=1+24+64*2;i<7+24+64*2;i++){
   areglo_paraboloide[i]=1;
 }
 for(int i=1+32+64*2;i<7+32+64*2;i++){
   areglo_paraboloide[i]=1;
 }
 for(int i=2+40+64*2;i<6+40+64*2;i++){
   areglo_paraboloide[i]=1;
 }
 areglo_paraboloide[3+48+64*2]=1;
 areglo_paraboloide[4+48+64*2]=1;
    //Nivel 4
  for(int i=2+8+64*3;i<6+8+64*3;i++){
  areglo_paraboloide[i]=1;
  }
  for(int i=1+16+64*3;i<7+16+64*3;i++){
  areglo_paraboloide[i]=1;
  }
  for(int i=1+24+64*3;i<7+24+64*3;i++){
  areglo_paraboloide[i]=1;
  }
  for(int i=1+32+64*3;i<7+32+64*3;i++){
  areglo_paraboloide[i]=1;
  }
  for(int i=1+40+64*3;i<7+40+64*3;i++){
  areglo_paraboloide[i]=1;
  }
  for(int i=2+48+64*3;i<6+48+64*3;i++){
  areglo_paraboloide[i]=1;
  }
  //Nivel 5
  for(int i=1+8+64*4;i<7+8+64*4;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+16+64*4;i<7+16+64*4;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+24+64*4;i<7+24+64*4;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+32+64*4;i<7+32+64*4;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+40+64*4;i<7+40+64*4;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+48+64*4;i<7+48+64*4;i++){
    areglo_paraboloide[i]=1;
  }
  //Nivel 6
  for(int i=2+64*5;i<6+64*5;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+8+64*5;i<7+8+64*5;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=0+16+64*5;i<0+48+64*5;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+48+64*5;i<7+48+64*5;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=2+56+64*5;i<6+56+64*5;i++){
    areglo_paraboloide[i]=1;
  }
  //Nivel 7
  for(int i=1+64*6;i<7+64*6;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=0+8+64*6;i<0+56+64*6;i++){
    areglo_paraboloide[i]=1;
  }
  for(int i=1+56+64*6;i<7+56+64*6;i++){
    areglo_paraboloide[i]=1;
  }
  
}
void hiperboloide1(){
  //Vaciamos
  for(int i=0;i<512;i++){
    areglo_hiperboloide1[i]=0;
  }
  //Nivel 0 y 7
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[i]=1;
  }
  areglo_hiperboloide1[1+8]=1;
  areglo_hiperboloide1[6+8]=1;
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[8*i]=1;
  }
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[7+8*i]=1;
  }
  areglo_hiperboloide1[1+48]=1;
  areglo_hiperboloide1[6+48]=1;
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[i+56]=1;
  }
  //
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[i+64*7]=1;
  }
  areglo_hiperboloide1[1+8+64*7]=1;
  areglo_hiperboloide1[6+8+64*7]=1;
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[8*i+64*7]=1;
  }
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[7+8*i+64*7]=1;
  }
  areglo_hiperboloide1[1+48+64*7]=1;
  areglo_hiperboloide1[6+48+64*7]=1;
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[i+56+64*7]=1;
  }
  //Nivel 1 y 6
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[1+8*i+64]=1;
    areglo_hiperboloide1[6+8*i+64]=1;
  }
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[i+8+64]=1;
    areglo_hiperboloide1[i+48+64]=1;
  }
  //
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[1+8*i+64*6]=1;
    areglo_hiperboloide1[6+8*i+64*6]=1;
  }
  for(int i=2;i<6;i++){
    areglo_hiperboloide1[i+8+64*6]=1;
    areglo_hiperboloide1[i+48+64*6]=1;
  }
  //Nivel  2 y 5

}

void imprimir_planor(){
  plano_recto();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_planor[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
  }
  //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
  
  
}
void imprimir_planoi(){
  plano_inclinado();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_planoi[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
  }
  //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
  
  
}
void imprimir_cono(){
  cono();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_cono[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
  }
  //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
}
void imprimir_elipsoide(){
  elipsoide();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_elipsoide[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
  }
  //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
}
void imprimir_paraboloide(){
  paraboloide();
  startMillis = millis();
  int f =0;
   while(f==0)
    {
    int point=0;
    for(int i = 0; i < 8; i++)//CAPAS
    {
        //ACTIVAMOS ALTA IMPEDANCIA
        digitalWrite(in,HIGH);
        //DESACTIVAMOS LA TIERRA DE LA CAPA QUE ACTIVAMOS EN EL CICLO ANTERIOR
        digitalWrite(tierra[i-1],LOW);
    
        for(int j = 0; j < 8; j++)//FILAS
        {  
            for(int k = 0; k < 8; k++)//DATOS
            {
                //CARGAMOS EL DATO EN LA LINEA K
                digitalWrite(dato[k],areglo_paraboloide[point]);
                //MOVEMOS UNA POSCICION A LA DERECHA EN EL ARRAY CUBO
                point++;
            }
            //PULSO PARA CADA FLIP-FLOP
            digitalWrite(clock[j],HIGH);
            digitalWrite(clock[j],LOW);
        }

        //QUITAMOS ALTA IMPEDANCIA
        digitalWrite(in,LOW);
        //ACTIVAMOS LA TIERRA DE LA CAPA
        digitalWrite(tierra[i],HIGH);
        //delayMicroseconds(1600);
        delay(1);
  }
  //APAGAMOS LA ULTIMA CAPA
    digitalWrite(tierra[7],LOW);
    if (millis() - startMillis >= velocidad_formas)  //test whether the period has elapsed
    {
        f=1;
    }
    }
}
