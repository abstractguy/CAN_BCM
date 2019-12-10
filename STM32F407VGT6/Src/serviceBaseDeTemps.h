#ifndef SERVICEBASEDETEMPS_H
  #define SERVICEBASEDETEMPS_H
  
  //MODULE: serviceBaseDeTemps
  //DESCRIPTION: pour mettre en place un service d'appels periodiques de fonctions
  //pointées par un tableau de pointeurs de fonctions. Le service met en place
  //une base de temps qui reposent sur l'emploi d'interruptions qui sont générées
  //par le compteur Timer6 du STM32F407 qui opère en mode Up
  
  //Dependances logicielles
  //(copiez et adaptez ce qui suit dans "main.h")
  //#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 3
  //pas de dépendances logicielles
  
  //Fonctions publiques:
  void serviceBaseDeTemps_initialise(void);
  
  //Variables publiques:
  extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);
#endif
