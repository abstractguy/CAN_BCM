#ifndef PILOTEIOT4_H
  #define PILOTEIOT4_H
  
  //MODULE: piloteIOT4
  //DESCRIPTION: pour commander la sortie IOT4.
  //DEFINITIONS REQUISES PAR LE MODULE:
  //Dependances materielles
  //(copiez et adaptez ce qui suit dans "main.h")
  //#define PILOTEIOT4_PORT LD5_GPIO_Port
  //#define PILOTEIOT4_SORTIE  LD5_Pin
  
  //Fonctions publiques:
  void piloteIOT4_initialise(void);
  void piloteIOT4_metLaSortieA(unsigned char Valeur);
#endif
