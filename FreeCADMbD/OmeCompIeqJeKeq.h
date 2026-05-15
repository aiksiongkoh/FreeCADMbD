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
        OmeCompIeqJeKeq(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : OmeCompIeJeKe(frmi, frmj, frmk, axisk) {}
        static std::shared_ptr<OmeCompIeqJeKeq> With();
        static std::shared_ptr<OmeCompIeqJeKeq> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepEdotI() override;

        FRowDsptr pomeiIeJeKepEI, pomeiIeJeKepEdotI, pomeiIeJeKepEK;
    };
}
