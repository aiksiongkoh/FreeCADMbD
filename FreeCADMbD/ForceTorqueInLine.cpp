#include "ForceTorqueInLine.h"
#include "ForceTorqueFunction.h"
#include "SimulationStoppingError.h"
#include "PartFrame.h"


using namespace MbD;

std::shared_ptr<ForceTorqueInLine> ForceTorqueInLine::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ForceTorqueInLine>(frmi, frmj);
    inst->initialize();
    return inst;
}

void ForceTorqueInLine::useEquationNumbers()
{
    ForceTorqueIJ::useEquationNumbers();
}

void ForceTorqueInLine::calcpFIeOpX(SpatialContainerFrame* partFrame)
{
    //aFIeO = tension * uIeJeO
    //pFIeOpX = uIeJeO * ptensionpX + tension * puIeJeOpX
    auto pFIeOpX = FullMatrix<double>::With(3, 3);
    auto ptensionpX = forceFunctions->front()->pvaluepX(partFrame);
    if (!ptensionpX->isZero()) {
        pFIeOpX->equalSelfPlus(uIeJeO->timesFullRow(ptensionpX));
    }
    auto puIeJeOpX = distIeJe->puIeJeOpX(partFrame);
    if (puIeJeOpX) {
        pFIeOpX->equalSelfPlus(puIeJeOpX->times(tension));
    }
    if (pFIeOpX->isZero()) {
        pFIeOpX = FMatDsptr();
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

void ForceTorqueInLine::calcpFIeOpE(SpatialContainerFrame* partFrame)
{
    //aFIeO = tension * uIeJeO
    //pFIeOpE = uIeJeO * ptensionpE + tension * puIeJeOpE
    auto pFIeOpE = FullMatrix<double>::With(3, 4);
    auto ptensionpE = forceFunctions->front()->pvaluepE(partFrame);
    if (!ptensionpE->isZero()) {
        pFIeOpE->equalSelfPlus(uIeJeO->timesFullRow(ptensionpE));
    }
    auto puIeJeOpE = distIeJe->puIeJeOpE(partFrame);
    if (puIeJeOpE) {
        pFIeOpE->equalSelfPlus(puIeJeOpE->times(tension));
    }
    if (pFIeOpE->isZero()) {
        pFIeOpE = FMatDsptr();
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

void ForceTorqueInLine::calcpFIeOpXdot(SpatialContainerFrame* partFrame)
{
    //aFIeO = tension * uIeJeO
    //pFIeOpXdot = uIeJeO * ptensionpXdot
    auto pFIeOpXdot = FullMatrix<double>::With(3, 3);
    auto ptensionpXdot = forceFunctions->front()->pvaluepXdot(partFrame);
    if (!ptensionpXdot->isZero()) {
        pFIeOpXdot->equalSelfPlus(uIeJeO->timesFullRow(ptensionpXdot));
    }
    if (pFIeOpXdot->isZero()) {
        pFIeOpXdot = FMatDsptr();
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

void ForceTorqueInLine::calcpFIeOpEdot(SpatialContainerFrame* partFrame)
{
    //aFIeO = tension * uIeJeO
    //pFIeOpEdot = uIeJeO * ptensionpEdot
    auto pFIeOpEdot = FullMatrix<double>::With(3, 4);
    auto ptensionpEdot = forceFunctions->front()->pvaluepEdot(partFrame);
    if (!ptensionpEdot->isZero()) {
        pFIeOpEdot->equalSelfPlus(uIeJeO->timesFullRow(ptensionpEdot));
    }
    if (pFIeOpEdot->isZero()) {
        pFIeOpEdot = FMatDsptr();
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

void ForceTorqueInLine::calcaTIeO()
{
    aTIeO = uIeJeO->times(twist);
}

void ForceTorqueInLine::calcpTIeOpX(SpatialContainerFrame* partFrame)
{
    //aTIeO = twist * uIeJeO
    //pTIeOpX = uIeJeO * ptwistpX + twist * puIeJeOpX
    auto pTIeOpX = FullMatrix<double>::With(3, 3);
    auto ptwistpX = torqueFunctions->front()->pvaluepX(partFrame);
    if (!ptwistpX->isZero()) {
        pTIeOpX->equalSelfPlus(uIeJeO->timesFullRow(ptwistpX));
    }
    auto puIeJeOpX = distIeJe->puIeJeOpX(partFrame);
    if (puIeJeOpX) {
        pTIeOpX->equalSelfPlus(puIeJeOpX->times(twist));
    }
    if (pTIeOpX->isZero()) {
        pTIeOpX = FMatDsptr();
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

void ForceTorqueInLine::calcpTIeOpE(SpatialContainerFrame* partFrame)
{
    //aTIeO = twist * uIeJeO
    //pTIeOpE = uIeJeO * ptwistpE + twist * puIeJeOpE
    auto pTIeOpE = FullMatrix<double>::With(3, 4);
    auto ptwistpE = torqueFunctions->front()->pvaluepE(partFrame);
    if (!ptwistpE->isZero()) {
        pTIeOpE->equalSelfPlus(uIeJeO->timesFullRow(ptwistpE));
    }
    auto puIeJeOpE = distIeJe->puIeJeOpE(partFrame);
    if (puIeJeOpE) {
        pTIeOpE->equalSelfPlus(puIeJeOpE->times(twist));
    }
    if (pTIeOpE->isZero()) {
        pTIeOpE = FMatDsptr();
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

void ForceTorqueInLine::calcpTIeOpXdot(SpatialContainerFrame* partFrame)
{
    //aTIeO = twist * uIeJeO
    //pTIeOpXdot = uIeJeO * ptwistpXdot
    auto pTIeOpXdot = FullMatrix<double>::With(3, 3);
    auto ptwistpXdot = torqueFunctions->front()->pvaluepXdot(partFrame);
    if (!ptwistpXdot->isZero()) {
        pTIeOpXdot->equalSelfPlus(uIeJeO->timesFullRow(ptwistpXdot));
    }
    if (pTIeOpXdot->isZero()) {
        pTIeOpXdot = FMatDsptr();
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

void ForceTorqueInLine::calcpTIeOpEdot(SpatialContainerFrame* partFrame)
{
    //aTIeO = twist * uIeJeO
    //pTIeOpEdot = uIeJeO * ptwistpEdot
    auto pTIeOpEdot = FullMatrix<double>::With(3, 4);
    auto ptwistpEdot = torqueFunctions->front()->pvaluepEdot(partFrame);
    if (!ptwistpEdot->isZero()) {
        pTIeOpEdot->equalSelfPlus(uIeJeO->timesFullRow(ptwistpEdot));
    }
    if (pTIeOpEdot->isZero()) {
        pTIeOpEdot = FMatDsptr();
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

double ForceTorqueInLine::getTension()
{
    return forceFunctions->front()->forTor();
}

double ForceTorqueInLine::getTwist()
{
    return torqueFunctions->front()->forTor();
}

void ForceTorqueInLine::setTension(Symsptr formula)
{
    forceFunctions->front()->setformula(formula);
}

void ForceTorqueInLine::setTwist(Symsptr formula)
{
    torqueFunctions->front()->setformula(formula);
}

void ForceTorqueInLine::simUpdateAll()
{
    distIeJe->simUpdateAll();
    calcuIeJeO();
    for (const auto func : *forceFunctions) func->simUpdateAll();
    for (const auto func : *torqueFunctions) func->simUpdateAll();
    calctension();
    calctwist();
    ForceTorqueIJ::simUpdateAll();
}

void ForceTorqueInLine::calcuIeJeO()
{
    uIeJeO = distIeJe->uIeJeO;
    puIeJeOpXI = distIeJe->puIeJeOpXI();
    puIeJeOpEI = distIeJe->puIeJeOpEI();
    puIeJeOpXJ = distIeJe->puIeJeOpXJ();
    puIeJeOpEJ = distIeJe->puIeJeOpEJ();
}

void ForceTorqueInLine::calctension()
{
    tension = forceFunctions->front()->forTor();
}

void ForceTorqueInLine::calctwist()
{
    twist = torqueFunctions->front()->forTor();
}

void ForceTorqueInLine::calcaFIeO()
{
    aFIeO = uIeJeO->times(tension);
}

void ForceTorqueInLine::initialize()
{
    ForceTorqueIJ::initialize();
    distIeJe = DistIeJe::With(geteFrmI(), geteFrmJ());
    distIeJe->owner = this;
    for (size_t i = 0; i < 1; i++)
    {
        auto forceFunc = ForceTorqueFunction::With();
        forceFunc->owner = this;
        forceFunctions->push_back(forceFunc);
        auto torqueFunc = ForceTorqueFunction::With();
        torqueFunc->owner = this;
        torqueFunctions->push_back(torqueFunc);
    }
}

void ForceTorqueInLine::fillAccICIterError(FColDsptr col)
{
    //if (has_qI) {
    //    col->atiplusFullColumn(iqXI, aFIeO);
    //    col->atiplusFullColumn(iqEI, (prOeOpEIT->timesFullColumn(aFIeO)));
    //    col->atiplusFullColumn(iqEI, (twoBIT->timesFullColumn(aTIeO)));
    //}
    //col->atiplusFullColumn(iqXJ, aFJeO);
    //col->atiplusFullColumn(iqEJ, (prOeOpEJT->timesFullColumn(aFJeO)));
    //col->atiplusFullColumn(iqEJ, (twoBJT->timesFullColumn(aTJeO)));
    ForceTorqueIJ::fillAccICIterError(col);
}

void ForceTorqueInLine::fillAccICIterJacob(SpMatDsptr mat)
{
    //Only pQ/pqddot, pQ/pLambda contribute
    //Coulomb friction contributes
    ForceTorqueIJ::fillAccICIterJacob(mat);
}

void ForceTorqueInLine::postDynCorrectorIteration()
{
    distIeJe->postDynCorrectorIteration();
    ForceTorqueIJ::postDynCorrectorIteration();
}

void ForceTorqueInLine::postDynOutput()
{
    distIeJe->postDynOutput();
    ForceTorqueIJ::postDynOutput();
}

void ForceTorqueInLine::postAccICIteration()
{
    distIeJe->postAccICIteration();
    ForceTorqueIJ::postAccICIteration();
}

void ForceTorqueInLine::preDynOutput()
{
    distIeJe->preDynOutput();
    ForceTorqueIJ::preDynOutput();
}

void ForceTorqueInLine::postDynPredictor()
{
    distIeJe->postDynPredictor();
    ForceTorqueIJ::postDynPredictor();
}

void ForceTorqueInLine::preAccIC()
{
    distIeJe->preAccIC();
    ForceTorqueIJ::preAccIC();
}

void ForceTorqueInLine::postInput()
{
    distIeJe->postInput();
    ForceTorqueIJ::postInput();
}

void ForceTorqueInLine::initializeLocally()
{
    distIeJe->initializeLocally();
    ForceTorqueIJ::initializeLocally();
}

void ForceTorqueInLine::initializeGlobally()
{
    distIeJe->initializeGlobally();
    ForceTorqueIJ::initializeGlobally();
}
