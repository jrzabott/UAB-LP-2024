#include <TipoVeiculo.h>
#include <stdio.h>
#include <stdlib.h>

#include "RegistoSensor.h"

int main() {
    char *tipo_veiculo_to_string = TipoVeiculoToString(LIGEIRO);
    // will print all vehicle types for testing
    printf("Ligeiro: ['%c'] ['%s']\n", getTipoVeiculo(LIGEIRO), tipo_veiculo_to_string);
    free(tipo_veiculo_to_string);

    tipo_veiculo_to_string = TipoVeiculoToString(PESADO);
    printf("Pesado: ['%c'] ['%s']\n", getTipoVeiculo(PESADO), tipo_veiculo_to_string);
    free(tipo_veiculo_to_string);

    tipo_veiculo_to_string = TipoVeiculoToString(MOTOCICLO);
    printf("Motociclo: ['%c'] ['%s']\n", getTipoVeiculo(MOTOCICLO), tipo_veiculo_to_string);
    free(tipo_veiculo_to_string);

    // test some unsupported vehicle type
    tipo_veiculo_to_string = TipoVeiculoToString(DESCONHECIDO);
    printf("Desconhecido: ['%c'] ['%s']\n", getTipoVeiculo(DESCONHECIDO), tipo_veiculo_to_string);
    free(tipo_veiculo_to_string);

    printf("\n\n=================================================\n");

    // Criar um novo RegistoSensor e depois imprimir no terminal o resultado
    RegistoSensor registo = {"00-00-00", LIGEIRO, 100, "A1", "Lisboa"};
    char *registo_sensor_to_string = RegistoSensorToString(registo);
    printf("%s", registo_sensor_to_string);
    free(registo_sensor_to_string);
    return 0;
}
