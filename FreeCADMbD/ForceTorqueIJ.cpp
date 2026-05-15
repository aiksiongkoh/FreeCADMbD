#include "ForceTorqueIJ.h"
#include "ForceTorqueFunction.h"
#include "System.h"

using namespace MbD;

void ForceTorqueIJ::calcaFJeO()
{
    aFJeO = aFIeO->negated();
}

void ForceTorqueIJ::calcaTJeO()
{
    aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
}

void ForceTorqueIJ::calcpTIeOpXI()
{
    calcpTIeOpX(prtFrmI);
}

void ForceTorqueIJ::calcpTIeOpEI()
{
    calcpTIeOpE(prtFrmI);
}

void ForceTorqueIJ::calcpTIeOpXJ()
{
    calcpTIeOpX(prtFrmJ);
}

void ForceTorqueIJ::calcpTIeOpEJ()
{
    calcpTIeOpE(prtFrmJ);
}

void ForceTorqueIJ::calcpTJeOpXI()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 3);
    terms->zeroSelf();
    if (dispIeJeO->getpVectorpXI()) {
        terms->equalSelfPlus(dispIeJeO->getpVectorpXI()->cross(aFIeO));
    }
    if (pFIeOpXI) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpXI));
    }
    if (pTIeOpXI) {
        terms->equalSelfMinus(pTIeOpXI);
    }
    if (terms->isZero()) {
        pTJeOpXI = FMatDsptr();
    }
    else {
        pTJeOpXI = terms;
    }
}

void ForceTorqueIJ::calcpTJeOpEI()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 4);
    terms->zeroSelf();
    if (dispIeJeO->getpVectorpEI()) {
        terms->equalSelfPlus(dispIeJeO->getpVectorpEI()->cross(aFIeO));
    }
    if (pFIeOpEI) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpEI));
    }
    if (pTIeOpEI) {
        terms->equalSelfMinus(pTIeOpEI);
    }
    if (terms->isZero()) {
        pTJeOpEI = FMatDsptr();
    }
    else {
        pTJeOpEI = terms;
    }
}

void ForceTorqueIJ::calcpTJeOpXJ()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 3);
    terms->zeroSelf();
    if (dispIeJeO->getpVectorpXJ()) {
        terms->equalSelfPlus(dispIeJeO->getpVectorpXJ()->cross(aFIeO));
    }
    if (pFIeOpXJ) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpXJ));
    }
    if (pTIeOpXJ) {
        terms->equalSelfMinus(pTIeOpXJ);
    }
    if (terms->isZero()) {
        pTJeOpXJ = FMatDsptr();
    }
    else {
        pTJeOpXJ = terms;
    }
}

void ForceTorqueIJ::calcpTJeOpEJ()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 4);
    terms->zeroSelf();
    if (dispIeJeO->getpVectorpEJ()) {
        terms->equalSelfPlus(dispIeJeO->getpVectorpEJ()->cross(aFIeO));
    }
    if (pFIeOpEJ) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpEJ));
    }
    if (pTIeOpEJ) {
        terms->equalSelfMinus(pTIeOpEJ);
    }
    if (terms->isZero()) {
        pTJeOpEJ = FMatDsptr();
    }
    else {
        pTJeOpEJ = terms;
    }
}

void ForceTorqueIJ::calcpTIeOpXdotI()
{
    calcpTIeOpXdot(prtFrmI);
}

void ForceTorqueIJ::calcpTIeOpEdotI()
{
    calcpTIeOpEdot(prtFrmI);
}

void ForceTorqueIJ::calcpTIeOpXdotJ()
{
    calcpTIeOpXdot(prtFrmJ);
}

void ForceTorqueIJ::calcpTIeOpEdotJ()
{
    calcpTIeOpEdot(prtFrmJ);
}

void ForceTorqueIJ::calcpTJeOpXdotI()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 3);
    terms->zeroSelf();
    if (pFIeOpXdotI) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpXdotI));
    }
    if (pTIeOpXdotI) {
        terms->equalSelfMinus(pTIeOpXdotI);
    }
    if (terms->isZero()) {
        pTJeOpXdotI = FMatDsptr();
    }
    else {
        pTJeOpXdotI = terms;
    }
}

void ForceTorqueIJ::calcpTJeOpEdotI()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 4);
    terms->zeroSelf();
    if (pFIeOpEdotI) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpEdotI));
    }
    if (pTIeOpEdotI) {
        terms->equalSelfMinus(pTIeOpEdotI);
    }
    if (terms->isZero()) {
        pTJeOpEdotI = FMatDsptr();
    }
    else {
        pTJeOpEdotI = terms;
    }
}

void ForceTorqueIJ::calcpTJeOpXdotJ()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 3);
    terms->zeroSelf();
    if (pFIeOpXdotJ) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpXdotJ));
    }
    if (pTIeOpXdotJ) {
        terms->equalSelfMinus(pTIeOpXdotJ);
    }
    if (terms->isZero()) {
        pTJeOpXdotJ = FMatDsptr();
    }
    else {
        pTJeOpXdotJ = terms;
    }
}

void ForceTorqueIJ::calcpTJeOpEdotJ()
{
    //aTJeO = rIeJeO->cross(aFIeO)->minusFullColumn(aTIeO);
    auto terms = FullMatrix<double>::With(3, 4);
    terms->zeroSelf();
    if (pFIeOpEdotJ) {
        terms->equalSelfPlus(rIeJeO->crossMatrix(pFIeOpEdotJ));
    }
    if (pTIeOpEdotJ) {
        terms->equalSelfMinus(pTIeOpEdotJ);
    }
    if (terms->isZero()) {
        pTJeOpEdotJ = FMatDsptr();
    }
    else {
        pTJeOpEdotJ = terms;
    }
}

FColDsptr ForceTorqueIJ::aFX() const
{
    if (has_qI) {
        return aFIeO;
    }
    return aFJeO->negated();
}

FColDsptr ForceTorqueIJ::aTX() const
{
    if (has_qI) {
        return aTIeO;
    }
    return aTJeO->negated();
}

void ForceTorqueIJ::simUpdateAll()
{
    //Order of functions matters here.
    rIeJeO = dispIeJeO->rIeJeO;
    if (has_qI) {
        auto eFrmIeq = std::dynamic_pointer_cast<EndFrameq>(eFrmI);
        prOIeOpEIT = eFrmIeq->prOeOpE->transpose();
        twoBOIT = eFrmIeq->aBOp()->transpose()->times(2.0);
    }
    else {
        assert(!prOIeOpEIT);
        assert(!twoBOIT);
    }
    if (has_qJ) {
        auto eFrmJeq = std::dynamic_pointer_cast<EndFrameq>(eFrmJ);
        prOJeOpEJT = eFrmJeq->prOeOpE->transpose();
        twoBOJT = eFrmJeq->aBOp()->transpose()->times(2.0);
    }
    else {
        assert(!prOJeOpEJT);
        assert(!twoBOJT);
    }
    calcaFIeO();
    calcaFJeO();
    calcaTIeO();
    calcaTJeO();
    calcpFIeOpXI();
    calcpFIeOpEI();
    calcpFIeOpXJ();
    calcpFIeOpEJ();
    calcpTIeOpXI();
    calcpTIeOpEI();
    calcpTIeOpXJ();
    calcpTIeOpEJ();
    calcpFJeOpXI();
    calcpFJeOpEI();
    calcpFJeOpXJ();
    calcpFJeOpEJ();
    calcpTJeOpXI();
    calcpTJeOpEI();
    calcpTJeOpXJ();
    calcpTJeOpEJ();
    calcpFIeOpXdotI();
    calcpFIeOpEdotI();
    calcpFIeOpXdotJ();
    calcpFIeOpEdotJ();
    calcpTIeOpXdotI();
    calcpTIeOpEdotI();
    calcpTIeOpXdotJ();
    calcpTIeOpEdotJ();
    calcpFJeOpXdotI();
    calcpFJeOpEdotI();
    calcpFJeOpXdotJ();
    calcpFJeOpEdotJ();
    calcpTJeOpXdotI();
    calcpTJeOpEdotI();
    calcpTJeOpXdotJ();
    calcpTJeOpEdotJ();
    calcaQXI();
    calcaQEI();
    calcaQXJ();
    calcaQEJ();
    calcpQXIpXI();
    calcpQXIpEI();
    calcpQXIpXJ();
    calcpQXIpEJ();
    calcpQEIpXI();
    calcpQEIpEI();
    calcpQEIpXJ();
    calcpQEIpEJ();
    calcpQXJpXI();
    calcpQXJpEI();
    calcpQXJpXJ();
    calcpQXJpEJ();
    calcpQEJpXI();
    calcpQEJpEI();
    calcpQEJpXJ();
    calcpQEJpEJ();
    calcpQXIpXdotI();
    calcpQXIpEdotI();
    calcpQXIpXdotJ();
    calcpQXIpEdotJ();
    calcpQEIpXdotI();
    calcpQEIpEdotI();
    calcpQEIpXdotJ();
    calcpQEIpEdotJ();
    calcpQXJpXdotI();
    calcpQXJpEdotI();
    calcpQXJpXdotJ();
    calcpQXJpEdotJ();
    calcpQEJpXdotI();
    calcpQEJpEdotI();
    calcpQEJpXdotJ();
    calcpQEJpEdotJ();
}

void ForceTorqueIJ::fillAccICIterError(FColDsptr col)
{
    if (has_qI) {
        col->atiplusFullColumn(iqXI, aQXI);
        col->atiplusFullColumn(iqEI, aQEI);
    }
    if (has_qJ) {
        col->atiplusFullColumn(iqXJ, aQXJ);
        col->atiplusFullColumn(iqEJ, aQEJ);
    }
}

void ForceTorqueIJ::fillAccICIterJacob(SpMatDsptr mat)
{
    //Only pQ/pqddot, pQ/pLambda contribute
    //Coulomb friction contributes
}

void ForceTorqueIJ::fillDynError(FColDsptr col)
{
    if (has_qI) {
        col->atiplusFullColumn(iqXI, aQXI);
        col->atiplusFullColumn(iqEI, aQEI);
    }
    if (has_qJ) {
        col->atiplusFullColumn(iqXJ, aQXJ);
        col->atiplusFullColumn(iqEJ, aQEJ);
    }
}

void ForceTorqueIJ::fillpFpy(SpMatDsptr mat)
{
    auto block = [&](size_t iQ, size_t iq, FMatDsptr pQpq) -> void {
        if (pQpq) {
            mat->atijplusFullMatrix(iQ, iq, pQpq);
        }
        };
    block(iqXI, iqXI, pQXIpXI);
    block(iqXI, iqEI, pQXIpEI);
    block(iqXI, iqXJ, pQXIpXJ);
    block(iqXI, iqEJ, pQXIpEJ);
    block(iqEI, iqXI, pQEIpXI);
    block(iqEI, iqEI, pQEIpEI);
    block(iqEI, iqXJ, pQEIpXJ);
    block(iqEI, iqEJ, pQEIpEJ);
    block(iqXJ, iqXI, pQXJpXI);
    block(iqXJ, iqEI, pQXJpEI);
    block(iqEJ, iqXI, pQEJpXI);
    block(iqEJ, iqEI, pQEJpEI);
    block(iqXJ, iqXJ, pQXJpXJ);
    block(iqXJ, iqEJ, pQXJpEJ);
    block(iqEJ, iqXJ, pQEJpXJ);
    block(iqEJ, iqEJ, pQEJpEJ);
}

void ForceTorqueIJ::fillpFpydot(SpMatDsptr mat)
{
    auto block = [&](size_t iQ, size_t iq, FMatDsptr pQpq) -> void {
        if (pQpq) {
            mat->atijplusFullMatrix(iQ, iq, pQpq);
        }
        };
    block(iqXI, iqXI, pQXIpXdotI);
    block(iqXI, iqEI, pQXIpEdotI);
    block(iqXI, iqXJ, pQXIpXdotJ);
    block(iqXI, iqEJ, pQXIpEdotJ);
    block(iqEI, iqXI, pQEIpXdotI);
    block(iqEI, iqEI, pQEIpEdotI);
    block(iqEI, iqXJ, pQEIpXdotJ);
    block(iqEI, iqEJ, pQEIpEdotJ);
    block(iqXJ, iqXI, pQXJpXdotI);
    block(iqXJ, iqEI, pQXJpEdotI);
    block(iqEJ, iqXI, pQEJpXdotI);
    block(iqEJ, iqEI, pQEJpEdotI);
    block(iqXJ, iqXJ, pQXJpXdotJ);
    block(iqXJ, iqEJ, pQXJpEdotJ);
    block(iqEJ, iqXJ, pQEJpXdotJ);
    block(iqEJ, iqEJ, pQEJpEdotJ);
}

void ForceTorqueIJ::calcpFIeOpXI()
{
    calcpFIeOpXI();
}

void ForceTorqueIJ::calcpFIeOpEI()
{
    calcpFIeOpE(prtFrmI);
}

void ForceTorqueIJ::calcpFIeOpXJ()
{
    calcpFIeOpX(prtFrmJ);
}

void ForceTorqueIJ::calcpFIeOpEJ()
{
    calcpFIeOpE(prtFrmJ);
}

void ForceTorqueIJ::calcpFJeOpXI()
{
    if (pFIeOpXI) {
        pFJeOpXI = pFIeOpXI->negated();
    }
    else
    {
        assert(!pFJeOpXI);
    }
}

void ForceTorqueIJ::calcpFJeOpEI()
{
    if (pFIeOpEI) {
        pFJeOpEI = pFIeOpEI->negated();
    }
    else
    {
        assert(!pFJeOpEI);
    }
}

void ForceTorqueIJ::calcpFJeOpXJ()
{
    if (pFIeOpXJ) {
        pFJeOpXJ = pFIeOpXJ->negated();
    }
    else
    {
        assert(!pFJeOpXJ);
    }
}

void ForceTorqueIJ::calcpFJeOpEJ()
{
    if (pFIeOpEJ) {
        pFJeOpEJ = pFIeOpEJ->negated();
    }
    else
    {
        assert(!pFJeOpEJ);
    }
}

void ForceTorqueIJ::calcpFIeOpXdotI()
{
    calcpFIeOpXdot(prtFrmI);
}

void ForceTorqueIJ::calcpFIeOpEdotI()
{
    calcpFIeOpEdot(prtFrmI);
}

void ForceTorqueIJ::calcpFIeOpXdotJ()
{
    calcpFIeOpXdot(prtFrmJ);
}

void ForceTorqueIJ::calcpFIeOpEdotJ()
{
    calcpFIeOpEdot(prtFrmJ);
}

void ForceTorqueIJ::calcpFJeOpXdotI()
{
    if (pFIeOpXdotI) {
        pFJeOpXdotI = pFIeOpXdotI->negated();
    }
    else
    {
        assert(!pFJeOpXdotI);
    }
}

void ForceTorqueIJ::calcpFJeOpEdotI()
{
    if (pFIeOpEdotI) {
        pFJeOpEdotI = pFIeOpEdotI->negated();
    }
    else
    {
        assert(!pFJeOpEdotI);
    }
}

void ForceTorqueIJ::calcpFJeOpXdotJ()
{
    if (pFIeOpXdotJ) {
        pFJeOpXdotJ = pFIeOpXdotJ->negated();
    }
    else
    {
        assert(!pFJeOpXdotJ);
    }
}

void ForceTorqueIJ::calcpFJeOpEdotJ()
{
    if (pFIeOpEdotJ) {
        pFJeOpEdotJ = pFIeOpEdotJ->negated();
    }
    else
    {
        assert(!pFJeOpEdotJ);
    }
}

void ForceTorqueIJ::setForceFunctions(FColsptr<Symsptr> col)
{
    assert(forceFunctions->size() == col->size());
    for (size_t i = 0; i < forceFunctions->size(); i++)
    {
        forceFunctions->at(i)->setformula(col->at(i));
    }
}

void ForceTorqueIJ::setTorqueFunctions(FColsptr<Symsptr> col)
{
    assert(torqueFunctions->size() == col->size());
    for (size_t i = 0; i < torqueFunctions->size(); i++)
    {
        torqueFunctions->at(i)->setformula(col->at(i));
    }
}

void ForceTorqueIJ::initialize()
{
    forceFunctions = std::make_shared<std::vector<std::shared_ptr<ForceTorqueFunction>>>();
    torqueFunctions = std::make_shared<std::vector<std::shared_ptr<ForceTorqueFunction>>>();
    dispIeJeO = DispIeJeO::With(geteFrmI(), geteFrmJ());
}

void ForceTorqueIJ::initializeGlobally()
{
    for (const auto func : *forceFunctions) func->initializeGlobally();
    for (const auto func : *torqueFunctions) func->initializeGlobally();
    pprOIeOpEIpEI = eFrmI->getpprOeOpEpE();  //This is constant.
    pprOJeOpEJpEJ = eFrmJ->getpprOeOpEpE();  //This is constant.
    ForceTorqueItem::initializeGlobally();
}

void ForceTorqueIJ::initializeLocally()
{
    prtFrmI = eFrmI->getPartFrame();
    prtFrmJ = eFrmJ->getPartFrame();
    has_qI = eFrmI->has_qX();
    has_qJ = eFrmJ->has_qX();
    for (const auto func : *forceFunctions) func->initializeLocally();
    for (const auto func : *torqueFunctions) func->initializeLocally();
    ForceTorqueItem::initializeLocally();
}

void ForceTorqueIJ::postInput()
{
    for (const auto func : *forceFunctions) func->postInput();
    for (const auto func : *torqueFunctions) func->postInput();
    ForceTorqueItem::postInput();
}

void ForceTorqueIJ::postStaticIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueIJ::preAccIC()
{
    for (const auto func : *forceFunctions) func->preAccIC();
    for (const auto func : *torqueFunctions) func->preAccIC();
    ForceTorqueItem::preAccIC();
}

void ForceTorqueIJ::preDynOutput()
{
    for (const auto func : *forceFunctions) func->preDynOutput();
    for (const auto func : *torqueFunctions) func->preDynOutput();
    ForceTorqueItem::preDynOutput();
}

void ForceTorqueIJ::preStatic()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueIJ::useEquationNumbers()
{
    if (has_qI) {
        iqXI = eFrmI->iqX();
        iqEI = eFrmI->iqE();
    }
    if (has_qJ) {
        iqXJ = eFrmJ->iqX();
        iqEJ = eFrmJ->iqE();
    }
}

void ForceTorqueIJ::postAccICIteration()
{
    for (const auto func : *forceFunctions) func->postAccICIteration();
    for (const auto func : *torqueFunctions) func->postAccICIteration();
    ForceTorqueItem::postAccICIteration();
}

void ForceTorqueIJ::postCollisionCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueIJ::postCollisionPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueIJ::postDynCorrectorIteration()
{
    for (const auto func : *forceFunctions) func->postDynCorrectorIteration();
    for (const auto func : *torqueFunctions) func->postDynCorrectorIteration();
    ForceTorqueItem::postDynCorrectorIteration();
}

void ForceTorqueIJ::postDynOutput()
{
    for (const auto func : *forceFunctions) func->postDynOutput();
    for (const auto func : *torqueFunctions) func->postDynOutput();
    ForceTorqueItem::postDynOutput();
}

void ForceTorqueIJ::postDynPredictor()
{
    for (const auto func : *forceFunctions) func->postDynPredictor();
    for (const auto func : *torqueFunctions) func->postDynPredictor();
    ForceTorqueItem::postDynPredictor();
}

void ForceTorqueIJ::calcpQXIpXI()
{
    if (has_qI) {
        pQXIpXI = pFIeOpXI;
    }
}

void ForceTorqueIJ::calcpQXIpEI()
{
    if (has_qI) {
        pQXIpEI = pFIeOpEI;
    }
}

void ForceTorqueIJ::calcpQXIpXJ()
{
    if (has_qI) {
        pQXIpXJ = pFIeOpXJ;
    }
}

void ForceTorqueIJ::calcpQXIpEJ()
{
    if (has_qI) {
        pQXIpEJ = pFIeOpEJ;
    }
}

void ForceTorqueIJ::calcpQEIpXI()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpXI) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpXI));
    }
    if (twoBOIT && pTIeOpXI) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpXI));
    }
    if (terms->isZero()) {
        pQEIpXI = FMatDsptr();
    }
    else {
        pQEIpXI = terms;
    }
}

void ForceTorqueIJ::calcpQEIpEI()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (pprOIeOpEIpEI) {
        terms->equalSelfPlus(pprOIeOpEIpEI->elementsTransposeTimesFullColumn(aFIeO));
    }
    if (prOIeOpEIT && pFIeOpEI) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpEI));
    }
    if (has_qI) {
        terms->equalSelfPlus(EulerParameters<double>::pBTpEtimesColumn(aTIeO->times(2.0)));
    }
    if (twoBOIT && pTIeOpEI) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpEI));
    }
    if (terms->isZero()) {
        pQEIpEI = FMatDsptr();
    }
    else {
        pQEIpEI = terms;
    }
}

void ForceTorqueIJ::calcpQEIpXJ()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpXJ) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpXJ));
    }
    if (twoBOIT && pTIeOpXJ) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpXJ));
    }
    if (terms->isZero()) {
        pQEIpXJ = FMatDsptr();
    }
    else {
        pQEIpXJ = terms;
    }
}

void ForceTorqueIJ::calcpQEIpEJ()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpEJ) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpEJ));
    }
    if (twoBOIT && pTIeOpEJ) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpEJ));
    }
    if (terms->isZero()) {
        pQEIpEJ = FMatDsptr();
    }
    else {
        pQEIpEJ = terms;
    }
}

void ForceTorqueIJ::calcpQXJpXI()
{
    if (has_qJ) {
        pQXJpXI = pFJeOpXI;
    }
}

void ForceTorqueIJ::calcpQXJpEI()
{
    if (has_qJ) {
        pQXJpEI = pFJeOpEI;
    }
}

void ForceTorqueIJ::calcpQXJpXJ()
{
    if (has_qJ) {
        pQXJpXJ = pFJeOpXJ;
    }
}

void ForceTorqueIJ::calcpQXJpEJ()
{
    if (has_qJ) {
        pQXJpEJ = pFJeOpEJ;
    }
}

void ForceTorqueIJ::calcpQEJpXI()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpXI) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpXI));
    }
    if (twoBOJT && pTJeOpXI) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpXI));
    }
    if (terms->isZero()) {
        pQEJpXI = FMatDsptr();
    }
    else {
        pQEJpXI = terms;
    }
}

void ForceTorqueIJ::calcpQEJpEI()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpEI) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpEI));
    }
    if (twoBOJT && pTJeOpEI) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpEI));
    }
    if (terms->isZero()) {
        pQEJpEI = FMatDsptr();
    }
    else {
        pQEJpEI = terms;
    }
}

void ForceTorqueIJ::calcpQEJpXJ()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpXJ) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpXJ));
    }
    if (twoBOJT && pTJeOpXJ) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpXJ));
    }
    if (terms->isZero()) {
        pQEJpXJ = FMatDsptr();
    }
    else {
        pQEJpXJ = terms;
    }
}

void ForceTorqueIJ::calcpQEJpEJ()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (pprOJeOpEJpEJ) {
        terms->equalSelfPlus(pprOJeOpEJpEJ->elementsTransposeTimesFullColumn(aFJeO));
    }
    if (prOJeOpEJT && pFJeOpEJ) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpEJ));
    }
    if (has_qJ) {
        terms->equalSelfPlus(EulerParameters<double>::pBTpEtimesColumn(aTJeO->times(2.0)));
    }
    if (twoBOJT && pTJeOpEJ) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpEJ));
    }
    if (terms->isZero()) {
        pQEJpEJ = FMatDsptr();
    }
    else {
        pQEJpEJ = terms;
    }
}

void ForceTorqueIJ::calcpQXIpXdotI()
{
    if (has_qI) {
        pQXIpXdotI = pFIeOpXdotI;
    }
}

void ForceTorqueIJ::calcpQXIpEdotI()
{
    if (has_qI) {
        pQXIpEdotI = pFIeOpEdotI;
    }
}

void ForceTorqueIJ::calcpQXIpXdotJ()
{
    if (has_qI) {
        pQXIpXdotJ = pFIeOpXdotJ;
    }
}

void ForceTorqueIJ::calcpQXIpEdotJ()
{
    if (has_qI) {
        pQXIpEdotJ = pFIeOpEdotJ;
    }
}

void ForceTorqueIJ::calcpQEIpXdotI()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpXdotI) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpXdotI));
    }
    if (twoBOIT && pTIeOpXdotI) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpXdotI));
    }
    if (terms->isZero()) {
        pQEIpXdotI = FMatDsptr();
    }
    else {
        pQEIpXdotI = terms;
    }
}

void ForceTorqueIJ::calcpQEIpEdotI()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpEdotI) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpEdotI));
    }
    if (twoBOIT && pTIeOpEdotI) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpEdotI));
    }
    if (terms->isZero()) {
        pQEIpEdotI = FMatDsptr();
    }
    else {
        pQEIpEdotI = terms;
    }
}

void ForceTorqueIJ::calcpQEIpXdotJ()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpXdotJ) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpXdotJ));
    }
    if (twoBOIT && pTIeOpXdotJ) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpXdotJ));
    }
    if (terms->isZero()) {
        pQEIpXdotJ = FMatDsptr();
    }
    else {
        pQEIpXdotJ = terms;
    }
}

void ForceTorqueIJ::calcpQEIpEdotJ()
{
    //aQEI = prOIeOpEIT * aFIeO + twoBOIT * aTIeO
    if (!has_qI) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOIeOpEIT && pFIeOpEdotJ) {
        terms->equalSelfPlus(prOIeOpEIT->timesFullMatrix(pFIeOpEdotJ));
    }
    if (twoBOIT && pTIeOpEdotJ) {
        terms->equalSelfPlus(twoBOIT->timesFullMatrix(pTIeOpEdotJ));
    }
    if (terms->isZero()) {
        pQEIpEdotJ = FMatDsptr();
    }
    else {
        pQEIpEdotJ = terms;
    }
}

void ForceTorqueIJ::calcpQXJpXdotI()
{
    if (has_qJ) {
        pQXJpXdotI = pFJeOpXdotI;
    }
}

void ForceTorqueIJ::calcpQXJpEdotI()
{
    if (has_qJ) {
        pQXJpEdotI = pFJeOpEdotI;
    }
}

void ForceTorqueIJ::calcpQXJpXdotJ()
{
    if (has_qJ) {
        pQXJpXdotJ = pFJeOpXdotJ;
    }
}

void ForceTorqueIJ::calcpQXJpEdotJ()
{
    if (has_qJ) {
        pQXJpEdotJ = pFJeOpEdotJ;
    }
}

void ForceTorqueIJ::calcpQEJpXdotI()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpXdotI) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpXdotI));
    }
    if (twoBOJT && pTJeOpXdotI) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpXdotI));
    }
    if (terms->isZero()) {
        pQEJpXdotI = FMatDsptr();
    }
    else {
        pQEJpXdotI = terms;
    }
}

void ForceTorqueIJ::calcpQEJpEdotI()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpEdotI) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpEdotI));
    }
    if (twoBOJT && pTJeOpEdotI) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpEdotI));
    }
    if (terms->isZero()) {
        pQEJpEdotI = FMatDsptr();
    }
    else {
        pQEJpEdotI = terms;
    }
}

void ForceTorqueIJ::calcpQEJpXdotJ()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 3);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpXdotJ) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpXdotJ));
    }
    if (twoBOJT && pTJeOpXdotJ) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpXdotJ));
    }
    if (terms->isZero()) {
        pQEJpXdotJ = FMatDsptr();
    }
    else {
        pQEJpXdotJ = terms;
    }
}

void ForceTorqueIJ::calcpQEJpEdotJ()
{
    //aQEJ = prOJeOpEJT * aFJeO + twoBOJT * aTJeO
    if (!has_qJ) return;
    auto terms = FullMatrix<double>::With(4, 4);
    terms->zeroSelf();
    if (prOJeOpEJT && pFJeOpEdotJ) {
        terms->equalSelfPlus(prOJeOpEJT->timesFullMatrix(pFJeOpEdotJ));
    }
    if (twoBOJT && pTJeOpEdotJ) {
        terms->equalSelfPlus(twoBOJT->timesFullMatrix(pTJeOpEdotJ));
    }
    if (terms->isZero()) {
        pQEJpEdotJ = FMatDsptr();
    }
    else {
        pQEJpEdotJ = terms;
    }
}

void ForceTorqueIJ::useUniqueDispIeJeO()
{
    auto dispIeJeOs = root()->dispIeJeOs;
    auto it = std::find_if(dispIeJeOs->begin(), dispIeJeOs->end(), [&](auto disp) {return disp->hasSameEndFrms(dispIeJeO); });
    if (it == dispIeJeOs->end()) {
        dispIeJeOs->push_back(dispIeJeO);
    }
    else {
        dispIeJeO = *it;
    }
}

void ForceTorqueIJ::useUniqueDispIeJeKe()
{
    // Do nothing.
}

void ForceTorqueIJ::calcaQXI()
{
    if (has_qI) {
        aQXI = aFIeO;
    }
    else {
        assert(!aQXI);
    }
}

void ForceTorqueIJ::calcaQEI()
{
    if (has_qI) {
        aQEI = prOIeOpEIT->timesFullColumn(aFIeO)->plusFullColumn(twoBOIT->timesFullColumn(aTIeO));
    }
    else {
        assert(!aQEI);
    }
}

void ForceTorqueIJ::calcaQXJ()
{
    if (has_qJ) {
        aQXJ = aFJeO;
    }
    else {
        assert(!aQXJ);
    }
}

void ForceTorqueIJ::calcaQEJ()
{
    if (has_qJ) {
        aQEJ = prOJeOpEJT->timesFullColumn(aFJeO)->plusFullColumn(twoBOJT->timesFullColumn(aTJeO));
    }
    else {
        assert(!aQEJ);
    }
}
