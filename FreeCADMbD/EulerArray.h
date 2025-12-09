/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "FullColumn.h"

namespace MbD {

    template<typename T>
    class EulerArray : public FullColumn<T>
    {
        //
    public:
        EulerArray(size_t count) : FullColumn<T>(count) {}
        EulerArray(size_t count, const T& value) : FullColumn<T>(count, value) {}
        EulerArray(std::initializer_list<T> list) : FullColumn<T>{ list } {}
        static std::shared_ptr<EulerArray<T>> With();

        void equalFullColumn(FColsptr<T> fullCol);
        void equalFullColumnAt(FColsptr<T> fullCol, size_t i);
        virtual void calc();

    };

    template<typename T>
    inline std::shared_ptr<EulerArray<T>> EulerArray<T>::With()
    {
        throw SimulationStoppingError("To be implemented.");
        auto inst = std::make_shared<EulerArray<T>>();
        inst->initialize();
        return inst;
    }

    template<typename T>
    inline void EulerArray<T>::equalFullColumn(FColsptr<T> fullCol)
    {
        this->equalArrayAt(fullCol, 0);
    }

    template<typename T>
    inline void EulerArray<T>::equalFullColumnAt(FColsptr<T> fullCol, size_t i)
    {
        this->equalArrayAt(fullCol, i);
    }

    template<typename T>
    inline void EulerArray<T>::calc()
    {
        throw SimulationStoppingError("To be implemented.");
    }
}

