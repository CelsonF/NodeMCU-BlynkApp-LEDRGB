
/*
 * Fita de LED RGB com NodeMCU(ESP8266-12E).
 *
 * Version 1.0
 *
 * Efeitos simples com seleção de paletas de cores , fadding e strobo(Flash) com  
 * fita de LED RGB(5050) / Não endereçavel no ESP8266-12E(NodeMCU).  
 *
 * Copyright 2018, Celson Fernando
 * 
 * Para maiores detalhes, veja http://www.youtube.com/watch?v=mSwRuOnOkTE
 * Add link you tube aqui
 *
 * @copyright     Copyright 2018, Celson Fernando, celson-araujo97@hotmail.com
 * Facebook
 * GitHub
 * 
 * @link          http://hgbrasil.com
 * 
 * Created on Hiperload.com - Simple share.
 */
#define BLYNK_PRINT Serial

//Cores da fita de LED , controlador de LED RGB ESP8266-12E (NODEMCU)
#define RED 15 // pino PWM D8 para a cor vermelha
#define GREEN 12 // pino PWM D7 para a cor verde
#define BLUE 13 // pino PWM D6 para a cor azul

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

//Aqui você coloca sua chave que foi disponibilizada no Blynk
char auth[] = "";

// Your WiFi credentials.
//Colocar endereço e senha do seu Wifi, o celular e o ESP precisam estar conectados a mesma rede.

//SSID(Nome da sua REDE) 
char ssid[] = "";

// Set password to "" for open networks.

//Senha da Sua Rede
char pass[] = "";

//função timer do blynk
BlynkTimer timer;

void setup()
{
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);

// Colocando os leds como Saidas
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

//Functions 


//função de desligar os Leds
void leds_desligados(){
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  }


//função de ligar todas as cores 
void led_ligado() {
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  }

//Se quiser pode colocar outras cores e adicionalos aos botões virtuais
//EXEMPLO:

/*
void led_purple() {
  analogWrite(RED, 255);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 255);
  }

*/


//Efeito de Flash(Piscar )
void strobo(){
  // Acende todas as cores juntas

  //Colocado FOR para aumentar a quantidade de vezes que o efeito ira se repetir
  // e os seguintes com delays menores
  //EXEMPLO

  //Se quiserem um padrão só podem comentar o segundo e terceiro FOR.
  //Mude o valor do delay para sua preferência 
  
 for (int i = 0; i <= 9; i++){ 
  //Acende todos as cores juntas (Branco)
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(250); 
  // Apaga todas as cores juntas (Preto)
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(250); }


  //2° FOR 
  //Acende todos as cores juntas (Branco)
  for (int i = 0; i <= 9; i++){ 
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(100); 
  // Apaga todas as cores juntas
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(100);
  }

  //3° FOR
  //Acende todos as cores juntas (Branco)
  for (int i = 0; i <= 9; i++){ 
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(50); 
  // Apaga todas as cores juntas
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(50);
 }
  // Como o delay é rápido, a fita da um efeito tipo strobo
}

//Efeito de Fadding passando por todas as cores
void fadding_cores(){
  
  // Declara as variáveis dos loops
  int r, g, b;
  
  // Fade do azul (ja estava aceso) até o violeta, adicionando o vermelho
  for(r = 1; r <= 255; r++){
    analogWrite(RED, r);
    delay(10);
  }
  
  // Fade do violeta até o vermelho, removendo o azul
  for(b = 255; b >= 1; b--){
    analogWrite(BLUE, b);
    delay(10);
  }
  
  // Fade do vermelho até o amarelo, adicionando o verde
  for(g = 1; g <= 255; g++){
    analogWrite(GREEN, g);
    delay(10);
  }
  
  // Fade do amarelo até o verde, removendo o vermelho
  for(r = 255; r >= 1; r--){
    analogWrite(RED, r);
    delay(10);
  }
  
  // Fade do verde até o turquesa, adicionando o azul
  for(b = 1; b <= 255; b++){
    analogWrite(BLUE, b);
    delay(10);
  }
  
  // Fade do turquesa até o azul, removendo o verde
  for(g = 255; g >= 1; g--){
    analogWrite(GREEN, g);
    delay(10);
  }
  // Em seguida o loop continua, com o azul aceso
}


BLYNK_WRITE(V5) // este é o número do pino virtual /pega valor inteiro e escreve na tela
{
  //Se o botão enviar 1
  if(param.asInt() == 1) {   // if Button sends 1
    //Ele começa a função
    led_ligado();           // start the function
  }
  else {
  leds_desligados();
  }
  }


BLYNK_WRITE(V6) {
  if (param.asInt() == 1) {
    strobo();
    }
  else {
    leds_desligados();
    }
  }


BLYNK_WRITE(V7) {
  if (param.asInt() == 1) {
    fadding_cores();
    }
    else {
      leds_desligados();
      }
  }

void loop()
{
  Blynk.run();

  timer.run(); // Initiates BlynkTimer
}



