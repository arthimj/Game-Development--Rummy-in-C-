#include <iostream>
#include <vector>
#include <string> 
#include <algorithm>
#include <ctime>
#include<stdlib.h>
#include<fstream>
using namespace std;
#define DECK_SIZE 52
#define CARDS_PER_PLAYER 7
#define NUMBER_OF_RANKS 13
#define NUMBER_OF_SUITS 4
#define RANK_OFFSET 2
#define ONE 1
#define TEN "10"
#define JACK "11"
#define QUEEN "12"
#define KING "13"
#define ACE "14"
#define DIAMOND "-D"
#define SPADE "-S"
#define CLUB "-C"
#define HEART "-H"
#define PICK_FROM_DECK -1
#define YES 1
#define TERMINATE_NUMBER -1
#define RANK_OFFSET 2
#define TWO_THROUGH_NINE_PTS 5
#define TEN_THROUGH_KING_PTS 10
#define ACE_POINTS 15
#define EMPTY 0
#define NUMBER_TO_CHECK 2
#define NEXT 1
#define NEXT_NEXT 2
#define DASH "-"
#define WINNING_SCORE 500
#define TWO_THROUGH_NINE_POINTS 5
#define TEN_THROUGH_KING_POINTS 10
#define ACE_POINTS 15
#define CARDS_DEALT 11
#define DECK_SIZE 52
#define EMPTY 0
#define TERMINATE_NUMBER -1
#define RANK_OFFSET 2
#define EVEN_ODD 2
#define YES 1

enum Rank
{
	Two, 
	Three, 
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

enum Suit
{
	D,
	H,
	S,
	C
};

class Cards
{
public:
	void InitializeDeck();
	void ShuffleDeck();
	void DisplayAvailableCards() const;
	string ReturnCard(const int& number) const;
		void PopOffCard();
	int GetDeckSize() const;
	int GetPickFromPileSize() const;
	void AdjustPickPile();
	string GetPickFromPileCard(const int& number) const;
	void InsertIntoPickFromPile(const string& card);
    void PopPickFromPileCard();
	string TopDeckCard () const;
private:
	vector<string> Deck;
	vector<string> PickFromPile;
};
class Player
{
public:
	Player(string name, int score = 0);
	virtual string GetName() const;
	virtual int GetScore() const;
	virtual int GetHandSize() const;
    virtual void CalculateScore();
	virtual string GetHandValue(const int& number) const;
	virtual void InsertIntoHand(const string& card);
	void DisplayHand() const;
	virtual int WhatDeckToPickFrom(const Cards& deck) const;
	virtual int WhatCardToDiscard () const;
	void OrganizeHand();
	virtual string ReturnCard (const int& number) const;
	virtual void PopCard (const int& number);
	virtual void DisplayMeldedCards () const;
	virtual void PopulateMeldedCards (const vector<int>& CardSpotsIWillMeld);
	virtual vector<int> SecondTimeMeld () const;
	virtual void ClearHandAndMeldedCards();
	vector<int> CardsToMeld() const;
	virtual void GamePlay (Cards& deck, const vector<string>& compsMeldedCards, const string& compsName);
	virtual void InsertFromPickFromPile (Cards& deck, const int& choice);
	virtual void DiscardCard (Cards& deck, const int& cardSpot);
	virtual vector<string> ReturnVectorOfMyMeldedCards () const;
	vector<int> RetrieveMeldSpots () const;

protected:
	string Name;
	int Score;
	vector<string> MeldedCards;
	vector<string> Hand;
};
class Computer: public Player
{
public:
	Computer(string name, int score=0) : Player(name,score)
	{
		Name = name;
		Score = score;
	}
virtual int WhatDeckToPickFrom(const Cards& deck) const;
virtual int WhatCardToDiscard () const;
	virtual void DisplayMeldedCards () const;
	virtual vector<int> SecondTimeMeld () const;
	void GamePlay (Cards& deck);
	int ConvertRank (const string& index) const;
	string RetrieveCardSuit (const string& index) const;
};
void Cards::InitializeDeck()
{
	for (int r = 0; r < NUMBER_OF_RANKS; r++)
	{
		for (int s = 0; s < NUMBER_OF_SUITS; s++)
		{
			string card;
			Rank cardRank = Rank(r);
			switch (cardRank)
			{
			case(Two):
			case(Three):
			case(Four):
			case(Five):
			case(Six):
			case(Seven):
			case(Eight):
			case(Nine):
				card += cardRank + RANK_OFFSET + '0';
				break;
			case(Ten):
				card = TEN;
				break;
			case(Jack):
				card = JACK;
				break;
			case(Queen):
				card = QUEEN;
				break;
			case(King):
				card = KING;
				break;
			case(Ace):
				card = ACE;
			}
			
			Suit cardSuit = Suit(s);
			switch (cardSuit)
			{
			case(D):
				card.append(DIAMOND);
				break;
			case(H):
				card.append(HEART);
				break;
			case(S):
				card.append(SPADE);
				break;
			case(C):
				card.append(CLUB);
			}
			Deck.push_back(card);
		}
	}
}

void Cards::ShuffleDeck()
{
	srand ( unsigned ( time(0) ) );
	random_shuffle(Deck.begin(),Deck.end());
}

void Cards::DisplayAvailableCards() const
{
	for (unsigned int i = 0; i < PickFromPile.size(); i++)
		cout << PickFromPile[i] << " ";
	cout << "\n\n";
}

string Cards::ReturnCard(const int& number) const
{
	return Deck[number];
}

void Cards::PopOffCard()
{
	Deck.pop_back();
}

int Cards::GetDeckSize() const
{
	return Deck.size();
}

void Cards::AdjustPickPile()
{
	int number = Deck.size() - ONE;
	string copy = Deck[number];
	Deck.pop_back();
	PickFromPile.push_back(copy);
}

int Cards::GetPickFromPileSize() const
{
	return PickFromPile.size();
}

string Cards::GetPickFromPileCard(const int& number) const
{
	return PickFromPile[number];
}

void Cards::InsertIntoPickFromPile(const string& card)
{
	PickFromPile.push_back(card);
}

void Cards::PopPickFromPileCard()
{
	PickFromPile.pop_back();
}

string Cards::TopDeckCard () const
{
	return Deck[GetDeckSize()-ONE];
}

Player::Player(string name, int score)
{
	Name = name;
	Score = score;
}

string Player::GetName() const
{
	return Name;
}

int Player::GetScore() const
{
	
	return Score;
}

void Player::CalculateScore()
{
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
	{
		string cardRank = MeldedCards[i].substr(0,MeldedCards[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < Rank(8) + RANK_OFFSET)
			Score += TWO_THROUGH_NINE_PTS;
		else if (value >= Rank(8) + RANK_OFFSET && value <= Rank(11) + RANK_OFFSET)
			Score += TEN_THROUGH_KING_PTS;
		else 
			Score += ACE_POINTS;
	}
	
 	for (unsigned int i = 0; i < Hand.size(); i++)
	{
		string cardRank = Hand[i].substr(0,Hand[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < Rank(8) + RANK_OFFSET)
			Score -= TWO_THROUGH_NINE_PTS;
		else if (value >= Rank(8) + RANK_OFFSET && value <= Rank(11) + RANK_OFFSET)
			Score -= TEN_THROUGH_KING_PTS;
		else 
			Score -= ACE_POINTS;
	}
}

int Player::GetHandSize() const
{
	return Hand.size();
}

string Player::GetHandValue(const int& number) const
{
	return Hand[number];
}

void Player::InsertIntoHand(const string& card)
{
	Hand.push_back(card);
}

void Player::DisplayHand() const
{
	cout << "Your hand:\n";
	for (unsigned int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n";
}

int Player::WhatDeckToPickFrom(const Cards& deck) const
{
	int choice;
	cout << "Would you like to pick up from the pick up pile? ";
	cin >> choice;
if (choice == YES)
	{
		int firstLocationFromDeck;
		
		cout << "\nWhat is the bottom card location you wish to pick up from the deck? ";
		cin >> firstLocationFromDeck;

		while (firstLocationFromDeck < 0 || firstLocationFromDeck >= deck.GetPickFromPileSize())
		{
			cout << "Invalid location. Try again: ";
			cin >> firstLocationFromDeck;
		}

		return firstLocationFromDeck;		
	} else
	{
		return PICK_FROM_DECK;
	}
}

int Player::WhatCardToDiscard () const
{
	int cardToDiscard;

	cout << "Which card would you like to discard? ";
	cin >> cardToDiscard;

	while (cardToDiscard < EMPTY || cardToDiscard >= GetHandSize())
	{
		cout << "That's an invalid indice. Try again! ";
		cin >> cardToDiscard;
	}

	return cardToDiscard;
}

void Player::OrganizeHand()
{
	sort(Hand.begin(),Hand.end());
}

string Player::ReturnCard (const int& number) const
{
	return Hand[number];
}

void Player::PopCard (const int& number)
{
	Hand.erase(Hand.begin() + number);
}


void Player::DisplayMeldedCards () const
{
	cout << "Your melded cards: \n";
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
	{
		cout << MeldedCards[i];
		if (i < MeldedCards.size() - 1)
			cout << " ";
	}
	cout << "\n\n";
}


void Player::PopulateMeldedCards (const vector<int>& CardSpotsIWillMeld)
{
	for (unsigned int i = 0; i < CardSpotsIWillMeld.size(); i++)
	{
		int locale = CardSpotsIWillMeld[i];
		string card = ReturnCard(locale);
		MeldedCards.push_back(card);	
		PopCard(locale);
	}
	sort(MeldedCards.begin(),MeldedCards.end());
}

vector<int> Player::SecondTimeMeld () const
{
	int answer;
	cout << "\nWould you like to meld? ";
	cin >> answer;
	
	vector<int> cardsToMeld;

	if (answer == YES)
		cardsToMeld = RetrieveMeldSpots();
	
	return cardsToMeld;
}

void Player::ClearHandAndMeldedCards()
{
	Hand.clear();
	MeldedCards.clear();
}

vector<int> Player::CardsToMeld() const
{
	vector<int> cardsIWillMeld;
	cout << "\n";
	DisplayHand();
		
	cardsIWillMeld = RetrieveMeldSpots();

	return cardsIWillMeld;
}

void Player::GamePlay (Cards& deck, const vector<string>& compsMeldedCards, const string& compsName)
{
	cout << "Your turn!\n\n";
	cout << "Current pick up pile:\n";	
	deck.DisplayAvailableCards();		
	OrganizeHand();
	DisplayHand();
	cout << "\n";
	DisplayMeldedCards();
	cout << compsName << "'s melded cards: \n";
	for (unsigned int i = 0; i < compsMeldedCards.size(); i++)
		cout << compsMeldedCards[i] << " ";
	cout << "\n\n";
	int choice = WhatDeckToPickFrom(deck);
	if (choice != PICK_FROM_DECK)	
	{
		InsertFromPickFromPile(deck,choice);
			OrganizeHand();
		PopulateMeldedCards(CardsToMeld());

		cout << "\n";
		DisplayMeldedCards();
	} 
	else
	 {
	InsertIntoHand(deck.TopDeckCard());
		deck.PopOffCard();
	if (GetHandSize() > EMPTY)
		{
			cout << "\n";
			OrganizeHand();
			DisplayHand();
			PopulateMeldedCards(SecondTimeMeld());
		}
	}
	cout << "\n";
	if(GetHandSize() > EMPTY)
	{
		OrganizeHand();
		DisplayHand();
		cout << "\n";
		DiscardCard(deck,WhatCardToDiscard());
	}
	cout << "\n";
}

void Player::InsertFromPickFromPile (Cards& deck, const int& choice)
{
	for (int i = deck.GetPickFromPileSize()-NEXT; i >= choice; i--)
	{
		InsertIntoHand(deck.GetPickFromPileCard(i));	
				deck.PopPickFromPileCard();						
	}
}

void Player::DiscardCard (Cards& deck, const int& cardSpot)
{
	deck.InsertIntoPickFromPile(ReturnCard(cardSpot));	
	PopCard(cardSpot);									
}

vector<string> Player::ReturnVectorOfMyMeldedCards () const
{
	return MeldedCards;
}

vector<int> Player::RetrieveMeldSpots () const
{
	vector<int> cardsToMeld;
	int location = EMPTY;

	cout << "\nWhich cards from your hand do you want to meld?\n";

	while (location != TERMINATE_NUMBER)
	{
		cin >> location;
		if (location != TERMINATE_NUMBER)
			cardsToMeld.push_back(location);
	}

	return cardsToMeld;
}
int Computer::WhatDeckToPickFrom(const Cards& deck) const
{
	int i = EMPTY; 
	while (i < GetHandSize() - 1)
	{
		int value1 = ConvertRank(Hand[i]);
		int value2 = ConvertRank(Hand[i+NEXT]);
      if (value1 == value2)
		{
			for (int j = 0; j < deck.GetPickFromPileSize(); j++)
			{
				int compareValue = ConvertRank(deck.GetPickFromPileCard(j));

				if (value1 == compareValue)
					return j;
			}
		}
		i++;
	}
return PICK_FROM_DECK;
}

int Computer::WhatCardToDiscard () const
{
	int compHandSize = GetHandSize();

	srand(time(NULL));

	int cardToDiscard = rand() % compHandSize;

	return cardToDiscard;
}

void Computer::DisplayMeldedCards () const
{
	cout << Name << "'s melded cards: \n";
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

vector<int> Computer::SecondTimeMeld () const
{
	vector<int> cardsCompWillMeld;
	unsigned int i = EMPTY; 
	while (i < Hand.size() - NUMBER_TO_CHECK)
	{
		int value1 = ConvertRank(Hand[i]);
		int value2 = ConvertRank(Hand[i+NEXT]);
		int value3 = ConvertRank(Hand[i+NEXT_NEXT]);
     	if (value1 == value2 && value1 == value3)
		{
			cardsCompWillMeld.push_back(i+NEXT_NEXT);
			cardsCompWillMeld.push_back(i+NEXT);
			cardsCompWillMeld.push_back(i);
				i = Hand.size() - NUMBER_TO_CHECK;
		} else
			i++;
	}
	if (cardsCompWillMeld.size() == EMPTY)
	{
		unsigned int j = EMPTY;
		while (j < Hand.size() - NUMBER_TO_CHECK)
		{
			int value1 = ConvertRank(Hand[j]);
			int value2 = ConvertRank(Hand[j+NEXT]);
			int value3 = ConvertRank(Hand[j+NEXT_NEXT]);
         	if (value3 == value2 + 1 && value2 == value1 + 1)
			{
				string cardSuit1 = RetrieveCardSuit(Hand[j]);
				string cardSuit2 = RetrieveCardSuit(Hand[j+NEXT]);
				string cardSuit3 = RetrieveCardSuit(Hand[j+NEXT_NEXT]);
						if (cardSuit1 == cardSuit2 && cardSuit2 == cardSuit3)
				{
					cardsCompWillMeld.push_back(j+NEXT_NEXT);
					cardsCompWillMeld.push_back(j+NEXT);
					cardsCompWillMeld.push_back(j);
					j = Hand.size() - NUMBER_TO_CHECK;
				} else
					j++;
			} else
				j++;
		}
	}

	return cardsCompWillMeld;
}

void Computer::GamePlay (Cards& deck)
{
	cout << Name << "'s turn!\n";
	
	OrganizeHand();
	int choice = WhatDeckToPickFrom(deck);

	if (choice != PICK_FROM_DECK)	
	{
		InsertFromPickFromPile(deck,choice);
			
		OrganizeHand();
	PopulateMeldedCards(SecondTimeMeld());

	} else {	
		InsertIntoHand(deck.TopDeckCard());
		deck.PopOffCard();
	}

	OrganizeHand();

	
	if(GetHandSize() > EMPTY)
		DiscardCard(deck,WhatCardToDiscard());

	cout << "\n";
}

int Computer::ConvertRank (const string& index) const
{
	string cardRank = index.substr(0,index.find(DASH));
		int value = atoi(cardRank.c_str());
		return value;
}

string Computer::RetrieveCardSuit (const string& index) const
{
	string suit = index.substr(index.find(DASH)+NEXT,index.size() - (index.find(DASH)+NEXT));
	return suit;
}
void outputIntro();
void outputEnding(Player& player, Computer& comp);
void dealDeck(Player& player, Computer& comp, Cards& deck, int count);
void ScoreOutput(Player& user, Computer& comp, int roundCount);

int main()
{
system("start song.mp3");
	outputIntro();
    string name;
	cout << "\nEnter your name: ";
	getline(cin, name);
	Player user(name);
    cout << "\nEnter a name for the computer: ";
	getline(cin,name);
	Computer comp(name);
	cout << "\n";
    unsigned int roundCount = EMPTY;
int p=0;
    while ( (user.GetScore() < WINNING_SCORE) && (comp.GetScore() < WINNING_SCORE) )
	{
		ScoreOutput(user,comp,roundCount);
		Cards deck;
		deck.InitializeDeck();
		deck.ShuffleDeck();
		user.ClearHandAndMeldedCards();
		comp.ClearHandAndMeldedCards();
        dealDeck(user,comp,deck,roundCount);
	     unsigned int count = roundCount;
        	while ( (user.GetHandSize() > EMPTY) && (comp.GetHandSize() > EMPTY) && (deck.GetDeckSize() > EMPTY) )
		{
					if (count % EVEN_ODD == EMPTY)	
				user.GamePlay(deck,comp.ReturnVectorOfMyMeldedCards(),comp.GetName());
			else						
				comp.GamePlay(deck);

			count++;
				//user.CalculateScore();
	            //comp.CalculateScore();
	           cout<<" if you want to quit press 1";
	           system("COLOR CF ");
	           int quit;
	           cin>>quit;
	           if(quit==1)
	           {cout<<"GAME OVER";
	           return 0;
			   }
	           system("COLOR 0F");
	           
				}
		roundCount++;

		int initialPlayerScore = user.GetScore();
		int initialCompScore = comp.GetScore();
		
	user.CalculateScore();
	comp.CalculateScore();

		cout << "Points scored this round:\n" << user.GetName() << ": " << user.GetScore() - initialPlayerScore << "\n" <<
			comp.GetName() << ": " << comp.GetScore() - initialCompScore << "\n\n";
cout<<"if you want to quit press 1";
		
	
		
	}
	
	outputEnding(user,comp);

	system("pause");
	return 0;
}


void outputIntro()
{
	cout << "Welcome to Rummy 500!\n";

	
	cout << "RULES OF THE GAME:\n" <<
		"It is you versus the computer.\n" <<
		"First player to " << WINNING_SCORE << " points wins.\n" <<
		"Each player is dealt " << CARDS_DEALT << " cards of a standard \n" <<
		DECK_SIZE << " card deck each hand.\n" <<
		"User (you) goes first; this alternates each hand.\n" <<
		"Players earn points by melding \ncards from their hand into the meld area.\n" <<
		"Players may meld a set of \ncards once they have at least 3 of a kind\n" <<
		"(ex: 3 " << Rank(5) << "s) or 3 in a row \nof the same suit (ex: 4,5,6 of spades).\n" <<
		"Each turns starts with picking \nup a card, and ends by discarding a card.\n" <<
		"The hand continues until \none player has used all of their cards.\n" <<
		"Points are tallied at the end of each hand.\n" <<
		"Point per card are as follows:\n" << 
		Rank(0) + RANK_OFFSET << " ... " << Rank(8) + RANK_OFFSET << " --> " << TWO_THROUGH_NINE_POINTS << " points\n" <<
		Rank(9) + RANK_OFFSET << " ... " << Rank(11) + RANK_OFFSET << " --> " << TEN_THROUGH_KING_POINTS << " points\n" <<
		Rank(12) + RANK_OFFSET << " --> " << ACE_POINTS << " points. " <<
		"New hands keep being dealt \nuntil a player has over " << WINNING_SCORE << " points.\n" <<
		"If both players end with over " << WINNING_SCORE << "\npoints, player with more points wins.\n" <<
		"When you are prompted for card \n" <<
		"locations, it is zero based. That is\n" <<
		"if you want the first card from your hand\n" <<
		"you would enter '" << EMPTY << "'. If choosing multiple cards\n" <<
		"use one space between numbers.\n" <<
		"The first letter or number is the rank\n" <<
		"and after the dash is the suit of the card\n" <<
		"H = Hearts, S = Spades, D = Diamonds, C = Clubs.\n" <<
		"Please not that the face cards will not be sorted in your hand,\n" <<
		"However, the non face cards will be sorted!\n" <<
		"You must meld at least one card when you pick\nit up from the pick up pile\n" <<
		YES << " means 'Yes' when asked yes/no questions.\nAnything else will be interpreted as a no.\n" <<
		"When melding cards, always tell which cards you \nwant to meld from your hand in decreasing location order.\n" <<
		"And when telling the computer these meld spots, \nterminate your entries with a " << TERMINATE_NUMBER << ".\n";
}

void outputEnding(Player& player, Computer& comp)
{
	ofstream myfile;
	myfile.open("rummy.txt",ios::out|ios::in|ios::binary);
	
	cout << "Final Score:\n" << player.GetName() << ": " << player.GetScore() << "\n" << comp.GetName() << ": " << comp.GetScore() << "\n\n";
   // myfile << player.GetName();
    myfile << player.GetScore();
    //myfile << comp.GetName();
    myfile << comp.GetScore();
	myfile.close();
	if ( player.GetScore() >= comp.GetScore() )
		cout << "Congratulations, " << player.GetName() << "! You beat the computer in Rummy 500!";
	else
		cout << "Sorry, " << comp.GetName() << " defeated you!";

	
	cout << "\n\nI hope you enjoyed my game!";
}

void dealDeck(Player& user, Computer& comp, Cards& deck, int count)
{
	if (count % EVEN_ODD == EMPTY)	
	{
		unsigned int i = EMPTY;
		while (i < EVEN_ODD*CARDS_DEALT)
		{
			user.InsertIntoHand(deck.TopDeckCard());
			deck.PopOffCard();
			i++;
			comp.InsertIntoHand(deck.TopDeckCard()); 
			deck.PopOffCard();
			i++;
		}
		deck.AdjustPickPile();
	} else						
	{
		unsigned int j = EMPTY;
		while (j < EVEN_ODD*CARDS_DEALT)
		{
			comp.InsertIntoHand(deck.TopDeckCard());
			deck.PopOffCard();
			j++;
			user.InsertIntoHand(deck.TopDeckCard());
			deck.PopOffCard();
			j++;
		}
		deck.AdjustPickPile();
	}
}

void ScoreOutput(Player& user, Computer& comp, int roundCount)
{
	cout << "After " << roundCount << " rounds:\n" <<		
		"Your current score: " << user.GetScore() << "\n" <<
		comp.GetName() << "'s current score: " << comp.GetScore() << "\n" <<
		"And the game continues...\n\n";
}
 
