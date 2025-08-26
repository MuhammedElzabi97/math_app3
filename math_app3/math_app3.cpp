#include <iostream>
using namespace std;

enum enOperationType {Add = 1 , Sub =2 , Mul = 3 , Div =4 , MixOp = 5};
enum enQuestionLevel {Easy = 1 , Med = 2 , Hard = 3 , Mix =4};

struct stQuestion
{
	int Number1=0;
	int Number2=0;
	enOperationType OpType;
	enQuestionLevel qLevel;
	int CorrectAnswer=0;
	int PlyerAnswer=0;
	bool AnswerResult = false;
};

struct stQuiz
{
	stQuestion Questions[100];
	int NumberOfRightAnswer=0;
	int NumberOfWrongAnswer=0;
	int NumberOfQuestions=0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	bool IsPass = false;
};

int AskNumberOfQuestions()
{
	int NumberOfQuestions;
	do
	{
		cout << "How many questions do you want to answer : ";
		cin >> NumberOfQuestions;
		
	} while (NumberOfQuestions <1 || NumberOfQuestions >10 );
	return NumberOfQuestions;
}

enOperationType AskOperationType()
{
	short OpType;
	do
	{
		cout << "Enter operation type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix :	";
		cin >> OpType;

	} while (OpType < 1 || OpType >5);
	return (enOperationType)OpType;
}

enQuestionLevel AskQuestionLevel()
{
	short qLevel;
	do
	{
		cout << "Enter question level [1] Easy , [2] Med , [3] Hard , [4] Mix :	";
		cin >> qLevel;

	} while (qLevel < 1 || qLevel >4);
	return (enQuestionLevel)qLevel;
}

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

int GetCorrectAnswer(short Number1, short Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

enOperationType GetRandomOperationType()
{
	short op = RandomNumber(1, 4);
	return (enOperationType)op;
}

stQuestion GenerateQuestion(enOperationType OperationType , enQuestionLevel QuestionLevel)
{
	stQuestion Question;
	
	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}
	if (OperationType == enOperationType::MixOp)
	{
		//OperationType = GetRandomOperationType();
		OperationType = (enOperationType)RandomNumber(1, 4);
	}

	Question.OpType = OperationType;
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
		Question.qLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::Med:
		Question.Number1 = RandomNumber(10, 20);
		Question.Number2 = RandomNumber(10, 20);

		Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
		Question.qLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(20, 50);
		Question.Number2 = RandomNumber(20, 50);

		Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
		Question.qLevel = QuestionLevel;
		return Question;
	}
}
void GenerateQuizQuestion(stQuiz& Quiz)
{
	for (int Question = 0; Question < Quiz.NumberOfQuestions; Question++)
	{
		Quiz.Questions[Question] = GenerateQuestion(Quiz.OperationType, Quiz.QuestionLevel);
	}
}

short GetPlayerAnswer()
{
	short Answer;
	cin >> Answer;
	return Answer;
}

string GetOpTypeSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "+";
	}
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		return "Easy";
	case enQuestionLevel::Med:
		return "Med";
	case enQuestionLevel::Hard:
		return "Hard";
	case enQuestionLevel::Mix:
		return "Mix";
	default:
		return "";
	}
}

void PrintQuizQuestion(stQuiz& Quiz , short QuestionNumber)
{	
	cout << "Question [" << QuestionNumber + 1 << " / " << Quiz.NumberOfQuestions << " ] " << endl;
	cout << Quiz.Questions[QuestionNumber].Number1 << endl;
	cout << Quiz.Questions[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quiz.Questions[QuestionNumber].OpType);
	cout << "\n__________" << endl;
//	Quiz.Questions[QuestionNumber].PlyerAnswer =  GetPlayerAnswer();
}

void SetSecreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectThePlayerAnswer(stQuiz& Quiz, short QuestionNumber)
{
	if (Quiz.Questions[QuestionNumber].PlyerAnswer != Quiz.Questions[QuestionNumber].CorrectAnswer)
	{
		Quiz.Questions[QuestionNumber].AnswerResult = false;
		Quiz.NumberOfWrongAnswer++;

		cout << "Wrong answer :-( \n";
		cout << "The right answer is : ";
		cout << Quiz.Questions[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quiz.Questions[QuestionNumber].AnswerResult = true;
		Quiz.NumberOfRightAnswer++;

		cout << "Right answer :-) \n";
		cout << "\n";
	}
	SetSecreenColor(Quiz.Questions[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionAnswer(stQuiz& Quiz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
	{
		PrintQuizQuestion(Quiz, QuestionNumber);
		Quiz.Questions[QuestionNumber].PlyerAnswer = GetPlayerAnswer();
		CorrectThePlayerAnswer(Quiz, QuestionNumber);
	}
	Quiz.IsPass=(Quiz.NumberOfRightAnswer >= Quiz.NumberOfWrongAnswer);	
}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "FAIL :-(";
}

void PrintQuizResult(stQuiz Quiz)
{
	cout << "\n________________________________________\n";
	cout << "Final Result " << GetFinalResultText(Quiz.IsPass);
	cout << "\n________________________________________\n";
	cout << "Number of questions : " << Quiz.NumberOfQuestions << endl;
	cout << "Questions level     : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
	cout << "Questions type      : " << GetOpTypeSymbol(Quiz.OperationType) << endl;
	cout << "Number of right answer : " << Quiz.NumberOfRightAnswer << endl;
	cout << "Number of wrong answer : " << Quiz.NumberOfWrongAnswer << endl;
	cout << "\n________________________________________\n";


}

void PlayMathGame()
{
	stQuiz Quiz;
	Quiz.NumberOfQuestions = AskNumberOfQuestions();
	Quiz.QuestionLevel = AskQuestionLevel();
	Quiz.OperationType = AskOperationType();

	GenerateQuizQuestion(Quiz);
	AskAndCorrectQuestionAnswer(Quiz);
	PrintQuizResult(Quiz);
}

void RestartGame()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	
	char PlayAgain = 'y';

	do
	{
		RestartGame();
		PlayMathGame();

		cout << "Do want to play again (Y/N) : ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y' );
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}
