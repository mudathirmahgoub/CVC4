/*********************                                                        */
/*! \file theory_bags_type_enumerator.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Kshitij Bansal, Tim King, Andrew Reynolds, Mudathir Mahgoub
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief type enumerator for bags
 **
 ** A bag enumerator that iterates over bags
 **/

#include "cvc4_private.h"

#ifndef CVC4__THEORY__BAGS__TYPE_ENUMERATOR_H
#define CVC4__THEORY__BAGS__TYPE_ENUMERATOR_H

#include "expr/kind.h"
#include "expr/type_node.h"
#include "theory/rewriter.h"
#include "theory/sets/normal_form.h"
#include "theory/type_enumerator.h"
#include "theory_sets_type_enumerator.h"

namespace CVC4 {
namespace theory {
namespace sets {

class BagEnumerator : public TypeEnumeratorBase<BagEnumerator>
{
 public:
  BagEnumerator(TypeNode type, TypeEnumeratorProperties* tep = nullptr);
  BagEnumerator(const BagEnumerator& enumerator);
  ~BagEnumerator();

  Node operator*() override;

  /**
   * This operator iterates over the infinite bags constructed from the element
   * type . The enumeration depends on the finiteness of the element type
   * Example iterating over bags of {"1", "2", "3", ...} will return the
   * following infinite sequence of bags:
   * {},                        sum = 0, index = 0
   * {("1",1)},                 sum = 2, index = 1
   * {("2",1)},                 sum = 3, index = 2
   * {("1",2)},                 sum = 3, index = 2
   * {("3", 1)},                sum = 4, index = 3
   * {("2", 2)},                sum = 4, index = 3
   * {("1", 3)},                sum = 4, index = 3
   * {("4", 1)},                sum = 5, index = 4
   * {("3", 2)},                sum = 5, index = 4
   * {("2", 3)},                sum = 5, index = 4
   * {("1", 4)},                sum = 5, index = 4
   * {("1", 1),("2", 1)},       sum = 5, index = 4
   * {("5", 1)},                sum = 6, index = 5
   * {("4", 2)},                sum = 6, index = 5
   * {("3", 3)},                sum = 6, index = 5
   * {("2", 4)},                sum = 6, index = 5
   * {("1", 5)},                sum = 6, index = 5
   * {("1", 1), ("2",2)},       sum = 6, index = 5
   * {("1", 2), ("2",1)},       sum = 6, index = 5
   * {("1", 2), ("2",1)},       sum = 6, index = 5
   */
  BagEnumerator& operator++() override;

  bool isFinished() override;

 private:
  SetEnumerator getPairsEnumerator(const TypeNode& type,
                              TypeEnumeratorProperties* tep) const;

  void convertIntToNat(Node * node);

  /** a pointer to the node manager */
  NodeManager* d_nodeManager;
  /** an enumerator for the set of pairs of element type x integer type */
  SetEnumerator d_pairsEnumerator;
  /** the current set returned by the set enumerator */
  Node d_currentBag;
}; /* class BagEnumerator */

}  // namespace sets
}  // namespace theory
}  // namespace CVC4

#endif /* CVC4__THEORY__BAGS__TYPE_ENUMERATOR_H */
