/*********************                                                        */
/*! \file bags_rewriter.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Mudathir Mohamed
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Bags theory rewriter.
 **/

#include "cvc4_private.h"

#ifndef CVC4__THEORY__BAGS__THEORY_BAGS_REWRITER_H
#define CVC4__THEORY__BAGS__THEORY_BAGS_REWRITER_H

#include "theory/rewriter.h"

namespace CVC4 {
namespace theory {
namespace bags {

class BagsRewriter : public TheoryRewriter
{
 public:
  /**
   * postRewrite nodes with kinds: MK_BAG, BAG_COUNT, UNION_MAX, UNION_DISJOINT,
   * INTERSECTION_MIN, DIFFERENCE_SUBTRACT, DIFFERENCE_REMOVE, BAG_CHOOSE,
   * BAG_CARD, BAG_IS_SINGLETON.
   * See the rewrite rules for these kinds below.
   */
  RewriteResponse postRewrite(TNode n) override;
  /**
   * preRewrite nodes with kinds: EQUAL, BAG_IS_INCLUDED.
   * See the rewrite rules for these kinds below.
   */
  RewriteResponse preRewrite(TNode n) override;

 private:
  /**
   * patterns for n
   * - (= A A) = true where A is a bag
   */
  RewriteResponse rewriteEqual(const TNode& n) const;

  /**
   * patterns for n
   * - (bag.is_included A B) = ((difference_subtract A B) == emptybag)
   */
  RewriteResponse rewriteIsIncluded(const TNode& n) const;

  /**
   * patterns for n:
   * - (mkBag x 0) = (emptybag T) where T is the type of x
   * - (mkBag x (-c)) = (emptybag T) where T is the type of x, and c > 0 is a
   *   constant
   * - otherwise = n
   */
  RewriteResponse rewriteMakeBag(const TNode& n) const;
  /**
   * patterns for n
   * - (bag.count x emptybag) = 0
   * - (bag.count x (mkBag x c) = c where c > 0 is a constant
   * - otherwise = n
   */
  RewriteResponse rewriteBagCount(const TNode& n) const;

  /**
   * patterns for n
   * - (union_max A emptybag) = A
   * - (union_max emptybag A) = A
   * - (union_max A A) = A
   * - (union_max A (union_max A B)) = (union_max A B)
   * - (union_max A (union_max B A)) = (union_max B A)
   * - (union_max (union_max A B) A) = (union_max A B)
   * - (union_max (union_max B A) A) = (union_max B A)
   * - (union_max A (union_disjoint A B)) = (union_disjoint A B)
   * - (union_max A (union_disjoint B A)) = (union_disjoint B A)
   * - (union_max (union_disjoint A B) A) = (union_disjoint A B)
   * - (union_max (union_disjoint B A) A) = (union_disjoint B A)
   * - otherwise = n
   */
  RewriteResponse rewriteUnionMax(const TNode& n) const;

  /**
   * patterns for n
   * - (union_disjoint A emptybag) = A
   * - (union_disjoint emptybag A) = A
   * - (union_disjoint (union_max A B) (intersection_min A B)) =
   *         (union_disjoint A B) // sum(a,b) = max(a,b) + min(a,b)
   * - other permutations of the above like swapping A and B, or swapping
   *   intersection_min and union_max
   * - otherwise = n
   */
  RewriteResponse rewriteUnionDisjoint(const TNode& n) const;

  /**
   * patterns for n
   * - (intersection_min A emptybag) = emptybag
   * - (intersection_min emptybag A) = emptybag
   * - (intersection_min A A) = A
   * - (intersection_min A (union_disjoint A B)) = A
   * - (intersection_min A (union_disjoint B A)) = A
   * - (intersection_min (union_disjoint A B) A) = A
   * - (intersection_min (union_disjoint B A) A) = A
   * - (intersection_min A (union_max A B)) = A
   * - (intersection_min A (union_max B A)) = A
   * - (intersection_min (union_max A B) A) = A
   * - (intersection_min (union_max B A) A) = A
   * - otherwise = n
   */
  RewriteResponse rewriteIntersectionMin(const TNode& n) const;

  /**
   * patterns for n
   * - (difference_subtract A emptybag) = A
   * - (difference_subtract emptybag A) = emptybag
   * - (difference_subtract A A) = emptybag
   * - (difference_subtract (union_disjoint A B) A) = B
   * - (difference_subtract (union_disjoint B A) A) = B
   * - (difference_subtract A (union_disjoint A B)) = emptybag
   * - (difference_subtract A (union_disjoint B A)) = emptybag
   * - (difference_subtract A (union_max A B)) = emptybag
   * - (difference_subtract A (union_max B A)) = emptybag
   * - (difference_subtract (intersection_min A B) A) = emptybag
   * - (difference_subtract (intersection_min B A) A) = emptybag
   * - otherwise = n
   */
  RewriteResponse rewriteDifferenceSubtract(const TNode& n) const;

  /**
   * patterns for n
   * - (difference_remove A emptybag) = A
   * - (difference_remove emptybag A) = emptybag
   * - (difference_remove A A) = emptybag
   * - (difference_remove A (union_disjoint A B)) = emptybag
   * - (difference_remove A (union_disjoint B A)) = emptybag
   * - (difference_remove A (union_max A B)) = emptybag
   * - (difference_remove A (union_max B A)) = emptybag
   * - (difference_remove (intersection_min A B) A) = emptybag
   * - (difference_remove (intersection_min B A) A) = emptybag
   * - otherwise = n
   */
  RewriteResponse rewriteDifferenceRemove(const TNode& n) const;
  /**
   * patterns for n
   * - (bag.choose (mkBag x c)) = x where c is a constant > 0
   * - otherwise = n
   */
  RewriteResponse rewriteChoose(const TNode& n) const;
  /**
   * patterns for n
   * - (bag.card (mkBag x c)) = c where c is a constant > 0
   * - (bag.card (union-disjoint A B)) = (+ (bag.card A) (bag.card B))
   * - otherwise = n
   */
  RewriteResponse rewriteCard(const TNode& n) const;

  /**
   * patterns for n
   * - (bag.is_singleton (mkBag x c)) = (c == 1)
   */
  RewriteResponse rewriteIsSingleton(const TNode& n) const;
}; /* class TheoryBagsRewriter */

}  // namespace bags
}  // namespace theory
}  // namespace CVC4

#endif /* CVC4__THEORY__BAGS__THEORY_BAGS_REWRITER_H */
