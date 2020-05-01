/*********************                                                        */
/*! \file theory_bags_rewriter.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds, Kshitij Bansal, Paul Meng
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Bags theory rewriter.
 **
 ** Bags theory rewriter.
 **/

#include "theory/bags/theory_bags_rewriter.h"

using namespace CVC4::kind;

namespace CVC4 {
namespace theory {
namespace bags {

RewriteResponse TheoryBagsRewriter::postRewrite(TNode node)
{
  return RewriteResponse(REWRITE_DONE, node);
}

RewriteResponse TheoryBagsRewriter::preRewrite(TNode node)
{
  return RewriteResponse(REWRITE_DONE, node);
}

}  // namespace bags
}  // namespace theory
}  // namespace CVC4
