#include "ForceTorqueActionKComp.h"
#include "ForceTorqueBasic.h"
#include "ForceTorqueFunction.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasicVector.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActionKComp> ForceTorqueActionKComp::With()
{
    auto inst = std::make_shared<ForceTorqueActionKComp>();
    inst->initialize();
    return inst;
}

void ForceTorqueActionKComp::calcPostDynCorrectorIteration()
{
    aAjOKe = efrmK->aAjOe(axis);
    aFTIeO = aAjOKe->times(forTorFunction->forTor());
}

void ForceTorqueActionKComp::fillAccICIterError(FColDsptr col)
{
    forTorBasicI->fillAccICIterErroraFTO(col, aFTIeO);
}

void ForceTorqueActionKComp::fillAccICIterJacob(SpMatDsptr mat)
{
    auto jointActions = forTorFunction->jointActions;
    auto pFTpJtActs = forTorFunction->pFTpJtActs();
    for (size_t i = 0; i < jointActions->size(); i++) {
        auto jointAction = jointActions->at(i);
        auto pFTpJtAct = pFTpJtActs->at(i);
        forTorBasicI->fillAccICIterJacobpFTOplam(mat, SparseMatrix<double>::colTimesRowTimesScalar(aAjOKe, jointAction->pvalueplam(), pFTpJtAct));
    }
}

void ForceTorqueActionKComp::fillDynError(FColDsptr col)
{
    forTorBasicI->fillDynErroraFTO(col, aFTIeO);
}

void ForceTorqueActionKComp::fillpFpy(SpMatDsptr mat)
{
    auto kineIJs = forTorFunction->kineIJs;
    auto kinedotIJs = forTorFunction->kinedotIJs;
    auto jointActions = forTorFunction->jointActions;
    auto pFTpkineIJs = forTorFunction->pFTpkineIJs();
    auto pFTpkinedotIJs = forTorFunction->pFTpkinedotIJs();
    auto pFTpJtActs = forTorFunction->pFTpJtActs();
    forTorBasicI->fillpFpyaFTO(mat, aFTIeO);
    auto pFTOpEj = std::static_pointer_cast<EndFrameqc>(efrmK)->pAjOepE(axis)->times(forTorFunction->forTor());
    forTorBasicI->fillpFpypFTOpEjpartj(mat, pFTOpEj, pfrmK);
    for (size_t i = 0; i < kineIJs->size(); i++)
    {
        auto kineIJ = kineIJs->at(i);
        auto pFTpkineIJ = pFTpkineIJs->at(i);
        fillpFpypFTpfunctionfunction(mat, pFTpkineIJ, kineIJ);
    }
    for (size_t i = 0; i < kinedotIJs->size(); i++)
    {
        auto kinedotIJ = kinedotIJs->at(i);
        auto pFTpkinedotIJ = pFTpkinedotIJs->at(i);
        fillpFpypFTpfunctionfunction(mat, pFTpkinedotIJ, kinedotIJ);
    }
    for (size_t i = 0; i < jointActions->size(); i++)
    {
        auto jointAction = jointActions->at(i);
        auto pFTpJtAct = pFTpJtActs->at(i);
        fillpFpypFTpfunctionfunction(mat, pFTpJtAct, jointAction);
    }
}

void ForceTorqueActionKComp::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    auto block = [&](FRowDsptr pvaluepXi,
        FRowDsptr pvaluepEi,
        PartFrame* partFramei) -> void {
            if (pvaluepXi == nullptr || pvaluepXi->empty()) {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    //Do nothing.
                }
                else {
                    forTorBasicI->fillpFpypFTOpEjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(aAjOKe, pvaluepEi, pFTpfunction), partFramei);
                }
            }
            else {
                if (pvaluepEi == nullptr || pvaluepEi->empty()) {
                    forTorBasicI->fillpFpypFTOpXjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(aAjOKe, pvaluepXi, pFTpfunction), partFramei);
                }
                else {
                    forTorBasicI->fillpFpypFTOpXjpFTOpEjpartj(mat,
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

void ForceTorqueActionKComp::fillpFpydot(SpMatDsptr mat)
{
    auto kinedotIJs = forTorFunction->kinedotIJs;
    auto jointActions = forTorFunction->jointActions;
    auto pFTpkinedotIJs = forTorFunction->pFTpkinedotIJs();
    auto pFTpJtActs = forTorFunction->pFTpJtActs();
    for (size_t i = 0; i < kinedotIJs->size(); i++)
    {
        auto kinedotIJ = kinedotIJs->at(i);
        auto pFTpkinedotIJ = pFTpkinedotIJs->at(i);
        fillpFpydotpFTpfunctionfunction(mat, pFTpkinedotIJ, kinedotIJ);
    }
    for (size_t i = 0; i < jointActions->size(); i++)
    {
        auto jointAction = jointActions->at(i);
        auto pFTpJtAct = pFTpJtActs->at(i);
        forTorBasicI->fillpFpydotpFOpmudot(mat, SparseMatrix<double>::colTimesRowTimesScalar(aAjOKe, jointAction->pvalueplam(), pFTpJtAct));
    }
}

void ForceTorqueActionKComp::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionKComp::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionKComp::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr ForceTorqueActionKComp::getFTIeO() const
{
    return aFTIeO;
}

void ForceTorqueActionKComp::forceOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t _axis)
{
    forTorBasicI = ForceBasicqcVector::With();
    forTorBasicI->parent = this;
    forTorBasicI->endFrame = frmi;
    axis = _axis;
    efrmK = frmk;
    pfrmK = efrmK->getPartFrame();
}

void ForceTorqueActionKComp::torqueOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t _axis)
{
    forTorBasicI = TorqueBasicVector::With();
    forTorBasicI->parent = this;
    forTorBasicI->endFrame = frmi;
    axis = _axis;
    efrmK = frmk;
    pfrmK = efrmK->getPartFrame();
}
