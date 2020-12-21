#include <dmt.hpp>

void dmt_init(void)
{
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
    }
    enet_deinitialize();
}