/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

///
/// \file TemplateParameter.h
///
/// @author Piotr Kuchta, June 2009

#ifndef TemplateParameters_H
#define TemplateParameters_H

#include <string>
#include <stdint.h>

#include "odb_api/MetaData.h"

namespace eckit { class PathName; }
namespace eckit { class DataHandle; }

namespace odb {

class DispatchingWriter;

struct TemplateParameter {
	TemplateParameter(size_t startPos, size_t endPos, size_t columnIndex, std::string name)
	: startPos(startPos), endPos(endPos), columnIndex(columnIndex), name(name)
	{}

	size_t startPos;
	size_t endPos;
	size_t columnIndex;
	std::string name;

private:
// No copy allowed.
	TemplateParameter(const TemplateParameter&);
	TemplateParameter& operator=(const TemplateParameter&);
};

class TemplateParameters : public std::vector<TemplateParameter*> {
public:
	TemplateParameters();
	TemplateParameters(const std::string& fileNameTemplate, const MetaData& = nullMD);
	~TemplateParameters();

	void release();
	static TemplateParameters& parse(const std::string& fileNameTemplate, TemplateParameters&, const MetaData& = nullMD);

private:
	TemplateParameters(const TemplateParameters&);
	TemplateParameters& operator=(const TemplateParameters&);

	static MetaData nullMD;
};

} // namespace odb

#endif
