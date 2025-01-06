#include <TipoVeiculo.h>
#include <stdio.h>

struct RegistoSensor {
      char *matricula;
      TipoVeiculo tipoVeiculo;
      int velocidade;
      char *via;
      char *local;
};

int main() {
      // will print all vehicle types for testing
      printf("Ligeiro: ['%c'] ['%s']\n", getTipoVeiculo(LIGEIRO), toString(LIGEIRO));
      printf("Pesado: ['%c'] ['%s']\n", getTipoVeiculo(PESADO), toString(PESADO));
      printf("Motociclo: ['%c'] ['%s']\n", getTipoVeiculo(MOTOCICLO), toString(MOTOCICLO));

      // test some unsupported vehicle type
        printf("Desconhecido: ['%c'] ['%s']\n", getTipoVeiculo(DESCONHECIDO), toString(DESCONHECIDO));
      return 0;
}

