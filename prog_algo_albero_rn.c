/*DIRETTIVE AL PREPROCESSORE*/
#include<stdio.h>
#include<stdlib.h>          //serve per malloc
#define bool int
#define true 1
#define false 0

/*DEFINIZIONE DEI TIPI*/
typedef enum { rosso, nero } colore_t;
int contatoreComplessita = 0;
//definizione del tipo di struttura nodo AVL
typedef struct nodo_albero_bin_rn
{
	int		tempo;
	double	gas,
		elettricita;
	colore_t colore;
	struct  nodo_albero_bin_rn *sx,			//collegamento a nodo sinistro
		*dx,        //collegamento a nodo destro
		*padre;     //collegamento al nodo padre
} nodo_albero_bin_rn_t;

/*DICHIARAZIONE DELLE FUNZIONI*/
int scelta_operazione(void);
void pulisci_buffer(void);
int inserisci_in_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int tem, double gas, double elettricita);
void ripristina_ins_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *nodo);
void ruota_sx(nodo_albero_bin_rn_t* nodo, nodo_albero_bin_rn_t* x);
void ruota_dx(nodo_albero_bin_rn_t *nodo, nodo_albero_bin_rn_t *x);
nodo_albero_bin_rn_t *cerca_valore(nodo_albero_bin_rn_t *sent_p, int valore);
int rimuovi_da_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int valore);
void ripristina_rim_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *nodo);
void stampa_albero(nodo_albero_bin_rn_t *nodo, nodo_albero_bin_rn_t *sent_p);

/*DEFINIZIONE DELLE FUNZIONI*/
// MAIN
int main(int argc, const char * argv[]) {

	int	scelta,				//lavoro: operazione scelta
		ins,				//lavoro: operazione andata a buon fine di inserimento nodo
		tem;				//lavoro: proprieta' tempo del nodo
	int valore;             //input: valore da cercare
	double gas,             //lavoro: proprieta' gas del nodo
		elett;              //lavoro: proprieta' elettricità del nodo
	int risultato,
		esito_lettura;      //lavoro: vede se l'input inserito è corretto
	char *stringaTempo;
	//lavoro: radice albero principale
	nodo_albero_bin_rn_t *sent_p = NULL;
	sent_p = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
	sent_p->sx = sent_p->dx = sent_p;
	sent_p->colore = nero;
	sent_p->padre = NULL;

	stringaTempo = (char *)calloc(10 + 1, sizeof(char));

	//apertura file per acquisizione dati
	FILE *file_dati = fopen("dati_riscaldamento.txt", "r");
	if (file_dati == NULL)
	{
		printf("Questo file non esiste.\n");
                return 0;
	}
	else
	{
		//dichiaro che i parametri del nuovo nodo creato devono avere valori uguali a quelli letti dal file
		while (fscanf(file_dati, "%s %lf %lf",
				stringaTempo, &gas, &elett)
				!= EOF)
		{
			//funzione di inserimento dei nodi
			tem = atoi(stringaTempo);
			ins = inserisci_in_albero_bin_ric_rn(sent_p, tem, gas, elett);

		}//end of while
	}//end fopen

	//chiusura file acquisizione dati
	fclose(file_dati);

	printf("---RILEVAZIONI---\n\n");
	stampa_albero(sent_p->sx, sent_p);
	printf("\nDati caricati correttamente dal file\n");

	do
	{
		/* Stampiamo il menu delle scelte */
		scelta = scelta_operazione();

		switch (scelta)
		{
		case 1:
			contatoreComplessita = 0;
			do
			{
				printf("Scegli una data di rilevazione(nel formato aaaaMMggHH): ");
				esito_lettura = scanf("%d", &valore);
				if (esito_lettura != 1 || valore <= 0)
					printf("\nFormato input non valido! Digitare nuovamente la data.\n\n");
				while (getchar() != '\n');
			} while (esito_lettura != 1 || valore <= 0);
			nodo_albero_bin_rn_t nodo;
			nodo = *cerca_valore(sent_p, valore);
			printf("\nComplessita' in passi: %d\n\n", contatoreComplessita);
			break;

		case 2:
			contatoreComplessita = 0;
			do
			{
				printf("Scegli una rilevazione da eliminare in base alla data: ");
				esito_lettura = scanf("%d", &valore);
				if (esito_lettura != 1 || valore <= 0)
					printf("\nFormato input non valido! Digitare nuovamente la data.\n\n");
				while (getchar() != '\n');
			} while (esito_lettura != 1 || valore <= 0);
			nodo_albero_bin_rn_t nodo_da_rimuovere;
			risultato = rimuovi_da_albero_bin_ric_rn(sent_p, valore);
			printf("\nComplessita' in passi: %d\n\n", contatoreComplessita);
			break;
		case 3:
			break;

		}
	} while (scelta != 3);

	return 0;
}

//MENU
int scelta_operazione(void)
{
	/* Definizione delle variabili locali relative alla funzione */
	bool esito_operazione = true; /* lavoro: esisto operazioni funzione */
	int scelta,                   /* input: operazione da eseguire */
		esito_lettura;            /* lavoro: esito lettura scanf */

	do
	{
		esito_operazione = true;

		printf("\nScegliere un'opzione:\n");
		printf("[1] Cercare e stampare i dati relativi a una determinata rilevazione\n");
		printf("[2] Cancellare i dati relativi a una determinata rilevazione\n");
		printf("[3] Uscire\n");
		esito_lettura = scanf("%d", &scelta);

		/* Svuotiamo il buffer da eventuali caratteri in eccesso */
		pulisci_buffer();

		if (esito_lettura != 1 || scelta < 1 || scelta > 3)
		{
			printf("Errore: inserire un numero da 1 a 3.\n");
			esito_operazione = false;
		}
	} while (!esito_operazione);

	return scelta;
}//end scelta_operazione

//PULISCI BUFFER
void pulisci_buffer(void)
{
	/* Definizione delle variabili locali relative alla funzione */
	char carattere_rimosso; /* lavoro: variabile pulitura buffer input */

	do
	{
		carattere_rimosso = getchar();
	} while (carattere_rimosso != '\n');
}

//INSERIMENTO
int inserisci_in_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int tempo, double gas, double elettricita)
{
	int inserito;
	nodo_albero_bin_rn_t *nodo, *padre, *nuovo;

	for (nodo = sent_p->sx, padre = sent_p;
		((nodo != sent_p) && (nodo->tempo != tempo)); padre = nodo, nodo = (tempo <= nodo->tempo) ?
		nodo->sx :
		nodo->dx);

	if (nodo != sent_p)
	{
		inserito = 0;
	}
	else
	{
		inserito = 1;
		nuovo = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
		nuovo->tempo = tempo;
		nuovo->gas = gas;
		nuovo->elettricita = elettricita;
		nuovo->colore = rosso;
		nuovo->sx = nuovo->dx = sent_p;
		nuovo->padre = padre;

		if (padre == sent_p)
		{
			sent_p->sx = sent_p->dx = nuovo;
		}
		else
		{
			if (tempo < padre->tempo)
			{
				padre->sx = nuovo;
			}
			else
			{
				padre->dx = nuovo;
			}
		}
		ripristina_ins_albero_bin_ric_rn(sent_p, nuovo);
	}
	return(inserito);
}

//RIPRISTINO ALBERO DOPO INSERIMENTO NUOVO NODO
void ripristina_ins_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p,
	nodo_albero_bin_rn_t *nodo) {

	nodo_albero_bin_rn_t *zio_p;

	while (nodo->padre->colore == rosso) {
		if (nodo->padre == nodo->padre->padre->sx) {
			zio_p = nodo->padre->padre->dx;
			if (zio_p->colore == rosso) {
				nodo->padre->colore = nero;
				zio_p->colore = nero;
				nodo->padre->padre->colore = rosso;
				nodo = nodo->padre->padre;
			}
			else {
				if (nodo == nodo->padre->dx) {
					nodo = nodo->padre;
					ruota_sx(sent_p, nodo);
				}

				nodo->padre->colore = nero;
				nodo->padre->padre->colore = rosso;
				ruota_dx(sent_p, nodo->padre->padre);
			}
		}
		else {
			zio_p = nodo->padre->padre->sx;
			if (zio_p->colore == rosso) {
				nodo->padre->colore = nero;
				zio_p->colore = nero;
				nodo->padre->padre->colore = rosso;
				nodo = nodo->padre->padre;
			}
			else {

				if (nodo == nodo->padre->sx) {
					nodo = nodo->padre;
					ruota_dx(sent_p, nodo);
				}

				nodo->padre->colore = nero;
				nodo->padre->padre->colore = rosso;
				ruota_sx(sent_p, nodo->padre->padre);
			}
		}
	}
	sent_p->sx->colore = nero;

}

//ROTAZIONE ALBERO A SINISTRA
void ruota_sx(nodo_albero_bin_rn_t* nodo, nodo_albero_bin_rn_t* x)
{
	nodo_albero_bin_rn_t *y;
	y = x->dx;
	x->dx = y->sx;
	y->sx->padre = x;
	y->padre = x->padre;

	if (x == nodo->sx)
	{
		nodo->sx = nodo->dx = y;
	}
	else
	{
		if (x == x->padre->sx)
		{
			x->padre->sx = y;
		}
		else
		{
			x->padre->dx = y;
		}
	}
	y->sx = x;
	x->padre = y;
}

//ROTAZIONE ALBERO A DESTRA
void ruota_dx(nodo_albero_bin_rn_t* nodo, nodo_albero_bin_rn_t* x) {
	nodo_albero_bin_rn_t *y;
	y = x->sx;
	x->sx = y->dx;
	y->dx->padre = x;
	y->padre = x->padre;

	if (x == nodo->dx)
	{
		nodo->dx = nodo->sx = y;
	}
	else
	{
		if (x == x->padre->dx)
		{
			x->padre->dx = y;
		}
		else
		{
			x->padre->sx = y;
		}
	}
	y->dx = x;
	x->padre = y;
}

//RICERCA
nodo_albero_bin_rn_t *cerca_valore(nodo_albero_bin_rn_t *sent_p, int valore) {
	nodo_albero_bin_rn_t *nodo;

	for (nodo = sent_p->sx;
		((nodo != sent_p) && (nodo->tempo != valore));
		contatoreComplessita++, nodo = (valore < nodo->tempo) ?
		nodo->sx :
		nodo->dx);
	if (nodo->tempo == 0x0)
		printf("\nDato non presente nelle rilevazioni.\n");
	else
		printf("TEMPO: %d\t\t\tGAS: %.2lf\t\t\tELETTRICITA': %.2lf\n",
		nodo->tempo, nodo->gas, nodo->elettricita);
	return(nodo);
}


//RIMOZIONE
int rimuovi_da_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int valore) {
	int rimosso;
	nodo_albero_bin_rn_t *nodo,
		*padre,
		*figlio,
		*sost;

	for (nodo = sent_p->sx, padre = sent_p;
		((nodo != sent_p) && (nodo->tempo != valore));
		contatoreComplessita++, padre = nodo, nodo = (valore < nodo->tempo) ?
		nodo->sx :
		nodo->dx);

	if (nodo == sent_p)
	{
		printf("\nDato non presente nelle rilevazioni!\n");
		rimosso = 0;
	}
	else
	{
		rimosso = 1;
		if ((nodo->sx == sent_p) || (nodo->dx == sent_p)) {
			figlio = (nodo->sx == sent_p) ?
				nodo->dx :
				nodo->sx;
			figlio->padre = padre;
			if (padre == sent_p)
				sent_p->sx = sent_p->dx = figlio;
			else
			{
				if (valore < padre->tempo)
					padre->sx = figlio;
				else
					padre->dx = figlio;
			}
		}
		else
		{
			sost = nodo;
			for (padre = sost, nodo = sost->sx;
				(nodo->dx != sent_p);
				padre = nodo, nodo = nodo->dx);
			sost->tempo = nodo->tempo;
			figlio = nodo->sx;
			figlio->padre = padre;
			if (padre == sost)
				padre->sx = figlio;
			else
				padre->dx = figlio;
		}
		if (nodo->colore == nero)
			ripristina_rim_albero_bin_ric_rn(sent_p, figlio);

		printf("\nRILEVAZIONI:\n");
		free(nodo);
		stampa_albero(sent_p->sx, sent_p);
	}
	return(rimosso);
}

//RIPRISTINA ALBERO DOPO RIMOZIONE
void ripristina_rim_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p,
	nodo_albero_bin_rn_t *nodo)
{

	nodo_albero_bin_rn_t *zio_p = NULL;

	while (nodo->padre->padre->colore == rosso)
		if (nodo->padre == nodo->padre->padre->sx)
		{
			zio_p = nodo->padre->padre->dx;
			if (zio_p->colore == rosso)
			{
				nodo->padre->colore = nero;
				zio_p->colore = nero;
				nodo->padre->padre->colore = rosso;
				nodo = nodo->padre->padre;
			}
			else
			{
				if (nodo == nodo->padre->dx)
				{
					nodo = nodo->padre;
					ruota_sx(sent_p, nodo);
				}
				nodo->padre->colore = nero;
				nodo->padre->padre->colore = rosso;
				ruota_dx(sent_p, nodo->padre->padre);
			}
		}
		else
		{
			zio_p = nodo->padre->padre->sx;
			if (zio_p->colore == rosso)
			{
				nodo->padre->colore = nero;
				zio_p->colore = nero;
				nodo->padre->padre->colore = rosso;
				nodo = nodo->padre->padre;
			}
			else
			{
				if (nodo == nodo->padre->sx)
				{
					nodo = nodo->padre;
					ruota_dx(sent_p, nodo);
				}
				nodo->padre->colore = nero;
				nodo->padre->padre->colore = rosso;
				ruota_sx(sent_p, nodo->padre->padre);
			}
		}
	sent_p->sx->colore = nero;
}

//STAMPA ORDINATA NODI ALBERO
void stampa_albero(nodo_albero_bin_rn_t *nodo, nodo_albero_bin_rn_t *sent_p) {
	if (nodo != sent_p) {
		stampa_albero(nodo->sx, sent_p);
		printf("TEMPO: %d\t\t\tGAS: %.2f\t\t\tELETTRICITA': \t\t\t%.2f\n",
			nodo->tempo,
			nodo->gas,
			nodo->elettricita);
		stampa_albero(nodo->dx, sent_p);
	}
}
