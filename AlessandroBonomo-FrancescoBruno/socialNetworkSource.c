#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define dimMaxUser 20 // dimensione globale massima per la stringa username
#define dimMaxPassword 20  // dimensione globale massima per la stringa password
#define dimMaxTestoPost 200  // dimensione globale massima per la stringa testo di un post
#define dimMaxPostsPerUtente 10  // dimensione globale massima dei post per ogni utente
#define dimUtentiPredefiniti 5  // dimensione globale degli utenti preimpostati nel programma

typedef struct post
{
    char testo[dimMaxTestoPost];
}post;

typedef struct utente
{
    char username[dimMaxUser];
    char password[dimMaxPassword];
    struct listaUtenti* utentiSeguiti;
    struct post posts[dimMaxPostsPerUtente];
    int contaPost;
}utente;

typedef struct listaUtenti
{
    struct utente user;
    struct listaUtenti* next;
}listaUtenti;

// lista contenente tutti gli utenti del social network
listaUtenti *utentiSocialNet=NULL;
// puntatore all'utente con cui si e' attualmente loggati (NULL se non si e' loggati)
utente* utenteLoggato=NULL;
// matrice di post predefiniti per i corrispettivi utenti predefiniti
post postsPredefiniti[dimUtentiPredefiniti][dimMaxPostsPerUtente] ={
    {
        {.testo = "Oggi e' una bella giornata"},
        {.testo = "Oggi e' una brutta giornata"},
        {.testo = "Mi annoio"},
        {.testo = "Sto studiando"},
        {.testo = "Buongiorno"},
        {.testo = "Kaffettino?"},
        {.testo = "Coprifuoco alle 23"},
        {.testo = "Forza Napoli"},
        {.testo = "Mi piacciono i cani"},
        {.testo = "Mi piacciono i gatti"}
    },
    {
        {.testo = "E anche oggi mi sono svegliato"},
        {.testo = "Sono stato licenziato"},
        {.testo = "Mia moglie ha chiesto il divorzio"},
        {.testo = "Mio figlio non mi vuole vedere"},
        {.testo = "Che bella giornata"},
        {.testo = "Ho divorziato"},
        {.testo = "Ciao amici"},
        {.testo = "Cerco lavoro"},
        {.testo = "Mi stanno pignorando casa"},
        {.testo = "Addio"}
    },
    {
        {.testo = "Ciao a tutti"},
        {.testo = "Oggi vado in chiesa"},
        {.testo = "Oggi esco"},
        {.testo = "Oggi sto a casa"},
        {.testo = "Oggi vado a mare tutto il giorno"},
        {.testo = "Mi hanno svaligiato casa"},
        {.testo = "Qualcuno mi presta soldi?"},
        {.testo = "Buonasera"},
        {.testo = "Buongiorno"},
        {.testo = "Buonanotte"}
    },
    {
        {.testo = "Sono uno scrittore"},
        {.testo = "Scrivo cose"},
        {.testo = "Scrivo quello che penso"},
        {.testo = "Penso cose"},
        {.testo = "Esisto"},
        {.testo = "Sto scrivendo"},
        {.testo = "Siamo umani"},
        {.testo = "Scrivo al computer"},
        {.testo = "Leggete i miei post"},
        {.testo = "Sono forte"}
    },
    {
        {.testo = "Oggi mi alleno"},
        {.testo = "Sono aumentato di massa"},
        {.testo = "Oggi allenamento"},
        {.testo = "Oggi riposo"},
        {.testo = "Seguo una dieta ipercalorica"},
        {.testo = "Sono soddisfatto"},
        {.testo = "Settimana ricalcolo massimali"},
        {.testo = "4 piegamenti in verticale"},
        {.testo = "8 muscle up"},
        {.testo = "20 trazioni prone"}
    }
};

// utenti predefiniti del social network
utente utentiPredefiniti[dimUtentiPredefiniti] ={
    { .username="Pippo", .password = "123"},
    { .username="Mario", .password = "456"},
    { .username="Giuseppe", .password = "789"},
    { .username="Luigi", .password = "ciao"},
    { .username="Giancarlo", .password = "password"}
};

// funzione per inserire username e password e ritorna l'utente inserito
utente LeggiUtenteDaTastiera()
{
    utente u;
    printf("Inserisci username: ");
    scanf("%s", u.username);
    printf("Inserisci password: ");
    scanf("%s", u.password);
    u.contaPost =0;
    u.utentiSeguiti = NULL;
    return u;
}
// funzione per inserire solo username e ritorna l'utente inserito
utente LeggiSoloUsernameUtente()
{
    utente u;
    printf("Inserisci username: ");
    scanf("%s", u.username);
    u.contaPost =0;
    u.utentiSeguiti = NULL;
    return u;
}
// funzione che stampa l'utente passato per parametro
void StampaUtente(utente u)
{
    printf("Username: %s\n", u.username);
    //printf("Username: %s, Password: %s\n", u.username, u.password);
    //StampaPostsUtente(u);
}
// funzione che stampa il post passato per parametro
void StampaPost(post p)
{
    printf("Contenuto post: %s\n",p.testo);
}
// funzione che stampa tutti i post presenti nella lista Posts dell'utente ricercato
void StampaPostsUtente(utente u)
{
    if(u.contaPost==0)
    {
        printf("L'utente %s non ha mai postato\n",u.username);
        return;
    }
    printf("Posts dell'utente %s (%d): \n",u.username,u.contaPost);
    for(int i=0;i<u.contaPost;i++)
        StampaPost(u.posts[i]);
}
// funzione che stampa l'ultimo post dell'utente passato per parametro
void StampaUltimoPostUtente(utente u)
{
    if(u.contaPost==0)
    {
        printf("L'utente %s non ha mai postato\n",u.username);
        return;
    }
    printf("Ultimo Post dell'utente %s: \n",u.username);
    StampaPost(u.posts[u.contaPost-1]);
}
// funzione che ricerca l'utente passato per confronto dell'username/password
// tra quelli nella lista passata (ritorna NULL se ricerca senza successo,
// altrimenti se la ricerca termina con successo allora viene ritornato il
// puntatore all'utente ricercato nella lista)
utente* GetPointerUtente(listaUtenti *testa,utente u)
{
    listaUtenti *p = testa;
    while(p!=NULL)
    {
        if(strcmp(p->user.password,u.password) == 0 &&
           strcmp(p->user.username,u.username) == 0)
            return p;
        p=p->next;
    }
    return NULL;
}
// funzione che ricerca l'utente passato per confronto dell'username
// tra quelli nella lista passata (ritorna NULL se ricerca senza successo,
// altrimenti se la ricerca termina con successo allora viene ritornato il
// puntatore all'utente ricercato nella lista)
utente* GetPointerUtenteByUsername(listaUtenti *testa,utente u)
{
    listaUtenti *p = testa;
    while(p!=NULL)
    {
        if(strcmp(p->user.username,u.username) == 0)
            return p;
        p=p->next;
    }
    return NULL;
}
// funzione di creazione post e successiva aggiunta alla lista Post dell'utente passato
void CreaPost(char testo[], utente* autore)
{
    // se non hai raggiunto il max di posts
    if(autore->contaPost<dimMaxPostsPerUtente)
    {
        strcpy(autore->posts[autore->contaPost].testo, testo);
        autore->contaPost++;
    }
    else
    {
        shiftSxPostUtente(autore);
        strcpy(autore->posts[autore->contaPost-1].testo, testo);
    }
}
// funzione di shift per eliminare il post meno recente dell'utente passato
void shiftSxPostUtente(utente *u)
{
    for(int i=0;i<u->contaPost-1;i++)
        strcpy(u->posts[i].testo, u->posts[i+1].testo);
}
// funzione per la creazione di una lista di utenti
// (ritorna la testa della lista appena creata)
listaUtenti* creaListaUtenti(utente primoUtente)
{
    listaUtenti* testa = malloc(sizeof(listaUtenti));
    testa->user = primoUtente;
    testa->next = NULL;
    return testa;
}
// funzione che aggiunge in coda alla lista passata l'utente passato
void PushTailUtente(listaUtenti **testa, utente u)
{
    if(*testa==NULL){
        *testa = creaListaUtenti(u);
        return;
    }
    listaUtenti* p = *testa;
    while(p->next!=NULL)
        p=p->next;
    listaUtenti *nuovoNodoUtente = malloc(sizeof(listaUtenti));
    nuovoNodoUtente->user = u;
    nuovoNodoUtente->next=NULL;
    p->next = nuovoNodoUtente;
}
// funzione che stampa tutti gli utenti presenti nella lista passata
void StampaListaUtenti(listaUtenti *testa)
{
    if(testa==NULL)
    {
        printf("Lista utenti vuota.\n");
        return;
    }
    //printf("Lista:\n");
    listaUtenti *p = testa;
    while(p!=NULL)
    {
        StampaUtente(p->user);
        p=p->next;
    }
}
// funzione di caricamento degli utenti predefiniti con i loro post associati
void caricaUtentiPredefiniti()
{
    for(int i=0;i<dimUtentiPredefiniti;i++)
    {
        for(int j=0;j<dimMaxPostsPerUtente;j++)
        {
            strcpy(utentiPredefiniti[i].posts[j].testo,
                   postsPredefiniti[i][j].testo);
        }
		utentiPredefiniti[i].contaPost = dimMaxPostsPerUtente;
        utentiPredefiniti[i].utentiSeguiti=NULL;
        PushTailUtente(&utentiSocialNet,utentiPredefiniti[i]);
    }
}
// funzione che ricerca l'utente passato nella lista passata, se la ricerca ha successo
// rimuove l'utente dalla lista e lo dealloca
void RimuoviUtente(listaUtenti** testa,utente u)
{
    listaUtenti* p = *testa, *prec=NULL,*del=NULL;
    if(p==NULL)return;
    while(p!=NULL)
    {
        if(prec!=NULL &&
           strcmp(p->user.username,u.username)==0 &&
           strcmp(p->user.password,u.password)==0)
        {
            del = p;
            prec->next = p->next;
        }
        prec = p;
        p=p->next;
    }
    p=*testa;
    if(strcmp(p->user.username,u.username)==0 &&
       strcmp(p->user.password,u.password)==0)
    {
        del = p;
        *testa = p->next;
    }
    free(del);
}
// funzione che aggiunge l'utente daSeguire nella lista UtentiSeguiti dell'utente segue
void SeguiUtente(utente *segue,utente *daSeguire)
{
    if(segue == NULL || daSeguire==NULL)return;
    listaUtenti *p = segue->utentiSeguiti;
    PushTailUtente(&p,*daSeguire);
    segue->utentiSeguiti = p;
}
// funzione che stampa gli utenti presenti nella lista UtentiSeguiti dell'utente passato
void StampaSeguiti(utente u)
{
    printf("Utenti seguiti da %s:\n",u.username);
    StampaListaUtenti(u.utentiSeguiti);
}
// funzione che stampa l'ultimo post dell'utente passato per parametro
void StampaUltimoPostDiOgniUtenteSeguito(utente u)
{
    listaUtenti* p = u.utentiSeguiti;
    if(p==NULL)
    {
        printf("Non segui nessuno.\n");
        return;
    }
    printf("Ultimi post degli utenti seguiti:\n");
    while(p!=NULL)
    {
        StampaUltimoPostUtente(p->user);
        p=p->next;
    }
}
// funzione che legge da tastiera l'utente per l'aggiunta alla lista utentiSocialNet
// ritorna sempre true
bool SignIn()
{
    utente u = LeggiUtenteDaTastiera();
    PushTailUtente(&utentiSocialNet,u);
    utenteLoggato = GetPointerUtente(utentiSocialNet,u);
    printf("Utente creato con successo!\n");
    return true;
}
// funzione che legge da tastiera l'utente e controlla che esista nella lista utentiSocialNet
// se esiste, ritorna true, altrimenti ritorna false
bool LogIn()
{
    utente u = LeggiUtenteDaTastiera();
    utenteLoggato = GetPointerUtente(utentiSocialNet,u);
    if(utenteLoggato!=NULL)
    {
        printf("Loggato con successo! Benvenuto %s!\n",u.username);
        return true;
    }
    else
    {
        printf("Login fallito.\n");
        return false;
    }
}
// funzione per la scelta di registrazione\accesso ad un utente presente nel programma o termine del programma
bool homePage()
{
    bool esito;
    do
    {
        printf("Home page\n");
        printf("1) Sign in\n");
        printf("2) Log in\n");
        printf("3) Termina\n");
        int operazione;
        printf("Scegli tra le operazioni: \n");
        scanf("%d",&operazione);
        switch(operazione)
        {
            case 1:
                esito = SignIn();
            break;
            case 2:
                esito = LogIn();
            break;
            case 3:
                return true;
            break;
            default:
                printf("Operazione non valida\n");
                esito = false;
            break;
        }
    }
    while(!esito);
    return false;
}
// funzione che legge un utente da tastiera, lo ricerca nella lista utentiSocialNet e stampa se esiste
void OperazioneTrovaUtente()
{
    utente u = LeggiSoloUsernameUtente();
    if(GetPointerUtenteByUsername(utentiSocialNet,u)!=NULL)
        printf("L'utente esiste.\n");
    else printf("L'utente non esiste.\n");
}
// funzione che legge un utente da tastiera, lo ricerca nella lista utentiSocialNet
// se esiste lo aggiunge alla lista UtentiSeguiti dell'utente loggato
void OperazioneSeguiUtente()
{
    utente u = LeggiSoloUsernameUtente();
    utente* uPointer = GetPointerUtenteByUsername(utentiSocialNet,u);
    if(uPointer!=NULL)
    {
        // cerca tra i seguiti uPointer, se non lo trovi allora puoi seguire
        if(GetPointerUtenteByUsername(utenteLoggato->utentiSeguiti,*uPointer)==NULL)
        {
            SeguiUtente(utenteLoggato,uPointer);
            printf("Utente seguito!\n");
        }
        else printf("Segui gia' questo utente.\n");
    }
    else printf("L'utente non esiste.\n");
}
// funzione per la creazione di un post, aggiunto alla lista Post dell'utente loggato
void OperazioneCreaUnPost()
{
    char testo[dimMaxTestoPost];
    printf("Inserisci testo del post: ");
    char temp;
    scanf("%c",&temp);
    scanf("%[^\n]",&testo);
    CreaPost(testo,utenteLoggato);
}
// funzione che legge un utente da tastiera, lo ricerca e, se lo trova stampa i suoi post
void OperazioneVediPostDiUnUtente()
{
    utente u = LeggiSoloUsernameUtente();
    utente* uPointer = GetPointerUtenteByUsername(utentiSocialNet,u);
    if(uPointer!=NULL)
    {
        StampaPostsUtente(*uPointer);
    }
    else printf("L'utente non esiste.\n");
}
// funzione per la cancellazione dell'utente loggato dalla lista utentiSocialNet
bool OperazioneCancellaUtente()
{
    char pw[dimMaxPassword];
    printf("Inserisci password di verifica: ");
    scanf("%s",&pw);
    if(strcmp(pw,utenteLoggato->password)==0)
    {
        char risp;
        printf("Sicuro di voler cancellare l'utente %s? (y/n): ",
               utenteLoggato->username);
        scanf("%c",&risp);//svuota buffer
        scanf("%c",&risp);
        if(risp == 'n')return false;
    }
    else
    {
        printf("Password errata.\n");
        return false;
    }
    RimuoviUtente(&utentiSocialNet,*utenteLoggato);
    printf("Utente rimosso.\n");
    return true;
}
// funzione per il richiamo delle operazioni, a seconda della scelta
void homePageLogged()
{
    bool esito;
    do
    {
        printf("\n");
        printf("Home page logged\n");
        printf("Loggato come %s\n",utenteLoggato->username);
        printf("1) Visualizza nomi degli utenti\n");
        printf("2) Cerca se esiste un utente\n");
        printf("3) Segui un utente\n");
        printf("4) Crea un post\n");
        printf("5) Vedi i post di un utente\n");
        printf("6) Vedi l'ultimo post di ogni utente seguito\n");
        printf("7) Log out\n");
        printf("8) Cancella utente\n");
        int operazione;
        esito = false;
        printf("Scegli tra le operazioni: \n");
        scanf("%d",&operazione);
        switch(operazione)
        {
            case 1:
                StampaListaUtenti(utentiSocialNet);
            break;
            case 2:
                OperazioneTrovaUtente();
            break;
            case 3:
                OperazioneSeguiUtente();
            break;
            case 4:
                OperazioneCreaUnPost();
            break;
            case 5:
                OperazioneVediPostDiUnUtente();
            break;
            case 6:
                StampaUltimoPostDiOgniUtenteSeguito(*utenteLoggato);
            break;
            case 7:
                printf("Bye %s!\n",utenteLoggato->username);
                esito = true;
            break;
            case 8:
                esito = OperazioneCancellaUtente();
            break;
            default:
                printf("Operazione non valida\n");
                esito = false;
            break;
        }
    }
    while(!esito);
}
int main()
{
    caricaUtentiPredefiniti();
    bool termina=false;
    do
    {
        termina = homePage();
        if(termina)
            break;
        homePageLogged();
    }
    while(true);
    printf("Termino programma.\n");


    return 0;
}
