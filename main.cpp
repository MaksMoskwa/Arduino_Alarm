
#include <Keypad.h>

#define ROZBROJONY 0
#define ZBROJENIE 1
#define UZBROJONY 2
#define ROZBRAJANIE 3
#define ALARM 4

#define PIR A0
#define BUZZER 10
#define LED_CZERWONA 11
#define LED_ZIELONA 12

const byte WIERSZE = 4;
const byte KOLUMNY = 4;

char klawisze[WIERSZE][KOLUMNY] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinyWierszy[WIERSZE] = {9, 8, 7, 6};
byte pinyKolumn[KOLUMNY] = {5, 4, 3, 2};

Keypad klawiatura = Keypad(
  makeKeymap(klawisze),
  pinyWierszy,
  pinyKolumn,
  WIERSZE,
  KOLUMNY
);

int stan = ROZBROJONY;

String poprawnyKod = "1234";
String wpisanyKod = "";

unsigned long czasStartu = 0;
unsigned long czasMigania = 0;

bool ledStan = false;

void obslugaKlawiatury() {

  char klawisz = klawiatura.getKey();

  if (klawisz) {

    if (klawisz == '#') {

      if (wpisanyKod == poprawnyKod) {

        Serial.println("Poprawny kod!");

        switch (stan) {

          case ROZBROJONY:
            stan = ZBROJENIE;
            czasStartu = millis();
            Serial.println("Rozpoczeto zbrojenie");
            break;

          case ZBROJENIE:
            stan = ROZBROJONY;
            Serial.println("Anulowano zbrojenie");
            break;

          case UZBROJONY:
            stan = ROZBRAJANIE;
            czasStartu = millis();
            Serial.println("Rozpoczeto rozbrajanie");
            break;

          case ROZBRAJANIE:
            stan = ROZBROJONY;
            Serial.println("Alarm rozbrojony");
            break;

          case ALARM:
            stan = ROZBRAJANIE;
            czasStartu = millis();
            Serial.println("Rozpoczeto rozbrajanie alarmu");
            break;
        }

      } else {
        Serial.println("Bledny kod");
      }

      wpisanyKod = "";
    }

    else if (klawisz == '*') {

      wpisanyKod = "";
      Serial.println("Wyczyszczono kod");

    }

    else if (klawisz >= '0' && klawisz <= '9') {

      if (wpisanyKod.length() < 4) {
        wpisanyKod += klawisz;
        Serial.println("Wpisywanie kodu");
      }
    }
  }
}

void uruchomAlarm() {

  if (millis() - czasMigania >= 300) {

    czasMigania = millis();
    ledStan = !ledStan;

    digitalWrite(LED_CZERWONA, ledStan);
    digitalWrite(LED_ZIELONA, ledStan);
    digitalWrite(BUZZER, ledStan);
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(PIR, INPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_CZERWONA, OUTPUT);
  pinMode(LED_ZIELONA, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_CZERWONA, LOW);
  digitalWrite(LED_ZIELONA, HIGH);

  Serial.println("SYSTEM ALARMOWY URUCHOMIONY");
  Serial.println("Wpisz kod i zatwierdz #");
}

void loop() {

  obslugaKlawiatury();

  switch (stan) {

    case ROZBROJONY:

      digitalWrite(BUZZER, LOW);
      digitalWrite(LED_CZERWONA, LOW);
      digitalWrite(LED_ZIELONA, HIGH);

      break;

    case ZBROJENIE:

      digitalWrite(LED_ZIELONA, HIGH);
      digitalWrite(LED_CZERWONA, LOW);
      digitalWrite(BUZZER, LOW);

      if (millis() - czasStartu >= 5000) {

        stan = UZBROJONY;

        Serial.println("ALARM UZBROJONY");
      }

      break;

    case UZBROJONY:

      digitalWrite(LED_ZIELONA, LOW);
      digitalWrite(LED_CZERWONA, HIGH);
      digitalWrite(BUZZER, LOW);

      if (digitalRead(PIR) == HIGH) {

        stan = ALARM;
        czasMigania = millis();
        ledStan = false;

        Serial.println("WYKRYTO RUCH! ALARM!");
      }

      break;

    case ROZBRAJANIE:

      digitalWrite(BUZZER, LOW);
      digitalWrite(LED_CZERWONA, LOW);
      digitalWrite(LED_ZIELONA, HIGH);

      if (millis() - czasStartu >= 3000) {

        stan = ROZBROJONY;

        Serial.println("SYSTEM ROZBROJONY");
      }

      break;

    case ALARM:

      uruchomAlarm();

      break;
  }
}
