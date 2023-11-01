# abalone {#mainpage}

## Project structure

![Project structure](structure.png)

See [files](https://nathanfallet.github.io/Abalone/files.html) for more details.

## Install GTK3

```bash
apt install libgtk-3-dev # Linux
brew install gtk+3 # macOS
```

## Compile and start the game

```bash
make
make nogui # Si GTK n'est pas installé
./abalone -l <noir/blanc> # jeu local contre l IA
./abalone -s <port> # lancer un serveur sur le port donné
./abalone -c <adresse>:<port> # se connecter à un serveur distant
```

## Documentation

Documentation is available on [nathanfallet.github.io/Abalone](https://nathanfallet.github.io/Abalone).

## Code coverage

Code coverage is available on [app.codecov.io/github/NathanFallet/Abalone](https://app.codecov.io/github/NathanFallet/Abalone).
