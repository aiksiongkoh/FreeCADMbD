/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>    
#include <string>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <iomanip>
#include <functional>
#include <vector>
#include <set>
#include <map>


namespace MbD {
    class MbDMath : public std::enable_shared_from_this<MbDMath>
    {
    public:
        static std::shared_ptr<MbDMath> With();

        void noop();
        static std::string xyzFromInt(int i);
        static std::string XYZFromInt(int i);
    };
}

