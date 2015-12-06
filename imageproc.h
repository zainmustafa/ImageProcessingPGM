// Written by Syed Hammad Ahmed
// OOP@DSU Fall 2015
// YOU MAY NOT MODIFY THIS FILE 

#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H

#include <string>
using namespace std;

int** readFile(string fileName, int& rows, int& cols, int& max);
void writeFile(string fileName, int** image, int rows, int cols, int max); // called from each of the following functions, to create a new file: see document for naming of new file
void invertColors(string fileName, int** image, int rows, int cols, int max); // makes brighter dark, and vice versa (see sample image)
void shrink2x(string fileName, int** image, int rows, int cols, int max);  // makes the image half the size
void enlarge2x(string fileName, int** image, int rows, int cols, int max); // makes the image twice the size
void brighten(string fileName, int** image, int rows, int cols, int max);  // brightens the image by 10%
void darken(string fileName, int** image, int rows, int cols, int max);    // darkens the image by 10%
void crop(string fileName, int** image, int rows, int cols, int max, int x1, int y1, int x2, int y2);  // see assignment document
void deallocate(int** image, int rows); // deletes the memory allocated by readFile function

#endif