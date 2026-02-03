#pragma once
#include "OmeCompIecJecKec.h"

namespace MbD {
    class OmeCompIecJeqcKec : public OmeCompIecJecKec
    {
        //pomeiIeJeKepEJ pomeiIeJeKepEdotJ 
    public:
        OmeCompIecJeqcKec() {}
        OmeCompIecJeqcKec(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIecJecKec(frmi, frmj) {}
        OmeCompIecJeqcKec(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) : OmeCompIecJecKec(frmi, frmj, efrmK, axisK) {}
        static std::shared_ptr<OmeCompIecJeqcKec> With();
        static std::shared_ptr<OmeCompIecJeqcKec> With(EndFrmsptr frmi, EndFrmsptr frmj);
        static std::shared_ptr<OmeCompIecJeqcKec> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepEdotJ() override;

        FRowDsptr pomeiIeJeKepEJ, pomeiIeJeKepEdotJ;
    };
}
