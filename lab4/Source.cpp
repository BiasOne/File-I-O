#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

void findMinAndMAxPrices();
void findMinAndMAxPieces();
void findName();
void findTheme();
void printMaxPrice();
void printMinPrice();
void printMaxPiece();
void printMinPiece();
void readAndWrite();
void AveragePrice();
void AveragePieces();
void BuyItAll();
void AverageMiniFigs();
void printMaxMiniFigs();


vector<string> NumberVect;
vector<int> MinifigsVect;
vector<int> PiecesVect;
vector<double> USPriceVect;
vector<string> NameVect;
vector<string> ThemeVect;

ifstream legoFiles;

int pricesMaxIndex;
int pricesMinIndex;
int piecesMaxIndex;
int piecesMinIndex;
int miniFigsMaxIndex;
int miniFigsMinIndex;


int main()
{	
	cout << fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	if (option == 1)
	{		
		legoFiles.open("lego1.csv");
		readAndWrite();		
	}
	else if (option == 2)
	{		
		legoFiles.open("lego2.csv");
		readAndWrite();		
	}
	else if (option == 3)
	{		
		legoFiles.open("lego3.csv");
		readAndWrite();		
	}
	else if (option == 4)
	{
		legoFiles.open("lego1.csv");
		readAndWrite();
		legoFiles.open("lego2.csv");
		readAndWrite();		
		legoFiles.open("lego3.csv");
		readAndWrite();		
	}
	else 
	{
		cout << "Invalid input" << endl;
	}
	
	cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;
	cout << endl;	
	int choice;
	cin >> choice;
	cin.get();  // Clear newline character for any later input
	
	if (choice == 1)
	{	
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		cout << "The most expensive set is: " << endl;
		printMaxPrice();
	}
	else if (choice == 2)
	{
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		cout << "The set with the highest parts count: " << endl;
		printMaxPiece();
	}
	else if (choice == 3)
	{			
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		findName();		
	}
	else if (choice == 4)
	{
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		findTheme();
	}
	else if (choice == 5)
	{
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		AveragePieces();			
	}
	else if (choice == 6)
	{	 
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		AveragePrice();
		cout << "Least expensive set: " << endl;
		printMinPrice();
		cout << "Most expensive set : " << endl;
		printMaxPrice();		
	}
	else if (choice == 7)
	{
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		AverageMiniFigs();		
		cout << "Set with the most minifigures:" << endl;
		printMaxMiniFigs();
	}
	else if (choice == 8)
	{	
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		BuyItAll();
	}
	else if (choice == 0)
	{	
		cout << "Total number of sets: " << USPriceVect.size() << endl;
		cout << endl;
		exit(1);
	}

	return 0;
}
void readAndWrite()
{	
	string Number;
	string Minifigs;
	string Pieces;
	string USPrice;
	string Name;
	string Theme;		
	
	if (legoFiles.fail())
	{
		throw runtime_error("An error has occurred. File not loaded");
		exit(1);
	}
	else
	{
		if (legoFiles.is_open())
		{
			string dummyLine;
			getline(legoFiles, dummyLine);

			while (!legoFiles.eof())
			{
				getline(legoFiles, Number, ',');
				NumberVect.push_back(Number);
				getline(legoFiles, Theme, ',');
				ThemeVect.push_back(Theme);
				getline(legoFiles, Name, ',');
				NameVect.push_back(Name);
				getline(legoFiles, Minifigs, ',');
				MinifigsVect.push_back(atoi(Minifigs.c_str()));
				getline(legoFiles, Pieces, ',');
				PiecesVect.push_back(atoi(Pieces.c_str()));
				getline(legoFiles, USPrice);
				USPriceVect.push_back(atof(USPrice.c_str()));				
			}
		}
	}	
	legoFiles.close();	
}

void findName()
{	
	string userInput;
	int tempCount = 0;

	getline(cin, userInput);		

	for (unsigned int i = 0; i < NameVect.size(); i++)
	{
		stringstream tempVect;
		string temp;
		string noSpaces = "";
		tempVect << NameVect[i];
		
		while (!tempVect.eof())
		{
			tempVect >> temp;
			noSpaces= noSpaces + temp;			
		}
		
		if(noSpaces.find(userInput) !=string::npos)
		{	
			tempCount++;
			if (tempCount == 1) 
			{
				cout << "Sets matching \"" << userInput << "\": " << endl;
			}
			cout << NumberVect[i] << " " << NameVect[i] << " $" << USPriceVect[i] << endl;			
		}		
	}
	if (tempCount == 0)
	{
		cout << "No sets found matching that search term" << endl;
	}
	
}

void findTheme()
{
	string userInput;
	
	getline(cin, userInput);

	cout << "Sets matching \"" << userInput << "\": " << endl;

	for (unsigned int i = 0; i < ThemeVect.size(); i++)
	{		
		if (ThemeVect[i] == userInput)
		{			
			cout << NumberVect[i] << " " << NameVect[i] << " $" << USPriceVect[i] << endl;
		}				
	}
}


void findMinAndMAxPrices() 
{	
	double highTemp = USPriceVect[1];
	double lowTemp = USPriceVect[1];
	for (unsigned int i = 0; i < USPriceVect.size(); i++)
	{		
		if (highTemp < USPriceVect[i])
		{
			highTemp = USPriceVect[i];
			pricesMaxIndex = i;
		}

		if (lowTemp > USPriceVect[i])
		{
			lowTemp = USPriceVect[i];
			pricesMinIndex = i;
		}
	}
}

void findMinAndMAxPieces()
{
	int mostPieces = PiecesVect[1];
	int leastPieces = PiecesVect[1];
	for (unsigned int i = 0; i < PiecesVect.size(); i++)
	{
		if (mostPieces < PiecesVect[i])
		{
			mostPieces = PiecesVect[i];
			piecesMaxIndex= i;
		}
		if (leastPieces>  PiecesVect[i])
		{
			leastPieces = PiecesVect[i];
			piecesMinIndex = i;
		}
	}
}

void findMinAndMAxMiniFigs()
{
	int mostMiniFigs = MinifigsVect[1];
	int leastMiniFigs = MinifigsVect[1];
	for (unsigned int i = 0; i < MinifigsVect.size(); i++)
	{
		if (mostMiniFigs < MinifigsVect[i])
		{
			mostMiniFigs = MinifigsVect[i];
			miniFigsMaxIndex = i;
		}
		if (leastMiniFigs> MinifigsVect[i])
		{
			leastMiniFigs = MinifigsVect[i];
			miniFigsMinIndex = i;
		}
	}
}

void printMaxMiniFigs()
{
	findMinAndMAxMiniFigs();

	cout << "Name: " << NameVect[miniFigsMaxIndex] << endl;
	cout << "Number: " << NumberVect[miniFigsMaxIndex] << endl;
	cout << "Theme: " << ThemeVect[miniFigsMaxIndex] << endl;
	cout << "Price: $" << USPriceVect[miniFigsMaxIndex] << endl;
	cout << "Minifigures: " << MinifigsVect[miniFigsMaxIndex] << endl;
	cout << "Piece count: " << PiecesVect[miniFigsMaxIndex] << endl;
	cout << endl;
}

void printMaxPiece() 
{
	
	findMinAndMAxPieces();	
	
	cout << "Name: " << NameVect[piecesMaxIndex] << endl;
	cout << "Number: " << NumberVect[piecesMaxIndex] << endl;
	cout << "Theme: " << ThemeVect[piecesMaxIndex] << endl;
	cout << "Price: $" << USPriceVect[piecesMaxIndex] << endl;
	cout << "Minifigures: " << MinifigsVect[piecesMaxIndex] << endl;
	cout << "Piece count: " << PiecesVect[piecesMaxIndex] << endl;
	cout << endl;
}

void printMinPiece()
{
	findMinAndMAxPieces();	
	
	cout << "Name: " << NameVect[piecesMinIndex] << endl;
	cout << "Number: " << NumberVect[piecesMinIndex] << endl;
	cout << "Theme: " << ThemeVect[piecesMinIndex] << endl;
	cout << "Price: $" << USPriceVect[piecesMinIndex] << endl;
	cout << "Minifigures: " << MinifigsVect[piecesMinIndex] << endl;
	cout << "Piece count: " << PiecesVect[piecesMinIndex] << endl;
	cout << endl;
}

void printMinPrice() 
{
	findMinAndMAxPrices();	
	
	cout << "Name: " << NameVect[pricesMinIndex] << endl;
	cout << "Number: " << NumberVect[pricesMinIndex] << endl;
	cout << "Theme: " << ThemeVect[pricesMinIndex] << endl;
	cout << "Price: $" << USPriceVect[pricesMinIndex] << endl;
	cout << "Minifigures: " << MinifigsVect[pricesMinIndex] << endl;
	cout << "Piece count: " << PiecesVect[pricesMinIndex] << endl;
	cout << endl;
}

void printMaxPrice()
{	
	findMinAndMAxPrices();	
	
	cout << "Name: " << NameVect[pricesMaxIndex] << endl;
	cout << "Number: " << NumberVect[pricesMaxIndex] << endl;
	cout << "Theme: " << ThemeVect[pricesMaxIndex] << endl;
	cout << "Price: $" << USPriceVect[pricesMaxIndex] << endl;
	cout << "Minifigures: " << MinifigsVect[pricesMaxIndex] << endl;
	cout << "Piece count: " << PiecesVect[pricesMaxIndex] << endl;
	cout << endl;
}

void AveragePrice()
{
	double sum=0;
	for (unsigned int i = 0; i < USPriceVect.size(); i++)
	{
		sum +=  USPriceVect[i];
	}
	sum = sum / USPriceVect.size();
	cout << "Average price for " << PiecesVect.size() << " sets: $" << sum << endl;
}

void AveragePieces()
{
	int sum = 0;
	for (unsigned int i = 0; i < PiecesVect.size(); i++)
	{
		sum += PiecesVect[i];
	}
	sum = sum / PiecesVect.size();
	cout << "Average part count for " << PiecesVect.size() << " sets: " << sum << endl;

}

void AverageMiniFigs()
{
	int sum = 0;
	for (unsigned int i = 0; i < MinifigsVect.size(); i++)
	{
		sum += MinifigsVect[i];
	}
	sum = sum / MinifigsVect.size();
	cout << "Average number of minifigures: " << sum << endl;

}

void BuyItAll()
{
	
	double sumForAll = 0;
	int sumPieces=0;
	int sumMiniFig = 0;

	for (unsigned int i = 0; i < USPriceVect.size(); i++)
	{
		sumForAll += USPriceVect[i];
		sumPieces += PiecesVect[i];
		sumMiniFig += MinifigsVect[i];
				
	}
	cout << "If you bought one of everything..." << endl;
	cout << "It would cost: $" << sumForAll << endl;
	cout << "You would have " << sumPieces << " pieces in your collection" << endl;
	cout << "You would have an army of " << sumMiniFig << "minifigures!" << endl;

}





