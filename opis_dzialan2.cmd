#define ROTATE_SPEED     30
/*
 *  Przykładowy zestaw poleceń
 */
  Set   Podstawa 2 0 -30    // Polozenie obiektu A 
  //Set   Podstawa 10 10 0   // Polozenie obiektu B
  Rotate Podstawa ROTATE_SPEED 40
  Pause 1000 /* Zawieszenie na 1 sek. */
  Move  Podstawa  10 5
  Rotate Podstawa ROTATE_SPEED 60 /* Rotate i Move wykonywane razem */
  Move  Podstawa 10 5            /* powoduja jazde po luku         */
