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
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintSet>();
}

void ASMTConstraintSet::updateFromMbD()
{
    //"
    //MbD returns aFIeO and aTIeO.
    //GEO needs aFImO and aTImO.
    //For Motion rImIeO is not zero and is changing.
    //aFImO = aFIeO.
    //aTImO = aTIeO + (rImIeO cross : aFIeO).
    //"
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

void ASMTConstraintSet::compareResults(AnalysisType)
{
    if (infxs == nullptr || infxs->empty()) return;
    auto mbdUnts = mbdUnits();
    auto factor = 1.0e-6;
    auto forceTol = mbdUnts->force * factor;
    auto torqueTol = mbdUnts->torque * factor;
    auto i = cFIO->size() - 1;
    size_t nDigit = 3;
    auto lambda = [&](std::string name, std::shared_ptr<std::vector<FColDsptr>> cols, size_t icomp, FRowDsptr invals, size_t i, size_t nSig, double tol) {
        auto val = cols->at(i)->at(icomp);
        auto inval = invals->at(i);
        if (std::abs(val) < tol && std::abs(inval) < tol) return;
        auto ratio = val / inval;
        auto relDiff = std::abs(ratio) - 1.0;
        if (ratio < 0.0) {
            std::cout << "                    Sign Error ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff) << std::endl;
        }
        if (std::abs(relDiff) >= std::pow(10, -int(nDigit))) {
            std::cout << "                    ";
            std::cout << i << " " << name << " " << val << " != " << inval << " relDiff = " << std::abs(relDiff) << std::endl;
        }
        };
    //Force
    lambda("FIOx", cFIO, 0, infxs, i, nDigit, forceTol);
    lambda("FIOy", cFIO, 1, infys, i, nDigit, forceTol);
    lambda("FIOz", cFIO, 2, infzs, i, nDigit, forceTol);
    //Torque
    lambda("TIOx", cTIO, 0, intxs, i, nDigit, torqueTol);
    lambda("TIOy", cTIO, 1, intys, i, nDigit, torqueTol);
    lambda("TIOz", cTIO, 2, intzs, i, nDigit, torqueTol);
}

void ASMTConstraintSet::outputResults(AnalysisType)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTConstraintSet::updateFromInputState()
{
    //Do nothing.
}
