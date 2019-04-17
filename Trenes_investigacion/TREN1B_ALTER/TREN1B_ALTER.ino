/* TREN 1 B Tiene un sensor foto menos sencible ajustar segun el caso*/
/* Este tren ha sido modificado para recibir la senal del Ir_inf por un puerto analogico A 2 para asi poder controlar 
su sencibilidad a la cercania de otros trenes, es el primero en recibir esta actualizacion todos excepto el 2 b seran modificados
de la misma manera
Modifique el tiempo de espera a 7 segundos para darle tiempo a los PIR de autoajustarse*/
#include <IRremote.h>

/* Pin de lectura IR  */
int ir_su = 9; 
int ir_inf = A2; 
// Foto
const int foto = A0;
// Motor
const int motor = 3;

/* var de ir remote introduce el pin de lectura*/
IRrecv ir_rec(ir_su);
decode_results resultados;

// Var. para guardar resultados de lectura
int ir_res = 0;
int foto_val = 0; 
int ir_val = 0; 
int estado_motor = LOW;

void setup()
{
  // Comienzo serial 
  delay(700);
  Serial.begin(9600);
  // activa la lectura
  ir_rec.enableIRIn(); 
  // activando salida del led
  pinMode(motor , OUTPUT);
  Serial.println("INICIO");
  Serial.print("Estado motor  ");
  Serial.println(estado_motor);
}


void loop() {
  
  if (ir_rec.decode(&resultados)) {
      ir_res = resultados.value;


     // Main POWER
  if( (ir_res == -18127  ) || (ir_res == -18126)  ){
    
    // Funcion Motor
    if (estado_motor == LOW){    
        estado_motor = HIGH;
        digitalWrite(motor , HIGH);
        Serial.print("Power ");
        Serial.println(ir_res);
        Serial.print("Estado motor  ");
        Serial.println(estado_motor);
      }
    else{// Si motor prendido apagalo
      estado_motor = LOW;
      digitalWrite(motor , LOW);
      Serial.print("Estado motor  ");
      Serial.println(estado_motor);
    }
  }
  
  // POWER especifico TREN 1 B
  else if (ir_res == 15494 ){
    
    // Funcion Motor
    if (estado_motor == LOW){
        estado_motor = HIGH;
        digitalWrite(motor , HIGH);
        Serial.println("Power DER arriva ");
        Serial.println(ir_res);
        Serial.print("Estado motor  ");
        Serial.println(estado_motor);
      }
    else{// Si led prendido apagalo
      estado_motor = LOW;
      digitalWrite(motor , LOW);
        Serial.println("Estado motor  ");
        Serial.print(estado_motor);
    }
    
  }
  else 
    Serial.println("Desconocido");

    ir_rec.resume(); // empezamos una nueva recepción
  
  }
  ////delay(200);

  // Stop en estacion
  foto_val = analogRead(foto);

  Serial.println(foto_val);
  
  if ( (foto_val > 200) && (estado_motor == HIGH)){
    estado_motor = LOW;
    digitalWrite(motor , LOW);
    Serial.println("fotosensor");
    Serial.print("Estado motor  ");
    Serial.println(estado_motor);
    delay(7000);
    estado_motor = HIGH;
    digitalWrite(motor , HIGH);
    Serial.println("Estado motor  ");
    Serial.print("Estado motor  ");
    Serial.println(estado_motor);
    delay(1000);
  }

  // Stop cuando cerca de otro tren
  ir_val = analogRead(ir_inf);  
  if ( (ir_val > 500 ) && (estado_motor == HIGH)){
    estado_motor = LOW;
    Serial.println("Ir frontal ");
    digitalWrite(motor , LOW);
    Serial.print("Estado motor  ");
    Serial.println(estado_motor);
    delay(1500);
    estado_motor = HIGH;
    digitalWrite(motor , HIGH);
    Serial.print("Estado motor  ");
    Serial.println(estado_motor);
  } 
  
}
