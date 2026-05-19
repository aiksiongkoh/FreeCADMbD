/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

 //#include <memory>
 //#include <vector>
 //#include <functional>

#include "SpatialContainerFrame.h"
#include "EndFrameq.h"
#include "FullColumn.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "MarkerFrame.h"

namespace MbD {
    class Part;
    class MarkerFrame;
    class EulerConstraint;
    class AbsConstraint;

    class AssemblyFrame : public SpatialContainerFrame
    {
        //ToDo: part iqX iqE qX qE qXdot qEdot qXddot qEddot aGeu aGabs markerFrames
    public:
        AssemblyFrame() {}
        AssemblyFrame(const std::string& str);
        static std::shared_ptr<AssemblyFrame> With();
        static std::shared_ptr<AssemblyFrame> With(const std::string& str);

        MkrFrmsptr createMarkerFrame(const std::string& str) override;
        System* root() override;
        void simUpdateAll() override;
        void setAssembly(System* x);
        System* getAssembly() const;

        void setPart(Part* x);
        FColFMatDsptr pAOppE() override;

        void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
        void reactivateRedundantConstraints() override;
        void constraintsReport() override;
        void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
        void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
        void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;

        System* assembly = nullptr; //Use raw pointer when pointing backwards.
    };
}

