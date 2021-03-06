/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// \file SQLMATCHSubquerySessionOutput.h
/// Piotr Kuchta - ECMWF Feb 09

#ifndef SQLMATCHSubquerySessionOutput_H
#define SQLMATCHSubquerySessionOutput_H

#include "odb_api/SQLOutput.h"

class SelectIterator;
namespace odb { namespace sql { namespace expression { namespace function { class FunctionMATCH; } } } } 

namespace odb {
namespace sql {

class ReaderIterator;

class SQLMATCHSubquerySessionOutput : public SQLOutput {
public:
	SQLMATCHSubquerySessionOutput(odb::sql::expression::function::FunctionMATCH&);
	SQLMATCHSubquerySessionOutput(const SQLMATCHSubquerySessionOutput&);
	virtual ~SQLMATCHSubquerySessionOutput(); 

	SQLMATCHSubquerySessionOutput& operator=(const SQLMATCHSubquerySessionOutput&);

protected:
	virtual void print(std::ostream&) const; 	


// -- Members
	odb::sql::expression::function::FunctionMATCH& f_;

// -- Methods
	// None

// -- Overridden methods
	virtual unsigned long long count();
	virtual void size(int);
	virtual void reset();
	virtual void flush(ecml::ExecutionContext*);
	virtual bool output(const expression::Expressions&, ecml::ExecutionContext*);
	virtual void prepare(SQLSelect&);
	virtual void cleanup(SQLSelect&);

	virtual void outputReal(double, bool) { NOTIMP; };
	virtual void outputDouble(double, bool) { NOTIMP; };
	virtual void outputInt(double, bool) { NOTIMP; };
	virtual void outputUnsignedInt(double, bool) { NOTIMP; };
	virtual void outputString(double, bool) { NOTIMP; };
	virtual void outputBitfield(double, bool) { NOTIMP; };

private:
    unsigned long long count_;
};

} // namespace sql
} // namespace odb

#endif
