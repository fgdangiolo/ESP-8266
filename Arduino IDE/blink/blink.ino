
/******************
 * Example: Blinky
 * Mini Wemos
 ***************** */

#define led_board 2
#define time_blink 100

void setup() {
  
  pinMode(led_board, OUTPUT);  // initialize D2 LED as output

}

void loop() {

  digitalWrite(led_board, HIGH);     // turn on LED 
  
  delay(time_blink);                // wait one second
  
  digitalWrite(led_board, LOW);      // turn off LED 
  
  delay(time_blink);                // wait one second
}
