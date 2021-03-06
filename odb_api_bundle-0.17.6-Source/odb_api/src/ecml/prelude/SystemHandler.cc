/*
 * (C) Copyright 1996-2016 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "SystemHandler.h"

#include "ecml/parser/Request.h"
#include "ecml/core/ExecutionContext.h"
#include "ecml/core/Environment.h"
#include "ecml/prelude/PrintHandler.h"

using namespace std;
using namespace ecml;

namespace ecml {

SystemHandler::SystemHandler(const std::string& name) : RequestHandler(name) {}

Values SystemHandler::handle(ExecutionContext& context)
{
    List r;

    Values vs (context.environment().lookup("values"));
    stringstream ss;
    PrintHandler::printList(ss, vs, " ", "");

    eckit::Log::debug() << "Executing system(\"" << ss.str() << ")\"" << endl;

    int rc (system (ss.str().c_str()));
    stringstream rs;
    rs << rc;
    r.append(rs.str());

    return r;
}

} // namespace ecml
