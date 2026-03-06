/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTMotion.h"
#include "ASMTAssembly.h"
#include "ASMTJoint.h"
#include "SimulationStoppingError.h"
#include "PrescribedMotion.h"

using namespace MbD;

std::shared_ptr<ASMTMotion> ASMTMotion::With()
{
    auto inst = std::make_shared<ASMTMotion>();
    inst->initialize();
    return inst;
}

void ASMTMotion::readMotionSeries(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    std::string substr = "MotionSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    assert(fullName("") == seriesName);
    lines.erase(lines.begin());
    
    auto infxs2 = readSeriesOf(lines, "FXonI");
    auto infys2 = readSeriesOf(lines, "FYonI");
    auto infzs2 = readSeriesOf(lines, "FZonI");
    auto intxs2 = readSeriesOf(lines, "TXonI");
    auto intys2 = readSeriesOf(lines, "TYonI");
    auto intzs2 = readSeriesOf(lines, "TZonI");

    for (size_t i = 0; i < infxs2->size(); ++i)
    {
        auto data = ForceTorqueData::With();
        auto lambda = [&](FRowDsptr rowx, FRowDsptr rowy, FRowDsptr rowz) -> FColDsptr
        {
            auto col = FullColumn<double>::With(3);
            col->at(0) = rowx->at(i);
            col->at(1) = rowy->at(i);
            col->at(2) = rowz->at(i);
            return col;
        };
        data->aFIO = lambda(infxs2, infys2, infzs2);
        data->aTIO = lambda(intxs2, intys2, intzs2);
        dataSeriesIn->push_back(data);
    }

    // readFXonIs(lines);
    // readFYonIs(lines);
    // readFZonIs(lines);
    // readTXonIs(lines);
    // readTYonIs(lines);
    // readTZonIs(lines);
}

void ASMTMotion::initMarkers()
{
    if (motionJoint == "") {
        assert(markerI->name != "");
        assert(markerJ->name != "");
    }
    else {
        auto jt = root()->jointAt(motionJoint);
        markerI = jt->markerI;
        markerJ = jt->markerJ;
    }
}

void ASMTMotion::storeOnLevel(std::ofstream&, size_t)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTMotion::storeOnTimeSeries(std::ofstream&)
{
    throw SimulationStoppingError("To be implemented.");
}

bool ASMTMotion::isMotion()
{
    return true;
}

void ASMTMotion::createMbD()
{
    ASMTConstraintSet::createMbD();
    auto mbdJt = std::static_pointer_cast<PrescribedMotion>(mbdObject);
    mbdSys()->addMotion(mbdJt);
}
