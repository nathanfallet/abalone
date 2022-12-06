# Code style

## Language

Everything should be named in English (`en_US`).

## Comments

```c
// Temporary comment
// TODO: Things to do
/* Definitive comment */
```

## Imports

**In `module_name.h`**:
Only import required local modules (e.g.: `#include "other.h"`)

**In `module_name.c`**:
Import required system modules (e.g.: `#include <stdio.h>`), and only the header for this module (only `#include "module_name.h"`, no other local module)

## Function name

```c
void module_name_function_name();
```

## Struct name (or enum)

```c
typedef struct {

} MyStruct;
```
