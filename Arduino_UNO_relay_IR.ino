   // Modulo Relee   
   // Conectamos el modulo de la siguiente forma:
   // GND -> GND
   // VDD -> 5V
   // IN  -> D2   

  #include <IRremote.h>

  const int recv_pin = 11;
  const int myRelee = 2;   // Declaramos la salida del relee (LOW encendido HIGH apagado)

  int actual_state = LOW;

    IRrecv irrecv(recv_pin);
    decode_results results;
    
    void setup(){
      // Relee
      pinMode(myRelee, OUTPUT); 
      // Declaramos que el pin sera salida
      // Preparamos el puerto serie
      Serial.begin(9600);
      irrecv.enableIRIn(); // inicio el IR para recibir codigos
      
      digitalWrite(myRelee, actual_state);
      Serial.println("Relee apagado");
    }

    void loop(){
      delay (2000);
      if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        if (results.value == 0xFFA25D) { // On/Off button
            /* cuando ingresa el comando por IR*/
            actual_state = (actual_state == LOW) ? HIGH : LOW;                        
            digitalWrite(myRelee, actual_state);
            Serial.println("Relee encendido");            
            /*fin relee*/
        }
        delay(1000);
        irrecv.resume(); // Recibe el proximo valor
      }     
      
    }
