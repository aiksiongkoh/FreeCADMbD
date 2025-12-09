#include "ForceTorqueActionInLine.h"
#include "ForceTorqueFunction.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasicVector.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActionInLine> ForceTorqueActionInLine::With()
{
    auto inst = std::make_shared<ForceTorqueActionInLine>();
    inst->initialize();
    return inst;
}

void ForceTorqueActionInLine::initialize()
{
    distIeJe = DistIeqcJeqc::With();
    ForceTorqueAction::initialize();
}

void ForceTorqueActionInLine::calcPostDynCorrectorIteration()
{
    auto uIeJeO = distIeJe->uIeJeO;
    auto tension = forTorFunction->forTor();
    aFTIeO = uIeJeO->times(tension);
}

void ForceTorqueActionInLine::fillAccICIterError(FColDsptr col)
{
    forTorBasicI->fillAccICIterErroraFTO(col, aFTIeO);
}

void ForceTorqueActionInLine::fillAccICIterJacob(SpMatDsptr mat)
{
    forTorBasicI->fillAccICIterJacob(mat);
}

void ForceTorqueActionInLine::fillDynError(FColDsptr col)
{
    forTorBasicI->fillDynErroraFTO(col, aFTIeO);
}

void ForceTorqueActionInLine::fillpFpy(SpMatDsptr mat)
{
    auto forTor = forTorFunction->forTor();
    forTorBasicI->fillpFpyaFTO(mat, aFTIeO);
    auto block = [&](FMatDsptr puIeJeOpXi, FMatDsptr puIeJeOpEi, PartFrame* partFramei) -> void {
        forTorBasicI->fillpFpypFTOpXjpFTOpEjpartj(mat, puIeJeOpXi->times(forTor), puIeJeOpEi->times(forTor), partFramei); };
    block(distIeJe->puIeJeOpXI(), distIeJe->puIeJeOpEI(), distIeJe->partFrameI());
    block(distIeJe->puIeJeOpXJ(), distIeJe->puIeJeOpEJ(), distIeJe->partFrameJ());

    auto block2 = [&](std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> functions, 
        FColDsptr pFTpfunctions) -> void {
        for (size_t i = 0; i < functions->size(); i++) {
            fillpFpypFTpfunctionfunction(mat, pFTpfunctions->at(i), functions->at(i));
        }
        };
    block2(forTorFunction->kineIJs, forTorFunction->pFTpkineIJs());
    block2(forTorFunction->kinedotIJs, forTorFunction->pFTpkinedotIJs());
    block2(forTorFunction->jointActions, forTorFunction->pFTpJtActs());
}

void ForceTorqueActionInLine::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    auto uIeJeO = distIeJe->uIeJeO;
    auto block = [&](FRowDsptr pvaluepXi,
        FRowDsptr pvaluepEi,
        PartFrame* partFramei) -> void {
            if (pvaluepXi == nullptr || pvaluepXi->empty()) {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    //Do nothing.
                }
                else {
                    forTorBasicI->fillpFpypFTOpEjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEi, pFTpfunction), partFramei);
                }
            }
            else {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    forTorBasicI->fillpFpypFTOpXjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXi, pFTpfunction), partFramei);
                }
                else {
                    forTorBasicI->fillpFpypFTOpXjpFTOpEjpartj(mat,
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

void ForceTorqueActionInLine::fillpFpydot(SpMatDsptr mat)
{
    auto uIeJeO = distIeJe->uIeJeO;
    auto kinedotIJs = forTorFunction->kinedotIJs;
    auto jointActions = forTorFunction->jointActions;
    auto pFTpkinedotIJs = forTorFunction->pFTpkinedotIJs();
    auto pFTpJtActs = forTorFunction->pFTpJtActs();
    for (size_t i = 0; i < kinedotIJs->size(); i++) {
        fillpFpydotpFTpfunctionfunction(mat, pFTpkinedotIJs->at(i), kinedotIJs->at(i));
    }
    for (size_t i = 0; i < jointActions->size(); i++) {
        forTorBasicI->fillpFpydotpFTOpmudot(mat, SparseMatrix<double>::colTimesRowTimesScalar(uIeJeO, jointActions->at(i)->pvalueplam(), -pFTpJtActs->at(i)));
    }
}

void ForceTorqueActionInLine::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    auto uIeJeO = distIeJe->uIeJeO;
    auto block = [&](FRowDsptr pvaluepXdoti,
        FRowDsptr pvaluepEdoti,
        PartFrame* partFramei) -> void {
            if (pvaluepXdoti == nullptr || pvaluepXdoti->empty()) {
                if (pvaluepEdoti == nullptr || pvaluepEdoti->empty()) {
                    //Do nothing.
                }
                else {
                    forTorBasicI->fillpFpydotpFTOpEdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEdoti, pFTpfunction), partFramei);
                }
            }
            else {
                if (pvaluepEdoti == nullptr || pvaluepEdoti->empty()) {
                    forTorBasicI->fillpFpydotpFTOpXdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXdoti, pFTpfunction), partFramei);
                }
                else {
                    forTorBasicI->fillpFpydotpFTOpXdotjpFTOpEdotjpartj(mat,
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

void ForceTorqueActionInLine::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    forTorBasicI = ForceBasicqcVector::With();
    forTorBasicI->parent = this;
    forTorBasicI->endFrame = eFrmI;
    distIeJe->withFrmIFrmJ(eFrmI, eFrmJ);
}

void ForceTorqueActionInLine::initializeGlobally()
{
    distIeJe->initializeGlobally();
    ForceTorqueAction::initializeGlobally();
}

void ForceTorqueActionInLine::initializeLocally()
{
    distIeJe->initializeLocally();
    ForceTorqueAction::initializeLocally();
}

void ForceTorqueActionInLine::postAccICIteration()
{
    distIeJe->postAccICIteration();
    forTorFunction->postAccICIteration();
    forTorBasicI->postAccICIteration();
    ForceTorqueAction::postAccICIteration();
}

void ForceTorqueActionInLine::postCollisionCorrectorIteration()
{
    distIeJe->postCollisionCorrectorIteration();
    forTorFunction->postCollisionCorrectorIteration();
    forTorBasicI->postCollisionCorrectorIteration();
    ForceTorqueAction::postCollisionCorrectorIteration();
}

void ForceTorqueActionInLine::postCollisionPredictor()
{
    distIeJe->postCollisionPredictor();
    forTorFunction->postCollisionPredictor();
    forTorBasicI->postCollisionPredictor();
    ForceTorqueAction::postCollisionPredictor();
}

void ForceTorqueActionInLine::postDynCorrectorIteration()
{
    distIeJe->postDynCorrectorIteration();
    forTorFunction->postDynCorrectorIteration();
    forTorBasicI->postDynCorrectorIteration();
    ForceTorqueAction::postDynCorrectorIteration();
}

void ForceTorqueActionInLine::postDynOutput()
{
    distIeJe->postDynOutput();
    forTorFunction->postDynOutput();
    forTorBasicI->postDynOutput();
    ForceTorqueAction::postDynOutput();
}

void ForceTorqueActionInLine::postDynPredictor()
{
    distIeJe->postDynPredictor();
    forTorFunction->postDynPredictor();
    forTorBasicI->postDynPredictor();
    ForceTorqueAction::postDynPredictor();
}

void ForceTorqueActionInLine::postInput()
{
    distIeJe->postInput();
    forTorFunction->postInput();
    forTorBasicI->postInput();
    ForceTorqueAction::postInput();
}

void ForceTorqueActionInLine::postStaticIteration()
{
    distIeJe->postStaticIteration();
    forTorFunction->postStaticIteration();
    forTorBasicI->postStaticIteration();
    ForceTorqueAction::postStaticIteration();
}

void ForceTorqueActionInLine::preAccIC()
{
    distIeJe->preAccIC();
    forTorFunction->preAccIC();
    forTorBasicI->preAccIC();
    ForceTorqueAction::preAccIC();
}

void ForceTorqueActionInLine::preDynOutput()
{
    distIeJe->preDynOutput();
    forTorFunction->preDynOutput();
    forTorBasicI->preDynOutput();
    ForceTorqueAction::preDynOutput();
}

void ForceTorqueActionInLine::preStatic()
{
    distIeJe->preStatic();
    forTorFunction->preStatic();
    forTorBasicI->preStatic();
    ForceTorqueAction::preStatic();
}

void ForceTorqueActionInLine::simUpdateAll()
{
    distIeJe->simUpdateAll();
    forTorFunction->simUpdateAll();
    forTorBasicI->simUpdateAll();
    ForceTorqueAction::simUpdateAll();
}

std::shared_ptr<ForceTorqueFunction> ForceTorqueActionInLine::tension()
{
    return forTorFunction;
}

void ForceTorqueActionInLine::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    forTorBasicI = TorqueBasicVector::With();
    forTorBasicI->parent = this;
    forTorBasicI->endFrame = eFrmI;
    distIeJe->withFrmIFrmJ(eFrmI, eFrmJ);
}

FColDsptr ForceTorqueActionInLine::uIeJeO()
{
    return distIeJe->uIeJeO;
}

void ForceTorqueActionInLine::useEquationNumbers()
{
    distIeJe->useEquationNumbers();
    forTorFunction->useEquationNumbers();
    forTorBasicI->useEquationNumbers();
}

FColDsptr ForceTorqueActionInLine::getFTIeO() const
{
    return aFTIeO;
}
