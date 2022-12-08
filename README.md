# Abalone game

## Project structure

![Project structure](structure.png)

## Install GTK3

```bash
apt install libgtk-3-dev # Linux
brew install gtk+3 # macOS
```

## Compile and start the game

```bash
make
./abalone -l <noir/blanc> : jeu local contre l IA  // exemple:  <./abalone -l noir>

./abalone -s <port> : lancer un serveur sur le port donné  // exemple:  <./abalone -c YYYY>

./abalone -c <adresse>:<port> : se connecter à un serveur distant  //exemple:  <./abalone -c XXX.XXX.XXX.XXX:YYYY>
```
