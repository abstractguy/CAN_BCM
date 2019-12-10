// piloteIOT3:
#include "main.h"
#include "piloteIOT3.h"

void piloteIOT3_metLaSortieA(unsigned char Valeur) {
  HAL_GPIO_WritePin(PILOTEIOT3_PORT, PILOTEIOT3_SORTIE, (GPIO_PinState)Valeur);  
}

void piloteIOT3_initialise(void) {
  HAL_GPIO_WritePin(PILOTEIOT3_PORT, PILOTEIOT3_SORTIE, GPIO_PIN_RESET);  
}
