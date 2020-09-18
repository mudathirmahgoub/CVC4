/*********************                                                        */
/*! \file solver_state.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds, Mudathir Mohamed
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Implementation of bags state object
 **/

#include "theory/bags/solver_state.h"

#include "expr/emptybag.h"
#include "options/sets_options.h"
#include "smt/logic_exception.h"
#include "theory/bags/skolem_cache.h"
#include "theory/bags/theory_bags_private.h"

using namespace std;
using namespace CVC4::kind;

namespace CVC4 {
namespace theory {
namespace bags {

SolverState::SolverState(context::Context* c,
                         context::UserContext* u,
                         Valuation val,
                         SkolemCache& skc)
    : TheoryState(c, u, val), d_skCache(skc)
{
  d_true = NodeManager::currentNM()->mkConst(true);
  d_false = NodeManager::currentNM()->mkConst(false);
}

}  // namespace bags
}  // namespace theory
}  // namespace CVC4
