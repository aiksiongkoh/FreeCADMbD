/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

 //#include <memory>
 //#include <iostream>
 //#include <vector>
 //#include <string>
 //#include <memory>
 //#include <cassert>
 //#include <algorithm>
 //#include <iterator>
 //#include <map>

#include "Symbolic.h"
#include "FullColumn.h"
#include "FullRow.h"
#include "FullMatrix.h"

namespace MbD {
	class MBDynSystem;
	class MBDynReference;
	class MBDynNode;
	class ASMTItem;
	class MBDynBody;
	class MBDynJoint;
	class MBDynDrive;
	class ASMTAssembly;

	class MBDynItem : public std::enable_shared_from_this<MBDynItem>
	{
		//
	public:
		static std::shared_ptr<MBDynItem> With();
		virtual void initialize();

		virtual MBDynSystem* root();

		void noop();
		virtual void parseMBDyn(std::vector<std::string>& lines);
		virtual void parseMBDyn(std::string line);
		virtual void readFunction(std::vector<std::string>& args);
		static std::vector<std::string> collectArgumentsFor(std::string title, std::string& statement);
		static std::vector<std::string>::iterator findLineWith(std::vector<std::string>& lines, std::vector<std::string>& tokens);
		static bool lineHasToken(const std::string& line, const std::string& token);
		static bool lineHasTokens(const std::string& line, std::vector<std::string>& tokens);
		//static bool lineHasTokens(int n, ...);
		template <typename... Tokens>
		static bool lineHasTokens(std::string_view line, Tokens&&... tokens);

		virtual std::shared_ptr<std::vector<std::shared_ptr<MBDynNode>>> mbdynNodes();
		virtual std::shared_ptr<std::vector<std::shared_ptr<MBDynBody>>> mbdynBodies();
		virtual std::shared_ptr<std::vector<std::shared_ptr<MBDynJoint>>> mbdynJoints();
		virtual std::shared_ptr<std::vector<std::shared_ptr<MBDynDrive>>> mbdynDrives();
		virtual std::vector<std::string> nodeNames();
		virtual std::shared_ptr<std::map<std::string, Symsptr>> mbdynVariables();
		virtual std::shared_ptr<std::map<std::string, std::shared_ptr<MBDynReference>>> mbdynReferences();
		virtual void createASMT();
		virtual std::shared_ptr<MBDynNode> nodeAt(std::string nodeName);
		virtual int labelIDat(std::string nodeName);
		virtual std::shared_ptr<MBDynBody> bodyWithNode(std::string nodeName);
		virtual std::shared_ptr<ASMTAssembly> asmtAssembly();
		virtual std::string formulaFromDrive(std::string driveName, std::string varName);
		void logString(const std::string& str);
		FRowDsptr readRowOfDoubles(const std::string& line);
		FColDsptr readColumnOfDoubles(const std::string& line);
		int readIntOffTop(std::vector<std::string>& args);
		double readDoubleOffTop(std::vector<std::string>& args);
		double readDouble(const std::string& line);
		size_t readInt(const std::string& line);
		bool readBool(const std::string& line);
		std::string asmtFormula(std::string mbdynFormula);
		std::string asmtFormulaIntegral(std::string mbdynFormula);

		FColDsptr readVector3(std::vector<std::string>& args);
		FColDsptr readPosition(std::vector<std::string>& args);
		FColDsptr readBasicPosition(std::vector<std::string>& args);
		FMatDsptr readOrientation(std::vector<std::string>& args);
		FMatDsptr readBasicOrientation(std::vector<std::string>& args);
		std::string popOffTop(std::vector<std::string>& args);
		std::string readStringNoSpacesOffTop(std::vector<std::string>& args);
		std::string stringOffTopHas(std::vector<std::string>& args, std::string token);
		void readLabel(std::vector<std::string>& args);
		std::string readJointTypeOffTop(std::vector<std::string>& args);
		std::string readToken(const std::string& line);

		std::string label;
		MBDynItem* owner = nullptr;
		std::shared_ptr<ASMTItem> asmtItem;
		std::vector<std::string> arguments;


	};

	template<typename ...Tokens>
	inline bool MBDynItem::lineHasTokens(std::string_view line, Tokens && ...tokens)
	{
		size_t index = 0;
		// fold-expression over parameter pack
		return (((index = line.find(tokens, index)) != std::string::npos
			&& (++index, true)) && ...);
	}
}
