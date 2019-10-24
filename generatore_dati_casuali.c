#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define SECONDI_IN_MINUTO 60
#define MINUTI_IN_ORA 60
#define ORE_IN_GIORNO 24
#define SECONDI_IN_ORA (SECONDI_IN_MINUTO * MINUTI_IN_ORA)
#define SECONDI_IN_GIORNO (ORE_IN_GIORNO * SECONDI_IN_ORA)
#define LUNGHEZZA_ORARIO 10


double randfromDouble(double min, double max);
int randfromInt(int min, int max);
char *genera_orario(void);

int main(void)
{
	FILE    *fptr;
	char    *orario_s;
	int     orario;
	int		numRilevazioni;
	srand(time(NULL));  	//setta il valore iniziale dei numeri psedudo casuali generati con random()


	printf("Inserire il numero di rilevazioni da generare: ");
	scanf("%d", &numRilevazioni);

	fptr = fopen("dati_riscaldamento.txt", "w");


	for (int i = 0; i < numRilevazioni; i++)
	{
		orario_s = genera_orario(); 		//salva in stringa l'orario
		orario = atoi(orario_s); 			//converte la stringa in un intero


		fprintf(fptr, "%d\t\t", orario);
		fprintf(fptr, "%.2f\t\t", randfromDouble(0.00, 30.00));
		fprintf(fptr, "%.2f\n", randfromDouble(0.00, 40.00));
	}
	fclose(fptr);
	printf("Creato file con %d dati casuali\n", numRilevazioni);

	return (0);
}

/* Genera un floating point casuale tra il min e il max specificati */
double randfromDouble(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

/* Genera un intero casuale tra il min e il max specificati */
int randfromInt(int min, int max)
{
	int range = (max - min);
	int div = RAND_MAX / range;
	return min + (rand() / div);
}

char *genera_orario(void)
{
	/* Definizione delle variabili locali relative alla funzione */
	bool esito_operazione = true; 	/* lavoro: esisto operazioni funzione */
	char *orario;                	/* output: orario formattato*/
	int totale_secondi_orario,    	/* lavoro: secondi orario casuale */
		orario_ore,               	/* lavoro: componente hh dell'orario */
		orario_giorno,              /* lavoro: componente gg dell'orario */
		orario_anno,               	/* lavoro: componente aa dell'orario */
		orario_mese,               	/* lavoro: componente mm dell'orario */
		lunghezza_stringa;        	/* lavoro: lunghezza stringa letta/allocata */

	/* Allochiamo lo spazio necessario all'orario */
	lunghezza_stringa = LUNGHEZZA_ORARIO + 1; 	//il +1 è per il segno '\0' alla fine
	orario = (char *)calloc(lunghezza_stringa, sizeof(char));

	/* Gestione NULL pointer */
	if (orario == NULL)
	{
		printf("Errore: memoria insufficiente!\n");
		esito_operazione = false;
	}

	if (esito_operazione)
	{
		/* Generiamo le componenti dell'orario */
		totale_secondi_orario = rand() % SECONDI_IN_GIORNO;
		orario_ore = totale_secondi_orario / SECONDI_IN_ORA;
		orario_anno = randfromInt(2010, 2022);
		orario_mese = randfromInt(1, 12);
		orario_giorno = randfromInt(1, 31);

		/* Concateniamo le componenti dell'orario; sprintf appende '\0' */
		sprintf(orario,
			"%d%02d%02d%02d",
			orario_anno,
			orario_mese,
			orario_giorno,
			orario_ore);
	}

	return orario;
}