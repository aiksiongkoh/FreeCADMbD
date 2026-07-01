/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include <cstddef>
#include <fstream>    

#include "ASMTSpatialContainer.h"
//Required for initialization
#include "ASMTConstantGravity.h"
#include "ASMTSimulationParameters.h"
#include "ASMTAnimationParameters.h"
#include "Units.h"
#include "System.h"

namespace MbD {
    class ASMTPart;
    class ASMTKinematicIJ;
    class ASMTConstraintSet;
    class ASMTForceTorque;
    class ASMTJoint;
    class ASMTMotion;
    class ASMTLimit;
    class SystemSolver;
    class ASMTItemIJ;
    class MBDynSystem;
    class ASMTTime;

    class ASMTAssembly : public ASMTSpatialContainer
    {
        //
    public:
        struct SimplePendulumMotion
        {
            // theta is measured from the downward vertical in the x-y plane.
            double theta = 0.0;
            // omega is d(theta)/dt about the +z axis.
            double omega = 0.0;
            // Bob position relative to the pivot: x right, y up.
            double x = 0.0;
            double y = 0.0;
            // Bob velocity components in the same x-y frame.
            double vx = 0.0;
            double vy = 0.0;
        };

        ASMTAssembly() {}
        static constexpr size_t resultComparisonDigits = 3;
        static std::shared_ptr<ASMTAssembly> With();
        void initialize() override;
        static void runSinglePendulumSuperSimplified();
        static void runSinglePendulumSuperSimplified2();
        static void runSinglePendulumSimplified();
        static void runSinglePendulum();
        static SimplePendulumMotion exactSimplePendulumMotion(double time, double length, double gravity, double initialTheta, double initialOmega = 0.0);
        static std::shared_ptr<ASMTAssembly> assemblyFromFile(const std::string& str);
        static std::shared_ptr<ASMTAssembly> runDynFile(const std::string& fileName);
        static std::shared_ptr<ASMTAssembly> runKineFile(const std::string& fileName);
        static std::shared_ptr<ASMTAssembly> runQuasiStaticFile(const std::string& fileName);
        static std::shared_ptr<ASMTAssembly> runDraggingTest();
        static std::vector<std::string> linesFromFile(const std::string& fileName);
        static std::shared_ptr<ASMTAssembly> readWriteKineFile(const std::string& fileName);
        static std::shared_ptr<ASMTAssembly> readWriteDynFile(const std::string& fileName);
        static std::shared_ptr<ASMTAssembly> readWriteDynFile2(const std::string& infilename, const std::string& outfilename);
        static std::shared_ptr<ASMTAssembly> readWriteReadDynFile(const std::string& fileName);

        ASMTAssembly* root() override;
        void setNotes(const std::string& str);
        void parseASMT(std::vector<std::string>& lines) override;
        void readNotes(std::vector<std::string>& lines);
        void readParts(std::vector<std::string>& lines);
        void readPart(std::vector<std::string>& lines);
        void readKinematicIJs(std::vector<std::string>& lines);
        void readKinematicIJ(std::vector<std::string>& lines);
        void readConstraintSets(std::vector<std::string>& lines);
        void readJoints(std::vector<std::string>& lines);
        void readMotions(std::vector<std::string>& lines);
        void readLimits(std::vector<std::string>& lines);
        void readGeneralConstraintSets(std::vector<std::string>& lines) const;
        void readForcesTorques(std::vector<std::string>& lines);
        void readConstantGravity(std::vector<std::string>& lines);
        void readSimulationParameters(std::vector<std::string>& lines);
        void readAnimationParameters(std::vector<std::string>& lines);
        void readSeries(std::vector<std::string>& lines);
        void readTimeSeries(std::vector<std::string>& lines);
        void readTimes(std::vector<std::string>& lines);
        void readAssemblySeries(std::vector<std::string>& lines);
        void readPartSeriesMany(std::vector<std::string>& lines);
        void readPartSeries(std::vector<std::string>& lines);
        void readJointSeriesMany(std::vector<std::string>& lines);
        void readJointSeries(std::vector<std::string>& lines);
        void readMotionSeriesMany(std::vector<std::string>& lines);
        void readMotionSeries(std::vector<std::string>& lines);
        void readForceTorqueSeries(std::vector<std::string>& lines);
        void readAllowRotationSeries(std::vector<std::string>& lines);
        void runDraggingLog(const std::string& chars);
        FColDsptr rOcmO() override;
        FColDsptr vOcmO() override;
        FColDsptr omeOpO() override;

        void outputFor(AnalysisType type);
        void preMbDrun(std::shared_ptr<System> mbdSys);
        void postMbDrun();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTItemIJ>>> connectorList() const;
        void deleteMbD() override;
        void createMbD() override;
        void outputFile(std::string filename);
        void storeOnLevel(std::ofstream& os, size_t level) override;

        /* This function performs a one shot solve of the assembly.*/
        void solve();

        void runPreDrag();
        void runDragStep(std::shared_ptr<std::vector<std::shared_ptr<ASMTPart>>> dragParts) const;
        void runPostDrag();
        void runKINEMATIC();
        void runDYNAMIC();
        void runQUASISTATIC();
        std::shared_ptr<ASMTSpatialContainer> spatialContainerAt(std::shared_ptr<ASMTAssembly> self, std::string& longname) const;
        std::shared_ptr<ASMTPart> partAt(const std::string& longname) const;
        std::shared_ptr<ASMTMarker> markerAt(std::string& longname) const;
        std::shared_ptr<ASMTJoint> jointAt(std::string& longname) const;
        std::shared_ptr<ASMTMotion> motionAt(std::string& longname) const;
        std::shared_ptr<ASMTForceTorque> forceTorqueAt(std::string& longname) const;
        std::shared_ptr<ASMTTime> geoTime() const;
        void updateFromMbD() override;
        std::shared_ptr<StateData> dataFromMbD() override;
        void compareResults2(AnalysisType type) override;
        void outputResults(AnalysisType type) override;
        void addTime(std::shared_ptr<ASMTTime> time);
        void addPart(std::shared_ptr<ASMTPart> part);
        void addJoint(std::shared_ptr<ASMTJoint> joint);
        void addMotion(std::shared_ptr<ASMTMotion> motion);
        void addForceTorque(std::shared_ptr<ASMTForceTorque> motion);
        void setConstantGravity(std::shared_ptr<ASMTConstantGravity> constantGravity);
        void setSimulationParameters(std::shared_ptr<ASMTSimulationParameters> simulationParameters);
        void setAnimationParameters(std::shared_ptr<ASMTAnimationParameters> animationParameters);
        std::shared_ptr<ASMTPart> partNamed(std::string partName) const;
        std::shared_ptr<ASMTPart> partPartialNamed(std::string partialName) const;
        void storeOnLevelNotes(std::ofstream& os, size_t level);
        void storeOnLevelParts(std::ofstream& os, size_t level);
        void storeOnLevelKinematicIJs(std::ofstream& os, size_t level);
        void storeOnLevelConstraintSets(std::ofstream& os, size_t level);
        void storeOnLevelForceTorques(std::ofstream& os, size_t level);
        void storeOnLevelJoints(std::ofstream& os, size_t level);
        void storeOnLevelMotions(std::ofstream& os, size_t level);
        void storeOnLevelGeneralConstraintSets(std::ofstream& os, size_t level);
        void storeOnTimeSeries(std::ofstream& os) override;
        void setinFileName(const std::string& str);
        void setoutFileName(const std::string& str);
        void updateFromInputState() override;
        void combineInputInitialConditionsWithCalculationResults();

        std::string inFileName = "";
        std::string outFileName = "";
        std::string notes = "(Text string: '' runs: (Core.RunArray runs: #() values: #()))";
        std::shared_ptr<std::vector<std::shared_ptr<ASMTPart>>> parts = std::make_shared<std::vector<std::shared_ptr<ASMTPart>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTKinematicIJ>>> kinematicIJs = std::make_shared<std::vector<std::shared_ptr<ASMTKinematicIJ>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTConstraintSet>>> constraintSets = std::make_shared<std::vector<std::shared_ptr<ASMTConstraintSet>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTJoint>>> joints = std::make_shared<std::vector<std::shared_ptr<ASMTJoint>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTMotion>>> motions = std::make_shared<std::vector<std::shared_ptr<ASMTMotion>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTLimit>>> limits = std::make_shared<std::vector<std::shared_ptr<ASMTLimit>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTForceTorque>>> forcesTorques = std::make_shared<std::vector<std::shared_ptr<ASMTForceTorque>>>();
        std::shared_ptr<ASMTConstantGravity> constantGravity = nullptr;
        std::shared_ptr<ASMTSimulationParameters> simulationParameters = nullptr;
        std::shared_ptr<ASMTAnimationParameters> animationParameters = nullptr;
        std::shared_ptr<std::vector<double>> itimes = std::make_shared<std::vector<double>>();
        std::shared_ptr<std::vector<double>> times = std::make_shared<std::vector<double>>();
        std::shared_ptr<ASMTTime> asmtTime;
        std::shared_ptr<Units> asmtUnits = nullptr;
        std::shared_ptr<System> mbdSystem = nullptr;
        MBDynSystem* mbdynItem = nullptr;
    };
}

