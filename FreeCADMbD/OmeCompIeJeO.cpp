#include "OmeCompIeJeO.h"

using namespace MbD;

void OmeCompIeJeO::withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axs)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    axis = axs;
}

void OmeCompIeJeO::simUpdateAll()
{
    //omeIeJeO = omeOJeO - omeOIeO
    throw SimulationStoppingError("To be implemented.");
}
