const int buttonPin1 = 2; 
const int buttonPin2 = 3; 
const int buttonPin3 = 4; 
const int buttonPin4 = 5; 
const int buttonPin5 = 6; 
const int buttonPin6 = 7; 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);  
  pinMode(buttonPin2, INPUT);  
  pinMode(buttonPin3, INPUT);  
  pinMode(buttonPin4, INPUT);  
  pinMode(buttonPin5, INPUT);  
  pinMode(buttonPin6, INPUT);  
}

void loop(){
  if (digitalRead(buttonPin1) == HIGH) {Serial.println("1"); }  
  if (digitalRead(buttonPin2) == HIGH) {Serial.println("2"); }  
  if (digitalRead(buttonPin3) == HIGH) {Serial.println("3"); }  
  if (digitalRead(buttonPin4) == HIGH) {Serial.println("4"); }  
  if (digitalRead(buttonPin5) == HIGH) {Serial.println("5"); }  
  if (digitalRead(buttonPin6) == HIGH) {Serial.println("6"); }
  delay(100);  
}
