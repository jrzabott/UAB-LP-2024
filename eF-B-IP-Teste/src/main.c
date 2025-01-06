#include <TipoVeiculo.h>
#include <stdio.h>

#include "RegistoSensor.h"

int main() {
    // will print all vehicle types for testing
    printf("Ligeiro: ['%c'] ['%s']\n", getTipoVeiculo(LIGEIRO), TipoVeiculoToString(LIGEIRO));
    printf("Pesado: ['%c'] ['%s']\n", getTipoVeiculo(PESADO), TipoVeiculoToString(PESADO));
    printf("Motociclo: ['%c'] ['%s']\n", getTipoVeiculo(MOTOCICLO), TipoVeiculoToString(MOTOCICLO));

    // test some unsupported vehicle type
    printf("Desconhecido: ['%c'] ['%s']\n", getTipoVeiculo(DESCONHECIDO), TipoVeiculoToString(DESCONHECIDO));

    printf("\n\n=================================================\n");

    // Criar um novo RegistoSensor e depois imprimir no terminal o resultado
    RegistoSensor registo = {"00-00-00", LIGEIRO, 100, "A1", "Lisboa"};
    printf("%s", RegistoSensorToString(registo));
    return 0;
}
