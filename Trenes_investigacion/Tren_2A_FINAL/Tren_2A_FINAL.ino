/* TREN 2 A */
#include <IRremote.h>

/* Pin de lectura IR  */
int ir_su = 9; 
int ir_inf = 7; 
// Foto
const int foto = A0;
// Motor
const int motor = 3;

/* var de ir remote introduce el pin de lectura*/
IRrecv ir_rec(ir_su);
decode_results resultados;

// Var. para guardar resultados de lectura
int ir_res = 0;
int foto_val = LOW; 
int ir_val = LOW; 
int estado_motor = LOW;

void setup()
{
  // Comienzo serial 
  delay(500);
  Serial.begin(9600);
  // activa la lectura
  ir_rec.enableIRIn(); 
  // activando salida del led
  pinMode(motor , OUTPUT);
  Serial.println("INICIO ");
}

void dump(decode_results *resultados) {
  
  ir_res = resultados->value;
  
  // Main POWER
  if( (ir_res == -18127) || (ir_res == -18126)  ){
    
    // Funcion Motor
    if (estado_motor == LOW){    
        estado_motor = HIGH;
        digitalWrite(motor , HIGH);
        Serial.print("Power ");
        Serial.println(ir_res);
      }
    else{// Si motor prendido apagalo
      estado_motor = LOW;
      digitalWrite(motor , LOW);
    }
  }
  
  // POWER especifico TREN 2 A
  else if (ir_res == 19382){
    
    // Funcion Motor
    if (estado_motor == LOW){
        estado_motor = HIGH;
        digitalWrite(motor , HIGH);
        Serial.println("Power DER arriva ");
        Serial.println(ir_res);
      }
    else{// Si led prendido apagalo
      estado_motor = LOW;
      digitalWrite(motor , LOW);
    }
    
  }
  else 
    Serial.println("Desconocido");
  

}

void loop() {
  
  if (ir_rec.decode(&resultados)) {
    dump(&resultados);
    ir_rec.resume(); // empezamos una nueva recepción
  }
  delay(200);
  
  // Stop en estacion
  foto_val = analogRead(foto);
  
  if ( (foto_val > 150) && (estado_motor == HIGH)){
    estado_motor = LOW;
    digitalWrite(motor , LOW);
    Serial.println("fotosensor ");
    delay(3500);
    estado_motor = HIGH;
    digitalWrite(motor , HIGH);
    delay(500);
  }

  // Stop cuando cerca de otro tren
  ir_val = digitalRead(ir_inf);  
  if ( (ir_val == HIGH ) && (estado_motor == HIGH)){
    estado_motor = LOW;
    Serial.println("Ir frontal ");
    digitalWrite(motor , LOW);
    delay(1500);
    estado_motor = HIGH;
    digitalWrite(motor , HIGH);
  } 
  
}
