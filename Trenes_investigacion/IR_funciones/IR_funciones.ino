#include <IRremote.h>

/* Pin de lectura IR Superior */
int ir_su = 11; 
// Led 
const int led = 9;

/* var de ir remote introduce el pin de lectura*/
IRrecv ir_rec(ir_su);
/* Aqui guarda los resultados - necesariamente la tiene que borrar! */
/* decode_results es una clase que tiene muchos datos dentro dentro*/
decode_results resultados;

// Var. para guardar resultados de lectura
int ir_res = 0;

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
  
  if( ir_res == -18127){
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
  else if (ir_res == 7622)
    Serial.println("Izq. Sup");
  else if (ir_res == 15494)
    Serial.println("Izq. Inf.");
  else if (ir_res == 19382)
    Serial.println("Der. Sup.");
  else if (ir_res == 9947)
    Serial.println("Der. inf.");
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
}
