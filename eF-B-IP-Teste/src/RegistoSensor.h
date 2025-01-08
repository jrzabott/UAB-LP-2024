//
// Created by jrzab on 1/6/2025.
//

#ifndef REGISTOSENSOR_H
#define REGISTOSENSOR_H

#include "TipoVeiculo.h"

typedef struct {
    char *matricula;
    TipoVeiculo tipoVeiculo;
    int velocidade;
    char *via;
    char *local;
} RegistoSensor;

char* registoSensorToString(RegistoSensor registo);

#endif //REGISTOSENSOR_H
