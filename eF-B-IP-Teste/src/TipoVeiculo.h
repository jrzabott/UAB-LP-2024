//
// Created by jrzab on 1/6/2025.
//

#ifndef TIPOVEICULO_H
#define TIPOVEICULO_H

extern const char* STR_LIGEIRO;
extern const char* STR_PESADO;
extern const char* STR_MOTOCICLO;
extern const char* STR_DESCONHECIDO;

typedef enum {
    LIGEIRO,        // Ligeiro
    PESADO,         // Pesado
    MOTOCICLO,      // Motociclo
    DESCONHECIDO    // Desconhecido = ?
} TipoVeiculo;

char getTipoVeiculo(TipoVeiculo tipoVeiculo);
TipoVeiculo getTipoVeiculoByChar(char tipoVeiculoChar);
char* toString(TipoVeiculo tipoVeiculo);

#endif //TIPOVEICULO_H
