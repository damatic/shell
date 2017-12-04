# Ljuska u pokušaju...

Projekt za završni rad na fakultetu informacijske tehnologije, smjer programiranje.

Programira se u C programskom jeziku, compile se izvodi s gcc, a debug s gdb.


Ljuska ima 13 vlastitih programa koje može izvršiti a to su:
- cat - ispis datoteke na ekran
- chmod - promjena prava pristupa datotekama i direktorijima
- copy - kopiranje datoteka pojedinačno, ne i direktorija sa sadržajem
- list - ispis sadržaja direktorija, ispisuje većinu informacija
- mkd - stvaranje novog direktorija
- mkf - stvaranje nove datoteke
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


Instaliranje Linux ljuske Slash

Za instaliranje Linux ljuske Slash potrebno je pokrenuti prevođenje pomoću naredbe make all
i to u direktoriju ./shell te u direktoriju ./shell/commands. Nakon izvršavanja naredbi,
u direktoriju ./shell stvori se izvršna datoteka shell_start koja se pokreće naredbom
./shell_start. Naredba ./shell_start pokreće Linux ljusku Slash. Prevođenje vanjskih
naredbi se izvršava pokretanjem naredbe make all iz direktorija ./shell/commands.
Prevedene izvršne datoteke smještene su u direktorij ./shell/obj_output.


