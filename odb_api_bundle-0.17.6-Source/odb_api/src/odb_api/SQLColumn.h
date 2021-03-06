/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File SQLColumn.h
// Baudouin Raoult - ECMWF Dec 03

#ifndef SQLColumn_H
#define SQLColumn_H

namespace eckit { class PathName; }

#include "odb_api/SQLIterator.h"
#include "odb_api/Types.h"

namespace odb {
namespace sql {

class SQLBitColumn;
class SQLIndex;
class SQLTable;

class SQLColumn : public SQLIterator {
public:
	SQLColumn(const type::SQLType&, SQLTable&, const std::string&, int, bool hasMissingValue, double missingValue, const BitfieldDef&);
	SQLColumn(const type::SQLType&, SQLTable&, const std::string&, int, bool hasMissingValue, double missingValue);
	virtual ~SQLColumn();

	void scan();

	unsigned long long noRows() const;

	const std::string& name() const { return name_; }
	int index() { return index_; }
	void index(int i) { index_ = i; }
	std::string fullName()    const;
	SQLTable* table()    const;


	bool hasMissingValue() const { return hasMissingValue_; }
	double missingValue() const { return missingValue_; }
	bool isBitfield() const { return isBitfield_; }
	const BitfieldDef& bitfieldDef() const { return bitfieldDef_; }

// -- Overridden methods
	// From SQLIterator

	virtual void rewind();
	virtual double next(bool& missing);
	virtual void advance(unsigned long);

	bool hasIndex() const { return indexing_.get() != 0; }
	void createIndex();
	void loadIndex();
	SQLIndex* getIndex(double*);

	eckit::PathName indexPath();
protected:
	unsigned long long noRows_;

	virtual void print(std::ostream&) const; 	
//private:
protected:
	SQLColumn(const SQLColumn&);
	SQLColumn& operator=(const SQLColumn&);

	void setPool(int);


	SQLTable& owner_;
	std::string    name_;
	int       index_;

	std::vector<int>          rows_;
	std::vector<SQLIterator*> iterators_;

	long long current_;
	long long last_;
	long long position_;
	SQLIterator* iterator_;

    std::auto_ptr<SQLIndex> indexing_;

	bool hasMissingValue_;
	double missingValue_;
	bool isBitfield_;
	const BitfieldDef bitfieldDef_;

	friend class odb::sql::SQLBitColumn;
};

} // namespace sql 
} // namespace odb 

#endif
