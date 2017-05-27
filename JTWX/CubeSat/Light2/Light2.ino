const int analogInPin = 30;
const int analogOutPin = 4;

int sensorValue = 0;
int outputValue = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("LIGHT!");

  pinMode(analogInPin, INPUT);
  pinMode(analogOutPin, OUTPUT);

}

void loop() {

  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1024, 0, 255);
  if (outputValue < 0) outputValue = 0;
  analogWrite(analogOutPin, outputValue);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  delay(2);
}
