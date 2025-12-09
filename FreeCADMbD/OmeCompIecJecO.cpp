#include "OmeCompIecJecO.h"

using namespace MbD;

void OmeCompIecJecO::withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axs)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    axis = axs;
}
