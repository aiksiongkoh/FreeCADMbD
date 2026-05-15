#pragma once
#include "OmeCompIeJeKe.h"

namespace MbD {
    class OmeCompIeJeqKe : public OmeCompIeJeKe
    {
        //pomeiIeJeKepEJ pomeiIeJeKepEdotJ
    public:
        OmeCompIeJeqKe() {}
        OmeCompIeJeqKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : OmeCompIeJeKe(frmi, frmj, frmk, axisk) {}
        static std::shared_ptr<OmeCompIeJeqKe> With();
        static std::shared_ptr<OmeCompIeJeqKe> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepEdotJ() override;

        FRowDsptr pomeiIeJeKepEJ, pomeiIeJeKepEdotJ;
    };
}
