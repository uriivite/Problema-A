#!/bin/bash

echo Compilació i execució de jaccard

make jaccard
./jaccard < fitxer_jaccard.txt
