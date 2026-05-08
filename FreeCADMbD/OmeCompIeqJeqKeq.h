/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "OmeCompIeqJeKeq.h"

namespace MbD {
    class OmeCompIeqJeqKeq : public OmeCompIeqJeKeq
    {
        //pomeiIeJeKepEJ pomeiIeJeKepEdotJ 
    public:
        OmeCompIeqJeqKeq() {}
        OmeCompIeqJeqKeq(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIeqJeKeq(frmi, frmj) {}
        OmeCompIeqJeqKeq(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) : OmeCompIeqJeKeq(frmi, frmj, efrmK, axisK) {}
        static std::shared_ptr<OmeCompIeqJeqKeq> With();
        static std::shared_ptr<OmeCompIeqJeqKeq> With(EndFrmsptr frmi, EndFrmsptr frmj);
        //static std::shared_ptr<OmeCompIeqJeqKeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        static std::shared_ptr<OmeCompIeqJeqKeq> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepEdotJ() override;

        FRowDsptr pomeiIeJeKepEJ, pomeiIeJeKepEdotJ;
    };
}
