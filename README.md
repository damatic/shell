# Ljuska u pokušaju...

Projekt za završni rad na fakultetu informacijske tehnologije, smjer programiranje.

Programira se u C programskom jeziku, compile se izvodi s gcc, a debug s gdb.

Program je u cijelosti "kompajliran". Ako bi se program na novo "kompajlirao" te bio spreman za pokretanje, potrebno je pokrenuti make file na dva mjesta, početnom "folderu" i u commands "folderu" s naredbom 'make clean', te zatim s naredbom 'make all'. Izvorni kod se "kompajlira" s argumentom -Wall, koje omogućuje "hvatanje" svih upozorenja i greški nastalih pri "kompajliranju". Potrebno je također promijeniti varijablu 'program_path' u main.c i postaviti na trenutnu putanju programa.


Ljuska trenutno ima 12 vlastitih programa koje može izvršiti a to su:
- cat - ispis datoteke na ekran
- chmod - promjena prava pristupa datotekama i direktorijima
- copy - kopiranje datoteka pojedinačno, ne i direktorija sa sadržajem
- list - ispis sadržaja direktorija, ispisuje većinu informacija
- mkd - stvaranje novog direktorija
- move - premještanje direktorija i datoteka na drugu lokaciju
- rm - brisanje datoteka ili praznih direktorija
- wc - ispis znakova/riječi/linija neke datoteke
- ps - ispis nekih informacija o trenutnim procesima, kao sto su PID, STATE, TTY i COMMAND
- kill - ubijanje procesa sa signalom SIGTERM ne sa SIGMKILL
- pipe - usmjeravanje izlaza jednog programa na ulaz drugoga
- head - ispis prvih 10 linija iz datoteke, moguće i preko pipe-a

Builtin programi/funkcije ljuske:
- exit - izlazak iz ljuske
- echo - ispis stringa ili sistemske varijable na ekran
- clear - čišćenje čitavog ekrana
- pwd - ispis trenutne putanje
- cdir - promjena trenutne putanje
- history - spremanje naredbi u datoteku, mogući pregled povijesti s strelicom za gore i dolje
- ph - ispis povijesti naredbi
- smart completion - završavanje imena datoteka/direktorija pomoću tab-a
