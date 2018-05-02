#pragma once

#include "Nodable.h"            // for constants and forward declarations
#include "vector"
#include <string>
#include "stdlib.h"		// for size_t

namespace Nodable{


	/* Base class for all Nodes */
	class Node{
	public:
		Node();
		~Node();
		virtual void      draw      (){};
		Node_Container*   getContext()const;
		void              setContext(Node_Container* _context);
		Node*             getInput  (size_t _id=0)const;
		Node*             getOutput (size_t _id=0)const;	
		void              setInput  (Node*, size_t _id=0);
		void              setOutput (Node*, size_t _id=0);

		static void       DrawRecursive(Node*, std::string _prefix = "");
	private:
		std::vector<Node*> input;
		std::vector<Node*> output;
		Node_Container*    context; /* the context that create this node */
	};	

	/* Node_BinaryOperation is an interface for all binary operations */
	class Node_BinaryOperation: public Node{
	public:		
		Node_BinaryOperation(Node_Value* _leftInput, Node_Value* _rightInput, Node_Value* _output);
		virtual ~Node_BinaryOperation();
		virtual void                  draw()override{printf("%s", "[BinaryOperation]");}
		virtual void                  evaluate               () = 0;
		/* return true is op needs to be evaluated before nextOp */
		static  bool                  NeedsToBeEvaluatedFirst(const char op, const char nextOp);
	protected:
		Node_Value* getLeftInput  ()const;
		Node_Value* getRightInput ()const;
		Node_Value* getOutput     ()const;
	private:
		Node_Value* leftInput;
		Node_Value* rightInput;
		Node_Value* output;
	};

	/* Implementation of the Node_BinaryOperation as a Sum */
	class Node_Add : public Node_BinaryOperation{
	public:
		Node_Add(Node_Value* _leftInput, Node_Value* _rightInput, Node_Value* _output);
		~Node_Add();
		void evaluate();
		void draw()override{printf("%s", "[Add]");}
	};

	/* Implementation of the Node_BinaryOperation as a Substraction */
	class Node_Substract : public Node_BinaryOperation{
	public:
		Node_Substract(Node_Value* _leftInput, Node_Value* _rightInput, Node_Value* _output);
		~Node_Substract();
		void evaluate();
		void draw()override{printf("%s", "[Substract]");}
	};

	/* Implementation of the Node_BinaryOperation as a Multiplication */
	class Node_Multiply : public Node_BinaryOperation{
	public:
		Node_Multiply(Node_Value* _leftInput, Node_Value* _rightInput, Node_Value* _output);
		~Node_Multiply();
		void evaluate();
		void draw()override{printf("%s", "[Multiply]");}
	};

	/* Implementation of the Node_BinaryOperation as a Division */
	class Node_Divide : public Node_BinaryOperation{
	public:
		Node_Divide(Node_Value* _leftInput, Node_Value* _rightInput, Node_Value* _output);
		~Node_Divide();
		void evaluate();
		void draw()override{printf("%s", "[Divide]");}
	};

	/* Implementation of the Node_BinaryOperation as an assignment */
	class Node_Assign : public Node_BinaryOperation{
	public:
		Node_Assign(Node_Value* _leftInput, Node_Value* _rightInput, Node_Value* _output);
		~Node_Assign();
		void evaluate();
		void draw()override{printf("%s", "[Assign]");}
	};

	/* Node_Symbol is a node that identify a value with its name */
	class Node_Symbol : public Node{
	public:
		Node_Symbol(const char* _name, Node* _value);
		~Node_Symbol();
		void draw()override{printf("%s", "[Symbol]");}
		Node* 			getValue()const;
		const char* 	getName()const;
	private:
		std::string 	name;
		Node* 			value;
	};
}
