# Progetto_C_albero_RN
Progetto in linguaggio C che utilizza un albero Rosso-Nero  per ordinare vari tipi di dato

Specifica del problema:
Si supponga di dover progettare un programma per l’analisi un sistema di riscaldamento di un edificio. Il sistema rileva il consumo di gas e di energia elettrica (relativi ad ogni ora) e scrive i dati relativi su un file di log in formato testo, secondo il seguente formato (si assumano campi separati da tabulazione o spazio):
• Tempo: un codice numerico che risulta dalla concatenazione di anno, mese, giorno e ora della rilevazione.
• Gas: un numero reale che rappresenta il consumo in m3 nell’ora di rilevamento.
• Elettricita’: un numero reale che rappresenta il consumo in KWh nell’ora di rilevamento.
Ad esempio:
Tempo   Gas  Elettricita’
2019042908   1.3  2.70
2019042909   0.3  4.26
2019042910   8.3  5.14
...          ...  ...

Si scriva un programma ANSI C che esegue le seguenti elaborazioni:
Acquisisce il file e memorizza le relative informazioni in una struttura dati di tipo albero.
Ricerca e restituisce il dato relativo ai consumi di una determinata rilevazione. Ad esempio: se l’utente chiede quali consumi sono stati effettuati il giorno 29/04/2019 dalle ore 09 alle ore 10, il programma deve restituire le informazioni contenute nella riga 3 (2019042910, 8.3, 5.14).
Permette la cancellazione del dato corrispondente ad una determinata rilevazione (tempo, gas, elettricità) sulla base della richiesta dell’utente (sempre tramite indicazione del tempo).
