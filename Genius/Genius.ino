/*
 * Código desenvolvido em 31/12/2019 por Rodrigo e Simone para o brinquedo Genius,
 * obedecendo o mesmo padrão de funcionamento do brinquedo original.
 * 
 * Durante o desenvolvimento, o foco sempre esteve na simplicidade e funcionalidade.
 * 
 * Para montar esse brinquedo, são necessários: 
 *    4 LEDS coloridos
 *    4 Botões
 *    1 Buzzer
 *    Vários jumpers e uma protoboard
 *    
 * Os leds foram todos ligados em pinos PWM pra ser possível montar o protótipo sem
 * a necessidade de resistores.
 * 
 * Os pinos dos botões estão todos configurados como INPUT_PULLUP, também dispensando o
 * uso de resistores adicionais.
 * 
 * Cada nota/botão/led é representado por um número inteiro de 1 a 4:
 *    1 - Verde
 *    2 - Amarelo
 *    3 - Vermelho
 *    4 - Azul
 */
/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/

  //Pinos dos LEDS - todos PWM
  #define led_vermelho 11
  #define led_azul 10
  #define led_amarelo 9
  #define led_verde 6
  
  //Pinos dos Botões
  #define botao_azul 12
  #define botao_vermelho 13
  #define botao_amarelo 8
  #define botao_verde 7
  
  //Pino do buzzer
  #define buzzer 5


/*
==============================================================================================================
CONSTANTES e VARIÁVEIS:
==============================================================================================================*/

  //Define o tempo em que cada nota toca quando a sequencia está sendo reproduzida. (menor = mais rápido)
  #define tempo_nota 500

  //Define qual o número máximo de notas criadas aleatoriamente
  #define quantas_notas 99
  
  //Inicializa as variáveis
  int notas[quantas_notas];
  int nivel_atual = 1;

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

  //Pinos dos LEDS e do Buzzer como saída
  pinMode(led_azul, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  //Pinos dos botões como entradas normalmente ligadas
  pinMode(botao_azul, INPUT_PULLUP);
  pinMode(botao_vermelho, INPUT_PULLUP);
  pinMode(botao_amarelo, INPUT_PULLUP);
  pinMode(botao_verde, INPUT_PULLUP);

  //Inicializa comunicação serial
  Serial.begin(9600);
  Serial.println("Começou!");

  //Define aleatoriamente a sequencia de notas. A sequencia de notas é um conjunto de valores inteiros de 1 a 4.
  randomSeed(analogRead(0));
  for (int x=0; x<quantas_notas; x++) {
      notas[x] = random(1,5);
    }


}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {


  joga(nivel_atual);       //função mais importante, veja abaixo.
  
  nivel_atual = nivel_atual+1;      //aumenta o nível, um por vez.
  
  delay(500);

  
}


/*==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/

void joga(int nivel) {
  //Reproduz a sequencia de notas até o nível atual
  for (int x=0; x<nivel; x++) {
    acende_toca(notas[x]);
    delay(tempo_nota/4); 
  }
  
  //Testa se o botão pressionado é o correto, caso positivo, reproduz a nota corresponde e passa para a nota seguinte
  for (int x=0; x<nivel; x++) {
     if (ler_botao()==notas[x]) {
        acende_toca(notas[x]);
        }
     else {
        perdeu();
            }
      }
   }


//Executada quando um botão incorreto é pressionado. (faz uns bips e acende os leds, quanto mais leds acesos, maior foi a pontuação obtida)
void perdeu() {
  
        tone(buzzer, 3000, 100);
        delay(100);
        tone(buzzer, 3000, 100);
        delay(100);
        tone(buzzer, 3000, 100);
        delay(100);
        tone(buzzer, 3000, 100);
        delay(100);
        Serial.println("Perdeu!");
        Serial.print("Nivel atingido: ");
        Serial.println(nivel_atual);
        if (nivel_atual>2) {
          analogWrite(led_verde, 200);
        }
        if (nivel_atual>5) {
          analogWrite(led_amarelo, 200);
        }
        if (nivel_atual>8) {
          analogWrite(led_vermelho, 200);
        }
        if (nivel_atual>11) {
          analogWrite(led_azul, 200);
        }
        while(true) {} //apenas para parar a execução do código
        
  }


//Espera um botão ser pressionado e retorna o número correspondente
int ler_botao() {
        
     while (true){   
        //Azul
        if (digitalRead(botao_azul) == LOW) {
          return 4;
          break;
        }
 
        //Vermelho
        else if (digitalRead(botao_vermelho) == LOW) {
          return 3;
          break;
        }
     
        //Amarelo
        else if (digitalRead(botao_amarelo) == LOW) {
          return 2;
          break;
        }

        //Verde
        else if (digitalRead(botao_verde) == LOW) {
          return 1;
          break;
        }

        }
}

//Acende o LED e toca o som correspondente a cada botão      
void acende_toca(int cor) {
        
        //Verde
        if (cor == 1) {
          analogWrite(led_verde, 200);
          tone(buzzer, 300, tempo_nota);
          delay(tempo_nota);
          analogWrite(led_verde, LOW);
        }  
      
        //Amarelo
        if (cor == 2) {
          analogWrite(led_amarelo, 255);
          tone(buzzer, 600, tempo_nota);
          delay(tempo_nota);
          analogWrite(led_amarelo, LOW);
        }  
      
        //Vermelho
        if (cor == 3) {
          analogWrite(led_vermelho, 255);
          tone(buzzer, 1200, tempo_nota);
          delay(tempo_nota);
          analogWrite(led_vermelho, LOW);
        }  
        
        //Azul
        if (cor == 4) {
          analogWrite(led_azul, 200);
          tone(buzzer, 2000, tempo_nota);
          delay(tempo_nota);
          analogWrite(led_azul, LOW);
        }
}


//Função para teste de hardware. Nela, ao pressionar o botão, o som correspondente toca e o LED acende.
void testa_hardware() {
  
  //Azul
  if (digitalRead(botao_azul) == LOW) {
    analogWrite(led_azul, 200);
    tone(buzzer, 2000, 10);
  }
  else {
    analogWrite(led_azul, LOW);
  }

  //Vermelho
  if (digitalRead(botao_vermelho) == LOW) {
    analogWrite(led_vermelho, 255);
    tone(buzzer, 1200, 10);
  }
  else {
    analogWrite(led_vermelho, LOW);
  }

  //Amarelo
  if (digitalRead(botao_amarelo) == LOW) {
    analogWrite(led_amarelo, 255);
    tone(buzzer, 600, 10);
  }
  else {
    analogWrite(led_amarelo, LOW);
  }

  //Verde
  if (digitalRead(botao_verde) == LOW) {
    analogWrite(led_verde, 200);
    tone(buzzer, 300, 10);
  }
  else {
    analogWrite(led_verde, LOW);
  }
}
