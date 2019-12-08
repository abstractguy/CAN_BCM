//processusClignotant:
//Historique: 
// 2019-10-27, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "piloteCAN1.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT1.h"
#include "processusClignotant.h"

//Definitions privees
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ETEINT_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_COURT_ALLUME_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ETEINT (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ETEINT_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)
#define PROCESSUSCLIGNOTANT_COMPTE_LONG_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_LONG_ALLUME_EN_MS * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ \
  /1000.0)

//Declarations de fonctions privees:
void processusClignotant_eteintUnPeu(void);
void processusClignotant_allumeUnPeu(void);
void processusClignotant_eteintLongtemps(void);
void processusClignotant_allumeLongtemps(void);

//Definitions de variables privees:
unsigned int processusClignotant_compteur;
unsigned char processusClignotant_donneesRecues[8];  
unsigned char processusClignotant_donneesATransmettre[8];

//Definitions de fonctions privees:
void processusClignotant_eteintUnPeu(void) {
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_COURT_ETEINT)
    return;
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_allumeUnPeu;
  
  piloteCAN1_transmetDesDonnes(PILOTECAN1_IDENTIFICATION_EN_TRANSMISSION,
                               processusClignotant_donneesATransmettre,
                               1);
}

void processusClignotant_allumeUnPeu(void)
{
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_COURT_ALLUME)
    return;
  
  piloteCAN1_litUnMessageRecu(processusClignotant_donneesRecues); 
  
  processusClignotant_compteur = 0;

  if (processusClignotant_donneesRecues[0] == 0x03) interfaceT1_allume();
  else interfaceT1_eteint();

  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintLongtemps;  
}

void processusClignotant_eteintLongtemps(void)
{
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_LONG_ETEINT)
    return;
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_allumeLongtemps;
}

void processusClignotant_allumeLongtemps(void)
{
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_LONG_ALLUME)
    return;
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;  
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusClignotant_initialise(void) {
  //processusClignotant_donneesATransmettre[0] = 0x01;
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] =
      processusClignotant_eteintUnPeu;
}
