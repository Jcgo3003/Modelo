#include <IRremote.h> 
int RECV_PIN = 9; //declaramos el pin que recibira la señal 
IRrecv irrecv(RECV_PIN); 
decode_results resultados; 

int ir_res = 0;

void setup() { 
Serial.begin(9600); //inicializamos el puerto serial a 9600 
irrecv.enableIRIn(); // Comienza a recibir los datos 
} 

void loop() { 
if (irrecv.decode(&resultados)) { 
ir_res = resultados.value;
Serial.print("Numero  ");
Serial.print(ir_res);
Serial.print(" HEX ");
Serial.println(resultados.value, HEX);
irrecv.resume(); // Se preparar para recibir el siguiente valor 
delay(10); 
} 
}
