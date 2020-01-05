#include "dependencies/easyPassDef.hpp"

using namespace easyPassDefinitions;

const char * systemException::what () const throw () {

  return processMessage.c_str();
}

template <class Type> bool validationRules::isNegative (Type parameter) {

    if (parameter < 0) return true;

    return false;
}

template <class Type> bool validationRules::isZero (Type parameter) {

    if (parameter == 0) return true;

    return false;
}

template <class Type> bool validationRules::isNegativeOrZero (Type parameter) {

    if (parameter <= 0) return true;

    return false;
}

template <class Type> bool validationRules::isEqual (limits<Type> limitsObject) {

    if (limitsObject.minimLimit == limitsObject.maximLimit) return true;

    return false;
}

template <class Type> Type randomGenerator::numberGenerator (limits<Type> limitsObject) {

  srand(time(0));

  Type generatedNumber = (fmod(rand(), (limitsObject.maximLimit - limitsObject.minimLimit + 0.5))) + limitsObject.minimLimit;

  return generatedNumber;
}

template <class Type> Type randomGenerator::staticNumberGenerator (limits<Type> limitsObject) {

  std::random_device randomDevice;

  std::mt19937 gen(randomDevice());

  std::uniform_int_distribution<int> distribution(limitsObject.minimLimit, limitsObject.maximLimit);

  return distribution(gen);
}

template <class Type> void randomGenerator::oneDimensionalArrayGenerator (oneDimensionalArrayType<Type> ODAObject, limits<Type> limitsObject) {

  if (isZero(ODAObject.length)) throw systemException (__error__.oneDimensionalArrayGeneratorZeroError);
  else if (isNegative(ODAObject.length)) throw systemException (__error__.oneDimensionalArrayGeneratorNegativeError);

  srand (time(NULL));

  for (size_t iterator = ODAObject.startPoint; iterator < ODAObject.length + ODAObject.endPoint; iterator++)
    ODAObject.oneDimensionalArray[iterator] = (rand() % (limitsObject.maximLimit - limitsObject.minimLimit + 1)) + limitsObject.minimLimit;
}

template <class Type> void randomGenerator::matrixGenerator (matrixType<Type> MTObject, limits<Type> limitsObject) {

  if (isZero(MTObject.line) && isZero(MTObject.column)) throw systemException (__error__.matrixGeneratorZeroError);
  else if (isNegative(MTObject.line) && isNegative(MTObject.column)) throw systemException (__error__.matrixGeneratorNegativeError);

  srand (time(NULL));

  for (size_t iterator = MTObject.startLinePoint; iterator < MTObject.line + MTObject.endLinePoint; iterator++)
    for (size_t jiterator = MTObject.endColumnPoint; jiterator < MTObject.column + MTObject.endColumnPoint; jiterator++)
      MTObject.matrix[iterator][jiterator] = (rand() % (limitsObject.maximLimit - limitsObject.minimLimit + 1)) + limitsObject.minimLimit;
}

template <class Type> void checkAndSupport::readOneDimensionalArray (oneDimensionalArrayType<Type> ODAObject) {

  std::cin >> ODAObject.length;

  if (isZero(ODAObject.length)) throw systemException (__error__.readOneDimensionalArrayZeroError);
  else if (isNegative(ODAObject.length)) throw systemException (__error__.readOneDimensionalArrayNegativeError);

  for (size_t iterator = ODAObject.startPoint; iterator < ODAObject.length + ODAObject.endPoint; iterator++)
    std::cin >> ODAObject.oneDimensionalArray[iterator];
}

template <class Type> void checkAndSupport::putsOneDimensionalArray (oneDimensionalArrayType<Type> ODAObject) {

  if (isZero(ODAObject.length)) throw systemException (__error__.putsOneDimensionalArrayZeroError);
  else if (isNegative(ODAObject.length)) throw systemException (__error__.putsOneDimensionalArrayNegativeError);

  for (size_t iterator = ODAObject.startPoint; iterator < ODAObject.length + ODAObject.endPoint; iterator++)
    std::cout << ODAObject.oneDimensionalArray[iterator] << " ";
}

template <class Type> void checkAndSupport::readMatrix (matrixType<Type> MTObject) {

  if (isZero(MTObject.line) && isZero(MTObject.column)) throw systemException (__error__.readMatrixZeroError);
  else if (isNegative(MTObject.line) && isNegative(MTObject.column)) throw systemException (__error__.readMatrixNegativeError);

  for (size_t iterator = MTObject.startLinePoint; iterator < MTObject.line + MTObject.endLinePoint; iterator++)
      for (size_t jiterator = MTObject.startColumnPoint; jiterator < MTObject.column + MTObject.endColumnPoint; jiterator++)
        std::cin >> MTObject.matrix[iterator][jiterator];
}

template <class Type> void checkAndSupport::putsMatrix (matrixType<Type> MTObject) {

  if (isZero(MTObject.line) && isZero(MTObject.column)) throw systemException (__error__.putsMatrixZeroError);
  else if (isNegative(MTObject.line) && isNegative(MTObject.column)) throw systemException (__error__.putsMatrixNegativeError);

  for (size_t iterator = MTObject.startLinePoint; iterator < MTObject.line + MTObject.endLinePoint; iterator++) {
      for (size_t jiterator = MTObject.startColumnPoint; jiterator < MTObject.column + MTObject.endColumnPoint; jiterator++)
        std::cout << MTObject.matrix[iterator][jiterator] << " ";
      std::cout <<'\n';
  }
}

template <class Type> void checkAndSupport::readTree (binaryTreeType<Type> *& root) {

  Type value;

  std::cin >> value;

  if (value != 0) {

    root = new binaryTreeType<int>;
    root->value = value;

    createTree(root->leftLeaf);
    createTree(root->rightLeaf);

  } else root = NULL;
}

template <class Type> void checkAndSupport::putsTree (binaryTreeType<Type> * root) {

  if (root != NULL) {

    std::cout << root->value << " ";
    RootLeftRight(root->leftLeaf);
    RootLeftRight(root->rightLeaf);
  }
}

template <class Type> bool assertions::assertPrimitiveDataTypes (limits<Type> limitsObject) {

  if (limitsObject.minimLimit == limitsObject.maximLimit) return true;

  std::cerr << "Get " << limitsObject.maximLimit << ", Expected " << limitsObject.minimLimit << " ";

  return false;
}

template <class Type> bool assertions::assertOneDimensionalArrays (oneDimensionalArrayType<Type> ODAObjectOne, oneDimensionalArrayType<Type> ODAObjectTwo) {

  limits<Type> lengths (ODAObjectOne.length, ODAObjectTwo.length);
  limits<Type> startPoints (ODAObjectOne.startPoint, ODAObjectTwo.startPoint);
  limits<Type> endPoints (ODAObjectOne.endPoint, ODAObjectTwo.endPoint);

  if (!isEqual(lengths)) throw systemException ("Can't work with unequal lengths");
  if (!isEqual(startPoints)) throw systemException ("Can't work with unequal start points");
  if (!isEqual(endPoints)) throw systemException ("Can't work with unequal end points");

  for (size_t iterator = ODAObjectOne.startPoint; iterator < ODAObjectOne.length + ODAObjectOne.endPoint; iterator++)
    if (ODAObjectOne[iterator] != ODAObjectTwo[iterator]) return false;

  return true;
}

template <class Type> bool assertions::assertMatrix (matrixType<Type> MTObjectOne, matrixType<Type> MTObjectTwo) {

  limits<Type> lines (MTObjectOne.line, MTObjectTwo.line);
  limits<Type> columns (MTObjectOne.column, MTObjectTwo.column);
  limits<Type> startLinePoints (MTObjectOne.startLinePoint, MTObjectTwo.startLinePoint);
  limits<Type> endLinePoints (MTObjectOne.endLinePoint, MTObjectTwo.endLinePoint);
  limits<Type> startColumnPoints (MTObjectOne.startLinePoint, MTObjectTwo.startColumnPoint);
  limits<Type> endColumnPoints (MTObjectOne.endLinePoint, MTObjectTwo.endLinePoint);

  if (!isEqual(lines)) throw systemException ("Can't work with unequal lines");
  if (!isEqual(columns)) throw systemException ("Can't work with unequal columns");
  if (!isEqual(startLinePoints)) throw systemException ("Can't work with unequal start line points");
  if (!isEqual(endLinePoints)) throw systemException ("Can't work with unequal end line points");
  if (!isEqual(startColumnPoints)) throw systemException ("Can't work with unequal start column points");
  if (!isEqual(endColumnPoints)) throw systemException ("Can't work with unequal end column points");

  for (size_t iterator = MTObjectOne.startLinePoint; iterator < MTObjectOne.line + MTObjectOne.endLinePoint; iterator++)
    for (size_t jiterator = MTObjectOne.startColumnPoint; jiterator < MTObjectOne.column + MTObjectOne.endColumnPoint; jiterator++)
      if (MTObjectOne[iterator][jiterator] != MTObjectTwo[iterator][jiterator]) return false;

  return true;
}

void assertions::countTest (char * testCase, bool testCasePassed) {

  if (testCasePassed) {

    passedCases++;

    std::cout << "Test case " << testCase;
    SetConsoleTextAttribute(HANDLE_CONSOLE, 2);
    std::cout << " passed" << '\n';
    SetConsoleTextAttribute(HANDLE_CONSOLE, 7);

  } else {

    failedCases++;

    std::cout << "Test case " << testCase;
    SetConsoleTextAttribute(HANDLE_CONSOLE, 4);
    std::cout << " failed" << '\n';
    SetConsoleTextAttribute(HANDLE_CONSOLE, 7);
  }
}

void assertions::getConclusion () {

  SetConsoleTextAttribute(HANDLE_CONSOLE, 2);

  std::cout << "\n==========================================================\n\n";
  std::cout << "Number of test cases passed " << passedCases << '\n';

  if (failedCases > 0) SetConsoleTextAttribute(HANDLE_CONSOLE, 4);

  std::cout << "Number of test cases failed " << failedCases << '\n';

  SetConsoleTextAttribute(HANDLE_CONSOLE, 2);

  std::cout << "Number of test cases " << passedCases + failedCases << '\n';
  std::cout << '\n';

  SetConsoleTextAttribute(HANDLE_CONSOLE, 7);
}
