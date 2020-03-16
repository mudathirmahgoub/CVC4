/*********************                                                        */
/*! \file emptybag.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Tim King, Kshitij Bansal
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief [[ Add one-line brief description here ]]
 **
 ** [[ Add lengthier description here ]]
 ** \todo document this file
 **/

#include "expr/emptybag.h"

#include <iosfwd>

#include "expr/expr.h"
#include "expr/type.h"

namespace CVC4 {

std::ostream& operator<<(std::ostream& out, const EmptyBag& asa) {
  return out << "emptybag(" << asa.getType() << ')';
}

size_t EmptyBagHashFunction::operator()(const EmptyBag& es) const {
  return TypeHashFunction()(es.getType());
}

/**
 * Constructs an emptybag of the specified type. Note that the argument
 * is the type of the bag itself, NOT the type of the elements.
 */
EmptyBag::EmptyBag(const BagType& bagType)
    : d_type(new BagType(bagType))
{
}

EmptyBag::EmptyBag(const EmptyBag& es)
    : d_type(new BagType(es.getType()))
{ }

EmptyBag& EmptyBag::operator=(const EmptyBag& es) {
  (*d_type) = es.getType();
  return *this;
}

EmptyBag::~EmptyBag() { delete d_type; }
const BagType& EmptyBag::getType() const {
  return *d_type;
}

bool EmptyBag::operator==(const EmptyBag& es) const
{
  return getType() == es.getType();
}

bool EmptyBag::operator!=(const EmptyBag& es) const { return !(*this == es); }
bool EmptyBag::operator<(const EmptyBag& es) const
{
  return getType() < es.getType();
}

bool EmptyBag::operator<=(const EmptyBag& es) const
{
  return getType() <= es.getType();
}

bool EmptyBag::operator>(const EmptyBag& es) const { return !(*this <= es); }
bool EmptyBag::operator>=(const EmptyBag& es) const { return !(*this < es); }
}/* CVC4 namespace */