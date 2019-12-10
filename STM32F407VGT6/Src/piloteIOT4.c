// piloteIOT4:
#include "main.h"
#include "piloteIOT4.h"

//Definitions de fonctions publiques:
void piloteIOT4_metLaSortieA(unsigned char Valeur) {
  HAL_GPIO_WritePin(PILOTEIOT4_PORT, PILOTEIOT4_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteIOT4_initialise(void) {
  HAL_GPIO_WritePin(PILOTEIOT4_PORT, PILOTEIOT4_SORTIE, GPIO_PIN_RESET);  
}
