/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <stdexcept>

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

        Result result(double t) const
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

        struct JacobiValues {
            double sn;
            double cn;
            double dn;
        };

        // C++20 supplies elliptic integrals, but not Jacobi elliptic functions.
        // Arithmetic-geometric mean and backward amplitude recurrence:
        // https://dlmf.nist.gov/22.20#ii (22.20.1, 22.20.3-5).
        // Called only with 0 <= k < 1; the separatrix is handled separately.
        static JacobiValues jacobi(double k, double u)
        {
            std::array<double, 32> a{}, c{};
            a[0] = 1.0;
            const double complementarySquared = (1.0 - k) * (1.0 + k);
            double b = std::sqrt(complementarySquared);
            size_t n = 0;
            while (std::abs(a[n] - b) > std::numeric_limits<double>::epsilon() * a[n]) {
                if (n + 1 == a.size()) {
                    throw std::runtime_error("Jacobi AGM did not converge.");
                }
                const double previousA = a[n];
                ++n;
                a[n] = (previousA + b) / 2.0;
                c[n] = (previousA - b) / 2.0;
                b = std::sqrt(previousA * b);
            }

            // Reduce the argument before the backward recurrence to retain
            // accuracy over multiple periods, including negative times.
            u = std::remainder(u, 4.0 * std::comp_ellint_1(k));
            double phi = std::ldexp(a[n] * u, static_cast<int>(n));
            while (n > 0) {
                const double correction = std::clamp(c[n] * std::sin(phi) / a[n], -1.0, 1.0);
                phi = (phi + std::asin(correction)) / 2.0;
                --n;
            }
            const double sn = std::sin(phi);
            const double cn = std::cos(phi);
            // Equivalent to sqrt(1-k*k*sn*sn), without cancellation near k=1.
            const double dn = std::sqrt(complementarySquared + k * k * cn * cn);
            return {sn, cn, dn};
        }

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
            const double k = std::sqrt(h_);

            double s = std::sin(theta0_ / 2.0) / k;
            s = std::clamp(s, -1.0, 1.0);

            double phi = std::asin(s);
            double u0 = std::ellint_1(k, phi);

            const double sigma = signNonzero(omega0_);
            double u = sigma * omega_n_ * t + u0;
            const auto [sn, cn, dn] = jacobi(k, u);

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
            const double k = 1.0 / std::sqrt(h_);
            const double sigma = signNonzero(omega0_);

            double phi0 = theta0_ / 2.0;
            double u0 = std::ellint_1(k, phi0);

            double u = sigma * omega_n_ * t / k + u0;

            const auto [sn, cn, dn] = jacobi(k, u);

            double am = std::atan2(sn, cn);

            return makeResult(t, 2.0 * am, 2.0 * sigma * omega_n_ * dn / k, Mode::Rotation);
        }
    };
}
