/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "OmeCompIeqcJecKeqc.h"

namespace MbD {
    class OmeCompIeqcJeqcKeqc : public OmeCompIeqcJecKeqc
    {
        //pomeiIeJeKepEJ pomeiIeJeKepEdotJ 
    public:
        OmeCompIeqcJeqcKeqc() {}
        OmeCompIeqcJeqcKeqc(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIeqcJecKeqc(frmi, frmj) {}
        OmeCompIeqcJeqcKeqc(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK) : OmeCompIeqcJecKeqc(frmi, frmj, efrmK, axisK) {}
        static std::shared_ptr<OmeCompIeqcJeqcKeqc> With();
        static std::shared_ptr<OmeCompIeqcJeqcKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
        //static std::shared_ptr<OmeCompIeqcJeqcKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        static std::shared_ptr<OmeCompIeqcJeqcKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        void initialize() override;

        void simUpdateAll() override;
        FRowDsptr pvaluepEJ() override;
        FRowDsptr pvaluepEdotJ() override;

        FRowDsptr pomeiIeJeKepEJ, pomeiIeJeKepEdotJ;
    };
}
