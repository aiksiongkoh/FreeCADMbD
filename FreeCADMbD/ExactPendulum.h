/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/jacobi_elliptic.hpp>

namespace MbD {
    class ExactPendulum
    {
        //\ddot{\theta}+\omega_n^2\sin\theta=0  LaTex
        //ddot theta + omega_n^2 sin theta = 0  OpenOffice Math
    public:
        enum class Mode {
            Oscillation,
            Separatrix,
            Rotation
        };

        struct Result {
            double time;
            double theta0;
            double omega0;
            double omega_n;
            double theta;
            double omega;
            double alpha;
            Mode mode;
        };

        ExactPendulum(double theta0, double omega0, double omega_n)
            : theta0_(theta0),
              omega0_(omega0),
              omega_n_(omega_n)
        {
            if (omega_n_ <= 0.0) {
                throw std::invalid_argument("omega_n must be positive.");
            }

            h_ = energyParameter();
        }

        Result theta(double t) const
        {
            if (h_ <= eps_) {
                return makeResult(t, theta0_, omega0_, Mode::Oscillation);
            }

            if (h_ < 1.0 - eps_) {
                return thetaOmegaOscillation(t);
            }

            if (std::abs(h_ - 1.0) <= eps_) {
                return thetaOmegaSeparatrix(t);
            }

            return thetaOmegaRotation(t);
        }

        double energy() const
        {
            return h_;
        }

    private:
        double theta0_;
        double omega0_;
        double omega_n_;
        double h_;

        static constexpr double eps_ = 1e-12;

        static double signNonzero(double x)
        {
            return x >= 0.0 ? 1.0 : -1.0;
        }

        double energyParameter() const
        {
            return std::pow(std::sin(theta0_ / 2.0), 2)
                 + std::pow(omega0_ / (2.0 * omega_n_), 2);
        }

        Result makeResult(double t, double theta, double omega, Mode mode) const
        {
            return { t, theta0_, omega0_, omega_n_, theta, omega, -omega_n_ * omega_n_ * std::sin(theta), mode };
        }

        Result thetaOmegaOscillation(double t) const
        {
            using boost::math::ellint_1;
            using boost::math::jacobi_cn;
            using boost::math::jacobi_sn;

            const double k = std::sqrt(h_);

            double s = std::sin(theta0_ / 2.0) / k;
            s = std::clamp(s, -1.0, 1.0);

            double phi = std::asin(s);
            double u0 = ellint_1(k, phi);

            const double sigma = signNonzero(omega0_);
            double u = sigma * omega_n_ * t + u0;
            double sn = jacobi_sn(k, u);
            double cn = jacobi_cn(k, u);

            return makeResult(t, 2.0 * std::asin(k * sn), 2.0 * sigma * k * omega_n_ * cn, Mode::Oscillation);
        }

        Result thetaOmegaSeparatrix(double t) const
        {
            const double sigma = signNonzero(omega0_);

            double a = std::sin(theta0_ / 2.0);
            a = std::clamp(a, -1.0 + eps_, 1.0 - eps_);

            double q = sigma * omega_n_ * t + std::atanh(a);

            return makeResult(t, 2.0 * std::asin(std::tanh(q)), 2.0 * sigma * omega_n_ / std::cosh(q), Mode::Separatrix);
        }

        Result thetaOmegaRotation(double t) const
        {
            using boost::math::ellint_1;
            using boost::math::jacobi_cn;
            using boost::math::jacobi_dn;
            using boost::math::jacobi_sn;

            const double k = 1.0 / std::sqrt(h_);
            const double sigma = signNonzero(omega0_);

            double phi0 = theta0_ / 2.0;
            double u0 = ellint_1(k, phi0);

            double u = sigma * omega_n_ * t / k + u0;

            double sn = jacobi_sn(k, u);
            double cn = jacobi_cn(k, u);
            double dn = jacobi_dn(k, u);

            double am = std::atan2(sn, cn);

            return makeResult(t, 2.0 * am, 2.0 * sigma * omega_n_ * dn / k, Mode::Rotation);
        }
    };
}
