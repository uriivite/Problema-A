#!/bin/bash

echo Compilació i execució de LHS

make LHS
./LHS < fitxer_LHS.txt
