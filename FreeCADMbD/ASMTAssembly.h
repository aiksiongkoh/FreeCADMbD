/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
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
        ASMTAssembly() {}
        static std::shared_ptr<ASMTAssembly> With();
        void initialize() override;
        static void runSinglePendulumSuperSimplified();
        static void runSinglePendulumSuperSimplified2();
        static void runSinglePendulumSimplified();
        static void runSinglePendulum();
        static std::shared_ptr<ASMTAssembly> assemblyFromFile(const std::string& str);
        static void runDynFile(const std::string& str);
        static void runKineFile(const std::string& str);
        static void runDraggingTest();
        static std::vector<std::string> linesFromFile(const std::string& str);
        static void readWriteKineFile(const std::string& str);
        static void readWriteDynFile(const std::string& str);

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
        void runDraggingLog(const std::string& chars);

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
        void initprincipalMassMarker();
        std::shared_ptr<ASMTSpatialContainer> spatialContainerAt(std::shared_ptr<ASMTAssembly> self, std::string& longname) const;
        std::shared_ptr<ASMTPart> partAt(const std::string& longname) const;
        std::shared_ptr<ASMTMarker> markerAt(std::string& longname) const;
        std::shared_ptr<ASMTJoint> jointAt(std::string& longname) const;
        std::shared_ptr<ASMTMotion> motionAt(std::string& longname) const;
        std::shared_ptr<ASMTForceTorque> forceTorqueAt(std::string& longname) const;
        FColDsptr vOcmO() override;
        FColDsptr omeOpO() override;
        std::shared_ptr<ASMTTime> geoTime() const;
        void updateFromMbD() override;
        void compareResults(AnalysisType type) override;
        void outputResults(AnalysisType type) override;
        void addTime(std::shared_ptr<ASMTTime> time);
        void addPart(std::shared_ptr<ASMTPart> part);
        void addJoint(std::shared_ptr<ASMTJoint> joint);
        void addMotion(std::shared_ptr<ASMTMotion> motion);
        void addForceTorque(std::shared_ptr<ASMTForceTorque> motion);
        void setConstantGravity(std::shared_ptr<ASMTConstantGravity> constantGravity);
        void setSimulationParameters(std::shared_ptr<ASMTSimulationParameters> simulationParameters);
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
        void setFilename(const std::string& str);
        void updateFromInputState() override;

        std::string filename = "";
        std::string notes = "(Text string: '' runs: (Core.RunArray runs: #() values: #()))";
        std::shared_ptr<std::vector<std::shared_ptr<ASMTPart>>> parts = std::make_shared<std::vector<std::shared_ptr<ASMTPart>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTKinematicIJ>>> kinematicIJs = std::make_shared<std::vector<std::shared_ptr<ASMTKinematicIJ>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTConstraintSet>>> constraintSets = std::make_shared<std::vector<std::shared_ptr<ASMTConstraintSet>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTJoint>>> joints = std::make_shared<std::vector<std::shared_ptr<ASMTJoint>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTMotion>>> motions = std::make_shared<std::vector<std::shared_ptr<ASMTMotion>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTLimit>>> limits = std::make_shared<std::vector<std::shared_ptr<ASMTLimit>>>();
        std::shared_ptr<std::vector<std::shared_ptr<ASMTForceTorque>>> forcesTorques = std::make_shared<std::vector<std::shared_ptr<ASMTForceTorque>>>();
        std::shared_ptr<ASMTConstantGravity> constantGravity = nullptr;
        std::shared_ptr<ASMTSimulationParameters> simulationParameters = ASMTSimulationParameters::With();
        std::shared_ptr<ASMTAnimationParameters> animationParameters = ASMTAnimationParameters::With();
        std::shared_ptr<std::vector<double>> itimes = std::make_shared<std::vector<double>>();
        std::shared_ptr<std::vector<double>> times = std::make_shared<std::vector<double>>();
        std::shared_ptr<ASMTTime> asmtTime;
        std::shared_ptr<Units> asmtUnits = Units::With();
        std::shared_ptr<System> mbdSystem = System::With();
        MBDynSystem* mbdynItem = nullptr;
    };
}

