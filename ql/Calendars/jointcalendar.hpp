
/*
 Copyright (C) 2003 RiskMap srl

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

/*! \file jointcalendar.hpp
    \brief Joint calendar
*/

#ifndef quantlib_joint_calendar_h
#define quantlib_joint_calendar_h

#include <ql/calendar.hpp>
#include <vector>

namespace QuantLib {

    namespace Calendars {

        //! rules for joining calendars
        enum JointCalendarRule { JoinHolidays,    /*!< A date is a holiday
                                                       for the joint calendar
                                                       if it is a holiday
                                                       for any of the given
                                                       calendars */
                                 JoinBusinessDays /*!< A date is a business day
                                                       for the joint calendar
                                                       if it is a business day
                                                       for any of the given
                                                       calendars */
        };

        //! Joint calendar
        /*! Depending on the chosen rule, this calendar has a set of
            business days given by either the union or the intersection
            of the sets of business days of the given calendars.
        */
        class JointCalendar : public Calendar {
          private:
            class Impl : public Calendar::Impl {
              public:
                Impl(const Calendar&, const Calendar&,
                     JointCalendarRule);
                Impl(const Calendar&, const Calendar&,
                     const Calendar&, JointCalendarRule);
                Impl(const Calendar&, const Calendar&,
                     const Calendar&, const Calendar&,
                     JointCalendarRule);
                std::string name() const;
                bool isBusinessDay(const Date&) const;
              private:
                JointCalendarRule rule_;
                std::vector<Calendar> calendars_;
            };
          public:
            JointCalendar(const Calendar&, const Calendar&,
                          JointCalendarRule = JoinHolidays);
            JointCalendar(const Calendar&, const Calendar&,
                          const Calendar&, 
                          JointCalendarRule = JoinHolidays);
            JointCalendar(const Calendar&, const Calendar&,
                          const Calendar&, const Calendar&,
                          JointCalendarRule = JoinHolidays);
        };

    }

}


#endif
