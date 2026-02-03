/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "OmeCompIecJecKec.h"

namespace MbD {
    class OmeCompIeqcJecKeqc : public OmeCompIecJecKec
    {
        //pomeiIeJeKepEI pomeiIeJeKepEdotI 
    public:
        OmeCompIeqcJecKeqc() {}
        OmeCompIeqcJecKeqc(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIecJecKec(frmi, frmj) {}
        OmeCompIeqcJecKeqc(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) : OmeCompIecJecKec(frmi, frmj, efrmK, axisK) {}
        static std::shared_ptr<OmeCompIeqcJecKeqc> With();
        static std::shared_ptr<OmeCompIeqcJecKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepEdotI() override;

        FRowDsptr pomeiIeJeKepEI, pomeiIeJeKepEdotI, pomeiIeJeKepEK;
    };
}
