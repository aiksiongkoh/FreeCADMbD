/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "EndFrameq.h"

namespace MbD {
    class EndFrameqccq : public EndFrameq
    {
        //targetFrame rpep pprOeOpEpEtarget 
    public:
        static std::shared_ptr<EndFrameqccq> With();
        void setTargetFrame(EndFrmsptr targetFrm) override;

        EndFrmsptr targetFrame;
        FColDsptr rpep;
        FMatFColDsptr pprOeOpEpEtarget;
    };
}
