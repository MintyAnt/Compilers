#include <vector>
#include <iostream>
#include <stdarg.h>
#include <map>
#include <intrin.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ahhhh
// cuz they aint defined yet, the horrors of one file to rull all classes
class Left;
class Right;
class Increment;
class Decrement;
class Input;
class Output;
class Loop;
class Sequence;
class Program;
class Visitor;
class ProcedureDefinition;
class ProcedureInvocation;
class Repetition;
class Strings;
class Breakpoint;
class Interpreter;

//@TODO fix memory leaks

//----------------------------------------------------------------------------------------------------//
class Visitor
{
public:
	// BRAIN F
	virtual void visit(Left* inNode) = 0;
	virtual void visit(Right* inNode) = 0;
	virtual void visit(Increment* inNode) = 0;
	virtual void visit(Decrement* inNode) = 0;
	virtual void visit(Input* inNode) = 0;
	virtual void visit(Output* inNode) = 0;
	virtual void visit(Loop* inNode) = 0;
	virtual void visit(Sequence* inNode) = 0;
	virtual void visit(Program* inNode) = 0;

	// RUM
	virtual void visit(ProcedureDefinition* inNode) = 0;
	virtual void visit(ProcedureInvocation* inNode) = 0;
	virtual void visit(Repetition* inNode) = 0;
	virtual void visit(Strings* inNode) = 0;
	virtual void visit(Breakpoint* inNode) = 0;
};

//----------------------------------------------------------------------------------------------------//
class Node
{
public:
	virtual void accept(Visitor* inVisitor) = 0;
};

//----------------------------------------------------------------------------------------------------//
class Left : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Right : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Increment : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Decrement : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Input : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Output : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Loop : public Node
{
public:
	Node* mChild;

public:
	Loop(Node* inChild)
		: mChild(inChild) 
	{}
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Sequence : public Node
{
public:
	vector<Node*> mChildren;

public:
	//----------------------------------------------------------------------------------------------------//
	Sequence(vector<Node*>& inChildren)
	{
		Node* next_child = NULL;
		vector<Node*>::iterator childIter;
		for (childIter = inChildren.begin(); childIter != inChildren.end(); ++childIter)
		{
			next_child = (*childIter);
			mChildren.push_back(next_child);
		}
	}
	//----------------------------------------------------------------------------------------------------//
	Sequence(Node* inChild, ...)
	{
		Node* next_child = NULL;
		va_list list;
		mChildren.push_back(inChild);
		va_start(list, inChild);
		while ((next_child = va_arg(list, Node*)) != NULL)
		{
			mChildren.push_back(next_child);
		}
		va_end(list);
	}
	//----------------------------------------------------------------------------------------------------//
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Program : public Node
{
public:
	Node* mChild;

public:
	//----------------------------------------------------------------------------------------------------//
	Program(Node* inChild) 
		: mChild(inChild) 
	{}
	//----------------------------------------------------------------------------------------------------//
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class ProcedureDefinition : public Node
{
public:
	Sequence* mProcedureSequence;

public:
	//----------------------------------------------------------------------------------------------------//
	ProcedureDefinition(Sequence* inProcedureSequence)
		: mProcedureSequence(inProcedureSequence)
	{}
	//----------------------------------------------------------------------------------------------------//
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class ProcedureInvocation : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Repetition : public Node
{
public:
	Node* mRepeatNode;
	int mNumRepeats;
	
public:
	//----------------------------------------------------------------------------------------------------//
	Repetition(Node* inRepeatNode, int inNumRepeats)
		: mRepeatNode(inRepeatNode)
		, mNumRepeats(inNumRepeats)
	{}
	//----------------------------------------------------------------------------------------------------//
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Strings : public Node
{
public:
	string mString;
public:
	//----------------------------------------------------------------------------------------------------//
	Strings(const string inString)
		: mString(inString)
	{}
	//----------------------------------------------------------------------------------------------------//
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Breakpoint : public Node
{
public:
	void accept(Visitor* inVisitor)
	{
		inVisitor->visit(this);
	}
};

//----------------------------------------------------------------------------------------------------//
class Printer : public Visitor
{
public:
	//----------------------------------------------------------------------------------------------------//
	void visit(Left* inNode)
	{
		cout << '<';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Right* inNode)
	{
		cout << '>';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Increment* inNode)
	{
		cout << '+';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Decrement* inNode)
	{
		cout << '-';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Input* inNode)
	{
		cout << ',';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Output* inNode)
	{
		cout << '.';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Loop* inNode)
	{
		cout << '[';
		inNode->mChild->accept(this);
		cout << ']';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Sequence* inNode)
	{
		vector<Node*>::iterator childIter;
		for (childIter = inNode->mChildren.begin(); childIter != inNode->mChildren.end(); ++childIter)
		{
			Node* currentChild = (*childIter);
			currentChild->accept(this);
		}
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Program* inNode)
	{
		inNode->mChild->accept(this);
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(ProcedureDefinition* inNode)
	{
		cout << '(';
		inNode->accept(this);
		cout << ')';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(ProcedureInvocation* inNode)
	{
		cout << ':';
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Repetition* inNode)
	{
		cout << inNode->mNumRepeats;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Strings* inNode)
	{

	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Breakpoint* inNode)
	{
		cout << '!';
	}
};

//----------------------------------------------------------------------------------------------------//
class Procedure
{
public:
	Sequence* mProcedureSequence;
	Procedure(Sequence* inSequence)
		: mProcedureSequence(inSequence)
	{}
	void execute(Visitor* inInterperter)
	{
		mProcedureSequence->accept(inInterperter);
	}
};

//----------------------------------------------------------------------------------------------------//
class Interpreter : public Visitor
{
public:
	char mCell[30000];
	unsigned short mPointer;
	map<unsigned short, Procedure*> mProcedures;
	vector<char> mBufferStack;

public:
	//----------------------------------------------------------------------------------------------------//
	void visit(Left* inNode)
	{
		mPointer--;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Right* inNode)
	{
		mPointer++;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Increment* inNode)
	{
		mCell[mPointer]++;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Decrement* inNode)
	{
		mCell[mPointer]--;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Input* inNode)
	{
		if (mBufferStack.empty())
			cin >> mCell[mPointer];
		else
		{
			char topChar = mBufferStack[mBufferStack.size()-1];
			mBufferStack.pop_back();
			mCell[mPointer] = topChar;
		}
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Output* inNode)
	{
		cout << mCell[mPointer];
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Loop* inNode)
	{
		while (mCell[mPointer])
		{
			inNode->mChild->accept(this);
		}
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Sequence* inNode)
	{
		vector<Node *>::iterator childIter;
		for (childIter = inNode->mChildren.begin(); childIter != inNode->mChildren.end(); ++childIter)
		{
			Node* currentChild = (*childIter);
			currentChild->accept(this);
		}
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Program* inNode)
	{
		for (int i = 0; i < 30000; i++)
		{
			mCell[i] = 0;
		}

		mPointer = 0;
		inNode->mChild->accept(this);
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(ProcedureDefinition* inNode)
	{
		// Set this procedures children as the current pointers address
		mProcedures[mPointer] = new Procedure(inNode->mProcedureSequence);
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(ProcedureInvocation* inNode)
	{
		mProcedures[mCell[mPointer]]->execute(this);
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Repetition* inNode)
	{
		for (int repeatIndex = 0; repeatIndex < inNode->mNumRepeats; ++repeatIndex)
		{
			inNode->mRepeatNode->accept(this);
		}
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Strings* inNode)
	{
		mBufferStack.insert(mBufferStack.end(), inNode->mString.rbegin(), inNode->mString.rend());
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Breakpoint* inNode)
	{
		__debugbreak();
	}
};

//----------------------------------------------------------------------------------------------------//
class Compiler : public Visitor
{
public:
	ofstream mOutputFile;
	int mCurrentTabAmmount;

public:
	//----------------------------------------------------------------------------------------------------//
	Compiler()
		: mOutputFile("compiled.py")
		, mCurrentTabAmmount(0)
	{}
	//----------------------------------------------------------------------------------------------------//
	string GetTabString()
	{
		string newString;
		const int numSpacesInTab = 4;
		for (int x = 0; x < mCurrentTabAmmount * numSpacesInTab; x++)
		{
			newString.append(" ");
		}

		return newString;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Left* inNode)
	{
		mOutputFile << GetTabString() << "pointer -= 1" << endl;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Right* inNode)
	{
		mOutputFile << GetTabString() << "pointer += 1" << endl;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Increment* inNode)
	{
		mOutputFile << GetTabString() << "cells[pointer] = chr(ord(cells[pointer]) + 1)" << endl;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Decrement* inNode)
	{
		mOutputFile << GetTabString() << "cells[pointer] = chr(ord(cells[pointer]) - 1)" << endl;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Input* inNode)
	{
		mOutputFile << GetTabString() << "if (not characterBuffer):" << endl;
		mCurrentTabAmmount++;
		mOutputFile << GetTabString() << "cells[pointer] = raw_input()" << endl;
		mCurrentTabAmmount--;

		mOutputFile << GetTabString() << "else:" << endl;
		mCurrentTabAmmount++;
		mOutputFile << GetTabString() << "cells[pointer] = characterBuffer.pop()" << endl;
		mCurrentTabAmmount--;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Output* inNode)
	{
		mOutputFile << GetTabString() << "print(cells[pointer])" << endl;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Loop* inNode)
	{
		mOutputFile << GetTabString() << "while (cells[pointer]):" << endl;
		mCurrentTabAmmount++;
		inNode->mChild->accept(this);
		mCurrentTabAmmount--;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Sequence* inNode)
	{
		vector<Node *>::iterator childIter;
		for (childIter = inNode->mChildren.begin(); childIter != inNode->mChildren.end(); ++childIter)
		{
			Node* currentChild = (*childIter);
			currentChild->accept(this);
		}
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Program* inNode)
	{
		// Imports
		mOutputFile << "" << endl;

		/*
		// Procedures
		mOutputFile << "class Procedure:" << endl;

		class Procedure
		{
		public:
		Sequence* mProcedureSequence;
		Procedure(Sequence* inSequence)
		: mProcedureSequence(inSequence)
		{}
		void execute(Visitor* inInterperter)
		{
		mProcedureSequence->accept(inInterperter);
		}
		};
		*/

		// Main file
		mOutputFile << "procedures = {}" << endl;
		mOutputFile << "characterBuffer = []" << endl;
		mOutputFile << "pointer = 0" << endl;
		mOutputFile << "cells = []" << endl;
		mOutputFile << "for i in range(30000):" << endl;
		mOutputFile << "    cells.append(0)" << endl;

		// Print out rest of program
		inNode->mChild->accept(this);
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(ProcedureDefinition* inNode)
	{
		// Set this procedures children as the current pointers address
		mOutputFile << GetTabString() << "procedures[pointer] = lambda:";
		inNode->mProcedureSequence->accept(this);
		//mProcedures[mPointer] = new Procedure(inNode->mProcedureSequence);
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(ProcedureInvocation* inNode)
	{
		mOutputFile << GetTabString() << "procedures[cells[pointer]]()" << endl;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Repetition* inNode)
	{
		mOutputFile << GetTabString() << "for repeatIndex in range(" << inNode->mNumRepeats << "):" << endl;
		mCurrentTabAmmount++;
		inNode->mRepeatNode->accept(this);
		mCurrentTabAmmount--;
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Strings* inNode)
	{
		//for (auto currentCharacter : inNode->mString)
		string::reverse_iterator stringIter;
		for (stringIter = inNode->mString.rbegin(); stringIter != inNode->mString.rend(); ++stringIter)
		{
			char currentCharacter = (*stringIter);
			mOutputFile << GetTabString() << "characterBuffer.append(\"";
			if (currentCharacter == '\0')
				mOutputFile << "\0";
			else
				mOutputFile << currentCharacter;
			mOutputFile << "\")" << endl;
		}
	}
	//----------------------------------------------------------------------------------------------------//
	void visit(Breakpoint* inNode)
	{
		__debugbreak();
	}
};

//----------------------------------------------------------------------------------------------------//
class RUM
{
public:
	//----------------------------------------------------------------------------------------------------//
	Sequence* ParseSequence(string inSource, bool inbJustParseOne = false)
	{
		static unsigned int sourceIndex = 0;
		vector<Node*> sequence;
		while (sourceIndex < inSource.size())
		{
			char command = inSource[sourceIndex];
			sourceIndex++;

			switch (command)
			{
			case '>':
				sequence.push_back(new Right());
				break;
			case '<':
				sequence.push_back(new Left());
				break;
			case '+':
				sequence.push_back(new Increment());
				break;
			case '-':
				sequence.push_back(new Decrement());
				break;
			case '.':
				sequence.push_back(new Output());
				break;
			case ',':
				sequence.push_back(new Input());
				break;
			case '[':
				sequence.push_back(new Loop(ParseSequence(inSource)));
				break;
			case ']':
				return new Sequence(sequence);
			case '(':
				sequence.push_back(new ProcedureDefinition(ParseSequence(inSource)));
				continue;
			case ')':
				return new Sequence(sequence);
				break;
			case ':':
				sequence.push_back(new ProcedureInvocation());
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				{
					string numberString;
					numberString.push_back(command);
					bool bAnotherNumber = true;

					unsigned int nextIndex = sourceIndex;
					while (bAnotherNumber)
					{
						if (nextIndex < inSource.size())
						{
							char nextCommand = inSource[nextIndex];
							if (nextCommand >= 48 && nextCommand <= 57)
							{
								nextIndex++;
								numberString.push_back(nextCommand);
								continue;
							}
						}
						bAnotherNumber = false;
					}

					int numberStringAsNumber = atoi(numberString.c_str());
					sourceIndex = nextIndex;
					//@TODO parse out entire sequences, not just primitives.
					//Sequence* repeatSequence = ParseSequence(inSource);
					Sequence* repeatSequence = ParseSequence(inSource, true);
					Repetition* repetition = new Repetition(repeatSequence, numberStringAsNumber);
					sequence.push_back(repetition);
				}
				break;
			case '!':
				sequence.push_back(new Breakpoint());
				break;
			case '\"':
				{
					string parsedString;
					while (inSource[sourceIndex] != '\"')
					{
						char nextCharacter = inSource[sourceIndex];
						sourceIndex++;
						parsedString.push_back(nextCharacter);
					}
					sourceIndex++;
					parsedString.push_back('\0');
					sequence.push_back(new Strings(parsedString));
				}
				break;
			}

			if (inbJustParseOne) 
				return new Sequence(sequence);
		}
		return new Sequence(sequence);
	}

	//----------------------------------------------------------------------------------------------------//
	Program* Parse(string inSource)
	{
		return new Program(ParseSequence(inSource));
	}
};

//----------------------------------------------------------------------------------------------------//
// Main //
//----------------------------------------------------------------------------------------------------//
int main(int argc, char** argv)
{
	RUM* rum = new RUM();
	// Brainfuck
	//Program* program = rum->Parse("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");
	// Rum, just procedures
	//Program* program = rum->Parse("(++++++++++<[>+>+<<-]>>[<<+>>-])>::::::::::::::<<<<<<<--------.>>>---------.+++++++..>---------.<<<<<<<------.<--------.>>>>>---.>>>.+++.<.--------.<<<<<<<+.");
	// Rum, Hello world with repetitions
	//Program* program = rum->Parse("10+[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");
	// Rum, strings
	Program* program = rum->Parse("\"helloworld\",[--------------------------------.,]");
	// Rum, procedures, strings, and repetitions
	//const string rawString = R"DELIM(+(,[.,])+(,[32-.,])"hello":[-]+", ":[-]++"world":)DELIM";
	//string rawString = "+(,[.,])+(,[32-.,])\"hello\":[-]+\", \":[-]++\"world\":"
	//Program* program = rum->Parse(rawString);


	Interpreter* interperter = new Interpreter();
	program->accept(interperter);
	Compiler* compiler = new Compiler();
	compiler->visit(program);
}