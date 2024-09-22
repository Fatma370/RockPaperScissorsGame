#include<iostream>
#include<cstdlib>
using namespace std;

enum enToolType {Rock=1,Paper=2,scissors=3};
enum enWinner {computer=1,Player1=2,Draw=3};

struct strRound {
	enToolType PlayerChoice;
	enToolType ComputerCoice;
	enWinner RoundWinner;
	int RoundNumber = 0;
};
struct strGame {
	int GameRounds=0;
	int Player1WonTimes=0;
	int ComputerWinTimes=0;
	int Drawtime=0;
	enWinner FinalWinner;

};

int GetRandomNumber(int from , int to) {
	return rand() % (to - from + 1) + from;

}

enToolType GetComputerChoice() {
	return ((enToolType)GetRandomNumber(1, 3));
}

int ReadNumberOfRounds() {
	int Number = 0;
	do {
		cout << "\n How Many rounds do you want to play from 1 to 10?   ";
		cin >> Number;
		if (Number < 1 || Number>10)
			cout << "invalid number. ";
	} while (Number < 1 || Number>10);
	return Number;
}

enToolType ReadUserChoice() {
	int UserCohice = 0;
	do {
		cout << "\n Your Choice: [1]:Rock , [2]:Paper , [3]:Scissores? ";
		cin >> UserCohice;
		if (UserCohice < 1 || UserCohice>3)
			cout << "ivalid Number. ";
	} while (UserCohice < 1 || UserCohice>3);
		return (enToolType)UserCohice;
}

enWinner WhoIsTheRoundWinner(strRound RounfInfo) {

	if (RounfInfo.PlayerChoice==RounfInfo.ComputerCoice) {

		 return enWinner::Draw;
	}

	else {
		switch (RounfInfo.ComputerCoice) {


		case enToolType::Rock:

			if (RounfInfo.PlayerChoice == enToolType::scissors)
				return enWinner::computer;
			break;

		case enToolType::Paper:
		
			if (RounfInfo.PlayerChoice == enToolType::Rock)
				return enWinner::computer;
			break;
	
		case enToolType::scissors:
			
	
			if (RounfInfo.PlayerChoice== enToolType::Paper)
				return enWinner::computer;
			break;
		
		}
		return enWinner::Player1;

	}

}

enWinner FinallGameWinner(int ComputerWinTimes,int Player1WonTimes) {
	if (ComputerWinTimes > Player1WonTimes)
		return enWinner::computer;
	else if (Player1WonTimes > ComputerWinTimes)
		return enWinner::Player1;
	else
		return enWinner::Draw;
}

string WinnerName(enWinner winner)
{
	string WinnerNameArr[3] = { "Computer","Player","Draw" };
	return WinnerNameArr[winner - 1];
}

string ToolName(enToolType toolType) {

	switch (toolType)
	{
	case enToolType::Paper:
		return "Paper";
	case enToolType::Rock:
		return "Rock";
	case enToolType::scissors:
		return "scissors";
	}
}

strRound FillRoundInfo(strRound &RoundInfo)
{
	RoundInfo.PlayerChoice = ReadUserChoice();
	RoundInfo.ComputerCoice = GetComputerChoice();
	RoundInfo.RoundWinner = WhoIsTheRoundWinner(RoundInfo);
	return RoundInfo;
}

void DisplayRoundInfo(strRound RoundInfo)
{
	cout << "___________________Round[" << RoundInfo.RoundNumber << "]_________________\n";
	//cout << "hi";
	cout << "Player1 Choice: " << ToolName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ToolName( RoundInfo.ComputerCoice )<< endl;
	cout << "Round Winner: " << WinnerName(RoundInfo.RoundWinner)<<endl;
	cout << "____________________________________________\n";

}

void ScoreCounter(int &ComputerScore, int &Player1Score,int  &DrawTimes, strRound RoundInfo)
{
	if (RoundInfo.RoundWinner == enWinner::computer)
	{
		system("color 4f");
		cout << "\a";
		ComputerScore++;
	}
	else if (RoundInfo.RoundWinner == enWinner::Player1)
	{
		system("color 2f");
		Player1Score++;
	}
	else
	{
		system("color 6f");
		DrawTimes++;
	}
}

string Tap(int Number) {
	string tab = " ";
	for (int i = 0; i < Number; i++)
	{
		tab += "\t";

	}
	return tab;
}

void DisplayGAmeOver() {
	cout << Tap(2) << "_______________________________________________\n";
	cout << Tap(4) << "+++ G a m e  O v e r +++" << Tap(4) << endl;
	cout << Tap(2) << "_______________________________________________\n";
	
}

void DisplayGameResults(strGame GameInfo)
{
	cout << Tap(2) << "______________[Game Results]_____________________\n";
	cout << Tap(2) << "Game Rounds          :" << GameInfo.GameRounds<<endl;
	cout << Tap(2) << "Player1 Won times   :" << GameInfo.Player1WonTimes<<endl;
	cout << Tap(2) << "Computer Won times  :" << GameInfo.ComputerWinTimes<<endl;
	cout << Tap(2) << "Final Winner        :" << WinnerName(GameInfo.FinalWinner)<<endl;
	cout << Tap(2) << "__________________________________________________________\n";
}
strGame FillGameResult(int computerScore,int PlayerScore, int DrawTimes,int GameRounds)
{
	strGame GameInfo;
	GameInfo.ComputerWinTimes = computerScore;
	GameInfo.Player1WonTimes = PlayerScore;
	GameInfo.Drawtime = DrawTimes;
	GameInfo.FinalWinner = FinallGameWinner(computerScore, PlayerScore);
	return GameInfo;

}
void ClearScreen() {
	system("cls");
	system("color 0f");

}


void GameRounds() {
	int NumberOfRounds = 0;
	NumberOfRounds = ReadNumberOfRounds();
	strRound RoundInfo;
	strGame Gameinfo;
	
	int Player1score = 0, ComputerScore = 0, DarwTimescount = 0;
	for (int Round = 1; Round <= NumberOfRounds; Round++)
	{
	
		RoundInfo.RoundNumber = Round;
		FillRoundInfo(RoundInfo);
		DisplayRoundInfo(RoundInfo);
		ScoreCounter(ComputerScore, Player1score, DarwTimescount, RoundInfo);
	}
	
	DisplayGAmeOver();
	DisplayGameResults(FillGameResult(ComputerScore, Player1score, DarwTimescount, NumberOfRounds));

}

void PlayGame()
{
	char Again = 'y';
	do {
		ClearScreen();
		GameRounds();
		cout << Tap(2)<<"do You want to play again? Y/y??\n ";
		cin >> Again;

	} while (Again == 'y' || Again == 'Y');
}

int main() {
	srand((unsigned)time(NULL));
	PlayGame();
}