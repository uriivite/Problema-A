#!/bin/bash

echo Compilació i execució de signatures

make signatures
./signatures < fitxer_signatures.txt
