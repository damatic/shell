# Ljuska u pokušaju...

Projekt za završni rad na fakultetu informacijske tehnologije, smjer programiranje.

Programira se u C programskom jeziku, compile se izvodi s gcc, a debug s gdb.

Kako bi se program "kompajlirao" te bio spreman za pokretanje, potrebno je pokrenuti make file na dva mjesta,
početnom "folderu" i u commands "folderu" s naredbom 'make all'. Izvorni kod se "kompajlira" s argumentom -Wall,
koje omogućuje "hvatanje" svih upozorenja i greški nastalih pri "kompajliranju".

Ljuska trenutno ima 8 vlastitih programa koje može izvršiti a to su:
'''
cat - ispis datoteke na ekran
chmod - promjena prava pristupa datotekama i direktorijima
copy - kopiranje datoteka ("u izradi rekurzivno kopiranje direktorija koji nije prazan")
list - ispis sadržaja direktorija, ispisuje većinu informacija ("u izradi list program s argumentima za sažeto i detaljno ispisivanje")
mkd - stvaranje novog direktorija
move - premještanje direktorija na neko drugo mjesto
rm - brisanje datoteka ("u izradi rekurzivno brisanje skupa datoteka")
wc - ispis znakova/riječi/linija neke datoteke
'''


pipe - u izradi...

U izradi su i sljedeći programi i dodaci:
history -  spremanje naredbi u datoteku
kill - ubijanje procesa
list process - listanj trenutnih procesa
background process - stavljanje procesa u pozadinu
smart completion - nekakav način za pametno završavanje imena datoteka, direktorija...

