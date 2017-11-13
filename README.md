# Ljuska u pokušaju...

Projekt za završni rad na fakultetu informacijske tehnologije, smjer programiranje.

Programira se u C programskom jeziku, compile se izvodi s gcc, a debug s gdb.

Program je u cijelosti "kompajliran". Ako bi se program na novo "kompajlirao" te bio spreman za pokretanje, potrebno je pokrenuti make file na dva mjesta, početnom "folderu" i u commands "folderu" s naredbom 'make clean', te zatim s naredbom 'make all'. Izvorni kod se "kompajlira" s argumentom -Wall, koje omogućuje "hvatanje" svih upozorenja i greški nastalih pri "kompajliranju". Potrebno je također promijeniti varijablu 'program_path' u main.c i postaviti na trenutnu putanju programa.


Ljuska trenutno ima 13 vlastitih programa koje može izvršiti a to su:
- cat - ispis datoteke na ekran
- chmod - promjena prava pristupa datotekama i direktorijima
- copy - kopiranje datoteka pojedinacno, ne i direktorija sa sadrzajem
- list - ispis sadržaja direktorija, ispisuje većinu informacija ("u izradi list program s argumentima za sažeto i detaljno ispisivanje")
- mkd - stvaranje novog direktorija
- move - premještanje premjestanje direktorija i datoteka na drugu lokaciju
- rm - brisanje datoteka ili praznih direktorija
- wc - ispis znakova/riječi/linija neke datoteke
- ps - ispis nekih informacija o trenutnim procesima, kao sto su PID, STATE, TTY i COMMAND
- kill - ubijanje procesa sa signalom SIGTERM ne sa SIGMKILL
- pipe - usmjeravanje izlaza jednog programa na ulaz drugoga
- head - ispis prvih 10 linija iz datoteke, moguce i preko pipe-a
- smart completion - zavrsavanje imena datoteka/direktorija pomocu tab-a

Builtin programi/funkcije ljuske:
- exit - izlazak iz ljuske
- echo - ispis stringa ili sistemske varijable na ekran
- clear - čišćenje čitavog ekrana
- pwd - isis trenutne putanje
- cdir - promjena trenutne putanje
- history - spremanje naredbi u datoteku, moguce pregledavanje povijesti s strelicom za gore i dolje ("poboljsati brojac koji broji naredbe")


U izradi su i sljedeći programi i dodaci:
- background process - stavljanje procesa u pozadinu...
