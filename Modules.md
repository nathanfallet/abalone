# Modules

## Constants

Some shared constants for the whole project.

## Game

A struct containing the board and some information about the game.
It also apply turns and send updates to other modules.

## Cell

An enum for a cell of the board (black, white, empty)

## Board

A struct representing a board.

## State

An enum representing the computed state of the game (in progress, someone won, or timeout)

## Move

A struct representing a move.
It also has helper functions to convert from/to a string.
It also check and apply it to a board.

## Score move

A move associated with a score.

## Terminal

A module to manage a game in the terminal (initialize and handle updates)

## IA

A module to manage a game viewed by the IA (initialize, handle updates, and calculate a move to return)

## Network

A module to manage a game via network (initialize, handle updates, and send/receive data by socket)
