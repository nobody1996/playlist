// Playlist-Verwaltung
// Rahmenprogramm
// Status: UnvollstÃĪndig

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

enum { STRLEN = 100 };
enum { PLLEN = 100 };
typedef char string[PLLEN];

/* Beginn Teilaufgabe a) */
typedef struct {
	string interpret;
	string titel;
	short jahr;
	short minuten;
	short sekunden;

} Song;
/* Ende Teilaufgabe a) */


/* --- Vorgebene Funktionen, nicht aendern --- */

/* Diese Funktion gibt einen zufaelligen Index
zwischen 0 und laenge-1 zurueck */
int zufallsIndex(int laenge) {
	return (int)rand() % laenge;
}

int laden(Song *playlist) {

	FILE* fin = NULL;
	int n = 0;

	if ((fin = fopen("playlist.dat", "rb")) != NULL) {
		while (fread(&(playlist[n]), sizeof(Song), 1, fin) > 0 && n < PLLEN)
			n++;
		printf("\nDatensaetze geladen!\n\n");
		fclose(fin);
	}
	else {
		printf("\nDerzeit sind keine Datensaetze gespeichert!\n\n");
	}

	return n;
}

void speichern(Song *playlist, int laenge) {

	FILE* fout = NULL;

	if ((fout = fopen("playlist.dat", "wb")) != NULL) {
		fwrite(playlist, sizeof(Song), laenge, fout);
		printf("\nDatensaetze gespeichert!\n\n");
		fclose(fout);
	}
	else {
		printf("\nSpeichern fehlgeschlagen\n\n");
	}
}
/* --- Ende der vorgebenen Funktionen --- */


/* Beginn Teilaufgabe b) */

/* Diese Funktion liest alle Attribute eines Songs
aus der Kommandozeile und gibt einen struct vom Typ Song zurueck */
Song einlesen( Song *playlist, int laenge ) {	
	Song neu;
	printf("\nim folgenden Format song eingeben: \nInterpret Titel Jahr minuten Sekunden (Leerzeichen im Titel/Interpret durch '_' ersetzen!)\n");
	scanf("%s %s %hu %hu %hu", neu.interpret, neu.titel, &neu.jahr, &neu.minuten, &neu.sekunden);
	printf("Eingelesen wurde: %s - %s, %hu, %hu:%hu", neu.interpret, neu.titel, neu.jahr, neu.minuten, neu.sekunden);

	if (laenge < PLLEN) {
		playlist[laenge] = neu;
	}

	return neu;
}


/* Diese Funktion gibt alle Attribute eines Songs aus */
void ausgeben( Song *song, int i ) {
	for (int a = 0; a < i; a++) {
		printf("\n%2d: %s - %s, %hu, %hu:%hu", a, song[a].interpret, song[a].titel, song[a].jahr, song[a].minuten, song[a].sekunden);
	}
}
/* Ende Teilaufgabe b) */


/* Beginn Teilaufgabe c) */
 int loeschen( Song *playlist, int laenge ){
	int pos;
	printf("Welche Song moechten sie Loeschen?\nID:");
	scanf("%d", &pos);
	for (;pos < laenge-1;pos++) {
		playlist[pos] = playlist[pos + 1];
	}
	laenge--;
	return laenge;
}
/* Ende Teilaufgabe c) */


/* Beginn Teilaufgabe d) */
void shuffle( Song *playlist, int laenge ) {
	int zufall1;
	int zufall2;
	for (int i = 0;i < laenge; i++) {
		zufall1 = zufallsIndex(laenge);
		zufall2 = zufallsIndex(laenge);
		playlist[laenge + 1] = playlist[zufall1];
		playlist[zufall1] = playlist[zufall2];
		playlist[zufall2] = playlist[laenge + 1];
	}

}
/* Ende Teilaufgabe d) */


/* Beginn Teilaufgabe e) */
int jahrSuchen( Song *playlist, int laenge ) {
	short jahr;
	int anzahl1 = 0;
	printf("Nach welchem Jahr Suchen sie?: ");
//	printf("%hu ", playlist[0].jahr);
	scanf("%hu", &jahr);
	for (int i = 0; i < laenge; i++) {
//		printf("%d ", playlist[i].jahr);
		if (playlist[i].jahr == jahr){
			printf("\n%2d: %s - %s, %hu, %hu:%hu", i, playlist[i].interpret, playlist[i].titel, playlist[i].jahr, playlist[i].minuten, playlist[i].sekunden);
			anzahl1++;
		}
	}
	return anzahl1;
}
/* Ende Teilaufgabe e) */


/* Beginn Teilaufgabe f) */
int interpretSuchen( Song *playlist, int laenge ) {
	string interpret;
	int anzahl = 0;
	printf("Nach welchem Interpreten Suchen sie? (Leerzeichen durch '_' ersetzen) : ");
	scanf("%s", interpret);
	for (int i = 0; i < laenge; i++) {
		if (strcmp(playlist[i].interpret, interpret) == 0) {
			printf("\n%2d: %s - %s, %hu, %hu:%hu", i, playlist[i].interpret, playlist[i].titel, playlist[i].jahr, playlist[i].minuten, playlist[i].sekunden);
			anzahl++;
		}
	}
	return anzahl;
}
/* Ende Teilaufgabe f) */


int main(void) {

	Song playlist[PLLEN];
	int laenge = 0, fertig = 0;
	char eingabe;
	int anzahl1;
	int anzahl2;
	Song save;
	

	srand(time(NULL));

	while (!fertig) {
		printf("\nl: laden\n");
		printf("s: speichern\n");
		printf("e: einlesen\n");
		printf("d: loeschen\n");
		printf("a: ausgeben\n");
		printf("m: mischen\n");
		printf("j: jahr suchen\n");
		printf("i: interpret suchen\n");
		printf("b: beenden\n\n");
		printf("Eingabe: ");
		scanf(" %c", &eingabe);
		
		getchar();
		
		switch (eingabe) {
		case 'l': laenge = laden(playlist); break;
		case 's': speichern(playlist, laenge); break;
		case 'b': fertig = 1; break;
		case 'e': einlesen(playlist, laenge);++laenge; break;
		case 'a': ausgeben(playlist, laenge);break;
		case 'd': laenge = loeschen(playlist, laenge);break;
		case 'm': shuffle(playlist, laenge);break;
		case 'j': printf("\n\nEs sind %d Songs aus dem Jahr in ihrer Playlist\n", jahrSuchen(playlist, laenge));break;
		case 'i': printf("\n\nEs sind %d Songs aus dem Jahr in ihrer Playlist\n", interpretSuchen(playlist, laenge));break;

		default: printf("Funktion nicht verfuebar!\n\n");
		}

	}

	return 0;
}
