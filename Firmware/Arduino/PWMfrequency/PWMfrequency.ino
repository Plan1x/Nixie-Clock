// Accelerating PWM frequency on D3 pin

void setup() 
{

pinMode(3, OUTPUT);

TCCR2B = (TCCR2B & 0xF8) | 0x01;


}

void loop() 
{

analogWrite(3, 150);

}
