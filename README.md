# Project Summary 
This academic project, designed for my Data Structures and Algorithms class, practically implements both a binary tree and a max heap in C. The project is divided into two major components:
## Part 1 - Fully Parenthesized Expression Tree
This section implements a parser and binary expression tree for arithmetic expressions of the form: '(((x1+5.12)*(x2-7.68))/x3)'
The parser constructs the tree from a fully parenthesized expression containing binary operators (+,-,*,/), floating point constants (format: Y.YY), and variables (x1-x9). The tree is then constructed using dynamic memory allocation and supports three traversal programs (each with its own executable, which can be generated via the make or make all command) executed as follows:
- Preorder: ./preorder '(((x1+5.12)*(x2-7.68))/x3)'
- Inorder: ./inorder '(((x1+5.12)*(x2-7.68))/x3)'
- Postorder: ./postorder '(((x1+5.12)*(x2-7.68))/x3)'
A full expression evaluator is also included, which performs expression calculation using provided variable assignments, implementing custom rounding rules based on the 3rd decimal digit, along with detecting syntax errors, division by zero, or undefined variables. Ran as follows:
- ./calculate '(((x1+5.12)*(x2-7.68))/x3)' 'x1=0.25;x2=0.67;x3=8.46'
## Part 2 - Max-Heap Construction from File Input
This program reads 200 two-digit integers from a text file f.dat and loads them into a 20 × 10 array.
The program treats each row as an object such that the first 3 integers are the heap key, while the remaining 7 integers are the payload. A max heap is then built using array-based complete binary tree formulas and a reverse-order percolate-down heapify algorithm. The program outputs he heap in the exact f.dat format, handling missing file or insufficient data errors. 

A single makefile is provided, which can be run using "make" or "make all", producing executables for preorder, inorder, postorder, calculate, and heap in ./bin/ folder.
Compilation uses: clang -std=c99 -Wall -pedantic

This project was in VSCode SOCS and uploaded to GitHub.
- December 11th, 2025
- Evan Leonard
