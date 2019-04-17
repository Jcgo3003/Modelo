#include <IRremote.h>

/* Pin de lectura IR Superior */
int ir_su = 11; 

/* var de ir remote introduce el pin de lectura*/
IRrecv ir_rec(ir_su);
/* Aqui guarda los resultados - necesariamente la tiene que borrar */
decode_results resultados;

// Var. para guardar resultados de lectura
int ir_res = 0;

void setup()
{
  // Comienzo serial 
  Serial.begin(9600);
  // activa la lectura
  ir_rec.enableIRIn(); 
}

void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()

  ir_res = results->value;
  Serial.print("El valor del boton es ");
  Serial.println(ir_res);  
  Serial.println("El boton que presionaste es ");
  
  if( ir_res == -18127)
    Serial.println("POWER");
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
  Serial.println("Esta es una nueva funcion");
  Serial.print("El valor de ir_res es ");
  Serial.println(ir_res);
  
  if (ir_rec.decode(&resultados)) {
    dump(&resultados);
    ir_rec.resume(); // empezamos una nueva recepción
  }
  delay(300);
}
