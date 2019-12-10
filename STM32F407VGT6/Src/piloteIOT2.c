// piloteIOT2:
#include "main.h"
#include "piloteIOT2.h"

//Definitions de fonctions publiques:
void piloteIOT2_metLaSortieA(unsigned char Valeur) {
  HAL_GPIO_WritePin(PILOTEIOT2_PORT, PILOTEIOT2_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteIOT2_initialise(void) {
  HAL_GPIO_WritePin(PILOTEIOT2_PORT, PILOTEIOT2_SORTIE, GPIO_PIN_RESET);  
}
