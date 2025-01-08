#include <TipoVeiculo.h>
#include <stdio.h>
#include <stdlib.h>

#include "RegistoSensor.h"

void imprimirSeparador(void) {
    printf("\n\n=================================================\n");
}

void testeImprimitTipoVeiculo(void) {
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

    imprimirSeparador();
}

void testImprimirRegistoSensor(void) {
    // Criar um novo RegistoSensor e depois imprimir no terminal o resultado
    RegistoSensor registo = {"00-00-00", LIGEIRO, 100, "A1", "Lisboa"};
    char *registoSensorStr = registoSensorToString(registo);
    printf("%s", registoSensorStr);

    imprimirSeparador();

    // alterar todos os campos do registo sensor e imprimir novamente
    registo.matricula = "11-11-11";
    registo.tipoVeiculo = PESADO;
    registo.velocidade = 50;
    registo.via = "A2";
    registo.local = "Porto";

    // Imprimir sem atribuir à variável para testar o ponteiro:
        // Apesar da alteração acima, o resultado deve ser o mesmo que o anterior, uma vez que o ponteiro foi alterado
        // mas o conteúdo da string não.
    // printf("%s", registoSensorStr);
    // imprimirSeparador();

    // atribuindo à variável, para comparar com o resultado
    registoSensorStr = registoSensorToString(registo);
    printf("%s", registoSensorStr);

    // por fim, não esquecer de libertar a memória alocada
    free(registoSensorStr);
}

int main() {
    testeImprimitTipoVeiculo();
    testImprimirRegistoSensor();
    return 0;
}
