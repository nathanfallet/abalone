# Possible moves and related checks

## Code structure

A main function with a switch case, and a dedicated function for each case.
Functions return `1` if move is valid and was applied, or `0` otherwise.

## Calculating deltas

Getting a move, for example `C3:C4`, we convert it to the table coordinates,
`((2, 2), (2, 3))` and we calculate the variation in line and col as `dx` and `dy` (always positive).

## Functions to read and write in the table

We add an extra layer to handle reading and writing outside of the table:
- read outside returns empty
- write outside is ignored

So that we can keep the same logic.

## Cases

### `dx = 0 and dy = 1` or `dx = 1 and dy = 0`

The move is valid if:
- the source color is mine
- the target color is empty

Then to apply the move:
- set the target color to source color
- set the source color to empty

### `dx = 0 and dy = 2` or `dx = 2 and dy = 0`

The move is valid if:
- the source and the next color are mine

**Empty target?**

Then to apply the move:
- set the target color to source color
- set the source color to empty

**Enemy target?**

The move is valid if:
- the target next color is empty

Then to apply the move:
- set the target color to source color
- set the target next color to enemy color
- set the source color to empty
- 
### `dx = 0 and dy = 3` or `dx = 3 and dy = 0`

The move is valid if:
- the source and the next color are mine

**Empty target?**

Then to apply the move:
- set the target color to source color
- set the source color to empty

**Enemy target? (one)**

The move is valid if:
- the target next color is empty

Then to apply the move:
- set the target color to source color
- set the target next color to enemy color
- set the source color to empty

**Enemy target? (two)**

The move is valid if:
- the target double next color is empty

Then to apply the move:
- set the target color to source color
- set the target next color to source color
- set the target double next color to enemy color
- set the source color to empty
- set the source next color to empty

### `dx = 1 and dy = 1`

The move is valid if:
- the source color is mine
- the target color is empty
- the two remaining colors are one mine and one empty

Then to apply the move:
- invert mine and empty on all the area

### `dx = 2 and dy = 1` or `dx = 1 and dy = 2`

The move is valid if:
- the source color is mine
- the target color is empty
- the four remaining colors are two mine and two empty, correctly placed

Then to apply the move:
- invert mine and empty on all the area
