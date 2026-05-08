/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicCompiIeJe.h"
#include "DispIeJeO.h"

namespace MbD {
    class DispCompiIeJeO : public KinematicCompiIeJe
    {
    public:
        DispCompiIeJeO() {}
        DispCompiIeJeO(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) : KinematicCompiIeJe(frmi, frmj, axis) {}

        static std::shared_ptr<DispCompiIeJeO> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);

        void initialize() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void useUniqueDispIeJeO() override;

        // dispIeJeO is updated at global level
        std::shared_ptr<DispIeJeO> dispIeJeO; 

    protected:
        std::shared_ptr<KinematicVectorIeJe> kineVector() const override;
        FColDsptr currentVector() const override;
    };
}
