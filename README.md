# ⏱️ Timer1 Overflow Interrupt — Register-Level (Arduino UNO)

This project demonstrates how to use **Timer1 Overflow Interrupt** on the **ATmega328P (Arduino UNO)** to toggle an LED at precise intervals.  
The LED connected to **PB5 (Digital Pin 13)** toggles every 1 second using **register-level configuration** and **ISR**.

---

## ⚙️ Hardware Used
- Arduino UNO (ATmega328P)
- LED connected to pin **D13 (PB5)**
- 220Ω current-limiting resistor

---

## 🔌 Pin Configuration

| Component | Function | Arduino Pin | Port |
|-----------|-----------|-------------|------|
| LED       | Output    | D13         | PB5  |
| VCC       | Power     | +5V         | —    |
| GND       | Ground    | GND         | —    |

---

## 🧩 Code Explanation

### Registers Used
| Register | Purpose |
|-----------|----------|
| **TCCR1A / TCCR1B** | Configure Timer1 mode and prescaler |
| **TIMSK1** | Enable Timer1 overflow interrupt |
| **TCNT1** | Timer1 counter register — sets starting value |
| **SREG** | Global Interrupt Enable |

### Timer Configuration
- **Mode:** Normal Mode (WGM13:0 = 0)  
- **Prescaler:** 1024 (CS12 + CS10)  
- **Overflow Time:** ~1 second  
- **Output Pin:** PB5 → Arduino D13  

---

## ⚙️ Working Principle
1. Timer1 counts from **TCNT1 = 49910** to **65535**.  
2. When the counter overflows, **TIMER1_OVF_vect ISR** is triggered.  
3. Inside the ISR, the LED toggles using `PORTB ^= (1<<PB5)` and **TCNT1 is reset** to 49910 for the next 1-second interval.  
4. The **main loop** remains empty — all timing handled by the interrupt.

---

## 🔧 Code

```c
void setup()
{
  DDRB |= (1<<DDB5);  // PB5 as output

  // Enable global interrupts
  SREG |= (1<<7);

  // Enable Timer1 overflow interrupt
  TIMSK1 |= (1<<TOIE1);

  // Timer1 Normal Mode
  TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
  TCCR1B &= (~(1<<WGM12)) & (~(1<<WGM13));

  // Prescaler = 1024
  TCCR1B |= (1<<CS12) | (1<<CS10);
  TCCR1B &= (~(1<<CS11));

  // Set initial counter for 1-second overflow
  TCNT1 = 49910;
}

void loop()
{
  // Main loop does nothing; ISR handles toggling
}

// Timer1 Overflow ISR
ISR(TIMER1_OVF_vect)
{
  PORTB ^= (1<<PB5);  // Toggle LED
  TCNT1 = 49910;      // Reset counter for 1-second period
}
