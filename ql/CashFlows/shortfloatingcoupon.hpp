
/*
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file shortfloatingcoupon.hpp
    \brief Short (or long) coupon at par on a term structure
*/

#ifndef quantlib_short_floating_rate_coupon_hpp
#define quantlib_short_floating_rate_coupon_hpp

#include <ql/CashFlows/parcoupon.hpp>

namespace QuantLib {

    namespace CashFlows {

        //! short coupon at par on a term structure
        /*! \warning This class does not perform any date adjustment,
            i.e., the start and end date passed upon construction
            should be already rolled to a business day.
        */
        class ShortFloatingRateCoupon : public ParCoupon {
          public:
            ShortFloatingRateCoupon(double nominal,
                const Date& paymentDate,
                const Handle<Indexes::Xibor>& index,
                const Date& startDate, const Date& endDate,
                int fixingDays,
                Spread spread = 0.0,
                const Date& refPeriodStart = Date(),
                const Date& refPeriodEnd = Date());
            //! throws when an interpolated fixing is needed
            double amount() const;
            //! \name Visitability
            //@{
            virtual void accept(Patterns::AcyclicVisitor&);
            //@}
        };


        // inline definitions

        inline 
        void ShortFloatingRateCoupon::accept(Patterns::AcyclicVisitor& v) {
            using namespace Patterns;
            Visitor<ShortFloatingRateCoupon>* v1 = 
                dynamic_cast<Visitor<ShortFloatingRateCoupon>*>(&v);
            if (v1 != 0)
                v1->visit(*this);
            else
                ParCoupon::accept(v);
        }

    }

}


#endif
