#pragma once
#include "OmeCompIeJeKe.h"

namespace MbD {
    class OmeCompIeJeqKe : public OmeCompIeJeKe
    {
        //pomeiIeJeKepEJ pomeiIeJeKepEdotJ
    public:
        OmeCompIeJeqKe() {}
        OmeCompIeJeqKe(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIeJeKe(frmi, frmj) {}
        OmeCompIeJeqKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) : OmeCompIeJeKe(frmi, frmj, efrmK, axisK) {}
        static std::shared_ptr<OmeCompIeJeqKe> With();
        static std::shared_ptr<OmeCompIeJeqKe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        static std::shared_ptr<OmeCompIeJeqKe> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepEdotJ() override;

        FRowDsptr pomeiIeJeKepEJ, pomeiIeJeKepEdotJ;
    };
}
