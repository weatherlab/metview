/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/eckit.h"
#include "odb_api/Decoder.h"
#include "odb_api/Expressions.h"
#include "odb_api/SQLSelect.h"
#include "odb_api/SQLSimpleOutput.h"

#include <limits>

namespace odb {
namespace sql {

SQLSimpleOutput::SQLSimpleOutput(std::ostream& out)
: out_(out), count_(0)
{
    out_ << std::fixed;
}

SQLSimpleOutput::~SQLSimpleOutput() {}

void SQLSimpleOutput::print(std::ostream& s) const
{
	s << "SQLSimpleOutput";
}

std::ostream& SQLSimpleOutput::format(std::ostream& o, size_t i) const
{
	o.width(columnWidths_[i]);
	return o << *columnAlignments_[i];
}

void SQLSimpleOutput::size(int) {}
void SQLSimpleOutput::reset() { count_ = 0; }
void SQLSimpleOutput::flush(ecml::ExecutionContext*) { out_ << std::flush; }

bool SQLSimpleOutput::output(const expression::Expressions& results, ecml::ExecutionContext* context)
{
	size_t n = results.size();
    for(size_t i = 0; i < n; i++)
    {
        if(i) out_ << config_.fieldDelimiter();
		currentColumn_ = i;
        results[i]->output(*this);
    }
    out_ << "\n";
	count_++;
	return true;
}

template <typename T> void SQLSimpleOutput::outputValue(double x, bool missing) 
{
    format(out_, currentColumn_);

    if (missing && !config_.doNotWriteNULL())
        out_ << "NULL";
    else
    {
        if (config_.fullPrecision())
        {
            out_.precision(std::numeric_limits<T>::digits10 + 2);
            out_ << std::fixed << static_cast<T>(x);
        }
        else
            out_ << static_cast<T>(x);
    }
}

void SQLSimpleOutput::outputReal(double x, bool missing) { outputValue<double>(x, missing); }
void SQLSimpleOutput::outputDouble(double x, bool missing) { outputValue<double>(x, missing); }
void SQLSimpleOutput::outputInt(double x, bool missing) { outputValue<long long>(x, missing); }
void SQLSimpleOutput::outputUnsignedInt(double x, bool missing) { outputValue<unsigned long>(x, missing); }

void SQLSimpleOutput::outputString(double x, bool missing)
{
	format(out_, currentColumn_);
	if (missing && !config_.doNotWriteNULL())
		out_ << "NULL";
	else
	{
        std::stringstream ss;
		ss << "'";
		char *p = reinterpret_cast<char*>(&x);
		for(size_t i = 0; i < sizeof(x); i++)
			if(p[i] != ' ' && isprint(p[i]))
				ss << p[i];
		ss << "'";

		out_ << ss.str();
	}
}

void SQLSimpleOutput::outputBitfield(double x, bool missing)
{
    if (! config_.displayBitfieldsBinary())
    {
        outputUnsignedInt(x, missing);
        return;
    }
	
	format(out_, currentColumn_);
	if (missing && !config_.doNotWriteNULL())
		out_ << "NULL";
	else
	{
        std::stringstream ss;
		Decoder::printBinary(ss, static_cast<unsigned long>(x));
		out_ << ss.str();
	}
}

void SQLSimpleOutput::prepare(SQLSelect& sql)
{
    printHeader(sql);
}

void SQLSimpleOutput::printHeader(SQLSelect& sql)
{
    const expression::Expressions& columns(sql.output());
    for (size_t i (0); i < columns.size(); i++)
    {
        const std::string& name (columns[i]->title());
        const type::SQLType* type (columns[i]->type());
 
        columnWidths_.push_back(config_.disableAlignmentOfColumns() ? 1 : std::max(type->width(), name.size()));
        columnAlignments_.push_back(type->format());

        if (! config_.doNotWriteColumnNames())
        {
            if(i) out_ << config_.fieldDelimiter();

            format(out_, i);

            if (config_.outputFormat() != "wide")
                out_ << name;
            else
            {
                std::stringstream ss;
                ss << name << ":" << type->name();
                out_ << ss.str();
            }

		}
		
	}
    if (! config_.doNotWriteColumnNames())
        out_ << "\n";
}

void SQLSimpleOutput::cleanup(SQLSelect& sql) {}
unsigned long long SQLSimpleOutput::count() { return count_; }

} // namespace sql
} // namespace odb
