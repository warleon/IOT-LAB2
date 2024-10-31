struct {
  unsigned int last=0;
  unsigned int current=0;
  unsigned int diff=0;
  const unsigned int irrigation=10;
  const unsigned int idle=15;

} time;
struct {
  const int HUMIDITY_PIN = A0;
  int humidity;
}input;
struct{
  const int RED_LED_PIN=2;
  const int BLUE_LED_PIN=3;
  const int RELAY_PIN=4;
  const int BUZZER_PIN=5;
}output;
struct{
  int humidity_percentage;
}computed;

void irrigationMode(){
  digitalWrite(output.BLUE_LED_PIN,0);
  digitalWrite(output.RELAY_PIN,0);
  delay(1000 * time.irrigation);
  digitalWrite(output.BLUE_LED_PIN,1);
  digitalWrite(output.RELAY_PIN,1);
}
void idleMode(){
  digitalWrite(output.BLUE_LED_PIN,1);
  digitalWrite(output.RELAY_PIN,1);
  Serial.println("Modo IDLE");
  delay(1000 * time.idle);
}
void alertMode(){
  digitalWrite(output.RED_LED_PIN,0);
  digitalWrite(output.BUZZER_PIN,0);
  delay(500);
  digitalWrite(output.RED_LED_PIN,1);
  digitalWrite(output.BUZZER_PIN,1);
  delay(500);
}

void mainLogic(){
  input.humidity=analogRead(input.HUMIDITY_PIN);
  computed.humidity_percentage= (float(1024 - input.humidity) / 1024.0f)*100.0f;
  Serial.print("Measured humidity: ");
  Serial.print(computed.humidity_percentage);
  Serial.println("%");
  if(computed.humidity_percentage<20){
    irrigationMode();
    idleMode();
  }
  else if(computed.humidity_percentage>80){
    alertMode();
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(input.HUMIDITY_PIN,INPUT);

  pinMode(output.BLUE_LED_PIN,OUTPUT);
  pinMode(output.BUZZER_PIN,OUTPUT);
  pinMode(output.RED_LED_PIN,OUTPUT);
  pinMode(output.RELAY_PIN,OUTPUT);

  digitalWrite(output.BLUE_LED_PIN,1);
  digitalWrite(output.BUZZER_PIN,1);
  digitalWrite(output.RED_LED_PIN,1);
  digitalWrite(output.RELAY_PIN,1);

  Serial.println("");
  time.current=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  time.last=time.current;
  time.current=millis();
  time.diff=time.current -time.last;
  

  mainLogic();
}