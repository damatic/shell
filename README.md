# Ljuska u pokušaju...

Projekt za završni rad na fakultetu informacijske tehnologije, smjer programiranje.

Programira se u C programskom jeziku, compile se izvodi s gcc, a debug s gdb.

Program je u cijelosti "kompajliran". Ako bi se program na novo "kompajlirao" te bio spreman za pokretanje, potrebno je pokrenuti make file na dva mjesta,
početnom "folderu" i u commands "folderu" s naredbom 'make clean', te zatim s naredbom 'make all'. Izvorni kod se "kompajlira" s argumentom -Wall,
koje omogućuje "hvatanje" svih upozorenja i greški nastalih pri "kompajliranju". Potrebno je također promijeniti varijablu 'program_path' u main.c i postaviti na trenutnu putanju programa.

Ljuska trenutno ima 8 vlastitih programa koje može izvršiti a to su:
- cat - ispis datoteke na ekran
- chmod - promjena prava pristupa datotekama i direktorijima
- copy - kopiranje datoteka ("u izradi rekurzivno kopiranje direktorija koji nije prazan")
- list - ispis sadržaja direktorija, ispisuje većinu informacija ("u izradi list program s argumentima za sažeto i detaljno ispisivanje")
- mkd - stvaranje novog direktorija
- move - premještanje direktorija na neko drugo mjesto
- rm - brisanje datoteka ("u izradi rekurzivno brisanje skupa datoteka")
- wc - ispis znakova/riječi/linija neke datoteke
- history -  spremanje naredbi u datoteku
- ps - ispis nekih informacija o trenutnim procesima, zasad rade samo ispis PID i CMD
- kill - ubijanje procesa sa signalom SIGTERM ne sa SIGMKILL
- pipe - usmjeravanje file descriptora radi, problem je citanje u drugom programu sa stdin-a...

U izradi su i sljedeći programi i dodaci:
- background process - stavljanje procesa u pozadinu
- smart completion - nekakav način za pametno završavanje imena datoteka, direktorija...

