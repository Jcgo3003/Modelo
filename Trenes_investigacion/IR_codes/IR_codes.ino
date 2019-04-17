#include <IRremote.h>

/* Pin de lectura IR Superior */
int ir_su = 9; 

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
  Serial.println(ir_res);  
 
}

void loop() {
  if (ir_rec.decode(&resultados)) {
    dump(&resultados);
    ir_rec.resume(); // empezamos una nueva recepción
  }
  delay(200);
}
