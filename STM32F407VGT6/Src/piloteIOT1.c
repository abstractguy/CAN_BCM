// piloteIOT1:
#include "main.h"
#include "piloteIOT1.h"

void piloteIOT1_metLaSortieA(unsigned char Valeur) {
  HAL_GPIO_WritePin(PILOTEIOT1_PORT, PILOTEIOT1_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteIOT1_initialise(void) {
  HAL_GPIO_WritePin(PILOTEIOT1_PORT, PILOTEIOT1_SORTIE, GPIO_PIN_RESET);  
}
