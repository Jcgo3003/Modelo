#include <IRremote.h>
/* Pin de lectura */
int RECV_PIN = 11; 

/* var de ir remote introduce el pin de lectura*/
IRrecv irrecv(RECV_PIN);
/* Otra var de ir remote para deco resultados */
decode_results results;

void setup()
{
  // Comienzo serial 
  Serial.begin(9600);
  // activa la lectura
  irrecv.enableIRIn(); // Empezamos la recepción  por IR
}

// funcion para leer resultados de ir
// utiliza una funcion para leer los resultados y la asigna a *results
void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()

  // imprime esto
  Serial.print("(");
  
  Serial.print(results->bits, DEC);
  Serial.print(" bits)");
  
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");

  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501 ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (HEX) , ");
  Serial.print(results->value, BIN);
  Serial.println(" (BIN)");

}

void loop() {
  if (irrecv.decode(&results)) {
    dump(&results);
    irrecv.resume(); // empezamos una nueva recepción
  }
  delay(300);
}
