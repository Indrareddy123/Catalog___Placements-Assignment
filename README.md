# Catalog Placements Assignment

## Instructions

1. Compile the `main.cpp` file using g++:
   ```
   g++ main.cpp -o main
   ```

2. Run with a JSON file:
   ```
   ./main test1.json
   ```

## Description

The program reads the secret sharing keys from a JSON file and reconstructs the original secret using Lagrange interpolation, even in the presence of one wrong key.