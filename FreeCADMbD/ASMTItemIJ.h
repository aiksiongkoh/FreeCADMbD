/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTItem.h"
#include "ASMTMarker.h"
#include "EndFrameq.h"

namespace MbD {
    template<typename T>
    class FullColumn;
    using FColDsptr = std::shared_ptr<FullColumn<double>>;
    
    class ASMTItemIJ : public ASMTItem
    {
        //
    public:
        ASMTItemIJ() {}
        static std::shared_ptr<ASMTItemIJ> With();
        void initialize() override;

        void parseASMT(std::vector<std::string>& lines) override;
        void setMarkerI(std::shared_ptr<ASMTMarker> mkrI);
        void setMarkerJ(std::shared_ptr<ASMTMarker> mkrJ);
        void readMarkerI(std::vector<std::string>& lines);
        void readMarkerJ(std::vector<std::string>& lines);
        void readFXonIs(std::vector<std::string>& lines);
        void readFYonIs(std::vector<std::string>& lines);
        void readFZonIs(std::vector<std::string>& lines);
        void readTXonIs(std::vector<std::string>& lines);
        void readTYonIs(std::vector<std::string>& lines);
        void readTZonIs(std::vector<std::string>& lines);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
        FMatDsptr aAOI(size_t i) const;
        FColDsptr aFII(size_t i);
        FColDsptr aFIO(size_t i);
        FColDsptr aTII(size_t i);
        FColDsptr aTIO(size_t i);
        virtual bool isJoint();
        virtual bool isMotion();
        virtual bool isForceTorque();

        std::shared_ptr<ASMTMarker> markerI, markerJ;
        std::shared_ptr<std::vector<FColDsptr>> cFIO;
        std::shared_ptr<std::vector<FColDsptr>> cTIO;
        std::shared_ptr<std::vector<FColDsptr>> in_cFIO;
        std::shared_ptr<std::vector<FColDsptr>> in_cTIO;
        FRowDsptr infxs, infys, infzs, intxs, intys, intzs;

    };
}

