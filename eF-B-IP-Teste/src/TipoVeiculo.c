//
// Created by jrzab on 1/6/2025.
//

#include "TipoVeiculo.h"

#include <stdio.h>
#include <stdlib.h>

const char *STR_LIGEIRO = "LIGEIRO";
const char *STR_PESADO = "PESADO";
const char *STR_MOTOCICLO = "MOTOCICLO";
const char *STR_DESCONHECIDO = "DESCONHECIDO";

char getTipoVeiculo(TipoVeiculo tipoVeiculo) {
    switch (tipoVeiculo) {
        case LIGEIRO:
            return 'L';
        case PESADO:
            return 'P';
        case MOTOCICLO:
            return 'M';
        default:
            return '?';
    }
}

TipoVeiculo getTipoVeiculoByChar(char tipoVeiculoChar) {
    switch (tipoVeiculoChar) {
        case 'L':
            return LIGEIRO;
        case 'P':
            return PESADO;
        case 'M':
            return MOTOCICLO;
        default:
            return DESCONHECIDO;
    }
}

char *TipoVeiculoToString(TipoVeiculo tipoVeiculo) {
    const char *tipoVeiculoStr;
    switch (tipoVeiculo) {
        case LIGEIRO:
            tipoVeiculoStr = STR_LIGEIRO;
        case PESADO:
            tipoVeiculoStr = STR_PESADO;
        case MOTOCICLO:
            tipoVeiculoStr = STR_MOTOCICLO;
        default:
            tipoVeiculoStr = STR_DESCONHECIDO;
    }

    // para calcular o tamanho do buffer necessário para a string
    // recorro à função snprintf com passando NULL como buffer, o que permite que calcule o tamanho da string final
    // sem a escrever em lado nenhum
    int len = snprintf(NULL, 0, "%s", tipoVeiculoStr);
    char *str = (char *) malloc(len + 1);
    snprintf(str, len + 1, "%s", tipoVeiculoStr);
    return str;
}
