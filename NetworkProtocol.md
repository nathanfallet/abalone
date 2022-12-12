# Protocol réseau pour les échanges

## Démarrage de la partie

Au démarrage de la partie, le serveur et le client se connectent au moyen d'un socket en TCP.

On utilise par défaut le port `6969`, sauf si un port est précisé en ligne de commande (via l'option `-s PORT`).

> ⚠️ On garde le même socket ouvert tout le long de la partie, il n'est pas nécessaire d'en créer un nouveau (surtout qu'une coupure de connexion pourrait casser la partie)

## Echange de coups

A chaque fois qu'un joueur joue, il envoit son coup sous forme de chaine de 6 caractères (ex: `A1:B1`, avec le caractère nul à la fin) sur le socket,
et attend la réponse de l'adversaire sous le même format.

> ⚠️ Attention à bien écrire/écouter dans le bon ordre, c'est le client qui joue en premier (car il est noir)

## Exemple de lecture et écriture

Au début de la partie, on initialise la connexion, et on conserve le descripteur du socket dans `fdclient`.

```c
// Stockage de la connexion (on la garde tout le long de la partie)
int fdclient;
```

```c
// Créer un serveur
int fdsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
int opt = 1;
setsockopt(fdsocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = INADDR_ANY;
addr.sin_port = htons(6969); // Valeur à remplacer
bind(fdsocket, (struct sockaddr *) &addr, sizeof(addr));
listen(fdsocket, 1);
fdclient = accept(fdsocket, NULL, NULL);
```

```c
// Créer un client
fdclient = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Valeur à remplacer
addr.sin_port = htons(6969); // Valeur à remplacer
if (connect(fdclient, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
    printf("Could not connect: %s\n", strerror(errno));
}
```

Une fois la connexion établie, que l'on soit client ou serveur, on peut lire et écrire sur le socket en utilisant `fdclient`.

```c
// Envoi de mon coup à l'adversaire
char *move = "A1:B1";
write(fdclient, move, sizeof(move));
```

```c
// Récupération du coup de l'adversaire (dans `opponent_move`)
char *opponent_move = malloc(sizeof(char) * 6);
read(fdclient, opponent_move, sizeof(opponent_move));
```

Il faut juste bien veiller à envoyer et récupérer les coups dans le bon ordre, car c'est le client qui joue en premier.
