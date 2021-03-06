/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */
/// @author Piotr Kuchta, May 2015

#ifndef eckit_ecml_VariableLookupHandler_H
#define eckit_ecml_VariableLookupHandler_H

#include <sstream>

#include "ecml/parser/Request.h"
#include "ecml/core/RequestHandler.h"

namespace ecml {

class VariableLookupHandler : public ecml::RequestHandler {
public:
    VariableLookupHandler(const std::string&, const std::string&);
    virtual Values handle(ExecutionContext&);
private:
    const std::string of_;
};

} // namespace ecml

#endif
