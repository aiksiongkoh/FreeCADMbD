#include "ForceTorqueGeneral.h"
#include "ForceTorqueGeneral.h"
#include "ForceTorqueFunction.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueGeneral> ForceTorqueGeneral::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    auto inst = std::make_shared<ForceTorqueGeneral>(frmi, frmj, frmk);
    inst->initialize();
    return inst;
}

FColDsptr ForceTorqueGeneral::aFX() const
{
    return FColDsptr();
}

FColDsptr ForceTorqueGeneral::aTX() const
{
    return FColDsptr();
}

void ForceTorqueGeneral::initialize()
{
    ForceTorqueIJ::initialize();
    aFIeKe = FullColumn<double>::With(3);
    aTIeKe = FullColumn<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        auto forceFunc = ForceTorqueFunction::With();
        forceFunc->owner = this;
        forceFunctions->push_back(forceFunc);
        auto torqueFunc = ForceTorqueFunction::With();
        torqueFunc->owner = this;
        torqueFunctions->push_back(torqueFunc);
    }
}

void ForceTorqueGeneral::calcPostDynCorrectorIteration()
{
    //Order of functions matters here.
    for (const auto func : *forceFunctions) func->calcPostDynCorrectorIteration();
    for (const auto func : *torqueFunctions) func->calcPostDynCorrectorIteration();
    calcaFIeKe();
    calcaTIeKe();
    aAOKe = eFrmK->aAOe;
    ForceTorqueIJ::calcPostDynCorrectorIteration();
    calcpFIeOpEK();
    calcpFJeOpEK();
    calcpTIeOpEK();
    calcpTJeOpEK();
    calcpQXIpEK();
    calcpQEIpEK();
    calcpQXJpEK();
    calcpQEJpEK();
}

FColDsptr MbD::ForceTorqueGeneral::getaFIeK() const
{
    auto answer = FullColumn<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        answer->at(i) = forceFunctions->at(i)->value();
    }
    return answer;
}

FColDsptr MbD::ForceTorqueGeneral::getaTIeK() const
{
    auto answer = FullColumn<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        answer->at(i) = torqueFunctions->at(i)->value();
    }
    return answer;
}

void ForceTorqueGeneral::fillAccICIterError(FColDsptr col)
{
    ForceTorqueIJ::fillAccICIterError(col);
}

void ForceTorqueGeneral::fillAccICIterJacob(SpMatDsptr mat)
{
    ForceTorqueIJ::fillAccICIterJacob(mat);
}

void ForceTorqueGeneral::fillpFpy(SpMatDsptr mat)
{
    ForceTorqueIJ::fillpFpy(mat);
    auto block = [&](size_t iQ, size_t iq, FMatDsptr pQpq) -> void {
        if (pQpq) {
            if (iq == SIZE_MAX) throw SimulationStoppingError("To be implemented.");
            mat->atijplusFullMatrix(iQ, iq, pQpq);
        }
        };
    block(iqXI, iqEK, pQXIpEK);
    block(iqEI, iqEK, pQEIpEK);
    block(iqXJ, iqEK, pQXJpEK);
    block(iqEJ, iqEK, pQEJpEK);
}

void ForceTorqueGeneral::fillStaticError(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::fillStaticJacob(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::setforceFunctions(FColsptr<Symsptr> col)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::initializeGlobally()
{
    ForceTorqueIJ::initializeGlobally();
}

void ForceTorqueGeneral::initializeLocally()
{
    ForceTorqueIJ::initializeLocally();
}

void ForceTorqueGeneral::postAccICIteration()
{
    ForceTorqueIJ::postAccICIteration();
}

void ForceTorqueGeneral::postCollisionCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::postCollisionPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::postDynCorrectorIteration()
{
    ForceTorqueIJ::postDynCorrectorIteration();
}

void ForceTorqueGeneral::postDynOutput()
{
    ForceTorqueIJ::postDynOutput();
}

void ForceTorqueGeneral::postDynPredictor()
{
    ForceTorqueIJ::postDynPredictor();
}

void ForceTorqueGeneral::postInput()
{
    ForceTorqueIJ::postInput();
}

void ForceTorqueGeneral::postStaticIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::preAccIC()
{
    ForceTorqueIJ::preAccIC();
}

void ForceTorqueGeneral::preDynOutput()
{
    ForceTorqueIJ::preDynOutput();
}

void ForceTorqueGeneral::preStatic()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::simUpdateAll()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::settorqueFunctions(FColsptr<Symsptr> col)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueGeneral::useEquationNumbers()
{
    ForceTorqueIJ::useEquationNumbers();
    if (eFrmK->has_qX()) {
        iqEK = eFrmK->iqE();
    }
}

void ForceTorqueGeneral::calcaFIeKe()
{
    for (size_t i = 0; i < 3; i++)
    {
        aFIeKe->atiput(i, forceFunctions->at(i)->value());
    }
}

void ForceTorqueGeneral::calcaTIeKe()
{
    for (size_t i = 0; i < 3; i++)
    {
        aTIeKe->atiput(i, torqueFunctions->at(i)->value());
    }
}

void ForceTorqueGeneral::calcaFIeO()
{
    //aFIeO = aAOKe * aFIeKe;
    aFIeO = aAOKe->timesFullColumn(aFIeKe);
}

void ForceTorqueGeneral::calcpFIeOpX(SpatialContainerFrame* partFrame)
{
    //pFIeOpX = aAOKe * pFIeKepX
    auto pFIeKepX = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pFIeKepX->at(i) = forceFunctions->at(i)->pvaluepX(partFrame);
    }
    auto pFIeOpX = FMatDsptr();
    if (!pFIeKepX->isZero()) {
        pFIeOpX = aAOKe->timesFullMatrix(pFIeKepX);
    }
    if (prtFrmI == partFrame) {
        pFIeOpXI = pFIeOpX;
    }
    else if (prtFrmJ == partFrame) {
        pFIeOpXJ = pFIeOpX;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpFIeOpE(SpatialContainerFrame* partFrame)
{
    //pFIeOpE = aAOKe * pFIeKepE
    auto pFIeKepE = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pFIeKepE->at(i) = forceFunctions->at(i)->pvaluepE(partFrame);
    }
    auto pFIeOpE = FMatDsptr();
    if (!pFIeKepE->isZero()) {
        pFIeOpE = aAOKe->timesFullMatrix(pFIeKepE);
    }
    if (prtFrmI == partFrame) {
        pFIeOpEI = pFIeOpE;
    }
    else if (prtFrmJ == partFrame) {
        pFIeOpEJ = pFIeOpE;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpFIeOpXdot(SpatialContainerFrame* partFrame)
{
    //pFIeOpXdot = aAOKe * pFIeKepXdot
    auto pFIeKepXdot = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pFIeKepXdot->at(i) = forceFunctions->at(i)->pvaluepXdot(partFrame);
    }
    auto pFIeOpXdot = FMatDsptr();
    if (!pFIeKepXdot->isZero()) {
        pFIeOpXdot = aAOKe->timesFullMatrix(pFIeKepXdot);
    }
    if (prtFrmI == partFrame) {
        pFIeOpXdotI = pFIeOpXdot;
    }
    else if (prtFrmJ == partFrame) {
        pFIeOpXdotJ = pFIeOpXdot;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpFIeOpEdot(SpatialContainerFrame* partFrame)
{
    //pFIeOpEdot = aAOKe * pFIeKepEdot
    auto pFIeKepEdot = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pFIeKepEdot->at(i) = forceFunctions->at(i)->pvaluepEdot(partFrame);
    }
    auto pFIeOpEdot = FMatDsptr();
    if (!pFIeKepEdot->isZero()) {
        pFIeOpEdot = aAOKe->timesFullMatrix(pFIeKepEdot);
    }
    if (prtFrmI == partFrame) {
        pFIeOpEdotI = pFIeOpEdot;
    }
    else if (prtFrmJ == partFrame) {
        pFIeOpEdotJ = pFIeOpEdot;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpFIeOpEK()
{
    //aFIeO = aAOKe * aFIeKe;
    pFIeOpEK = eFrmK->pAOepEtimesFullColumn(aFIeKe);
}

void ForceTorqueGeneral::calcpFJeOpEK()
{
    if (pFIeOpEK) {
        pFJeOpEK = pFIeOpEK->negated();
    }
    else {
        assert(!pFJeOpEK);
    }
}

void ForceTorqueGeneral::calcaTIeO()
{
    //aTIeO = aAOKe * aTIeKe;
    aTIeO = aAOKe->timesFullColumn(aTIeKe);
}

void ForceTorqueGeneral::calcpTIeOpX(SpatialContainerFrame* partFrame)
{
    //pTIeOpX = aAOKe * pTIeKepX
    auto pTIeKepX = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pTIeKepX->at(i) = torqueFunctions->at(i)->pvaluepX(partFrame);
    }
    auto pTIeOpX = FMatDsptr();
    if (!pTIeKepX->isZero()) {
        pTIeOpX = aAOKe->timesFullMatrix(pTIeKepX);
    }
    if (prtFrmI == partFrame) {
        pTIeOpXI = pTIeOpX;
    }
    else if (prtFrmJ == partFrame) {
        pTIeOpXJ = pTIeOpX;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpTIeOpE(SpatialContainerFrame* partFrame)
{
    //pTIeOpE = aAOKe * pTIeKepE
    auto pTIeKepE = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pTIeKepE->at(i) = torqueFunctions->at(i)->pvaluepE(partFrame);
    }
    auto pTIeOpE = FMatDsptr();
    if (!pTIeKepE->isZero()) {
        pTIeOpE = aAOKe->timesFullMatrix(pTIeKepE);
    }
    if (prtFrmI == partFrame) {
        pTIeOpEI = pTIeOpE;
    }
    else if (prtFrmJ == partFrame) {
        pTIeOpEJ = pTIeOpE;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpTIeOpXdot(SpatialContainerFrame* partFrame)
{
    //pTIeOpXdot = aAOKe * pTIeKepXdot
    auto pTIeKepXdot = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pTIeKepXdot->at(i) = torqueFunctions->at(i)->pvaluepXdot(partFrame);
    }
    auto pTIeOpXdot = FMatDsptr();
    if (!pTIeKepXdot->isZero()) {
        pTIeOpXdot = aAOKe->timesFullMatrix(pTIeKepXdot);
    }
    if (prtFrmI == partFrame) {
        pTIeOpXdotI = pTIeOpXdot;
    }
    else if (prtFrmJ == partFrame) {
        pTIeOpXdotJ = pTIeOpXdot;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpTIeOpEdot(SpatialContainerFrame* partFrame)
{
    //pTIeOpEdot = aAOKe * pTIeKepEdot
    auto pTIeKepEdot = FullMatrix<double>::With(3);
    for (size_t i = 0; i < 3; i++)
    {
        pTIeKepEdot->at(i) = torqueFunctions->at(i)->pvaluepEdot(partFrame);
    }
    auto pTIeOpEdot = FMatDsptr();
    if (!pTIeKepEdot->isZero()) {
        pTIeOpEdot = aAOKe->timesFullMatrix(pTIeKepEdot);
    }
    if (prtFrmI == partFrame) {
        pTIeOpEdotI = pTIeOpEdot;
    }
    else if (prtFrmJ == partFrame) {
        pTIeOpEdotJ = pTIeOpEdot;
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void ForceTorqueGeneral::calcpTIeOpEK()
{
    //aTIeO = aAOKe * aTIeKe;
    pTIeOpEK = eFrmK->pAOepEtimesFullColumn(aTIeKe);
}

void ForceTorqueGeneral::calcpTJeOpEK()
{
    //aTJeO = dispIeJeO->rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    if (pFIeOpEK && pTIeOpEK) {
        pTJeOpEK = dispIeJeO->rIeJeO->crossMatrix(pFIeOpEK)->minusFullMatrix(pTIeOpEK);
    }
    else
    {
        assert(!pTJeOpEK);
    }
}

void ForceTorqueGeneral::calcpQXIpEK()
{
    if (has_qI) {
        pQXIpEK = pFIeOpEK;
    }
}

void ForceTorqueGeneral::calcpQEIpEK()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpEK) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpEK));
    }
    if (twoBOIT && pTIeOpEK) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpEK));
    }
    if (terms->isZero()) {
        pQEIpEK = FMatDsptr();
    }
    else {
        pQEIpEK = terms;
    }
}

void ForceTorqueGeneral::calcpQXJpEK()
{
    if (has_qJ) {
        pQXJpEK = pFJeOpEK;
    }
    else {
        assert(!pQXJpEK);
    }
}

void ForceTorqueGeneral::calcpQEJpEK()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpEK) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpEK));
    }
    if (twoBOJT && pTJeOpEK) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpEK));
    }
    if (terms->isZero()) {
        pQEJpEK = FMatDsptr();
    }
    else {
        pQEJpEK = terms;
    }
}
