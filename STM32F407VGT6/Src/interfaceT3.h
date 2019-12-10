#ifndef INTERFACET3_H
  #define INTERFACET3_H
  // DESCRIPTION: pour interagir avec un temoin lumineux T3 relie a un STM32F407.
  // Copiez et adaptez ce qui suit dans "main.h".
  // #define INTERFACET3_VALEUR_POUR_ALLUMER  1   
  // #define INTERFACET3_VALEUR_POUR_ETEINDRE 0

  void interfaceT3_allume(void);
  void interfaceT3_eteint(void);
  void interfaceT3_initialise(void);
#endif
