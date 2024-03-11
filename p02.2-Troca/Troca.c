#include <stdio.h>
//
// Created by jrzab on 2024-03-11.
//
int main() {
    // Three int vars
    int x = 3;
    int y = 7;

    // Swap x and y values algebrically
    x =+ y; // TODO - check if this could overflow (?)
    y = x - y;
    x = x - y;

    // print results on screen
    printf("x: %d, y:%d", x, y);
}