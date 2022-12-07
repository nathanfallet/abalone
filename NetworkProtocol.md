# Protocol réseau pour les échanges

## Démarrage de la partie

Au démarrage de la partie, le serveur et le client se connectent au moyen d'un socket en TCP.

> ⚠️ On garde le même socket ouvert tout le long de la partie, il n'est pas nécessaire d'en créer un nouveau (surtout qu'une coupure de connexion pourrait casser la partie)

## Echange de coups

A chaque fois qu'un joueur joue, il envoit son coup sous forme de chaine de 6 caractères (ex: `A1:B1`, avec le caractère nul à la fin) sur le socket,
et attend la réponse de l'adversaire sous le même format.

> ⚠️ Attention à bien écrire/écouter dans le bon ordre, c'est le client qui joue en premier (car il est noir)

## Exemple de lecture et écriture

```c
// Envoi de mon coup à l'adversaire
char *move = move_to_string(last_move); // Ex: "A1:B1"
write(fdclient, move, sizeof(move));

// Récupération du coup de l'adversaire
char *opponent_move = malloc(sizeof(char) * 6);
read(fdclient, opponent_move, sizeof(opponent_move));
Move result = move_from_string(opponent_move);
```

## Mot de la fin

N'hésitez pas à venir me voir si vous avez des questions, ou pour tester le protocol avec notre équipe. Bon courage !
