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
Song einlesen( void ) {	
	Song neu;
	printf("im folgenden Format song eingeben: \nInterpret Titel Jahr minuten Sekunden (Leerzeichen im Titel/Interpret durch '_' ersetzen!)");
	scanf("%s %s %d %d %d", neu.interpret, neu.titel, neu.jahr, neu.minuten, neu.sekunden);
}


/* Diese Funktion gibt alle Attribute eines Songs aus */
// void ausgeben( Song song, int i ) {


// }
/* Ende Teilaufgabe b) */


/* Beginn Teilaufgabe c) */
// int loeschen( Song *playlist, int pos, int laenge ) {


// }
/* Ende Teilaufgabe c) */


/* Beginn Teilaufgabe d) */
// void shuffle( Song *playlist, int laenge ) {


// }
/* Ende Teilaufgabe d) */


/* Beginn Teilaufgabe e) */
// int jahrSuchen( Song *playlist, int jahr, int laenge ) {


// }
/* Ende Teilaufgabe e) */


/* Beginn Teilaufgabe f) */
// int interpretSuchen( Song *playlist, char *interpret, int laenge ) {


// }
/* Ende Teilaufgabe f) */


int main(void) {

	Song playlist[PLLEN];
	int laenge = 0, fertig = 0;
	char eingabe;

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
		case 'e': einlesen(); break;
		default: printf("Funktion nicht verfuebar!\n\n");
		}

	}

	return 0;
}
