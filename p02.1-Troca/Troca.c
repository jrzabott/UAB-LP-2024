#include <stdio.h>
//
// Created by jrzab on 2024-03-11.
//
int main() {
    // Three int vars
    int x = 3;
    int y = 7;
    int aux;

    // Swap x and y values using a temporary variable
    aux = x;
    x = y;
    y = aux;

    // print results on screen
    printf("x: %d, y:%d", x, y);
}