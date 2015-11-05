# nn-xo

Pokusíme se vytvořit vícevrstvout neuronovou sít která bude rozpoznávat stav koncové hry piškvorek, tj {vyhrál X, vyhrál 0, remíza}.

## Stages
1. Vstupem neuronky bude pole o 9 prvcích. Každý prvek pole bude nabývat hodnoty z množiny {X, O, Prázné}.
2. Vstupem neuronky bude bitmapa o velikosti 9x9. Jednotlivá pole budou velikosti 3x3.
3. Vsupem neuronky bude bitmapa o velikosti zatím neznámé. Bitmapa bude rozpoznávat hru zakreslenou pomocí ruky.

## Utilities
* Generátor všech možných koncovích her.
* Generátor bitmapy pro stage 2.

## Training Data set
https://archive.ics.uci.edu/ml/datasets/Tic-Tac-Toe+Endgame
