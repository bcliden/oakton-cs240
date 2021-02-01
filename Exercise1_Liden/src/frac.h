class FractionType
{
public:
  void Initialize(int numerator, int denominator);
  // Function: Initialize the fraction
  // Pre:  None
  // Post: Fraction is initialized
  int NumeratorIs();
  // Function: Returns the value of the numerator
  // Pre:  Fraction has been initialized
  // Post: numerator is returned
  int DenominatorIs();
  // Function: Returns the value of the denominator
  // Pre:  Reaction has been initialized 
  // Post: denominator is returned
  bool IsZero();
  // Function: Determines if fraction is zero
  // Pre:  Fraction has been initialized
  // Post: Returns true if numerator is zero
  bool IsNotProper();
  // Function: Determines if fraction is a proper fraction
  // Pre:  Fraction has been initialized
  // Post: Returns true if fraction is greater than one
  int ConvertToProper();
  // Function: Converts the fraction to a whole number and a 
  //       fractional part
  // Pre:  Fraction has been initialized, is in reduced form, and  
  //       is not a proper fraction
  // Post: Returns whole number
  //       Remaining fraction is original fraction minus the
  //       whole number; fraction is in reduced form 


  /**
   * BELOW: Additions by Benjamin Liden for
   * 	Prof. Temesvari's CS240 Ex. 1
   *
   * 	- Operator Overloads
   * 		- (+)
   * 		- (-)
   * 		- (*)
   * 		- (/)
   * 	- Extra Credit
   * 		- reduce
   * 		- print
   */

  FractionType operator+(const FractionType& addend);
  FractionType operator-(const FractionType& minuend);
  FractionType operator/(const FractionType& divisor);
  FractionType operator*(const FractionType& multiplier);
  void reduce();
  void print();

private:
  int num;
  int denom;
};

