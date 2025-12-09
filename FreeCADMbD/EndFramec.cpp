/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <assert.h>
#include <memory>

#include "EndFramec.h"
#include "PartFrame.h"
#include "MarkerFrame.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<EndFramec> EndFramec::With(const std::string& str)
{
    auto inst = std::make_shared<EndFramec>(str);
    inst->initialize();
    return inst;
}

void EndFramec::initialize()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr EndFramec::aAeO() const
{
    return aAOe->transpose();
}

System* EndFramec::root()
{
    return markerFrame->root();
}

void EndFramec::setMarkerFrame(MarkerFrame* markerFrm)
{
    markerFrame = markerFrm;
}

MarkerFrame* EndFramec::getMarkerFrame() const
{
    return markerFrame;
}

void EndFramec::initEndFrameqct()
{
    throw SimulationStoppingError("To be implemented.");
}

void EndFramec::initEndFrameqct2()
{
    throw SimulationStoppingError("To be implemented.");
}

void EndFramec::calcPostDynCorrectorIteration()
{
    rOeO = markerFrame->rOmO;
    aAOe = markerFrame->aAOm;
}

void EndFramec::fillContactEndFrames(std::set<EndFramec*> efrms)
{
}

FColDsptr EndFramec::ieO()
{
    return aAOe->column(0);
}

FColDsptr EndFramec::jeO()
{
    return aAOe->column(1);
}

FColDsptr EndFramec::keO()
{
    return aAOe->column(2);
}

FColDsptr EndFramec::aAjOe(size_t j)
{
    return aAOe->column(j);
}

void EndFramec::aApm(FMatDsptr mat)
{
    markerFrame->aApm = mat;
}

double EndFramec::riOeO(size_t i)
{
    return rOeO->at(i);
}

FColDsptr EndFramec::rpmp()
{
    return markerFrame->rpmp;
}

FColDsptr EndFramec::rmeO()
{
    return rOeO->minusFullColumn(markerFrame->rOmO);
}

FColDsptr EndFramec::rpep()
{
    return FColDsptr();
}

FColFMatDsptr EndFramec::pAOppE()
{
    return FColFMatDsptr();
}

FMatDsptr EndFramec::aBOp()
{
    return FMatDsptr();
}

std::shared_ptr<EndFrameqc> EndFramec::newCopyEndFrameqc()
{
    auto frmIeqc = EndFrameqc::With();
    markerFrame->addEndFrame(frmIeqc);
    return frmIeqc;
}

std::shared_ptr<EndFrameqc> EndFramec::followEndFrame(EndFrmsptr frmi)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<EndFrameqc>();
}

bool EndFramec::isEndFrameqc()
{
    return false;
}

PartFrame* EndFramec::getPartFrame()
{
    return markerFrame->getPartFrame();
}

std::shared_ptr<EulerParameters<double>> EndFramec::qEOe()
{
    return aAOe->asEulerParameters();
}

FColDsptr EndFramec::vOeO()
{
    return markerFrame->vOmO();
}

FColDsptr EndFramec::aOeO()
{
    return markerFrame->aOmO();
}
