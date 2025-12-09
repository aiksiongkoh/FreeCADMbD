#include "ForceTorqueActReactKComp.h"
#include "ForceBasicqccqVector.h"
#include "ForceTorqueActionKComp.h"
#include "TorqueBasicVector.h"
#include "ForceTorqueFunction.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReactKComp> ForceTorqueActReactKComp::With()
{
    auto inst = std::make_shared<ForceTorqueActReactKComp>();
    inst->initialize();
    return inst;
}

void ForceTorqueActReactKComp::initialize()
{
    forTorAction = ForceTorqueActionKComp::With();
}

std::shared_ptr<ForceTorqueActReactKComp> ForceTorqueActReactKComp::ForceOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, EndFrmsptr eFrmK, size_t axis)
{
    auto forTor = ForceTorqueActReactKComp::With();
    forTor->forceOnFrmIandFrmJwrtFrmKaxis(eFrmI, eFrmJ, eFrmK, axis);
    return forTor;
}

std::shared_ptr<ForceTorqueActReactKComp> ForceTorqueActReactKComp::TorqueOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, EndFrmsptr eFrmK, size_t axis)
{
    auto forTor = ForceTorqueActReactKComp::With();
    forTor->torqueOnFrmIandFrmJwrtFrmKaxis(eFrmI, eFrmJ, eFrmK, axis);
    return forTor;
}

void ForceTorqueActReactKComp::calcPostDynCorrectorIteration()
{
    aFTJeO = forTorAction->getFTIeO()->negated();
}

void ForceTorqueActReactKComp::fillAccICIterError(FColDsptr col)
{
    forTorAction->fillAccICIterError(col);
    forTorBasicJ->fillAccICIterErroraFTO(col, aFTJeO);
}

void ForceTorqueActReactKComp::fillAccICIterJacob(SpMatDsptr mat)
{
    auto forTorActionKComp = std::static_pointer_cast<ForceTorqueActionKComp>(forTorAction);
    forTorActionKComp->fillAccICIterJacob(mat);
    auto aAjOKe = forTorActionKComp->aAjOKe;
    auto forTorFunction = forTorActionKComp->forTorFunction;
    auto jointActions = forTorFunction->jointActions;
    auto pFTpJtActs = forTorFunction->pFTpJtActs();
    for (size_t i = 0; i < jointActions->size(); i++)
    {
        auto jointAction = jointActions->at(i);
        auto mpFTpJtAct = -pFTpJtActs->at(i);
        forTorBasicJ->fillAccICIterJacobpFTOplam(mat, SparseMatrix<double>::colTimesRowTimesScalar(aAjOKe, jointAction->pvalueplam(), mpFTpJtAct));
    }
}

void ForceTorqueActReactKComp::fillDynError(FColDsptr col)
{
    forTorAction->fillDynError(col);
    forTorBasicJ->fillDynErroraFTO(col, aFTJeO);
}

void ForceTorqueActReactKComp::fillpFpy(SpMatDsptr mat)
{
    auto forTorActKComp = std::static_pointer_cast<ForceTorqueActionKComp>(forTorAction);
    forTorActKComp->fillpFpy(mat);
    auto forTorFunction = forTorActKComp->forTorFunction;
    auto kineIJs = forTorFunction->kineIJs;
    auto kinedotIJs = forTorFunction->kinedotIJs;
    auto jointActions = forTorFunction->jointActions;
    auto pFTpkineIJs = forTorFunction->pFTpkineIJs();
    auto pFTpkinedotIJs = forTorFunction->pFTpkinedotIJs();
    auto pFTpJtActs = forTorFunction->pFTpJtActs();
    forTorBasicJ->fillpFpyaFTO(mat, aFTJeO);
    auto pFTOpEj = std::static_pointer_cast<EndFrameqc>(forTorActKComp->efrmK)->pAjOepE(forTorActKComp->axis)->times(-forTorFunction->forTor());
    forTorBasicJ->fillpFpypFTOpEjpartj(mat, pFTOpEj, forTorActKComp->pfrmK);
    for (size_t i = 0; i < kineIJs->size(); i++)
    {
        auto kineIJ = kineIJs->at(i);
        auto mpFTpkineIJ = -pFTpkineIJs->at(i);
        fillpFpypFTpfunctionfunction(mat, mpFTpkineIJ, kineIJ);
    }
    for (size_t i = 0; i < kinedotIJs->size(); i++)
    {
        auto kinedotIJ = kinedotIJs->at(i);
        auto mpFTpkinedotIJ = -pFTpkinedotIJs->at(i);
        fillpFpypFTpfunctionfunction(mat, mpFTpkinedotIJ, kinedotIJ);
    }
    for (size_t i = 0; i < jointActions->size(); i++)
    {
        auto jointAction = jointActions->at(i);
        auto mpFTpJtAct = -pFTpJtActs->at(i);
        fillpFpypFTpfunctionfunction(mat, mpFTpJtAct, jointAction);
    }
}

void ForceTorqueActReactKComp::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    auto aAjOKe = std::static_pointer_cast<ForceTorqueActionKComp>(forTorAction)->aAjOKe;
    auto block = [&](FRowDsptr pvaluepXi,
        FRowDsptr pvaluepEi,
        PartFrame* partFramei) -> void {
            if (pvaluepXi == nullptr || pvaluepXi->empty()) {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    //Do nothing.
                }
                else {
                    forTorBasicJ->fillpFpypFTOpEjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(aAjOKe, pvaluepEi, pFTpfunction), partFramei);
                }
            }
            else {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    forTorBasicJ->fillpFpypFTOpXjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(aAjOKe, pvaluepXi, pFTpfunction), partFramei);
                }
                else {
                    forTorBasicJ->fillpFpypFTOpXjpFTOpEjpartj(mat,
                        FullMatrix<double>::colTimesRowTimesScalar(aAjOKe, pvaluepXi, pFTpfunction),
                        FullMatrix<double>::colTimesRowTimesScalar(aAjOKe, pvaluepEi, pFTpfunction),
                        partFramei);
                };
            }
        };
    auto mdbfunc = std::static_pointer_cast<MbDSymbolicFunction>(function);
    block(mdbfunc->pvaluepXI(), mdbfunc->pvaluepEI(), mdbfunc->partFrameI());
    block(mdbfunc->pvaluepXJ(), mdbfunc->pvaluepEJ(), mdbfunc->partFrameJ());
    block(mdbfunc->pvaluepXK(), mdbfunc->pvaluepEK(), mdbfunc->partFrameK());
}

void ForceTorqueActReactKComp::fillpFpydot(SpMatDsptr mat)
{
    auto forTorActionKComp = std::static_pointer_cast<ForceTorqueActionKComp>(forTorAction);
    forTorActionKComp->fillpFpydot(mat);
    auto aAjOKe = forTorActionKComp->aAjOKe;
    auto forTorFunction = forTorActionKComp->forTorFunction;
    auto kinedotIJs = forTorFunction->kinedotIJs;
    auto jointActions = forTorFunction->jointActions;
    auto pFTpkinedotIJs = forTorFunction->pFTpkinedotIJs();
    auto pFTpJtActs = forTorFunction->pFTpJtActs();
    for (size_t i = 0; i < kinedotIJs->size(); i++)
    {
        auto kinedotIJ = kinedotIJs->at(i);
        auto mpFTpkinedotIJ = -pFTpkinedotIJs->at(i);
        fillpFpydotpFTpfunctionfunction(mat, mpFTpkinedotIJ, kinedotIJ);
    }
    for (size_t i = 0; i < jointActions->size(); i++)
    {
        auto jointAction = jointActions->at(i);
        auto mpFTpJtAct = -pFTpJtActs->at(i);
        forTorBasicJ->fillpFpydotpFOpmudot(mat, SparseMatrix<double>::colTimesRowTimesScalar(aAjOKe, jointAction->pvalueplam(), mpFTpJtAct));
    }
}

void ForceTorqueActReactKComp::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActReactKComp::forceOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis)
{
    forTorAction->forceOnFrmIwrtFrmKaxis(frmi, frmk, axis);
    forTorBasicJ = ForceBasicqccqVector::With();
    forTorBasicJ->parent = this;
    forTorBasicJ->endFramefollowEndFrame(frmj, frmi);
}

void ForceTorqueActReactKComp::torqueOnFrmIandFrmJwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis)
{
    forTorAction->torqueOnFrmIwrtFrmKaxis(frmi, frmk, axis);
    forTorBasicJ = TorqueBasicVector::With();
    forTorBasicJ->parent = this;
    forTorBasicJ->endFrame = frmj;
}
