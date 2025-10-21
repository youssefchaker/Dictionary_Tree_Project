# Dictionary Tree Project

This project is a C program that builds a dictionary from a list of words using a binary search tree and displays information about the dictionary.

## Features

*   Builds a dictionary from a text file (`dico.txt`).
*   Counts the occurrences of each word.
*   Displays the dictionary in a table format.
*   Shows the total number of words and the number of unique words.
*   Visualizes the dictionary as a binary search tree in ASCII format.

## How to Build and Run

### Prerequisites

*   A C compiler (like `gcc`).
*   `make` utility.

### Building

To build the project, run the `make` command in the project's root directory:

```sh
make
```

This will create an executable file named `Dictionary_Tree_Project`.

### Running

To run the program, execute the following command:

```sh
./Dictionary_Tree_Project
```

The program will then prompt you to choose a mode and the number of words to process from the `dico.txt` file.

### Cleaning

To remove the compiled files, run:

```sh
make clean
```

## File Structure

*   `main.c`: The main entry point of the program.
*   `dico.h`, `dico.c`: Contain the logic for the dictionary, including functions for inserting words, counting occurrences, and displaying the dictionary.
*   `arbre.h`, `arbre.c`: Define the binary search tree data structure and related functions.
*   `dico.txt`: The text file containing the words to be used for building the dictionary.
*   `Makefile`: The build script for the project.
