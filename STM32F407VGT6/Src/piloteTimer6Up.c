// piloteTimer6Up:
#include "main.h"
#include "piloteTimer6Up.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern TIM_HandleTypeDef htim6; // defini pas le hal et declare ici.

void (*piloteTimer6Up_execute)(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim == &htim6) {
    piloteTimer6Up_execute();
  }
}

void piloteTimer6Up_permetLesInterruptions(void) {
  HAL_TIM_Base_Start_IT(&htim6);  
}

void piloteTimer6Up_initialise(void) {
  piloteTimer6Up_execute = neFaitRien;  
}
