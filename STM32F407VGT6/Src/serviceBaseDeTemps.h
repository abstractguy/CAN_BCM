#ifndef SERVICEBASEDETEMPS_H
  #define SERVICEBASEDETEMPS_H
  // DESCRIPTION: pour mettre en place un service d'appels periodiques de fonctions
  // point�es par un tableau de pointeurs de fonctions. Le service met en place
  // une base de temps qui reposent sur l'emploi d'interruptions qui sont g�n�r�es
  // par le compteur Timer6 du STM32F407 qui op�re en mode Up.
     
  // Copiez et adaptez ce qui suit dans "main.h".
  // #define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 3
  
  void serviceBaseDeTemps_initialise(void);
  void serviceBaseDeTemps_gere(void);
  extern void (*serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_NOMBRE_DE_PHASES])(void);
#endif
