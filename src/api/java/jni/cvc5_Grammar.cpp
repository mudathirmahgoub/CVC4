/******************************************************************************
 * Top contributors (to current version):
 *   Mudathir Mohamed
 *
 * This file is part of the cvc5 project.
 *
 * Copyright (c) 2009-2021 by the authors listed in the file AUTHORS
 * in the top-level source directory and their institutional affiliations.
 * All rights reserved.  See the file COPYING in the top-level source
 * directory for licensing information.
 * ****************************************************************************
 *
 * The cvc5 Java API.
 */

#include "cvc5_Grammar.h"

#include "api/cpp/cvc5.h"
#include "cvc5JavaApi.h"

using namespace cvc5::api;

/*
 * Class:     cvc5_Grammar
 * Method:    deletePointer
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_cvc5_Grammar_deletePointer(JNIEnv*,
                                                       jclass,
                                                       jlong pointer)
{
  delete ((Grammar*)pointer);
}

/*
 * Class:     cvc5_Grammar
 * Method:    addRule
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_cvc5_Grammar_addRule(JNIEnv* env,
                                                 jobject,
                                                 jlong pointer,
                                                 jlong ntSymbolPointer,
                                                 jlong rulePointer)
{
  CVC5_JAVA_API_TRY_CATCH_BEGIN;
  Grammar* current = (Grammar*)pointer;
  Term* ntSymbol = (Term*)ntSymbolPointer;
  Term* rule = (Term*)rulePointer;
  current->addRule(*ntSymbol, *rule);
  CVC5_JAVA_API_TRY_CATCH_END(env);
}

/*
 * Class:     cvc5_Grammar
 * Method:    addRules
 * Signature: (JJ[J)V
 */
JNIEXPORT void JNICALL Java_cvc5_Grammar_addRules(JNIEnv* env,
                                                  jobject,
                                                  jlong pointer,
                                                  jlong ntSymbolPointer,
                                                  jlongArray rulePointers)
{
  CVC5_JAVA_API_TRY_CATCH_BEGIN;
  Grammar* current = (Grammar*)pointer;
  Term* ntSymbol = (Term*)ntSymbolPointer;
  // get the size of pointers
  jsize size = env->GetArrayLength(rulePointers);

  std::vector<jlong> cRules(size);
  // copy java array to the buffer
  env->GetLongArrayRegion(rulePointers, 0, size, cRules.data());
  // copy the terms into a vector
  std::vector<Term> rules;
  for (jlong cRule : cRules)
  {
    Term* term = (Term*)(cRule);
    rules.push_back(*term);
  }

  current->addRules(*ntSymbol, rules);
  CVC5_JAVA_API_TRY_CATCH_END(env);
}

/*
 * Class:     cvc5_Grammar
 * Method:    addAnyConstant
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_cvc5_Grammar_addAnyConstant(JNIEnv* env,
                                                        jobject,
                                                        jlong pointer,
                                                        jlong ntSymbolPointer)
{
  CVC5_JAVA_API_TRY_CATCH_BEGIN;
  Grammar* current = (Grammar*)pointer;
  Term* ntSymbol = (Term*)ntSymbolPointer;
  current->addAnyConstant(*ntSymbol);
  CVC5_JAVA_API_TRY_CATCH_END(env);
}

/*
 * Class:     cvc5_Grammar
 * Method:    addAnyVariable
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_cvc5_Grammar_addAnyVariable(JNIEnv* env,
                                                        jobject,
                                                        jlong pointer,
                                                        jlong ntSymbolPointer)
{
  CVC5_JAVA_API_TRY_CATCH_BEGIN;
  Grammar* current = (Grammar*)pointer;
  Term* ntSymbol = (Term*)ntSymbolPointer;
  current->addAnyVariable(*ntSymbol);
  CVC5_JAVA_API_TRY_CATCH_END(env);
}

/*
 * Class:     cvc5_Grammar
 * Method:    toString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_cvc5_Grammar_toString(JNIEnv* env,
                                                     jobject,
                                                     jlong pointer)
{
  CVC5_JAVA_API_TRY_CATCH_BEGIN;
  Grammar* current = (Grammar*)pointer;
  return env->NewStringUTF(current->toString().c_str());
  CVC5_JAVA_API_TRY_CATCH_END_RETURN(env, nullptr);
}
