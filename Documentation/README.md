# GUI

Sistema di rendering dell'interfaccia utente. Ogni elemento della gui consiste in un puntatore allocato sullo heep, la
cui memoria viene rilasciata ogni volta che si abbandona la pagina di utilizzo (eliminazione out-of-scope).

Le tre sezioni principali (note generiche, bloccate e preferite) condividono la maggior parte dei codici, eccezione
fattasi per i codici di edit delle note. La condivisione dei codici e la distinzione degli elementi di cui fare il
render è basta su un passaggio di parametri booleani tra una pagina e l'altra, che avviene automaticamente in base al
tipo di azione richiesta. Ad esempio: per passare dalle note generiche a quelle bloccate, premendo sull'apposito
bottone, la home page viene distrutta
(tramite l'apposito metodo). Dopo di che, viene chiamato di nuovo il metodo della home page, ma con parametri diversi,
di modo che gli elementi della pagina siano quelli richiesti.

# LsmL

Sistema di dataBasing su cui l'applicazione si appoggia per il suo intero funzionamento. I dati salvati localmente
vengono letti, aggiunti e modificati dalla libreria interprete apposita. Per questa classe viene fornita una
documentazione dedicata, data la sua complessità.

# Note

Classe di appoggio sulla quale vengono salvati i dati delle note (come titolo, contenuto, e due booleani in caso sia
bloccata o preferita). I suoi metodi sono esclusivamente Getters e Setters, tuttavia non c'è interazione diretta col
dataBase.

# NotesManager

Classe che si occupa della crezione, distruzione e modifica delle note, oltre che del loro contenimento. La classe
interagisce col database, per otttemperare alle proprie funzioni di lettura e scrittura di su esso. NotesMenager viene
invocata e "letta" dalla GUI, per la visualizzazione di tutte le note salvate.

# NoteFolder

CLasse di appoggio, che ha l'unica funzione di contenere i dati relativi alle cartelle, quali il nome della raccolta e
il titolo delle note che contiene. Anche i suoi metodi sono solo Getters e Setters.

# FolderManager

Classe che si occupa della della creazione, modifica e distruzione delle cartelle di note. Anche questa interagisce col
database, tuttavia ne sfrutta uno dedicato. Ogni volta che una nota viene distrutta o ne viene modificato il titolo,
questa classe controlla se la nota in questione è presente in una cartella. In caso affermativo si occupa di aggiornare
il dataBase. Anche questa classe viene "letta" dalla GUI, per la creaziopne dei bottoni relativi ad ogni raccolta.