// processusClignotant:
#include "main.h"
#include "piloteCAN1.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
#include "interfaceT3.h"
#include "interfaceT4.h"
#include "processusClignotant.h"

#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS \
  * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS \
  * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS \
  * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS \
  * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  / 1000.0)

void processusClignotant_eteintUnPeu(void);
void processusClignotant_allumeUnPeu(void);
void processusClignotant_eteintLongtemps(void);
void processusClignotant_allumeLongtemps(void);

unsigned int processusClignotant_compteur;
unsigned char processusClignotant_donneesRecues[8];  
unsigned char processusClignotant_donneesATransmettre[8];

void processusClignotant_eteintUnPeu(void) {
  if (++processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT)
    return;
  
  processusClignotant_compteur = 0;
  
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_allumeUnPeu;
  
  piloteCAN1_transmetDesDonnes(PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION,
                               processusClignotant_donneesATransmettre,
                               1);
}

void processusClignotant_allumeUnPeu(void) {
  if (++processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME)
    return;
  
  piloteCAN1_litUnMessageRecu(processusClignotant_donneesRecues); 
  
  processusClignotant_compteur = 0;

  if (processusClignotant_donneesRecues[0] == 0x03) {
    interfaceT1_allume();
    interfaceT2_allume();
    interfaceT3_allume();
    interfaceT4_allume();
  } else {
    interfaceT1_eteint();
    interfaceT2_eteint();
    interfaceT3_eteint();
    interfaceT4_eteint();
  }

  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintLongtemps;  
}

void processusClignotant_eteintLongtemps(void) {
  if (++processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_LONG_ETEINT)
    return;
  
  processusClignotant_compteur = 0;
  
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_allumeLongtemps;
}

void processusClignotant_allumeLongtemps(void) {
  if (++processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_LONG_ALLUME)
    return;
  
  processusClignotant_compteur = 0;
  
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;  
}

void processusClignotant_initialise(void) {
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;
}
