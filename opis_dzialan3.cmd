#define ROTATE_SPEED 30
/*
* Przykładowy zestaw poleceń
*/
Begin_Parallel_Actions
Set Podstawa 2 0 30 // Polozenie obiektu A
Set Podstawa2 10 10 0 // Polozenie obiektu B
End_Parallel_Actions

Begin_Parallel_Actions
Rotate Podstawa ROTATE_SPEED 40
End_Parallel_Actions
Begin_Parallel_Actions Pause 1000 /* Zawieszenie na 1 sek. */ End_Parallel_Actions

Begin_Parallel_Actions
Move Podstawa 10 10
Rotate Podstawa2 ROTATE_SPEED 60 /* Rotate i Move wykonywane razem */
Move Podstawa2 10 10 /* powoduja jazde po luku */
End_Parallel_Actions
