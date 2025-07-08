// instantiate_all.cpp -------------------------------------------------
#include "instantiate.h"


/* --------------------------------------------------------------------
   Recursively build every subset of the pin set {BEGIN … END}
   that is 1-MAXLEN elements long, and instantiate LED_Controller
   for each subset via inst<Pins...>().               C++17
   ------------------------------------------------------------------ */

/* ---------------- primary template -------------------------------- */
template<
    int CUR,            // pin we are looking at now
    int END,            // highest pin we allow
    int MAXLEN,         // subset size limit
    int... Pins         // pins chosen so far
>
struct expand
{
    static void run()
    {
        /* --------- emit the subset collected up to this point ------- */
        if constexpr (sizeof...(Pins) > 0)            // ignore empty set
            inst<Pins...>();                          // forces LED_Controller

        /* --------- stop once we have passed END -------------------- */
        if constexpr (CUR > END) return;
        if constexpr (CUR <= END) {
            /* ---------- branch 1 : **take** CUR (if space left) -------- */
            if constexpr (sizeof...(Pins) < MAXLEN)
                expand<CUR + 1, END, MAXLEN, Pins..., CUR>::run();

            /* ---------- branch 2 : **skip** CUR ------------------------ */
            expand<CUR + 1, END, MAXLEN, Pins...>::run();
        }
    }
};

/* --------------------------------------------------------------------
   Kick everything off once at namespace scope.  This is evaluated at
   load-time but all the heavy work (the recursion + instantiations)
   happens at compile time, so the MCU does nothing at run time.
   ------------------------------------------------------------------ */
namespace {
    const bool generated = ( expand<10, 18, 5>::run(), true );
}
