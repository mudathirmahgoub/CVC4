/*********************                                                        */
/*! \file normal_form.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Kshitij Bansal, Andrew Reynolds, Tim King
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Normal form for set constants.
 **
 ** Normal form for set constants.
 **/

#include "cvc4_private.h"

#ifndef CVC4__THEORY__BAGS__NORMAL_FORM_H
#define CVC4__THEORY__BAGS__NORMAL_FORM_H

namespace CVC4 {
namespace theory {
namespace sets {

class BagsNormalForm
{
 public:
  template <bool ref_count>
  static Node elementsToBag(const std::vector<NodeTemplate<ref_count> >& elements,
                            TypeNode bagType)
  {
    typedef typename std::vector<NodeTemplate<ref_count> >::const_iterator
        ElementsIterator;
    NodeManager* nm = NodeManager::currentNM();
    if (elements.size() == 0)
    {
      return nm->mkConst(EmptyBag(nm->toType(bagType)));
    }
    else
    {
      ElementsIterator it = elements.begin();
      Node current = nm->mkConst(EmptyBag(nm->toType(bagType)));
      while (++it != elements.end())
      {
        current = nm->mkNode(kind::INSERT, current, *it);
      }
      return current;
    }
  }

  static bool checkNormalConstant(TNode n)
  {
    Debug("bags-checknormal")
        << "[bags-checknormal] checkNormal " << n << " :" << std::endl;
    if (n.getKind() == kind::EMPTYBAG)
    {
      return true;
    }
    else if (n.getKind() == kind::INSERT)
    {
      // assuming (insert NodeN... Node1 emptybag)
      size_t size = n.getNumChildren();
      // check NodeN >= ... >= Node1

      for(size_t i = 1; i < size; i++)
      {
        if(n[i] > n[i-1])
        {
          Debug("bags-checknormal") << "n[i-1] = " << n[i-1] << ", n[i] = "
              << n[i] << std::endl;
          return false;
        }
      }
      // we made it
      return true;
    }
    else
    {
      return false;
    }
  }

  static std::vector<Node> getElementsFromNormalConstant(TNode n)
  {
    Assert(n.isConst());
    std::vector<Node> ret;
    if (n.getKind() == kind::EMPTYSET)
    {
      return ret;
    }
    while (n.getKind() == kind::INSERT)
    {
      // (insert element bag)
      ret.insert(ret.begin(), n[0]);
      n = n[1];
    }
    Assert(n.getKind() == kind::EMPTYBAG);
    return ret;
  }

  // AJR

  static void getElementsFromBop(Kind k, Node n, std::vector<Node>& els)
  {
    if (n.getKind() == k)
    {
      for (unsigned i = 0; i < n.getNumChildren(); i++)
      {
        getElementsFromBop(k, n[i], els);
      }
    }
    else
    {
      if (std::find(els.begin(), els.end(), n) == els.end())
      {
        els.push_back(n);
      }
    }
  }
  static Node mkBop(Kind k,
                    std::vector<Node>& els,
                    TypeNode tn,
                    unsigned index = 0)
  {
    if (index >= els.size())
    {
      return NodeManager::currentNM()->mkConst(EmptySet(tn.toType()));
    }
    else if (index == els.size() - 1)
    {
      return els[index];
    }
    else
    {
      return NodeManager::currentNM()->mkNode(
          k, els[index], mkBop(k, els, tn, index + 1));
    }
  }
};
}  // namespace sets
}  // namespace theory
}  // namespace CVC4

#endif
