//
// Created by jrzab on 1/6/2025.
//

#include "RegistoSensor.h"
#include "TipoVeiculo.h"

#include <stdio.h>
#include <stdlib.h>

char* RegistoSensorToString(RegistoSensor registo) {
    char *format= "Matricula: %s\nTipo: %s\nVelocidade: %d\nVia: %s\nLocal: %s\n";
    int len = snprintf(NULL, 0, format,
        registo.matricula,
        TipoVeiculoToString(registo.tipoVeiculo),
        registo.velocidade,
        registo.via,
        registo.local);

    char *str = (char *) malloc(len + 1);
    snprintf(str, len + 1, format,
        registo.matricula,
        TipoVeiculoToString(registo.tipoVeiculo),
        registo.velocidade,
        registo.via,
        registo.local);
    return str;
}
