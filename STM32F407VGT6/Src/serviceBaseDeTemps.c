// serviceBaseDeTemps:
#include "main.h"
#include "piloteTimer6Up.h"
#include "serviceBaseDeTemps.h"

void serviceBaseDeTemps_gere(void) {
  for (unsigned char i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++) {
    serviceBaseDeTemps_execute[i]();
  }
}

void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);

void serviceBaseDeTemps_initialise(void) {
  for (unsigned char i = 0; i < SERVICEBASEDETEMPS_NOMBRE_DE_PHASES; i++) {
    serviceBaseDeTemps_execute[i] = neFaitRien;
  }
  
  piloteTimer6Up_execute = serviceBaseDeTemps_gere;
}
