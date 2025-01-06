//
// Created by jrzab on 1/6/2025.
//

#include "TipoVeiculo.h"

const char* STR_LIGEIRO = "LIGEIRO";
const char* STR_PESADO = "PESADO";
const char* STR_MOTOCICLO = "MOTOCICLO";
const char* STR_DESCONHECIDO = "DESCONHECIDO";

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

char* toString(TipoVeiculo tipoVeiculo) {
      switch (tipoVeiculo) {
            case LIGEIRO:
                  return STR_LIGEIRO;
            case PESADO:
                  return STR_PESADO;
            case MOTOCICLO:
                  return STR_MOTOCICLO;
            default:
                  return STR_DESCONHECIDO;
      }
}