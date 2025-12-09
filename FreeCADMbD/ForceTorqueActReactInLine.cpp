#include "ForceTorqueActReactInLine.h"
#include "MarkerFrame.h"
#include "ForceTorqueActionInLine.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasicVector.h"
#include "ForceTorqueFunction.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReactInLine> ForceTorqueActReactInLine::With()
{
    auto inst = std::make_shared<ForceTorqueActReactInLine>();
    inst->initialize();
    return inst;
}

void ForceTorqueActReactInLine::initialize()
{
    forTorAction = ForceTorqueActionInLine::With();
}

std::shared_ptr<ForceTorqueActReactInLine> ForceTorqueActReactInLine::ForceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    auto forTorActReactInLine = ForceTorqueActReactInLine::With();
    forTorActReactInLine->forceOnFrmIandFrmJ(eFrmI, eFrmJ);
    return forTorActReactInLine;
}

std::shared_ptr<ForceTorqueActReactInLine> ForceTorqueActReactInLine::TorqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    auto forTorActReactInLine = ForceTorqueActReactInLine::With();
    forTorActReactInLine->torqueOnFrmIandFrmJ(eFrmI, eFrmJ);
    return forTorActReactInLine;
}

void ForceTorqueActReactInLine::calcPostDynCorrectorIteration()
{
    auto forTorActionInLine = std::static_pointer_cast<ForceTorqueActionInLine>(forTorAction);
    aFTJeO = forTorActionInLine->aFTIeO->negated();
}

void ForceTorqueActReactInLine::fillAccICIterError(FColDsptr col)
{
    forTorAction->fillAccICIterError(col);
    forTorBasicJ->fillAccICIterErroraFTO(col, aFTJeO);
}

void ForceTorqueActReactInLine::fillAccICIterJacob(SpMatDsptr mat)
{
    forTorAction->fillAccICIterJacob(mat);
    forTorBasicJ->fillAccICIterJacob(mat);
}

void ForceTorqueActReactInLine::fillDynError(FColDsptr col)
{
    forTorAction->fillDynError(col);
    forTorBasicJ->fillDynErroraFTO(col, aFTJeO);
}

void ForceTorqueActReactInLine::fillpFpy(SpMatDsptr mat)
{
    auto forTorActionInLine = std::static_pointer_cast<ForceTorqueActionInLine>(forTorAction);
    forTorActionInLine->fillpFpy(mat);
    auto distIeJe = forTorActionInLine->distIeJe;
    auto tension = forTorActionInLine->tension();
    auto mforTor = -tension->forTor();
    forTorBasicJ->fillpFpyaFTO(mat, aFTJeO);
    auto block = [&](FMatDsptr puIeJeOpXi, FMatDsptr puIeJeOpEi, PartFrame* partFramei) -> void {
        forTorBasicJ->fillpFpypFTOpXjpFTOpEjpartj(mat, puIeJeOpXi->times(mforTor), puIeJeOpEi->times(mforTor), partFramei); };
    block(distIeJe->puIeJeOpXI(), distIeJe->puIeJeOpEI(), distIeJe->partFrameI());
    block(distIeJe->puIeJeOpXJ(), distIeJe->puIeJeOpEJ(), distIeJe->partFrameJ());

    auto block2 = [&](std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> functions,
        FColDsptr pFTpfunctions) -> void {
            for (size_t i = 0; i < functions->size(); i++) {
                fillpFpypFTpfunctionfunction(mat, -pFTpfunctions->at(i), functions->at(i));
            }
        };
    block2(tension->kineIJs, tension->pFTpkineIJs());
    block2(tension->kinedotIJs, tension->pFTpkinedotIJs());
    block2(tension->jointActions, tension->pFTpJtActs());
}

void ForceTorqueActReactInLine::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    auto uIeJeO = std::static_pointer_cast<ForceTorqueActionInLine>(forTorAction)->uIeJeO();
    auto block = [&](FRowDsptr pvaluepXi,
        FRowDsptr pvaluepEi,
        PartFrame* partFramei) -> void {
            if (pvaluepXi == nullptr || pvaluepXi->empty()) {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    //Do nothing.
                }
                else {
                    forTorBasicJ->fillpFpypFTOpEjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEi, pFTpfunction), partFramei);
                }
            }
            else {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    forTorBasicJ->fillpFpypFTOpXjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXi, pFTpfunction), partFramei);
                }
                else {
                    forTorBasicJ->fillpFpypFTOpXjpFTOpEjpartj(mat,
                        FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXi, pFTpfunction),
                        FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEi, pFTpfunction),
                        partFramei);
                };
            }
        };
    auto mdbfunc = std::static_pointer_cast<MbDSymbolicFunction>(function);
    block(mdbfunc->pvaluepXI(), mdbfunc->pvaluepEI(), mdbfunc->partFrameI());
    block(mdbfunc->pvaluepXJ(), mdbfunc->pvaluepEJ(), mdbfunc->partFrameJ());
    block(mdbfunc->pvaluepXK(), mdbfunc->pvaluepEK(), mdbfunc->partFrameK());
}

void ForceTorqueActReactInLine::fillpFpydot(SpMatDsptr mat)
{
    forTorAction->fillpFpydot(mat);
    auto forTorActionInLine = std::static_pointer_cast<ForceTorqueActionInLine>(forTorAction);
    auto distIeJe = forTorActionInLine->distIeJe;
    auto uIeJeO = distIeJe->uIeJeO;
    auto tension = forTorActionInLine->tension();
    auto kinedotIJs = tension->kinedotIJs;
    auto jointActions = tension->jointActions;
    auto pFTpkinedotIJs = tension->pFTpkinedotIJs();
    auto pFTpJtActs = tension->pFTpJtActs();
    for (size_t i = 0; i < kinedotIJs->size(); i++) {
        fillpFpydotpFTpfunctionfunction(mat, -pFTpkinedotIJs->at(i), kinedotIJs->at(i));
    }
    for (size_t i = 0; i < jointActions->size(); i++) {
        forTorBasicJ->fillpFpydotpFTOpmudot(mat, SparseMatrix<double>::colTimesRowTimesScalar(uIeJeO, jointActions->at(i)->pvalueplam(), -pFTpJtActs->at(i)));
    }
}

void ForceTorqueActReactInLine::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    auto uIeJeO = std::static_pointer_cast<ForceTorqueActionInLine>(forTorAction)->uIeJeO();
    auto block = [&](FRowDsptr pvaluepXdoti,
        FRowDsptr pvaluepEdoti,
        PartFrame* partFramei) -> void {
            if (pvaluepXdoti == nullptr || pvaluepXdoti->empty()) {
                if (pvaluepEdoti == nullptr || pvaluepEdoti->empty()) {
                    //Do nothing.
                }
                else {
                    forTorBasicJ->fillpFpydotpFTOpEdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEdoti, pFTpfunction), partFramei);
                }
            }
            else {
                if (pvaluepEdoti == nullptr || pvaluepEdoti->empty()) {
                    forTorBasicJ->fillpFpydotpFTOpXdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXdoti, pFTpfunction), partFramei);
                }
                else {
                    forTorBasicJ->fillpFpydotpFTOpXdotjpFTOpEdotjpartj(mat,
                        FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXdoti, pFTpfunction),
                        FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEdoti, pFTpfunction),
                        partFramei);
                };
            }
        };
    auto mdbfunc = std::static_pointer_cast<MbDSymbolicFunction>(function);
    block(mdbfunc->pvaluepXdotI(), mdbfunc->pvaluepEdotI(), mdbfunc->partFrameI());
    block(mdbfunc->pvaluepXdotJ(), mdbfunc->pvaluepEdotJ(), mdbfunc->partFrameJ());
    block(mdbfunc->pvaluepXdotK(), mdbfunc->pvaluepEdotK(), mdbfunc->partFrameK());
}

void ForceTorqueActReactInLine::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    forTorAction->forceOnFrmIandFrmJ(eFrmI, eFrmJ);
    forTorBasicJ = ForceBasicqcVector::With();
    forTorBasicJ->parent = this;
    forTorBasicJ->endFrame = eFrmJ;
}

void ForceTorqueActReactInLine::initializeGlobally()
{
    forTorAction->initializeGlobally();
    forTorBasicJ->initializeGlobally();
}

void ForceTorqueActReactInLine::initializeLocally()
{
    forTorAction->initializeLocally();
    forTorBasicJ->initializeLocally();
}

void ForceTorqueActReactInLine::postAccICIteration()
{
    forTorAction->postAccICIteration();
    forTorBasicJ->postAccICIteration();
    ForceTorqueActReact::postAccICIteration();
}

void ForceTorqueActReactInLine::postCollisionCorrectorIteration()
{
    forTorAction->postCollisionCorrectorIteration();
    forTorBasicJ->postCollisionCorrectorIteration();
    ForceTorqueActReact::postCollisionCorrectorIteration();
}

void ForceTorqueActReactInLine::postCollisionPredictor()
{
    forTorAction->postCollisionPredictor();
    forTorBasicJ->postCollisionPredictor();
    ForceTorqueActReact::postCollisionPredictor();
}

void ForceTorqueActReactInLine::postDynCorrectorIteration()
{
    forTorAction->postDynCorrectorIteration();
    forTorBasicJ->postDynCorrectorIteration();
    ForceTorqueActReact::postDynCorrectorIteration();
}

void ForceTorqueActReactInLine::postDynOutput()
{
    forTorAction->postDynOutput();
    forTorBasicJ->postDynOutput();
    ForceTorqueActReact::postDynOutput();
}

void ForceTorqueActReactInLine::postDynPredictor()
{
    forTorAction->postDynPredictor();
    forTorBasicJ->postDynPredictor();
    ForceTorqueActReact::postDynPredictor();
}

void ForceTorqueActReactInLine::postInput()
{
    forTorAction->postInput();
    forTorBasicJ->postInput();
    ForceTorqueActReact::postInput();
}

void ForceTorqueActReactInLine::postStaticIteration()
{
    forTorAction->postStaticIteration();
    forTorBasicJ->postStaticIteration();
    ForceTorqueActReact::postStaticIteration();
}

void ForceTorqueActReactInLine::preAccIC()
{
    forTorAction->preAccIC();
    forTorBasicJ->preAccIC();
    ForceTorqueActReact::preAccIC();
}

void ForceTorqueActReactInLine::preDynOutput()
{
    forTorAction->preDynOutput();
    forTorBasicJ->preDynOutput();
    ForceTorqueActReact::preDynOutput();
}

void ForceTorqueActReactInLine::preStatic()
{
    forTorAction->preStatic();
    forTorBasicJ->preStatic();
    ForceTorqueActReact::preStatic();
}

void ForceTorqueActReactInLine::simUpdateAll()
{
    forTorAction->simUpdateAll();
    forTorBasicJ->simUpdateAll();
    ForceTorqueActReact::simUpdateAll();
}

void ForceTorqueActReactInLine::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    forTorAction->torqueOnFrmIandFrmJ(eFrmI, eFrmJ);
    forTorBasicJ = TorqueBasicVector::With();
    forTorBasicJ->parent = this;
    forTorBasicJ->endFrame = eFrmJ;
}
