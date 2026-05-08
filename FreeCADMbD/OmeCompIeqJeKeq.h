/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "OmeCompIeJeKe.h"

namespace MbD {
    class OmeCompIeqJeKeq : public OmeCompIeJeKe
    {
        //pomeiIeJeKepEI pomeiIeJeKepEdotI 
    public:
        OmeCompIeqJeKeq() {}
        OmeCompIeqJeKeq(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIeJeKe(frmi, frmj) {}
        OmeCompIeqJeKeq(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) : OmeCompIeJeKe(frmi, frmj, efrmK, axisK) {}
        static std::shared_ptr<OmeCompIeqJeKeq> With();
        static std::shared_ptr<OmeCompIeqJeKeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepEdotI() override;

        FRowDsptr pomeiIeJeKepEI, pomeiIeJeKepEdotI, pomeiIeJeKepEK;
    };
}
