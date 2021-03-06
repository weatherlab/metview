/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "odb_api/EqRegionCache.h"
#include "odb_api/FunctionEQ_BOXLON.h"

namespace odb {
namespace sql {
namespace expression {
namespace function {

const type::SQLType* FunctionEQ_BOXLON::type() const { return &type::SQLType::lookup("double"); }

FunctionEQ_BOXLON::FunctionEQ_BOXLON(const std::string& name,const expression::Expressions& args)
: FunctionExpression(name,args)
{}

FunctionEQ_BOXLON::FunctionEQ_BOXLON(const FunctionEQ_BOXLON& other)
: FunctionExpression(other.name_, other.args_)
{}

SQLExpression* FunctionEQ_BOXLON::clone() const { return new FunctionEQ_BOXLON(*this); }

FunctionEQ_BOXLON::~FunctionEQ_BOXLON() {}

double FunctionEQ_BOXLON::eval(bool& missing) const
{
    double lat_degrees = args_[0]->eval(missing);
    double lon_degrees = args_[1]->eval(missing);
    double resol = args_[2]->eval(missing);
    EqRegionCache p;
    double res;
    res = p.get_midlon(resol, lat_degrees, lon_degrees);

	return res;
}

} // namespace function
} // namespace expression
} // namespace sql
} // namespace odb

