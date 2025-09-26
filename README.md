Come Funziona la Comunicazione tra Client e Server tramite Segnali in C: Un Riepilogo Completo

La comunicazione tra processi tramite segnali in C è un meccanismo potente ma delicato, soprattutto quando si tratta di inviare dati bit per bit tra client e server. In questo articolo analizzeremo passo dopo passo come si può implementare un server che riceve dati via segnali SIGUSR1 e SIGUSR2, gestisce questi segnali con un handler personalizzato e invia un acknowledgment al client per confermare la ricezione.

1. Impostazione del Server: Preparazione e Registrazione degli Handler

Il server parte e svolge le iniziali operazioni, ad esempio convertire argomenti da stringa a numero con ft_atoi, ottenere il proprio PID con getpid, e infine preparare l’ambiente per la ricezione di segnali.

Registrazione del gestore segnali con sigaction

Il punto critico è la funzione:

void install_server_signal_handlers(void (*handler)(int, siginfo_t *, void *))
{
    struct sigaction sa;

    sa.sa_sigaction = handler;       // Handler a 3 parametri
    sa.sa_flags = SA_SIGINFO;        // Attiva la modalità con info avanzate
    sigemptyset(&sa.sa_mask);        // Nessun segnale bloccato durante l’handler

    sigaction(SIGUSR1, &sa, NULL);   // Registra handler per SIGUSR1
    sigaction(SIGUSR2, &sa, NULL);   // Registra handler per SIGUSR2
}


Qui si passa un puntatore a funzione (l’handler) che accetta 3 parametri:

int signo — il numero del segnale ricevuto (SIGUSR1 o SIGUSR2)

siginfo_t *info — informazioni aggiuntive, come il PID del processo mittente

void *context — contesto opzionale (solitamente ignorato)

Questo permette di gestire segnali con più informazioni e flessibilità.

2. Il Ruolo del Puntatore a Funzione Handler

Il parametro handler passato a install_server_signal_handlers è un puntatore a funzione con firma:

void ft_handler(int signo, siginfo_t *info, void *context);


Il nome della funzione, senza parentesi, è l’indirizzo della funzione stessa, quindi è un puntatore. Passandolo, si dice al kernel “usa questa funzione per gestire SIGUSR1 e SIGUSR2”.

3. Come Funziona l’Handler dei Segnali: Ricezione e Ricostruzione del Messaggio

Quando il server riceve un segnale SIGUSR1 o SIGUSR2, il kernel chiama automaticamente ft_handler, passando i parametri sopra citati.

Dentro ft_handler si può:

Decodificare il bit ricevuto (ad esempio, SIGUSR1 = bit 0, SIGUSR2 = bit 1)

Inserire il bit nel buffer per ricostruire il carattere o messaggio

Gestire lo stato della ricezione, come contare i bit, formare caratteri completi, ecc.

4. Acknowledgment: Come il Server Conferma la Ricezione al Client

Dopo aver processato correttamente il bit ricevuto, il server invia un segnale di conferma al client per sincronizzare l’invio.

Questo avviene con la funzione:

void send_ack(pid_t client_pid)
{
    kill(client_pid, SIGUSR1);
}


client_pid è il PID del client che ha inviato il segnale, ottenuto da info->si_pid dentro l’handler.

kill(client_pid, SIGUSR1); manda il segnale SIGUSR1 al client, che interpreta come “acknowledgment ricevuto”.

Il client, a sua volta, aspetta questo segnale prima di inviare il bit successivo, garantendo così una comunicazione affidabile e sincronizzata.

5. Sincronizzazione con la Variabile g_ack e Funzioni di Supporto

Nel file ack_utils.h troviamo:

volatile sig_atomic_t g_ack;
Una variabile atomica e volatile per comunicare in sicurezza tra handler e codice normale.

ack_handler(int sig);
Handler semplice che setta g_ack = 1 quando arriva un segnale di ack.

wait_for_ack();
Funzione che mette in pausa il processo finché g_ack non viene settato a 1, evitando condizioni di race usando pause().

install_ack_handler();
Installa ack_handler per il segnale SIGUSR1 usando la vecchia API signal().

6. Il Flusso Completo della Comunicazione

Il server chiama install_server_signal_handlers(ft_handler), impostando il suo handler avanzato per i segnali.

Il client invia bit tramite SIGUSR1 (bit 0) e SIGUSR2 (bit 1).

Il server, nella funzione ft_handler, riceve il segnale, ricostruisce i bit in caratteri o messaggi.

Al termine della ricezione di un bit, il server invia SIGUSR1 al client con send_ack(info->si_pid).

Il client, che aspetta questo ack, procede con l’invio del bit successivo.

Il ciclo continua fino a quando l’intero messaggio è stato trasmesso.

Conclusione

L’uso di sigaction con un handler a 3 parametri, l’estrazione del PID del mittente con siginfo_t, e l’invio di segnali di acknowledgment tramite kill sono i cardini di una comunicazione affidabile via segnali in C.

Questo sistema consente di implementare protocolli di comunicazione semplici ma robusti tra processi, come nel progetto Minitalk, dove il server riceve messaggi bit per bit da più client, garantendo sincronizzazione e correttezza dei dati.
