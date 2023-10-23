# Food Web Analysis Project

## Introduction

This project performs a food web analysis by constructing a dynamically allocated struct array of organisms based on user-specified predator-prey relationships. The analysis identifies relationships between organisms in the food web and reassesses these relationships upon the extinction of a species. The extinction requires a complete removal of the organism from the food web, affecting both the array of organisms and the set of predator-prey relationships.

## Organization and Structure

### Org Struct & Dynamic Arrays

Organisms are represented by the `Org` struct:

```c
typedef struct Org_struct {
    char name[20];
    int* prey; // Dynamic array of indices
    int numPrey;
} Org;
```

The food web is represented as a dynamic array of `Org` structs, referred to as `web`. The array size (`numOrgs`) and organisms' names are initialized based on user input.

### Starter Code & Input Files

The starter code includes the `Org` struct definition, function headers, and the initial setup of the `web` array. The program reads user input for the number of organisms, their names, and predator-prey relationships.

Compile and run the program with input redirection:

```bash
gcc main.c -o prog.out
./prog.out < InputFileName.txt
```

### Programming Task I - buildWeb()

Implement the `buildWeb()` function to add predator-prey relationships to the food web. This involves memory allocation for prey arrays, appending new prey indices, and updating the size of prey arrays. Ensure memory efficiency and correctness in representing the food web.

### Programming Task II - Food Web Analysis

Conduct analyses to identify:
- Apex predators
- Producers
- Most flexible eaters
- Tastiest food
- Heights of organisms in the food web
- Categorization of organisms (producer, herbivore, omnivore, carnivore)

Follow the detailed instructions in the provided description for each analysis.

### Programming Task III - Species Extinction

Implement functionality to handle the extinction of a species, updating the food web accordingly. This involves removing the extinct organism and updating the predator-prey relationships.

## Compilation and Running

Compile the program with:

```bash
gcc main.c -o prog.out
```

Run the program with an input file:

```bash
./prog.out < InputFileName.txt
```

## Contribution and Feedback

Feel free to contribute to this project or provide feedback by opening issues or pull requests on the project's GitHub repository.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
