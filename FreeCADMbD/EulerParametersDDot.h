/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "EulerArray.h"
#include "FullColumn.h"
#include "FullMatrix.h"
#include "EulerParametersDot.h"

namespace MbD {

    template<typename T>
    class EulerParametersDDot : public EulerArray<T>
    {
        //qEdot aAddot aBddot aCddot 
    public:
        EulerParametersDDot() : EulerArray<T>(4) {}
        EulerParametersDDot(size_t count) : EulerArray<T>(count) {}
        EulerParametersDDot(size_t count, const T& value) : EulerArray<T>(count, value) {}
        EulerParametersDDot(std::initializer_list<T> list) : EulerArray<T>{ list } {}
        static std::shared_ptr<EulerParametersDDot<T>> With();
        static std::shared_ptr<EulerParametersDDot<T>> With(size_t count);
        void initialize() override;

        void calcAddotBddotCddot();
        void calc() override;
        FColDsptr alpOpO();

        std::shared_ptr<EulerParametersDot<T>> qEdot;
        FMatDsptr aAddot, aBddot, aCddot;
    };

    template <typename T>
    inline std::shared_ptr<EulerParametersDDot<T>> EulerParametersDDot<T>::With()
    {
        auto inst = std::make_shared<EulerParametersDDot<T>>();
        inst->initialize();
        return inst;
    }

    template <typename T>
    inline std::shared_ptr<EulerParametersDDot<T>> EulerParametersDDot<T>::With(size_t count)
    {
        auto inst = std::make_shared<EulerParametersDDot<T>>(count);
        inst->initialize();
        return inst;
    }

    template <typename T>
    inline void EulerParametersDDot<T>::initialize()
    {
        aAddot = FullMatrix<double>::With(3, 3);
        aBddot = FullMatrix<double>::With(3, 4);
        aCddot = FullMatrix<double>::With(3, 4);
    }

    template <typename T>
    inline void EulerParametersDDot<T>::calcAddotBddotCddot()
    {
        auto aE0ddot = this->at(0);
        auto aE1ddot = this->at(1);
        auto aE2ddot = this->at(2);
        auto aE3ddot = this->at(3);
        auto mE0ddot = -aE0ddot;
        auto mE1ddot = -aE1ddot;
        auto mE2ddot = -aE2ddot;
        aBddot->at(0)->at(0) = aE3ddot;
        aBddot->at(0)->at(1) = mE2ddot;
        aBddot->at(0)->at(2) = aE1ddot;
        aBddot->at(0)->at(3) = mE0ddot;
        aBddot->at(1)->at(0) = aE2ddot;
        aBddot->at(1)->at(1) = aE3ddot;
        aBddot->at(1)->at(2) = mE0ddot;
        aBddot->at(1)->at(3) = mE1ddot;
        aBddot->at(2)->at(0) = mE1ddot;
        aBddot->at(2)->at(1) = aE0ddot;
        aBddot->at(2)->at(2) = aE3ddot;
        aBddot->at(2)->at(3) = mE2ddot;
        aCddot->at(0)->at(0) = aE3ddot;
        aCddot->at(0)->at(1) = aE2ddot;
        aCddot->at(0)->at(2) = mE1ddot;
        aCddot->at(0)->at(3) = mE0ddot;
        aCddot->at(1)->at(0) = mE2ddot;
        aCddot->at(1)->at(1) = aE3ddot;
        aCddot->at(1)->at(2) = aE0ddot;
        aCddot->at(1)->at(3) = mE1ddot;
        aCddot->at(2)->at(0) = aE1ddot;
        aCddot->at(2)->at(1) = mE0ddot;
        aCddot->at(2)->at(2) = aE3ddot;
        aCddot->at(2)->at(3) = mE2ddot;
        aAddot = qEdot->aBdot
            ->timesTransposeFullMatrix(qEdot->aCdot)
            ->plusFullMatrix(qEdot->aB()->timesTransposeFullMatrix(aCddot))
            ->times(2.0);
    }

    template <typename T>
    inline void EulerParametersDDot<T>::calc()
    {
        calcAddotBddotCddot();
    }
    template <typename T>
    inline FColDsptr EulerParametersDDot<T>::alpOpO()
    {
        return FColDsptr();
    }
}
