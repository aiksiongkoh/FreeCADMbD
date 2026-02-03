/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

//#include <string>
//#include <vector>

#include "FullColumn.h"
#include "FullRow.h"
#include "FullMatrix.h"
#include "DiagonalMatrix.h"
#include "SparseMatrix.h"
#include "enum.h"

namespace MbD {
    class System;
    class Constraint;
    class StateData;
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class Item : public std::enable_shared_from_this<Item>
    {
        //name
    public:
        virtual ~Item() = default;
        Item();
        Item(const std::string& str) : name(str) {}

        static std::shared_ptr<Item> With(const std::string& str);
        static void noop();

        virtual void initialize();
        virtual void initializeGlobally();
        virtual void initializeLocally();

        virtual void postInput();
        virtual void useEquationNumbers();

        virtual void preICRestart();
        virtual void prePosIC();
        virtual void prePosKine();
        virtual void postPosIC();
        virtual void postPosICIteration();
        virtual void fillPosICError(FColDsptr col);
        virtual void fillPosICJacob(SpMatDsptr mat);
        virtual void fillPosKineError(FColDsptr col);
        virtual void fillPosKineJacob(SpMatDsptr mat);
        virtual void discontinuityAtICAddTo(std::shared_ptr<std::vector<DiscontinuityType>> disconTypes);
        virtual void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints);
        virtual void fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints);
        virtual void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints);
        virtual void fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints);
        virtual void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints);
        virtual void constraintsReport();
        virtual void reactivateRedundantConstraints();
        virtual void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos);
        virtual void fillqsuWeights(DiagMatDsptr diagMat);
        virtual void fillqsuWeightsSmall(FColDsptr col);
        virtual void fillqsulam(FColDsptr col);
        virtual void setqsulam(FColDsptr col);
        virtual void fillqsu(FColDsptr col);
        virtual void setqsu(FColDsptr qsuOld);


        virtual void preVelIC();
        virtual void fillVelICError(FColDsptr col);
        virtual void fillVelICJacob(SpMatDsptr mat);
        virtual void postVelIC();
        virtual void fillqsudotWeights(DiagMatDsptr diagMat);
        virtual void fillqsudot(FColDsptr col);
        virtual void setqsudot(FColDsptr col);
        virtual void setqsudotlam(FColDsptr col);

        virtual void preAccIC();
        virtual void fillAccICIterError(FColDsptr col);
        virtual void fillAccICIterJacob(SpMatDsptr mat);
        virtual void postAccICIteration();
        virtual void postAccIC();
        virtual void fillqsuddotlam(FColDsptr col);
        virtual void setqsuddotlam(FColDsptr col);

        virtual void preDyn();
        virtual void preDynCorrector();
        virtual void preDynCorrectorIteration();
        virtual void preDynFirstStep();
        virtual void preDynOutput();
        virtual void preDynPredictor();
        virtual void preDynStep();
        virtual void fillDynError(FColDsptr col);
        virtual void fillpFpy(SpMatDsptr mat);
        virtual void fillpFpydot(SpMatDsptr mat);
        virtual void postDyn();
        virtual void postDynCorrector();
        virtual void postDynCorrectorIteration();
        virtual void postDynFirstStep();
        virtual void postDynOutput();
        virtual void postDynPredictor();
        virtual void postDynStep();
        virtual void storeDynState();
        virtual double suggestSmallerOrAcceptDynFirstStepSize(double hnew);
        virtual double suggestSmallerOrAcceptDynStepSize(double hnew);
        virtual void simUpdateAll();
        virtual double checkForDynDiscontinuityBetweenand(double tprev, double t);
        virtual void discontinuityAtaddTypeTo(double t, std::shared_ptr<std::vector<DiscontinuityType>> disconTypes);
        virtual void fillpqsumu(FColDsptr col);
        virtual void setpqsumu(FColDsptr col);
        virtual void fillpqsumudot(FColDsptr col);
        virtual void setpqsumudot(FColDsptr col);
        virtual void setpqsumuddot(FColDsptr col);

        virtual void preStatic();
        virtual void fillStaticError(FColDsptr col);
        virtual void fillStaticJacob(SpMatDsptr mat);
        virtual void postStaticIteration();
        virtual void postStatic();

        virtual void preCollision();
        virtual void preCollisionDerivativeIC();
        virtual void fillCollisionDerivativeICError(FColDsptr col);
        virtual void fillCollisionDerivativeICJacob(SpMatDsptr mat);
        virtual void postCollisionDerivativeIC();
        virtual void preCollisionCorrector();
        virtual void preCollisionCorrectorIteration();
        virtual void preCollisionPredictor();
        virtual void preCollisionStep();
        virtual void fillCollisionError(FColDsptr col);
        virtual void fillCollisionpFpy(SpMatDsptr mat);
        virtual void fillCollisionpFpydot(SpMatDsptr mat);
        virtual void postCollisionCorrector();
        virtual void postCollisionCorrectorIteration();
        virtual void postCollisionPredictor();
        virtual void postCollisionStep();
        virtual void storeCollisionState();
        virtual void checkForCollisionDiscontinuityBetweenand(double impulsePrevious, double impulse);
        virtual double suggestSmallerOrAcceptCollisionFirstStepSize(double hnew);
        virtual double suggestSmallerOrAcceptCollisionStepSize(double hnew);
        virtual void normalImpulse(double imp);
        virtual void fillqsudotPlam(FColDsptr col);
        virtual void fillqsudotPlamDeriv(FColDsptr col);
        virtual void setqsudotPlam(FColDsptr col);
        virtual void setqsudotPlamDeriv(FColDsptr col);

        virtual System* root();
        virtual void registerName();
        virtual std::string classname();
        virtual EndFrmsptr geteFrmI() { return nullptr; }
        virtual EndFrmsptr geteFrmJ() { return nullptr; }
        virtual EndFrmsptr geteFrmK() { return nullptr; }
        virtual void getString(const std::string& str);
        virtual bool isJointForce();
        virtual bool isJointTorque();
        virtual bool isKinedotIJ();
        virtual bool isKineIJ();
        virtual std::shared_ptr<StateData> stateData();
        virtual double value();
        virtual void logString(const std::string& str);
        virtual void logStringwithArgument(const std::string& str, const std::string& str1);
        virtual void logStringwithArguments(const std::string& str, std::shared_ptr<std::vector<std::string&>> arrayOfChars);
        virtual std::ostream& printOn(std::ostream& s) const;
        friend std::ostream& operator<<(std::ostream& s, const Item& item);

        std::string name;
        Item* owner = nullptr;    //Use raw pointer when pointing backwards.
    };
}

