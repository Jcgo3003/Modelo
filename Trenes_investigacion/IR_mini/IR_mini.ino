#include <IRremote.h>

/* Pin de lectura IR Superior */
int ir_su = 9; 
/* Pin de lectura IR Inferior */
int ir_inf = 7; 
// Foto
const int foto = 5;
// Led 
const int led = 3;


/* var de ir remote introduce el pin de lectura*/
IRrecv ir_rec(ir_su);
/* Aqui guarda los resultados - necesariamente la tiene que borrar! */
/* decode_results es una clase que tiene muchos datos dentro dentro*/
decode_results resultados;

// Var. para guardar resultados de lectura
int ir_res = 0;
int foto_val = LOW; 
int ir_val = LOW; 
int estado_led = LOW;  

void setup()
{
  // Comienzo serial 
  Serial.begin(9600);
  // activa la lectura
  ir_rec.enableIRIn(); 
  // activando salida del led
  pinMode(led , OUTPUT);
  
}

void dump(decode_results *resultados) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()

  ir_res = resultados->value;
  Serial.print("El valor del boton es ");
  Serial.println(ir_res);  
  Serial.println("El boton que presionaste es ");
  // Main POWER
  if( ir_res == -18127){
    // Funcion led
    Serial.println("POWER");
    // Si led apagado prendelo
    if (estado_led == LOW){
        Serial.println("On");
        estado_led = HIGH;
        digitalWrite(led , HIGH);
      }
    else{// Si led prendido apagalo
      Serial.println("Off");
      estado_led = LOW;
      digitalWrite(led , LOW);
    }
  }
  // POWER especifico TREN 1 A
  else if (ir_res == 19382){
    Serial.println("Der. Sup.");
    // Funcion led
    Serial.println("POWER");
    // Si led apagado prendelo
    if (estado_led == LOW){
        Serial.println("On");
        estado_led = HIGH;
        digitalWrite(led , HIGH);
      }
    else{// Si led prendido apagalo
      Serial.println("Off");
      estado_led = LOW;
      digitalWrite(led , LOW);
    }
  }
  else 
    Serial.println("Desconocido");
  

}

void loop() {
//  Serial.println("Esta es una nueva funcion");
//  Serial.print("El valor de ir_res es ");
//  Serial.println(ir_res);
  
  if (ir_rec.decode(&resultados)) {
    Serial.print("El valor de resultados es ");
    dump(&resultados);
    ir_rec.resume(); // empezamos una nueva recepción
  }
  delay(300);

  foto_val = digitalRead(foto);  
  if ( (foto_val == HIGH ) && (estado_led == HIGH)){
    estado_led = LOW;
    digitalWrite(led , LOW);
    Serial.println("Stop por foto led");
    Serial.println("Off");
    delay(3000);
    estado_led = HIGH;
    digitalWrite(led , HIGH);
    delay(2000);
    Serial.println("ARRANCANDO ");
    Serial.println("On");
  }

  ir_val = digitalRead(ir_inf);  
  if ( (ir_val == HIGH ) && (estado_led == HIGH)){
    estado_led = LOW;
    digitalWrite(led , LOW);
    Serial.println("Stop por ir inf");
    Serial.println("Off");
    delay(3000);
    estado_led = HIGH;
    digitalWrite(led , HIGH);
    Serial.println("ARRANCANDO ");
    Serial.println("On");
  }
 
  
}
