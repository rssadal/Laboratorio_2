#define TIMER_INTERRUPT_DEBUG 2
#define _TIMERINTERRUPT_LOGLEVEL_ 0

#define USE_TIMER_1 true

#if (defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_BT) || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FEATHER328P) || defined(ARDUINO_AVR_METRO) || defined(ARDUINO_AVR_PROTRINKET5) || defined(ARDUINO_AVR_PROTRINKET3) || defined(ARDUINO_AVR_PROTRINKET5FTDI) || defined(ARDUINO_AVR_PROTRINKET3FTDI))
#define USE_TIMER_2 true
#warning Using Timer1, Timer2
#else
#define USE_TIMER_3 true
#warning Using Timer1, Timer3
#endif

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TimerInterrupt.h"
#include "sirene.h"
#include "botoes.h"
#include "joystick.h"
#include <LiquidCrystal.h>
#include "pitches.h"
#include "relogio.h"

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 13
#endif

#if USE_TIMER_1
//Comu zerial(3,4);
//timer base_tempo;
Sirene buzzer(9);
botoes button(7);
joystick joyXalto(A0, alto);
joystick joyXbaixo(A0, baixo);
joystick joyYalto(A1, alto);
joystick joyYbaixo(A1, baixo);
//DISPLAY
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Relogio relog(1000);

void TimerHandler1(unsigned int outputPin = LED_BUILTIN) {

  buzzer.base_tempo();
  button.tick();
  joyXalto.tick();
  joyXbaixo.tick();
  joyYalto.tick();
  joyYbaixo.tick();
  relog.tick();
  Serial.println(analogRead(A0));
}

#endif

#if (USE_TIMER_2 || USE_TIMER_3)

void TimerHandler(unsigned int outputPin = LED_BUILTIN) {

  //  zerial.processa_envio();
}

#endif

unsigned int outputPin1 = LED_BUILTIN;
unsigned int outputPin = A5;

#define USING_LOOP_TEST false

#define TIMER1_INTERVAL_MS 1
#define TIMER1_FREQUENCY (float)(1000.0f / TIMER1_INTERVAL_MS)

#define TIMER_INTERVAL_MS 100
#define TIMER_FREQUENCY (float)(1000.0f / TIMER_INTERVAL_MS)


#if USING_LOOP_TEST
#define TIMER1_DURATION_MS (10UL * TIMER1_INTERVAL_MS)
#define TIMER_DURATION_MS (20UL * TIMER_INTERVAL_MS)
#else
#define TIMER1_DURATION_MS 0
#define TIMER_DURATION_MS 0
#endif


void setup() {
  //base_tempo.timer_pool_init();
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  lcd.begin(16, 2);
  //lcd.print("Pessoal");
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.print(F("\nStarting TimerInterruptTest on "));
  Serial.println(BOARD_TYPE);
  Serial.println(TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = "));
  Serial.print(F_CPU / 1000000);
  Serial.println(F(" MHz"));

#if USE_TIMER_1

  // Timer0 is used for micros(), millis(), delay(), etc and can't be used
  // Select Timer 1-2 for UNO, 0-5 for MEGA
  // Timer 2 is 8-bit timer, only for higher frequency

  ITimer1.init();

  // Using ATmega328 used in UNO => 16MHz CPU clock ,

  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1, outputPin1, TIMER1_DURATION_MS)) {
    Serial.print(F("Starting  ITimer1 OK, millis() = "));
    Serial.println(millis());
  } else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

#endif

#if USE_TIMER_2

  ITimer2.init();

  if (ITimer2.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler, outputPin, TIMER_DURATION_MS)) {
    Serial.print(F("Starting  ITimer2 OK, millis() = "));
    Serial.println(millis());
  } else
    Serial.println(F("Can't set ITimer2. Select another freq. or timer"));

#elif USE_TIMER_3

  ITimer3.init();

  if (ITimer3.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler, outputPin, TIMER_DURATION_MS)) {
    Serial.print(F("Starting  ITimer3 OK, millis() = "));
    Serial.println(millis());
  } else
    Serial.println(F("Can't set ITimer3. Select another freq. or timer"));

#endif
}
byte tempo;
int estado_pisca;
int estado_botao = 0;
int teste = 0;
int estado_loop = 0;
int loop_hora, loop_min, desp_min, desp_hora = 1;

void loop() {

  lcd.setCursor(0, 1);
  if (relog.hora() < 10) {
    lcd.print("0");
  } else {
    lcd.print("");
  }
  lcd.print(relog.hora());
  lcd.print(":");
  if (relog.minuto() < 10) {
    lcd.print("0");
  } else {
    lcd.print("");
  }
  lcd.print(relog.minuto());
  buzzer.tick();

  switch (estado_loop) {
    case 0:
      if (button.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 20;
      }
      if(relog.hora()==desp_hora && relog.minuto()==desp_min){
        buzzer.liga(ligar_sirene);
      }
      if(joyYbaixo.status() == pressionado){
        buzzer.liga(desligar_sirene);
      }
      break;
    case 20:
      lcd.setCursor(0,0);
      lcd.print("Ajuste de horario");
      if (joyYbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 21;
        lcd.clear();
      }
      if (button.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 1;
      }
      break;
    case 21:
      lcd.setCursor(0,0);
      lcd.print("Despertador");
      if (joyYbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 20;
        lcd.clear();
      }
      if (button.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 10;
        loop_hora=desp_hora;
        loop_min=desp_min;
      }
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Ajuste de horario");
      lcd.setCursor(8, 1);
      lcd.print(loop_hora);
      lcd.print(":");
      lcd.print(loop_min);
      if (joyXalto.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_hora < 24) {
          loop_hora++;
        }
      }

      if (joyXbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_hora > 0) {
          loop_hora--;
        }
      }

      if (joyYbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 2;
      }
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Ajuste de horario");
      lcd.setCursor(8, 1);
      lcd.print(loop_hora);
      lcd.print(":");
      lcd.print(loop_min);
      if (joyXalto.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_min < 60) {
          loop_min++;
        }
      }

      if (joyXbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_min > 0) {
          loop_min--;
        }
      }

      if (joyYbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 0;
        lcd.clear();
        relog.ajuste(loop_hora, loop_min);
      }

      break;
    case 10:
      lcd.setCursor(0, 0);
      lcd.print("Despertador");
      lcd.setCursor(8, 1);
      lcd.print(loop_hora);
      lcd.print(":");
      lcd.print(loop_min);
      if (joyXalto.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_hora < 24) {
          loop_hora++;
        }
      }

      if (joyXbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_hora > 0) {
          loop_hora--;
        }
      }

      if (joyYbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        estado_loop = 11;
        lcd.clear();
      }

      break;
    case 11:
      lcd.setCursor(0, 0);
      lcd.print("Despertador");
      lcd.setCursor(8, 1);
      lcd.print(loop_hora);
      lcd.print(":");
      lcd.print(loop_min);
      if (joyXalto.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_min < 60) {
          loop_min++;
        }
      }

      if (joyXbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        if (loop_min > 0) {
          loop_min--;
        }
      }

      if (joyYbaixo.status() == pressionado) {
        buzzer.liga(ligar_bip);
        desp_min = loop_min;
        desp_hora = loop_hora;
        estado_loop = 0;
        lcd.clear();
      }

      break;
  }
}
