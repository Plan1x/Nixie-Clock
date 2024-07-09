// Accelerating PWM frequency on D3 pin

void setup() 
{
Serial.begin(115200);

//pinMode(3, OUTPUT);

//TCCR2B = (TCCR2B & 0xF8) | 0x01;


}

void loop() 
{
if(Serial.available() > 0)
{
  Serial.println(Serial.read());
}

}
