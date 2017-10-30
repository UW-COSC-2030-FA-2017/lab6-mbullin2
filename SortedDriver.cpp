// SortedDriver.cpp
// Michael Bullinger
// October 29, 2017




#include "RandomUtilities.h"

#include "ContainerPrinting.h"

#include "winTimer.h"

#include <list>

#include <iostream>

#include <vector>

#include <algorithm>





using namespace std;





// post: a sorted vector of listSize random doubles from

//         the range minNum to maxNum has been returned.

vector<double>

getNums(size_t listSize, double minNum, double maxNum)

{

	vector<double> theList;

	for (size_t i = 0; i < listSize; ++i)

	{

		theList.push_back(randReal(minNum, maxNum));

	}



	sort(begin(theList), end(theList));



	return theList;

}





// post: a sorted list of numWords words of length

//         wordLength with characters chosen randomly from

//         alphabet has been returned.

list<string>

getWords(size_t numWords, size_t wordLength, string alphabet)

{

	list<string> theWords;

	for (size_t i = 0; i < numWords; ++i)

	{

		string word;

		for (size_t j = 0; j < wordLength; ++j)

		{

			word += alphabet.at(randInt(0, alphabet.size()));

		}

		theWords.push_back(word);

	}



	theWords.sort();



	return theWords;

}





// pre:  number is not empty; 

//       number is sorted from smallest to largest

// post: The most isolated entry in number has been returned

// mostIsolated function changed by Michael Bullinger on October 23, 2017
double mostIsolated(vector<double> & number)

{
	double temp = number[0];
	double temp2 = 0;
	double temp3 = 0;
	double temp4 = 0;
	double temp5 = 0;
	for (int i = 1; i <= number.size()-1; i++)
	{
		temp2 = ((number[i] - number[i-1]));
		if (i < number.size()-1)
		{
			temp4 = (number[i + 1] - number[i]);
		}
		else
		{
			temp4 = 0;
		}
		temp5 = temp2 + temp4;
		if ((temp5 > temp3))
		{
			temp3 = temp5;
			temp = number[i];
		}
	}
	return temp;

}




// pre:  A and B are sorted.

// post: The number of strings in A that do not occur in B

//         has been returned.

int

unmatched(list<string> & A, list<string> & B)

{
	int temp = 0;
	list<string>::iterator listA = A.begin();
	list<string>::iterator listB = B.begin();
	while (listA != A.end() && listB != B.end())
	{
		if (*listA == *listB)
		{
			listA++;
		}
		else if (*listA < *listB)
		{
			*listA++;
			temp++;
		}
		else if (*listA > *listB)
		{
			listB++;
		}
	}
	return temp;
}


int

main()

{

	cout << "Find the most isolated number" << endl

		<< "-----------------------------" << endl << endl;

	while (true)

	{

		cout << "Enter size for numbers: ";

		int n = 0;

		cin >> n;

		if (n <= 0)

			break;

		cout << "Enter seed for rand: ";

		unsigned int seed;

		cin >> seed;

		srand(seed);



		// Construct a sorted list of numbers

		Timer get;

		get.start();

		vector<double> numbers = getNums(n, -n, n);

		get.stop();

		cout << "Constructed in " << get() << " seconds"

			<< endl;



		if (n < 10)

			cout << numbers << endl << endl;



		// Report a most isolated isolated number

		Timer time;

		time.start();

		double isolated = mostIsolated(numbers);

		time.stop();

		cout << "The most isolated number is "

			<< isolated << endl

			<< "calculated in " << time() << " seconds"

			<< endl << endl;

	}





	cout << endl << endl;

	cout << "Count the unmatched words" << endl

		<< "-------------------------" << endl << endl;

	while (true)

	{

		cout << "Enter size for words lists: ";

		int n = 0;

		cin >> n;

		if (n <= 0)

			break;

		cout << "Enter word length: ";

		int wordSize;

		cin >> wordSize;

		cout << "Enter alphabet: ";

		string alphabet;

		cin >> alphabet;



		cout << "Enter seed for rand: ";

		unsigned int seed;

		cin >> seed;

		srand(seed);



		// Construct two sorted vectors of words

		Timer get;

		get.start();

		list<string> A = getWords(n, wordSize, alphabet);

		list<string> B = getWords(n, wordSize, alphabet);

		get.stop();

		cout << "Constructed in " << get() << " seconds"

			<< endl;



		if (wordSize * n < 60)

		{

			cout << "A is: " << A << endl

				<< "B is: " << B << endl;

		}



		// Report the number of words in the first sorted list

		//   that are not in the second sorted list

		Timer time;

		time.start();

		int count = unmatched(A, B);

		time.stop();

		cout << count

			<< " words in A were not in B" << endl

			<< "calculated in " << time() << " seconds"

			<< endl << endl;

	}



	return 0;

}