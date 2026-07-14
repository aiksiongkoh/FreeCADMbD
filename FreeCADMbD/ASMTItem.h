/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "FullColumn.h"
#include "FullRow.h"
#include "FullMatrix.h"
#include "DiagonalMatrix.h"
#include "SparseMatrix.h"
#include "enum.h"

#include <algorithm>

namespace MbD
{
    class ASMTAssembly;
    class Units;
    class ASMTSpatialContainer;
    class ASMTPart;
    class System;
    class Constant;
    class Item;
    class Part;
    class StateData;

    class ASMTItem : public std::enable_shared_from_this<ASMTItem>
    {
        //
    public:
        ASMTItem() {}
        // virtual ~ASMTItem() {}
        static std::shared_ptr<ASMTItem> With();
        static void noop();
        virtual void initialize();
        virtual void initializeGlobally();
        virtual void initializeLocally();

        virtual ASMTAssembly *root();
        virtual ASMTSpatialContainer *partOrAssembly();
        virtual ASMTPart *part();

        virtual std::string classname();
        void setName(const std::string &str);
        virtual void parseASMT(std::vector<std::string> &lines);
        std::string popOffTop(std::vector<std::string> &lines);
        std::string readStringTrimmedOffTop(std::vector<std::string> &lines);
        std::string readStringNoSpacesOffTop(std::vector<std::string> &lines);
        void readStringNoSpacesOffTopEqualOrThrow(std::vector<std::string> &lines, std::string str);
        FRowDsptr readRowOfDoubles(const std::string &line);
        FRowDsptr readRowOfDoublesOffTop(std::vector<std::string> &lines);
        FRowDsptr readSeriesOf(std::vector<std::string> &lines, std::string str);
        FColDsptr readColumnOfDoubles(const std::string &line);
        FColDsptr readColumnOfDoublesOffTop(std::vector<std::string> &lines);
        double readDouble(const std::string &line);
        int readInt(const std::string &line);
        size_t readSize_t(const std::string &line);
        bool readBool(const std::string &line);
        std::string readString(const std::string &line);
        void readName(std::vector<std::string> &lines);
        virtual std::string fullName(const std::string &partialName);
        void readDoublesInto(std::string &str, std::string label, FRowDsptr &row);
        virtual void deleteMbD();
        virtual void createMbD();
        virtual void updateFromMbD();
        virtual std::shared_ptr<StateData> dataFromMbD();
        virtual void compareResults2(AnalysisType type);
        virtual void outputResults(AnalysisType type);
        virtual std::string reportComparisonWith(std::shared_ptr<ASMTItem> other);
        template <typename T>
        static std::string itemCollectionComparisonWith(
            const std::string& label,
            const std::shared_ptr<std::vector<std::shared_ptr<T>>>& items,
            const std::shared_ptr<std::vector<std::shared_ptr<T>>>& otherItems);
        std::shared_ptr<Units> asmtUnits();
        std::shared_ptr<Units> mbdUnits();
        std::shared_ptr<System> mbdSys();
        std::shared_ptr<Constant> sptrConstant(double value);
        virtual void storeOnLevel(std::ofstream &os, size_t level);
        virtual void storeOnLevelTabs(std::ofstream &os, size_t level);
        virtual void storeOnLevelString(std::ofstream &os, size_t level, const std::string &str);
        virtual void storeOnLevelDouble(std::ofstream &os, size_t level, double value);
        virtual void storeOnLevelInt(std::ofstream &os, size_t level, int i);
        virtual void storeOnLevelSize_t(std::ofstream &os, size_t level, size_t i);
        virtual void storeOnLevelBool(std::ofstream &os, size_t level, bool value);
        template <typename T>
        void storeOnLevelArray(std::ofstream &os, size_t level, std::vector<T> array);
        virtual void storeOnLevelName(std::ofstream &os, size_t level);
        virtual void storeOnTimeSeries(std::ofstream &os);
        void storeOnArray(std::ofstream &os, const std::string &str, std::shared_ptr<std::vector<double>> arr);
        void storeOnArrayArray(std::ofstream &os, const std::string &str, std::shared_ptr<std::vector<FColDsptr>> arrarr, size_t i);
        void logString(const std::string &str);
        bool hasOutputEqualTol(std::string name, double val, double inval, size_t nSig, double tol);

        std::string name;
        ASMTItem *owner = nullptr;
        std::shared_ptr<Item> mbdObject;
        std::shared_ptr<std::vector<std::shared_ptr<StateData>>> dataSeries = std::make_shared<std::vector<std::shared_ptr<StateData>>>();
        std::shared_ptr<std::vector<std::shared_ptr<StateData>>> dataSeriesIn = std::make_shared<std::vector<std::shared_ptr<StateData>>>();
    };

    template <typename T>
    inline std::string ASMTItem::itemCollectionComparisonWith(
        const std::string& label,
        const std::shared_ptr<std::vector<std::shared_ptr<T>>>& items,
        const std::shared_ptr<std::vector<std::shared_ptr<T>>>& otherItems)
    {
        if (!items && !otherItems) {
            return std::string{};
        }
        if (!items) {
            return "Missing " + label + ".\n";
        }
        if (!otherItems) {
            return "Missing comparison " + label + ".\n";
        }
        for (const auto& item : *items) {
            auto itemName = item->fullName("");
            auto found = std::find_if(
                otherItems->begin(),
                otherItems->end(),
                [&itemName](const auto& otherItem) {
                    return otherItem->fullName("") == itemName;
                });
            if (found == otherItems->end()) {
                return "Missing " + label + ": " + itemName + "\n";
            }
            auto report = item->reportComparisonWith(*found);
            if (!report.empty()) {
                return report;
            }
        }
        for (const auto& otherItem : *otherItems) {
            auto otherItemName = otherItem->fullName("");
            auto found = std::find_if(
                items->begin(),
                items->end(),
                [&otherItemName](const auto& item) {
                    return item->fullName("") == otherItemName;
                });
            if (found == items->end()) {
                return "Extra " + label + ": " + otherItemName + "\n";
            }
        }
        return std::string{};
    }

    template <typename T>
    inline void ASMTItem::storeOnLevelArray(std::ofstream &os, size_t level, std::vector<T> array)
    {
        storeOnLevelTabs(os, level);
        for (size_t i = 0; i < array.size() - 1; i++)
        {
            os << array[i] << '\t';
        }
        os << array.back();
        os << std::endl;
    }
}
