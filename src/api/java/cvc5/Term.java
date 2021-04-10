package cvc5;

public class Term extends AbstractPointer implements Comparable<Term>
{
  // region construction and destruction
  Term(Solver solver, long pointer)
  {
    super(solver, pointer);
  }

  protected static native void deletePointer(long pointer);

  public long getPointer()
  {
    return pointer;
  }

  // endregion

  /**
   * Syntactic equality operator.
   * Return true if both terms are syntactically identical.
   * Both terms must belong to the same solver object.
   *
   * @param t the term to compare to for equality
   * @return true if the terms are equal
   */
  @Override public boolean equals(Object t)
  {
    if (this == t)
      return true;
    if (t == null || getClass() != t.getClass())
      return false;
    return equals(pointer, ((Term) t).getPointer());
  }

  private native boolean equals(long pointer1, long pointer2);

  /**
   * Comparison for ordering on terms.
   *
   * @param t the term to compare to
   * @return a negative integer, zero, or a positive integer as this term
   * is less than, equal to, or greater than the specified term.
   */
  @Override public int compareTo(Term t)
  {
    return this.compareTo(pointer, t.getPointer());
  }

  private native int compareTo(long pointer1, long pointer2);

  /**
   * @return the number of children of this term
   */
  int getNumChildren()
  {
    return getNumChildren(pointer);
  }

  private native int getNumChildren(long pointer);

  /**
   * Get the child term at a given index.
   *
   * @param index the index of the child term to return
   * @return the child term with the given index
   */
  Term getChild(int index) throws CVC5ApiException
  {
    if (index < 0)
    {
      throw new CVC5ApiException("Expected index '" + index + "' to be non negative.");
    }
    long termPointer = getChild(pointer, index);
    return new Term(solver, termPointer);
  }

  private native long getChild(long pointer, int index);

  /**
   * @return the id of this term
   */
  long getId()
  {
    return getId(pointer);
  }

  private native long getId(long pointer);

  /**
   * @return the kind of this term
   */
  Kind getKind()
  {
    try
    {
      int value = getKind(pointer);
      return Kind.fromInt(value);
    }
    catch(CVC5ApiException e)
    {
      e.printStackTrace();
      throw new RuntimeException(e.getMessage());
    }
  }

  private native int getKind(long pointer);

  /**
   * @return the sort of this term
   */
  Sort getSort()
  {
    long sortPointer = getSort(pointer);
    return new Sort(solver, sortPointer);
  }

  private native long getSort(long pointer);

  /**
   * @return the result of replacing 'term' by 'replacement' in this term
   */
  Term substitute(Term term, Term replacement)
  {
    long termPointer = substitute(pointer, term.getPointer(), replacement.getPointer());
    return new Term(solver, termPointer);
  }

  private native long substitute(long pointer, long termPointer, long replacementPointer);

  /**
   * @return the result of simultaneously replacing 'terms' by 'replacements'
   * in this term
   */
  Term substitute(Term[] terms, Term[] replacements)
  {
    long[] termPointers = new long[terms.length];
    for (int i = 0; i < termPointers.length; i++)
    {
      termPointers[i] = terms[i].getPointer();
    }
    long[] replacementPointers = new long[replacements.length];
    for (int i = 0; i < replacements.length; i++)
    {
      replacementPointers[i] = replacements[i].getPointer();
    }

    long termPointer = substitute(pointer, termPointers, replacementPointers);
    return new Term(solver, termPointer);
  }

  private native long substitute(long pointer, long[] termPointers, long[] replacementPointers);

  /**
   * @return true iff this term has an operator
   */
  boolean hasOp()
  {
    return hasOp(pointer);
  }

  private native boolean hasOp(long pointer);

  /**
   * @return the Op used to create this term
   * Note: This is safe to call when hasOp() returns true.
   */
  Op getOp()
  {
    long opPointer = getOp(pointer);
    return new Op(solver, opPointer);
  }

  private native long getOp(long pointer);

  /**
   * @return true if this Term is a null term
   */
  boolean isNull()
  {
    return isNull(pointer);
  }

  private native boolean isNull(long pointer);

  /**
   * Return the base (element stored at all indices) of a constant array
   * throws an exception if the kind is not CONST_ARRAY
   *
   * @return the base value
   */
  Term getConstArrayBase()
  {
    long termPointer = getConstArrayBase(pointer);
    return new Term(solver, termPointer);
  }

  private native long getConstArrayBase(long pointer);

  /**
   * Return the elements of a constant sequence
   * throws an exception if the kind is not CONST_SEQUENCE
   *
   * @return the elements of the constant sequence.
   */
  Term[] getConstSequenceElements()
  {
    long[] termPointers = getConstSequenceElements(pointer);
    Term[] terms = new Term[termPointers.length];
    for (int i = 0; i < termPointers.length; i++)
    {
      terms[i] = new Term(solver, termPointers[i]);
    }

    return terms;
  }

  private native long[] getConstSequenceElements(long pointer);

  /**
   * Boolean negation.
   *
   * @return the Boolean negation of this term
   */
  Term notTerm()
  {
    long termPointer = notTerm(pointer);
    return new Term(solver, termPointer);
  }

  private native long notTerm(long pointer);

  /**
   * Boolean and.
   *
   * @param t a Boolean term
   * @return the conjunction of this term and the given term
   */
  Term andTerm(Term t)
  {
    long termPointer = andTerm(pointer, t.getPointer());
    return new Term(solver, termPointer);
  }

  private native long andTerm(long pointer, long termPointer);

  /**
   * Boolean or.
   *
   * @param t a Boolean term
   * @return the disjunction of this term and the given term
   */
  Term orTerm(Term t)
  {
    long termPointer = orTerm(pointer, t.getPointer());
    return new Term(solver, termPointer);
  }

  private native long orTerm(long pointer, long termPointer);

  /**
   * Boolean exclusive or.
   *
   * @param t a Boolean term
   * @return the exclusive disjunction of this term and the given term
   */
  Term xorTerm(Term t)
  {
    long termPointer = xorTerm(pointer, t.getPointer());
    return new Term(solver, termPointer);
  }

  private native long xorTerm(long pointer, long termPointer);

  /**
   * Equality.
   *
   * @param t a Boolean term
   * @return the Boolean equivalence of this term and the given term
   */
  Term eqTerm(Term t)
  {
    long termPointer = eqTerm(pointer, t.getPointer());
    return new Term(solver, termPointer);
  }

  private native long eqTerm(long pointer, long termPointer);

  /**
   * Boolean implication.
   *
   * @param t a Boolean term
   * @return the implication of this term and the given term
   */
  Term impTerm(Term t)
  {
    long termPointer = impTerm(pointer, t.getPointer());
    return new Term(solver, termPointer);
  }

  private native long impTerm(long pointer, long termPointer);

  /**
   * If-then-else with this term as the Boolean condition.
   *
   * @param thenTerm the 'then' term
   * @param elseTerm the 'else' term
   * @return the if-then-else term with this term as the Boolean condition
   */
  Term iteTerm(Term thenTerm, Term elseTerm)
  {
    long termPointer = iteTerm(pointer, thenTerm.getPointer(), elseTerm.getPointer());
    return new Term(solver, termPointer);
  }

  private native long iteTerm(long pointer, long thenPointer, long elsePointer);

  /**
   * @return a string representation of this term
   */
  protected native String toString(long pointer);

  /**
   * @return true if the term is an integer that fits within signed 32 bits.
   */
  boolean isInt32()
  {
    return isInt32(pointer);
  }

  private native boolean isInt32(long pointer);

  /**
   * @return the stored integer as an int.
   * Note: Asserts isInt32().
   */
  int getInt32()
  {
    return getInt32(pointer);
  }

  private native int getInt32(long pointer);

  /**
   * @return true if the term is an integer that fits within unsigned 32 bits.
   */
  boolean isUInt32()
  {
    return isUInt32(pointer);
  }

  private native boolean isUInt32(long pointer);

  /**
   * @return the stored integer as an int.
   * Note: Asserts isUInt32().
   */
  int getUInt32()
  {
    return getUInt32(pointer);
  }

  private native int getUInt32(long pointer);

  /**
   * @return true if the term is an integer that fits within signed 64 bits.
   */
  boolean isInt64()
  {
    return isInt64(pointer);
  }

  private native boolean isInt64(long pointer);

  /**
   * @return the stored integer as a long.
   * Note: Asserts isInt64().
   */
  long getInt64()

  {
    return getInt64(pointer);
  }

  private native long getInt64(long pointer);

  /**
   * @return true if the term is an integer that fits within unsigned 64 bits.
   */
  boolean isUInt64()

  {
    return isUInt64(pointer);
  }

  private native boolean isUInt64(long pointer);

  /**
   * @return the stored integer as a long.
   * Note: Asserts isUInt64().
   */
  long getUInt64()
  {
    return getUInt64(pointer);
  }

  private native long getUInt64(long pointer);

  /**
   * @return true if the term is an integer.
   */
  boolean isInteger()
  {
    return isInteger(pointer);
  }

  private native boolean isInteger(long pointer);

  /**
   * @return the stored integer in (decimal) string representation.
   * Note: Asserts isInteger().
   */
  String getInteger()
  {
    return getInteger(pointer);
  }

  private native String getInteger(long pointer);

  /**
   * @return true if the term is a string constant.
   */
  boolean isString()
  {
    return isString(pointer);
  }

  private native boolean isString(long pointer);

  /**
   * @return the stored string constant.
   * <p>
   * Note: This method is not to be confused with toString() which returns the
   * term in some string representation, whatever data it may hold.
   * Asserts isString().
   */
  String getString()
  {
    return getString(pointer);
  }

  private native String getString(long pointer);
}