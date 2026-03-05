/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTConstraintSet.h"
#include "ASMTAssembly.h"
#include "ASMTMarker.h"
#include "JointIJ.h"
#include "FullMatrix.h"
#include "EndFrameqc.h"
#include "Part.h"
#include "SimulationStoppingError.h"
#include "ForceTorqueData.h"
#include "ConstraintSet.h"

using namespace MbD;

std::shared_ptr<ASMTConstraintSet> ASMTConstraintSet::With()
{
    auto inst = std::make_shared<ASMTConstraintSet>();
    inst->initialize();
    return inst;
}

void ASMTConstraintSet::createMbD()
{
    auto mbdJt = mbdClassNew();
    mbdObject = mbdJt;
    mbdJt->name = fullName("");
    auto mrkI = std::static_pointer_cast<EndFramec>(markerI->mbdObject);
    auto mrkJ = std::static_pointer_cast<EndFramec>(markerJ->mbdObject);
    mbdJt->connectsItoJ(mrkI, mrkJ);
}

std::shared_ptr<ConstraintSet> ASMTConstraintSet::mbdClassNew()
{
    // Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintSet>();
}

void ASMTConstraintSet::updateFromMbD()
{
    //"
    // MbD returns aFIeO and aTIeO.
    // GEO needs aFImO and aTImO.
    // For Motion rImIeO is not zero and is changing.
    // aFImO = aFIeO.
    // aTImO = aTIeO + (rImIeO cross : aFIeO).
    //"
    auto data = dataFromMbD();
    dataSeries->push_back(data);

    auto mbdUnts = mbdUnits();
    auto mbdJoint = std::static_pointer_cast<JointIJ>(mbdObject);
    auto aFIeO = mbdJoint->aFX()->times(mbdUnts->force);
    auto aTIeO = mbdJoint->aTX()->times(mbdUnts->torque);
    auto rImIeO = mbdJoint->eFrmI->rmeO()->times(mbdUnts->length);
    auto aFIO = aFIeO;
    auto aTIO = aTIeO->plusFullColumn(rImIeO->cross(aFIeO));
    cFIO->push_back(aFIO);
    cTIO->push_back(aTIO);
}

std::shared_ptr<StateData> MbD::ASMTConstraintSet::dataFromMbD()
{
    auto mbdUnts = mbdUnits();
    auto aConstraintSet = std::static_pointer_cast<ConstraintSet>(mbdObject);
    auto answer = ForceTorqueData::With();
    answer->aFIO = aConstraintSet->aFIeO()->times(mbdUnts->force);
    answer->aTIO = aConstraintSet->aTIeO()->times(mbdUnts->torque);
    return answer;
}

void ASMTConstraintSet::compareResults(AnalysisType)
{
    // Redundant constraint removal is very sensitive to numerical noise.
    // Joint ForceTorque can change a lot when new and old redundant constraints are not the same.
    if (infxs == nullptr || infxs->empty())
        return;
    auto lambda = [&](std::string name, std::shared_ptr<std::vector<FColDsptr>> cols, size_t icomp, FRowDsptr invals, size_t i, size_t nSig, double tol)
    {
        auto val = cols->at(i)->at(icomp);
        auto inval = invals->at(i);
        auto tol2 = tol / 10.0;
        if (std::abs(val) < tol2 && std::abs(inval) < tol2)
            return;
        auto ratio = val / inval;
        auto relDiff = std::abs(ratio) - 1.0;
        if (ratio < 0.0)
        {
            std::cout << "                    Sign Error ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << " Redundant Constraint Differences??? ";
            std::cout << std::endl;
        }
        else if (std::abs(relDiff) >= std::pow(10, -int(nSig)))
        {
            std::cout << "                    ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << " Redundant Constraint Differences??? ";
            std::cout << std::endl;
        }
    };

    auto mbdUnts = mbdUnits();
    size_t nDigit = 3;
    auto factor = std::pow(10, -int(nDigit));
    auto forceTol = mbdUnts->force * factor;
    auto torqueTol = mbdUnts->torque * factor;
    auto i = cFIO->size() - 1;
    // Force
    lambda("FIOx", cFIO, 0, infxs, i, nDigit, forceTol);
    lambda("FIOy", cFIO, 1, infys, i, nDigit, forceTol);
    lambda("FIOz", cFIO, 2, infzs, i, nDigit, forceTol);
    // Torque
    lambda("TIOx", cTIO, 0, intxs, i, nDigit, torqueTol);
    lambda("TIOy", cTIO, 1, intys, i, nDigit, torqueTol);
    lambda("TIOz", cTIO, 2, intzs, i, nDigit, torqueTol);
}

void MbD::ASMTConstraintSet::compareResults2(AnalysisType type)
{
    // Redundant constraint removal is very sensitive to numerical noise.
    // Joint ForceTorque can change a lot when new and old redundant constraints are not the same.
    if (dataSeriesIn == nullptr || dataSeriesIn->empty())
        return;
    auto lambda = [&](std::string name, size_t i, FColDsptr col, FColDsptr incol, size_t nSig, double tol)
    {
        auto val = col->at(i);
        auto inval = incol->at(i);
        auto tol2 = tol / 10.0;
        if (std::abs(val) < tol2 && std::abs(inval) < tol2)
            return;
        auto ratio = val / inval;
        auto relDiff = std::abs(ratio) - 1.0;
        if (ratio < 0.0)
        {
            std::cout << "                    Sign Error ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << " Redundant Constraint Differences??? ";
            std::cout << std::endl;
        }
        else if (std::abs(relDiff) >= std::pow(10, -int(nSig)))
        {
            std::cout << "                    ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff);
            std::cout << " Redundant Constraint Differences??? ";
            std::cout << std::endl;
        }
    };

    auto mbdUnts = mbdUnits();
    size_t nDigit = 3;
    auto factor = std::pow(10, -int(nDigit));
    auto forceTol = mbdUnts->force * factor;
    auto torqueTol = mbdUnts->torque * factor;
    auto i = dataSeries->size() - 1;
    auto forceTorqueData = std::dynamic_pointer_cast<ForceTorqueData>(dataSeries->at(i));
    auto forceTorqueDataIn = std::dynamic_pointer_cast<ForceTorqueData>(dataSeriesIn->at(i));
    auto aFIeO = forceTorqueData->aFIO;
    auto inFIeO = forceTorqueDataIn->aFIO;
    // Force
    lambda("FIOx", 0, aFIeO, inFIeO, nDigit, forceTol);
    lambda("FIOy", 1, aFIeO, inFIeO, nDigit, forceTol);
    lambda("FIOz", 2, aFIeO, inFIeO, nDigit, forceTol);
    // Torque
    auto aTIeO = forceTorqueData->aTIO;
    auto inTIeO = forceTorqueDataIn->aTIO;
    lambda("TIOx", 0, aTIeO, inTIeO, nDigit, torqueTol);
    lambda("TIOy", 1, aTIeO, inTIeO, nDigit, torqueTol);
    lambda("TIOz", 2, aTIeO, inTIeO, nDigit, torqueTol);
}

void ASMTConstraintSet::outputResults(AnalysisType)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTConstraintSet::updateFromInputState()
{
    // Do nothing.
}
