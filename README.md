🔐 System alarmowy Arduino – czujnik PIR i klawiatura 4x4
📌 Opis projektu

Projekt przedstawia prosty system alarmowy oparty na platformie Arduino, wykorzystujący czujnik ruchu PIR, klawiaturę matrycową 4x4, buzzer oraz diody LED.

System umożliwia uzbrajanie i rozbrajanie alarmu za pomocą indywidualnego kodu PIN. Cała logika działania została oparta na maszynie stanów (State Machine), wykorzystującej instrukcję switch case.

Po wpisaniu poprawnego kodu alarm rozpoczyna proces uzbrajania. Użytkownik ma wtedy 5 sekund na opuszczenie chronionego obszaru. Po upływie tego czasu system przechodzi w stan uzbrojony i reaguje na wykrycie ruchu przez czujnik PIR.

W przypadku wykrycia ruchu uruchamiany jest alarm dźwiękowy i świetlny.

⚙️ Wykorzystane komponenty
Arduino (np. Arduino Uno)
Czujnik ruchu PIR
Klawiatura matrycowa 4x4
Buzzer piezoelektryczny
Czerwona dioda LED
Zielona dioda LED
Rezystory do diod LED
Przewody połączeniowe
Płytka stykowa
🔌 Podłączenie elementów
Element	Pin Arduino
Czujnik PIR	A0
Buzzer	10
Czerwona dioda LED	11
Zielona dioda LED	12
Klawiatura – wiersz 1	9
Klawiatura – wiersz 2	8
Klawiatura – wiersz 3	7
Klawiatura – wiersz 4	6
Klawiatura – kolumna 1	5
Klawiatura – kolumna 2	4
Klawiatura – kolumna 3	3
Klawiatura – kolumna 4	2

Uwaga: Diody LED należy podłączyć przez odpowiednie rezystory ograniczające prąd.

🔄 Stany systemu alarmowego

System wykorzystuje pięć stanów zdefiniowanych za pomocą #define.

Stan	Wartość	Opis
ROZBROJONY	0	Alarm jest wyłączony. Zielona dioda świeci.
ZBROJENIE	1	Trwa 5-sekundowe odliczanie przed uzbrojeniem alarmu.
UZBROJONY	2	System monitoruje pomieszczenie za pomocą czujnika PIR.
ROZBRAJANIE	3	Trwa proces rozbrajania alarmu.
ALARM	4	Buzzer wydaje dźwięk, a diody LED migają.
Schemat działania
text
       ROZBROJONY
            |
        Poprawny PIN
            |
            v
        ZBROJENIE
         (5 sek.)
            |
            v
        UZBROJONY
            |
      Wykrycie ruchu
            |
            v
          ALARM
            |
       Poprawny PIN
            |
            v
       ROZBRAJANIE
         (3 sek.)
            |
            v
       ROZBROJONY

1. ROZBROJONY
System alarmowy jest nieaktywny.
Czujnik PIR nie wywołuje alarmu.
Zielona dioda LED świeci.
Wpisanie poprawnego kodu i zatwierdzenie klawiszem # rozpoczyna proces uzbrajania.
2. ZBROJENIE
Rozpoczyna się 5-sekundowe odliczanie.
Użytkownik może w tym czasie swobodnie poruszać się po pomieszczeniu.
Po upływie 5 sekund system automatycznie przechodzi do stanu UZBROJONY.
Możliwe jest anulowanie zbrojenia poprzez ponowne wpisanie poprawnego kodu.
3. UZBROJONY
System aktywnie monitoruje pomieszczenie.
Czujnik PIR wykrywa ruch.
W przypadku wykrycia ruchu system automatycznie przechodzi do stanu ALARM.
Czerwona dioda LED sygnalizuje uzbrojenie systemu.
4. ROZBRAJANIE
Po wpisaniu poprawnego kodu podczas uzbrojenia rozpoczyna się proces rozbrajania.
Trwa on 3 sekundy.
Po upływie tego czasu system przechodzi do stanu ROZBROJONY.
5. ALARM
Uruchamiany jest buzzer piezoelektryczny.
Czerwona i zielona dioda LED migają.
Alarm działa do momentu wpisania poprawnego kodu PIN.
Poprawny kod rozpoczyna proces rozbrajania.
🔑 Obsługa klawiatury

System wykorzystuje czterocyfrowy kod PIN.

Domyślny kod:

text
1234


Sposób obsługi:

Wpisz czterocyfrowy kod na klawiaturze.
Naciśnij #, aby zatwierdzić kod.
Jeśli kod jest poprawny, system wykona odpowiednią operację zależną od aktualnego stanu.
Jeśli kod jest niepoprawny, system wyświetli komunikat o błędzie w monitorze portu szeregowego.

Dodatkowe funkcje klawiatury:

# – zatwierdzenie wpisanego kodu.
* – wyczyszczenie aktualnie wpisywanego kodu.
0-9 – wprowadzanie cyfr kodu.
💻 Wykorzystane technologie i funkcje

Projekt został napisany w języku C++ z wykorzystaniem środowiska Arduino IDE.

Najważniejsze elementy programu:

#define – definiowanie nazw stanów oraz pinów Arduino.
switch case – obsługa przechodzenia pomiędzy stanami systemu.
millis() – odmierzanie czasu bez blokowania działania programu.
digitalRead() – odczytywanie sygnału z czujnika PIR.
digitalWrite() – sterowanie diodami LED i buzzerem.
Keypad.h – obsługa klawiatury matrycowej 4x4.
String – przechowywanie i porównywanie wpisywanego kodu PIN.
📚 Wymagana biblioteka

Do poprawnego działania projektu wymagana jest biblioteka:

Keypad

Można ją zainstalować w Arduino IDE poprzez:

Szkic → Dołącz bibliotekę → Zarządzaj bibliotekami

Następnie wyszukaj bibliotekę Keypad i zainstaluj ją.

🚀 Uruchomienie projektu
Podłącz wszystkie komponenty zgodnie z tabelą połączeń.
Otwórz kod projektu w Arduino IDE.
Zainstaluj bibliotekę Keypad.
Wybierz odpowiednią płytkę Arduino i port COM.
Wgraj program do mikrokontrolera.
Otwórz Monitor portu szeregowego i ustaw prędkość 9600 baud.
Wpisz kod PIN 1234 i zatwierdź klawiszem #.

System jest gotowy do działania.

🎯 Cel projektu

Celem projektu jest stworzenie prostego systemu alarmowego oraz praktyczne wykorzystanie programowania mikrokontrolerów Arduino.

Projekt pozwala zapoznać się z:

Obsługą czujników ruchu PIR.
Obsługą klawiatury matrycowej.
Sterowaniem sygnalizacją świetlną i dźwiękową.
Wykorzystaniem instrukcji switch case.
Implementacją maszyny stanów (State Machine).
Wykorzystaniem funkcji millis() do kontroli czasu.
Tworzeniem prostych systemów zabezpieczeń.
