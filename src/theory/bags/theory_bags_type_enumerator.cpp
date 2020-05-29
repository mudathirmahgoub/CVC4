/*********************                                                        */
/*! \file theory_bags_type_enumerator.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Kshitij Bansal, Tim King, Andrew Reynolds, Mudathir Mahgoub
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief bag enumerator implementation
 **
 ** bag enumerator implementation
 **/

#include "theory/bags/theory_bags_type_enumerator.h"

#include "expr/datatype.h"
#include "expr/emptybag.h"
#include "theory_bags_type_enumerator.h"
// ToDo: refine this include
#include "theory/bags/theory_bags_private.h"

namespace CVC4 {
namespace theory {
namespace bags {

BagEnumerator::BagEnumerator(TypeNode type, TypeEnumeratorProperties* tep)
    : TypeEnumeratorBase<BagEnumerator>(type),
      d_nodeManager(NodeManager::currentNM()),
      d_elementTypeEnumerator(type.getBagElementType(), tep)
{
  d_currentBag = d_nodeManager->mkConst(EmptyBag(type.toType()));
  d_element = *d_elementTypeEnumerator;
}

BagEnumerator::BagEnumerator(const BagEnumerator& enumerator)
    : TypeEnumeratorBase<BagEnumerator>(enumerator.getType()),
      d_nodeManager(enumerator.d_nodeManager),
      d_elementTypeEnumerator(enumerator.d_elementTypeEnumerator),
      d_currentBag(enumerator.d_currentBag),
      d_element(enumerator.d_element)
{
}

BagEnumerator::~BagEnumerator() {}

Node BagEnumerator::operator*()
{
  Trace("bag-type-enum") << "BagEnumerator::operator* d_currentBag = "
                         << d_currentBag << std::endl;

  return d_currentBag;
}

BagEnumerator& BagEnumerator::operator++()
{
  // increase the multiplicity by one
  Node one = d_nodeManager->mkConst(Rational(1));
  Node singleton = d_nodeManager->mkNode(kind::BAG_SINGLETON, d_element, one);
  d_currentBag =
      d_nodeManager->mkNode(kind::DISJOINT_UNION, singleton, d_currentBag);

  Assert(d_currentBag.isConst());
  Assert(d_currentBag == Rewriter::rewrite(d_currentBag));

  Trace("bag-type-enum") << "BagEnumerator::operator++ d_currentBag = "
                         << d_currentBag << std::endl;
  return *this;
}

bool BagEnumerator::isFinished()
{
  // bags sequence is infinite and it never ends
  return false;
}

}  // namespace bags
}  // namespace theory
}  // namespace CVC4
