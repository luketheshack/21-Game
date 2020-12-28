#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <stack>

using namespace std;

vector<string> suits = {"HEARTS", "CLUBS", "SPADES", "DIAMONDS"};
vector<string> ranks = {"TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE"};

class Player;
class Card;
class Deck;


class Card 
{
private:
    int value {};
    string rank {};
    string suit {};

public:
    Card() {
        suit = suits[rand()%suits.size()];
        rank = ranks[rand()%suits.size()];
        if (rank == "TWO") value = 2;
        if (rank == "THREE") value = 3;
        if (rank == "FOUR") value = 4;
        if (rank == "FIVE") value = 5;
        if (rank == "SIX") value = 6;
        if (rank == "SEVEN") value = 7;
        if (rank == "EIGHT") value = 8;
        if (rank == "NINE") value = 9;
        if (rank == "TEN") value = 10;
        if (rank == "JACK") value = 10;
        if (rank == "QUEEN") value = 10;
        if (rank == "KING") value = 10;
        if (rank == "ACE") value = 11;
    }

    Card(int s, int r) {
        suit = suits[s];
        rank = ranks[r];
        if (rank == "TWO") value = 2;
        if (rank == "THREE") value = 3;
        if (rank == "FOUR") value = 4;
        if (rank == "FIVE") value = 5;
        if (rank == "SIX") value = 6;
        if (rank == "SEVEN") value = 7;
        if (rank == "EIGHT") value = 8;
        if (rank == "NINE") value = 9;
        if (rank == "TEN") value = 10;
        if (rank == "JACK") value = 10;
        if (rank == "QUEEN") value = 10;
        if (rank == "KING") value = 10;
        if (rank == "ACE") value = 11;
    }

    void showCard(string name) {
        cout << name << " holds the " << rank << " of " << suit << "." << endl;
    }

    int getValue() {
        return value;
    }
};


class Deck 
{
private:
    stack<Card> allcards;

public:
    Deck() {
        vector<Card> placeholder;
        for (int r = 0; r < ranks.size(); r++) {
            for (int s = 0; s < suits.size(); s++) {
                Card now {s, r};
                placeholder.push_back(now);
            }
        }
        random_shuffle(placeholder.begin(), placeholder.end());
        for (int i = 0; i < placeholder.size(); i++) {
            allcards.push(placeholder[i]);
        }
    }

    void dealCard(Player &p);
    void dealStartingHand(vector<Player> &players);
};


class Player
{
private:
    int handvalue;
    string name;
    vector<Card> cards;
    bool valid;

public:
    Player(string type) {
        name = type;
        valid = true;
    }

    string getName() {
        return name;
    }
    
    void addCard(Card c) {
        cards.push_back(c);
    } 

    void getHandValue() {
        int newvalue = 0;
        for (int i = 0; i < cards.size(); i++) {
            int val = cards[i].getValue();
            newvalue += val;
        } 
        handvalue = newvalue;
        valid = (handvalue <= 21) ? true : false;
        if (!valid) {
            cout << "Oh no! " << name << " busted!" << "\n\n";
        }
        else if (handvalue == 21) {
            cout << name << " got 21!" << "\n\n";
        }
        else {
            cout << "The value of " << name << "'s hand is " << newvalue << "." << endl;
        }
    }

    int returnHandValue() {
        return handvalue;
    }

    void showAllCards() {
        for (int i = 0; i < cards.size(); i++) {
            cards[i].showCard(name);
        }
        cout << "\n";
    }

    // for Dealer
    void showTopCard() {
        cards[0].showCard(name);
        cout << "\n";
    }

    string getAction() {
        string action;
        cout << "Would you like to hit or stand? " << endl;
        cin >> action;
        cout << "\n\n";
        return action;
    }

    void doAction(Deck &deck) {
        string action = getAction();
        
        if (action == "hit") {
            cout << name << " has chosen to HIT." << endl;
            deck.dealCard(*this);
            showAllCards();
            getHandValue();
            if (handvalue > 21) return;
            doAction(deck);
        }
        else {
            cout << name << " has chosen to STAND." << "\n" << endl;
        }
        return;
    }

    void dealerAction(Deck &deck) {
        getHandValue();
        while (handvalue <= 16) {
            cout << name << " has chosen to HIT." << "\n\n";
            deck.dealCard(*this);
            showAllCards();
            getHandValue();
        }
    }

};

void Deck::dealCard(Player &p) {
    Card top = allcards.top();
    allcards.pop();
    p.addCard(top);
}

void Deck::dealStartingHand(vector<Player> &players) {
    for (int i = 0; i < players.size(); i++) {
        for (int j = 0; j < 2; j++) {
            Card top = allcards.top();
            allcards.pop();
            players[i].addCard(top);
        }
    }
}

void winningHand(vector<Player> players) {
    string winnerName = players[0].getName();
    int winnerValue = players[0].returnHandValue();
    int thisValue;
    for (int i = 1; i < players.size(); i++) {
        if (players[i].returnHandValue() > winnerValue) {
            winnerValue = players[i].returnHandValue();
            winnerName = players[i].getName();
        }
    }
    cout << winnerName << " wins the hand!" << endl;
}


string typePlayerName() {
    string name;
    cout << "What is your name?" << endl;
    cin >> name;
    cout << "\n\n";
    return name;
}

void showInitialHands(vector<Player> &players) {
    players[0].showTopCard();
    for (int i = 1; i < players.size(); i++) {
        players[i].showAllCards();
        players[i].getHandValue();
    }
}

void playRound(string name) {
    Deck deck;

    vector<Player> players;
    Player DEALER = {"Dealer"};
    Player YOU = {name};
    players.push_back(DEALER);
    players.push_back(YOU);

    deck.dealStartingHand(players);
    showInitialHands(players);


    for (int i = 1; i < players.size(); i++) {
        players[i].doAction(deck);
    }
    
    players[0].showAllCards();
    players[0].dealerAction(deck);

    winningHand(players);
}

int main() {
    string name = typePlayerName(), action;
    string cont = {};
    
    do {
        system("clear");
        playRound(name);
        cout << "\n" << "Continue? (y/n)" << "\n\n";
        cin >> cont;
    } while (cont == "y");


    system("clear");
    cout << "\n\n\n" << "Goodbye!" << "\n\n";
    return 0;
}