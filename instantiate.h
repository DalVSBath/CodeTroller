// instantiate_all.h ---------------------------------------------------
#pragma once
#include "A_LED_Controller.h"

/* touch the type to make the compiler generate it */
template<int... Pins>
inline void inst() { (void)sizeof(LED_Controller<Pins...>); }
