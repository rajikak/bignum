#include "CodeGen.h"
#include "bignum.h"

using namespace llvm;

namespace {

class ToIRVisitor : public ASTVisitor {

	Module *M;
	IRBuilder<> Builder;
	Type *VoidTy;
	Type *Int32Ty;
	Type *Int8PtrTy;
	Type *Int8PtrPtrTy;
	Constant *Int32Zero;
	Value *V; // current value
	StringMap<Value *> nameMap;

	public:
		ToIRVisitor(Module *M) : M(M), Builder(M->getContext()){
			VoidTy = Type::getVoidTy(M->getContext());
			Int32Ty = Type::getInt32Ty(M->getContext());
			Int8PtrTy = Type::getInt8PtrTy(M->getContext());
			Int8PtrPtrTy = Int8PtrTy->getPointerTo();
			Int32Zero = ConstantInt::get(Int32Ty, 0, true);
		}

		void run(AST *Tree) {
			FunctionType *MainFnTy = FunctionType::get(Int32Ty, {Int32Ty, Int8PtrPtrTy}, false);
			Function *MainFn = Function::Create(MainFnTy, GlobalValue::ExternalLinkage, "main", M);
			BasicBlock *BB = BasicBlock::Create(M->getContext(), "entry", MainFn);
			Builder.SetInsertPoint(BB);

			Tree->accept(*this);

			// write the result to the console
			FunctionType *WriteToConsoleFnTy = FunctionType::get(VoidTy, {Int32Ty}, false);
			Function *WriteToConsoleFn = Function::Create(WriteToConsoleFnTy, GlobalValue::ExternalLinkage, "calc_write", M); 
		    Builder.CreateCall(WriteToConsoleFnTy, WriteToConsoleFn, {V});

			Builder.CreateRet(Int32Zero);
		}

		virtual void visit(BinaryOp &Node) override {
			Node.getLeft()->accept(*this);
			Value *Left = V;
			Node.getRight()->accept(*this);
			Value *Right = V;

			switch (Node.getOperator()){
				case BinaryOp::Plus:
					V = Builder.CreateNSWAdd(Left, Right);
					break;
				case BinaryOp::Minus:
					V = Builder.CreateNSWSub(Left, Right);
					break;
				case BinaryOp::Mul:
					V = Builder.CreateNSWMul(Left, Right);
					break;
				case BinaryOp::Div:
					V = Builder.CreateSDiv(Left, Right);
					break;
				case BinaryOp::Pow:
				case BinaryOp::Exp:
				case BinaryOp::Rho:
				case BinaryOp::Itoa:
					cout << "error, binary operation not implemented, " << Node.getOperator() << endl; 
					break;
				default:
					cout << "error, unsupported binary operation, " << Node.getOperator() << endl;
					break;
			}
		};

		virtual  void visit (UnaryOp &Node) override {
			Node.getOperand()->accept(*this);
			Value *Left = V;

			switch (Node.getOperator()){
				case UnaryOp::Itoa:
					cout << "todo: handle `itoa` operator";
					break;
				case UnaryOp::Rand:
					cout << "todo: handle `rand` operator";
					break;
				default:
					cout << "error, unsupported unary operator, " << Node.getOperator() << endl;
					break;
			}
		};

		virtual void visit (Expression &Node) override {
	    	Node.accept(*this);
		};

		virtual void visit (Factor &Node) override {
			int intVal;
			Node.getVal().getAsInteger(10, intVal);
			V = ConstantInt::get(Int32Ty, intVal, true);
		};
};
}

void CodeGen::compile(AST *Tree) {
	LLVMContext Ctx;
	Module *M = new Module("bignum", Ctx);
	ToIRVisitor ToIR(M);
	ToIR.run(Tree);
	M->print(outs(), nullptr);
}
