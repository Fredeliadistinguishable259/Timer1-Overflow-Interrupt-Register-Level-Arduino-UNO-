void setup()
{
  //Enable the Global Interrupt Enable bit
  SREG |= (1<<7);

  //Enable the Required Timer Interrupt
  TIMSK1 |= (1<<TOIE1);
  
  //Set Mode of the Timer
  TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
  TCCR1B &= (~(1<<WGM12)) & (~(1<<WGM13));

  //Set the Prescaler for the Timer
  TCCR1B |= (1<<CS12) | (1<<CS10);
  TCCR1B &= (~(1<<CS11));

  //Set the Period for the Timer
  TCNT1 = 49910; //1 Second
}

void loop()
{

}

//Implement the Interrupt Handler Function
ISR(TIMER1_OVF_vect)
{
  //User Code
  PORTB ^= (1<<PB5);
  TCNT1 = 49910;
}