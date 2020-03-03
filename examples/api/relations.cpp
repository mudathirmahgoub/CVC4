/*********************                                                        */
/*! \file relations.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Mudathir Mahgoub
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief Reasoning about relations with CVC4 via C++ API.
 **
 ** A simple demonstration of reasoning about strings with CVC4 via C++ API.
 **/
#include <cvc4/cvc4.h>

#include <iostream>
/*
This file uses the API to make a sat call equivalent to the following benchmark:
(set-logic ALL)
(set-option :finite-model-find true)
(set-option :produce-models true)
(set-option :sets-ext true)
(set-option :output-language "smt2")
(declare-sort Person 0)
(declare-fun people () (Set (Tuple Person)))
(declare-fun males () (Set (Tuple Person)))
(declare-fun females() (Set (Tuple Person)))
(declare-fun father () (Set (Tuple Person Person)))
(declare-fun mother () (Set (Tuple Person Person)))
(declare-fun parent () (Set (Tuple Person Person)))
(declare-fun ancestor () (Set (Tuple Person Person)))
(declare-fun descendant () (Set (Tuple Person Person)))

(assert (= people (as univset (Set (Tuple Person)))))
(assert (not (= males (as emptyset (Set (Tuple Person))))))
(assert (not (= females (as emptyset (Set (Tuple Person))))))
(assert (= (intersection males females) (as emptyset (Set (Tuple Person)))))

; father relation is not empty
(assert (not (= father (as emptyset (Set (Tuple Person Person))))))
; mother relation is not empty
(assert (not (= mother (as emptyset (Set (Tuple Person Person))))))

; fathers are males
(assert (subset (join father people) males))
; mothers are females
(assert (subset (join mother people) females))

; parent
(assert (= parent (union father mother)))

; no self ancestor
(assert (forall ((x Person)) (not (member (mkTuple x x) ancestor))))

; descendant
(assert (= descendant (tclosure parent)))

; ancestor
(assert (= ancestor (transpose descendant)))

(check-sat)
(get-model)
 */

using namespace CVC4;
using namespace std;

int main()
{
  ExprManager manager;
  SmtEngine smtEngine(&manager);

  // Set the logic
  smtEngine.setLogic("ALL");

  // options
  smtEngine.setOption("produce-models", true);
  smtEngine.setOption("finite-model-find", true);
  smtEngine.setOption("sets-ext", true);
  smtEngine.setOption("output-language", "smt2");

  // (declare-sort Person 0)
  Type personType = manager.mkSort("Person", 0);
  vector<Type> vector1;
  vector1.push_back(personType);

  // (Tuple Person)
  Type tupleArity1 = manager.mkTupleType(vector1);
  // (Set (Tuple Person))
  SetType relationArity1 = manager.mkSetType(tupleArity1);

  vector<Type> vector2;
  vector2.push_back(personType);
  vector2.push_back(personType);
  // (Tuple Person Person)
  DatatypeType tupleArity2 = manager.mkTupleType(vector2);
  // (Set (Tuple Person Person))
  SetType relationArity2 = manager.mkSetType(tupleArity2);

  // empty set
  EmptySet emptySet(relationArity1);
  Expr emptySetExpr = manager.mkConst(emptySet);

  // empty relation
  EmptySet emptyRelation(relationArity2);
  Expr emptyRelationExpr = manager.mkConst(emptyRelation);

  // universe set
  Expr universeSet =
      manager.mkNullaryOperator(relationArity1, Kind::UNIVERSE_SET);

  // variables
  Expr people = manager.mkVar("people", relationArity1);
  Expr males = manager.mkVar("males", relationArity1);
  Expr females = manager.mkVar("females", relationArity1);
  Expr father = manager.mkVar("father", relationArity2);
  Expr mother = manager.mkVar("mother", relationArity2);
  Expr parent = manager.mkVar("parent", relationArity2);
  Expr ancestor = manager.mkVar("ancestor", relationArity2);
  Expr descendent = manager.mkVar("descendent", relationArity2);

  Expr isEmpty1 = manager.mkExpr(Kind::EQUAL, males, emptySetExpr);
  Expr isEmpty2 = manager.mkExpr(Kind::EQUAL, females, emptySetExpr);

  // (assert (= people (as univset (Set (Tuple Person)))))
  Expr peopleAreTheUniverse = manager.mkExpr(Kind::EQUAL, people, universeSet);
  // (assert (not (= males (as emptyset (Set (Tuple Person))))))
  Expr maleSetIsNotEmpty = manager.mkExpr(Kind::NOT, isEmpty1);
  // (assert (not (= females (as emptyset (Set (Tuple Person))))))
  Expr femaleSetIsNotEmpty = manager.mkExpr(Kind::NOT, isEmpty2);

  // (assert (= (intersection males females) (as emptyset (Set (Tuple
  // Person)))))
  Expr malesFemalesIntersection =
      manager.mkExpr(Kind::INTERSECTION, males, females);
  Expr malesAndFemalesAreDisjoint =
      manager.mkExpr(Kind::EQUAL, malesFemalesIntersection, emptySetExpr);

  // (assert (not (= father (as emptyset (Set (Tuple Person Person))))))
  // (assert (not (= mother (as emptyset (Set (Tuple Person Person))))))
  Expr isEmpty3 = manager.mkExpr(Kind::EQUAL, father, emptyRelationExpr);
  Expr isEmpty4 = manager.mkExpr(Kind::EQUAL, mother, emptyRelationExpr);
  Expr fatherIsNotEmpty = manager.mkExpr(Kind::NOT, isEmpty3);
  Expr motherIsNotEmpty = manager.mkExpr(Kind::NOT, isEmpty4);

  // fathers are males
  // (assert (subset (join father people) males))
  Expr fathers = manager.mkExpr(Kind::JOIN, father, people);
  Expr fathersAreMales = manager.mkExpr(Kind::SUBSET, fathers, males);

  // mothers are females
  // (assert (subset (join mother people) females))
  Expr mothers = manager.mkExpr(Kind::JOIN, mother, people);
  Expr mothersAreFemales = manager.mkExpr(Kind::SUBSET, mothers, females);

  // (assert (= parent (union father mother)))
  Expr unionFatherMother = manager.mkExpr(Kind::UNION, father, mother);
  Expr parentIsFatherOrMother =
      manager.mkExpr(Kind::EQUAL, parent, unionFatherMother);

  // (assert (= parent (union father mother)))
  Expr transitiveClosure = manager.mkExpr(Kind::TCLOSURE, parent);
  Expr descendentFormula =
      manager.mkExpr(Kind::EQUAL, descendent, transitiveClosure);

  // (assert (= parent (union father mother)))
  Expr transpose = manager.mkExpr(Kind::TRANSPOSE, descendent);
  Expr ancestorFormula = manager.mkExpr(Kind::EQUAL, ancestor, transpose);

  // (assert (forall ((x Person)) (not (member (mkTuple x x) ancestor))))
  Expr x = manager.mkBoundVar("x", personType);
  Expr constructor = tupleArity2.getDatatype()[0].getConstructor();
  Expr xxTuple = manager.mkExpr(Kind::APPLY_CONSTRUCTOR, constructor, x, x);
  Expr member = manager.mkExpr(Kind::MEMBER, xxTuple, ancestor);
  Expr notMember = manager.mkExpr(Kind::NOT, member);

  Expr quantifiedVariables = manager.mkExpr(Kind::BOUND_VAR_LIST, x);
  Expr noSelfAncestor =
      manager.mkExpr(Kind::FORALL, quantifiedVariables, notMember);

  // formulas
  Expr formula1 = manager.mkExpr(Kind::AND,
                                 peopleAreTheUniverse,
                                 maleSetIsNotEmpty,
                                 femaleSetIsNotEmpty,
                                 malesAndFemalesAreDisjoint);

  Expr formula2 = manager.mkExpr(Kind::AND,
                                 formula1,
                                 fatherIsNotEmpty,
                                 motherIsNotEmpty,
                                 fathersAreMales,
                                 mothersAreFemales);

  Expr formula3 = manager.mkExpr(Kind::AND,
                                 formula2,
                                 parentIsFatherOrMother,
                                 descendentFormula,
                                 ancestorFormula,
                                 noSelfAncestor);

  // check sat
  Result result = smtEngine.checkSat(formula3);

  // output
  cout << "CVC4 reports: " << formula3 << " is " << result << "." << endl;
  cout << "people     = " << smtEngine.getValue(people) << endl;
  cout << "males      = " << smtEngine.getValue(males) << endl;
  cout << "females    = " << smtEngine.getValue(females) << endl;
  cout << "father     = " << smtEngine.getValue(father) << endl;
  cout << "mother     = " << smtEngine.getValue(mother) << endl;
  cout << "parent     = " << smtEngine.getValue(parent) << endl;
  cout << "descendent = " << smtEngine.getValue(descendent) << endl;
  cout << "ancestor   = " << smtEngine.getValue(ancestor) << endl;
}
