/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "EndFrameqc.h"

namespace MbD {
    class EndFrameqccq : public EndFrameqc
    {
        //targetFrame rpep pprOeOpEpEtarget 
    public:
        static std::shared_ptr<EndFrameqccq> With();
        void setTargetFrame(std::shared_ptr<EndFramec> targetFrm) override;

        EndFrmsptr targetFrame;
        FColDsptr rpep;
        FMatFColDsptr pprOeOpEpEtarget;
    };
}
