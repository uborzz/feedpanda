/**  
 *
 *     ********************************************************
 *     ********************************************************
 *     ***                                                  ***
 *     ***                    FEEDPANDA                     ***
 *     ***                                                  ***
 *     ******************************************************** 
 *     ********************************************************

    Desc.  Juguete alimentador comida gatos, rollo wack a mole

/******************************************************************
 *                           Librerias                            *
 ******************************************************************/ 
#include <Servo.h>


/******************************************************************
 *                Definicion de las variables                     *
 ******************************************************************/

/*  Definicion de los pines de la placa que se van a usar         */
  #define pin_led1          1
  #define pin_boton1        2
  #define pin_led2          3  
  #define pin_boton2        4
  #define pin_sensor           10
  #define pin_servo            11
  #define speakerPin      12

  Servo servo;
  
  
  int i;
  int estado;
  int aciertos;
  int boton1;
  int boton2;
  int led1;
  int led2;  
  int sensor;
  int coin;

long tiempoActual;
long tiempoAnterior;


  long tiempoBoton;
/******************************************************************
 *                   Definicion de las funciones                  *
 ******************************************************************/  

void LucesON() {
    digitalWrite(pin_led1, HIGH);
    digitalWrite(pin_led2, HIGH);
}

void LucesOFF() {
    digitalWrite(pin_led1, LOW);
    digitalWrite(pin_led2, LOW);
}

void Luz1() { 
    digitalWrite(pin_led1, HIGH);
    digitalWrite(pin_led2, LOW); 
}

void Luz2() {
    digitalWrite(pin_led2, HIGH);
    digitalWrite(pin_led1, LOW);             
}

void sonidofail(){
      tone(speakerPin, 150);
      delay(120);
      tone(speakerPin, 100);
      delay(200);
      noTone(speakerPin);
      delay(50);
}

void sonidook(){
      tone(speakerPin, 330+aciertos*20);
      delay(150);
      noTone(speakerPin);
      delay(50);
}

void sonidostart(){
      tone(speakerPin, 560);
      delay(300);
      noTone(speakerPin);
      delay(10);
      tone(speakerPin, 545);
      delay(150);
      tone(speakerPin, 575);
      delay(400);
      noTone(speakerPin);
      delay(50);
}

void musicawin()
{
   for (int i = 0; i < 3; i++)
   {
      tone(speakerPin, 524);
      delay(150);
      noTone(speakerPin);
      delay(10);
   }
      tone(speakerPin, 524);
      delay(400);
      noTone(speakerPin);
      delay(10);

      tone(speakerPin, 415);
      delay(360);
      noTone(speakerPin);
      delay(10);

      tone(speakerPin, 466);
      delay(360);
      noTone(speakerPin);
      delay(10);

      tone(speakerPin, 524);
      delay(240);
      noTone(speakerPin);
      delay(20);
      

      tone(speakerPin, 466);
      delay(140);
      
     

      tone(speakerPin, 524);
      delay(500);
      noTone(speakerPin);
      delay(20);
}

void Juego()    {
   
    coin = random(1,3);
    tiempoAnterior = millis();
  
    while (1) {
      
      switch (coin)  {
      case 1: Luz1();  break;  
      case 2: Luz2();  break;    
      }

      boton1 = digitalRead(pin_boton1);
      boton2 = digitalRead(pin_boton2);

      if ((coin == 1 && boton1 == 1) || (coin == 2 && boton2 == 1)) {
       aciertos = aciertos+1;
       LucesOFF();
       if (aciertos >= 4) { aciertos = 0; estado = 3; return; }
       sonidook();
       delay(800);
       return;
      }       
      
      tiempoActual = millis();
      if (tiempoActual - tiempoAnterior >=tiempoBoton) {estado= 0; LucesOFF(); delay(1000); return;}
      if ((coin == 1 && boton2==1) || (coin ==2 && boton1 ==1)) {aciertos = 0;  LucesOFF(); sonidofail(); estado = 0; delay(1000); return;}
            
  }
}

 void Espera(){
  while (1){
    boton1 = digitalRead(pin_boton1);
    boton2 = digitalRead(pin_boton2);
    if (boton1==1 || boton2 ==1) {estado = 2;  sonidostart(); delay(100); return;}  
    } 
 }

  void Premio()  {
    
    LucesON();
    musicawin();
    
    //ACCIONAMIENTO-> Crear función
    //servo.write(115);delay(2000);
    //servo.write(90);delay(50);
        
        delay(3000); // Cooldown
        
        LucesOFF();
        delay(1000);
        estado=0;
  }


///******************************************************************
// *                             Setup                              *
// ******************************************************************/

void setup() 
{  

    servo.attach(pin_servo);

    randomSeed(analogRead(0));
    estado = 0;
    i=0;
    
    tiempoActual = 0;
    tiempoAnterior = 0;
    
    tiempoBoton = 5000; // 5 segundos.
    
    pinMode(pin_led1, OUTPUT);
    pinMode(pin_led2, OUTPUT);
    pinMode(pin_boton1, INPUT);
    pinMode(pin_boton2, INPUT);
    pinMode(pin_sensor, INPUT);
   
  
   servo.write(90);//ajustar offset
   delay(20);
   
}

//
///******************************************************************
// *                Bucle principal del programa                    *
// ******************************************************************/
 
void loop() 
{ 
  
  // Máquina de estados.

   switch(estado) {
     
     case 0:  Espera(); break;
     case 1:  break;
     case 2:  Juego(); break;
     case 3:  Premio(); break;
   }
   
    delay(10);

}

