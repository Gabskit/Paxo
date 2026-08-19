
package parser // Paxo

import "github.com/antlr4-go/antlr/v4"


// PaxoListener is a complete listener for a parse tree produced by PaxoParser.
type PaxoListener interface {
	antlr.ParseTreeListener

	// EnterProgram is called when entering the program production.
	EnterProgram(c *ProgramContext)

	// EnterStatement is called when entering the statement production.
	EnterStatement(c *StatementContext)

	// EnterVarDeclaration is called when entering the varDeclaration production.
	EnterVarDeclaration(c *VarDeclarationContext)

	// EnterType is called when entering the type production.
	EnterType(c *TypeContext)

	// EnterScope is called when entering the scope production.
	EnterScope(c *ScopeContext)

	// EnterAssignment is called when entering the assignment production.
	EnterAssignment(c *AssignmentContext)

	// EnterCondStatement is called when entering the condStatement production.
	EnterCondStatement(c *CondStatementContext)

	// EnterMatchCase is called when entering the matchCase production.
	EnterMatchCase(c *MatchCaseContext)

	// EnterLoopStatement is called when entering the loopStatement production.
	EnterLoopStatement(c *LoopStatementContext)

	// EnterLoopMode is called when entering the loopMode production.
	EnterLoopMode(c *LoopModeContext)

	// EnterLoopDelimiter is called when entering the loopDelimiter production.
	EnterLoopDelimiter(c *LoopDelimiterContext)

	// EnterLoopEndDelimiter is called when entering the loopEndDelimiter production.
	EnterLoopEndDelimiter(c *LoopEndDelimiterContext)

	// EnterTryCatchStatement is called when entering the tryCatchStatement production.
	EnterTryCatchStatement(c *TryCatchStatementContext)

	// EnterFunctionDeclaration is called when entering the functionDeclaration production.
	EnterFunctionDeclaration(c *FunctionDeclarationContext)

	// EnterPkgDeclaration is called when entering the pkgDeclaration production.
	EnterPkgDeclaration(c *PkgDeclarationContext)

	// EnterBlock is called when entering the block production.
	EnterBlock(c *BlockContext)

	// EnterParameterList is called when entering the parameterList production.
	EnterParameterList(c *ParameterListContext)

	// EnterArgumentList is called when entering the argumentList production.
	EnterArgumentList(c *ArgumentListContext)

	// EnterCallExpr is called when entering the callExpr production.
	EnterCallExpr(c *CallExprContext)

	// EnterArrayAccessExpr is called when entering the arrayAccessExpr production.
	EnterArrayAccessExpr(c *ArrayAccessExprContext)

	// EnterNotgateExpr is called when entering the notgateExpr production.
	EnterNotgateExpr(c *NotgateExprContext)

	// EnterIntLitExpr is called when entering the intLitExpr production.
	EnterIntLitExpr(c *IntLitExprContext)

	// EnterDecLitExpr is called when entering the decLitExpr production.
	EnterDecLitExpr(c *DecLitExprContext)

	// EnterCharLitExpr is called when entering the charLitExpr production.
	EnterCharLitExpr(c *CharLitExprContext)

	// EnterStringLitExpr is called when entering the stringLitExpr production.
	EnterStringLitExpr(c *StringLitExprContext)

	// EnterBoolBitExpr is called when entering the boolBitExpr production.
	EnterBoolBitExpr(c *BoolBitExprContext)

	// EnterBoolTritExpr is called when entering the boolTritExpr production.
	EnterBoolTritExpr(c *BoolTritExprContext)

	// EnterPtrLitExpr is called when entering the ptrLitExpr production.
	EnterPtrLitExpr(c *PtrLitExprContext)

	// EnterArrayLitExpr is called when entering the arrayLitExpr production.
	EnterArrayLitExpr(c *ArrayLitExprContext)

	// EnterArrayAccExpr is called when entering the arrayAccExpr production.
	EnterArrayAccExpr(c *ArrayAccExprContext)

	// EnterIdentExpr is called when entering the identExpr production.
	EnterIdentExpr(c *IdentExprContext)

	// EnterPkgExpr is called when entering the pkgExpr production.
	EnterPkgExpr(c *PkgExprContext)

	// EnterFuncExpr is called when entering the funcExpr production.
	EnterFuncExpr(c *FuncExprContext)

	// EnterMultDivExpr is called when entering the multDivExpr production.
	EnterMultDivExpr(c *MultDivExprContext)

	// EnterAddSubExpr is called when entering the addSubExpr production.
	EnterAddSubExpr(c *AddSubExprContext)

	// EnterShiftExpr is called when entering the shiftExpr production.
	EnterShiftExpr(c *ShiftExprContext)

	// EnterRelationalExpr is called when entering the relationalExpr production.
	EnterRelationalExpr(c *RelationalExprContext)

	// EnterBitwiseExpr is called when entering the bitwiseExpr production.
	EnterBitwiseExpr(c *BitwiseExprContext)

	// EnterArrayLiteral is called when entering the arrayLiteral production.
	EnterArrayLiteral(c *ArrayLiteralContext)

	// EnterArrayAccess is called when entering the arrayAccess production.
	EnterArrayAccess(c *ArrayAccessContext)

	// ExitProgram is called when exiting the program production.
	ExitProgram(c *ProgramContext)

	// ExitStatement is called when exiting the statement production.
	ExitStatement(c *StatementContext)

	// ExitVarDeclaration is called when exiting the varDeclaration production.
	ExitVarDeclaration(c *VarDeclarationContext)

	// ExitType is called when exiting the type production.
	ExitType(c *TypeContext)

	// ExitScope is called when exiting the scope production.
	ExitScope(c *ScopeContext)

	// ExitAssignment is called when exiting the assignment production.
	ExitAssignment(c *AssignmentContext)

	// ExitCondStatement is called when exiting the condStatement production.
	ExitCondStatement(c *CondStatementContext)

	// ExitMatchCase is called when exiting the matchCase production.
	ExitMatchCase(c *MatchCaseContext)

	// ExitLoopStatement is called when exiting the loopStatement production.
	ExitLoopStatement(c *LoopStatementContext)

	// ExitLoopMode is called when exiting the loopMode production.
	ExitLoopMode(c *LoopModeContext)

	// ExitLoopDelimiter is called when exiting the loopDelimiter production.
	ExitLoopDelimiter(c *LoopDelimiterContext)

	// ExitLoopEndDelimiter is called when exiting the loopEndDelimiter production.
	ExitLoopEndDelimiter(c *LoopEndDelimiterContext)

	// ExitTryCatchStatement is called when exiting the tryCatchStatement production.
	ExitTryCatchStatement(c *TryCatchStatementContext)

	// ExitFunctionDeclaration is called when exiting the functionDeclaration production.
	ExitFunctionDeclaration(c *FunctionDeclarationContext)

	// ExitPkgDeclaration is called when exiting the pkgDeclaration production.
	ExitPkgDeclaration(c *PkgDeclarationContext)

	// ExitBlock is called when exiting the block production.
	ExitBlock(c *BlockContext)

	// ExitParameterList is called when exiting the parameterList production.
	ExitParameterList(c *ParameterListContext)

	// ExitArgumentList is called when exiting the argumentList production.
	ExitArgumentList(c *ArgumentListContext)

	// ExitCallExpr is called when exiting the callExpr production.
	ExitCallExpr(c *CallExprContext)

	// ExitArrayAccessExpr is called when exiting the arrayAccessExpr production.
	ExitArrayAccessExpr(c *ArrayAccessExprContext)

	// ExitNotgateExpr is called when exiting the notgateExpr production.
	ExitNotgateExpr(c *NotgateExprContext)

	// ExitIntLitExpr is called when exiting the intLitExpr production.
	ExitIntLitExpr(c *IntLitExprContext)

	// ExitDecLitExpr is called when exiting the decLitExpr production.
	ExitDecLitExpr(c *DecLitExprContext)

	// ExitCharLitExpr is called when exiting the charLitExpr production.
	ExitCharLitExpr(c *CharLitExprContext)

	// ExitStringLitExpr is called when exiting the stringLitExpr production.
	ExitStringLitExpr(c *StringLitExprContext)

	// ExitBoolBitExpr is called when exiting the boolBitExpr production.
	ExitBoolBitExpr(c *BoolBitExprContext)

	// ExitBoolTritExpr is called when exiting the boolTritExpr production.
	ExitBoolTritExpr(c *BoolTritExprContext)

	// ExitPtrLitExpr is called when exiting the ptrLitExpr production.
	ExitPtrLitExpr(c *PtrLitExprContext)

	// ExitArrayLitExpr is called when exiting the arrayLitExpr production.
	ExitArrayLitExpr(c *ArrayLitExprContext)

	// ExitArrayAccExpr is called when exiting the arrayAccExpr production.
	ExitArrayAccExpr(c *ArrayAccExprContext)

	// ExitIdentExpr is called when exiting the identExpr production.
	ExitIdentExpr(c *IdentExprContext)

	// ExitPkgExpr is called when exiting the pkgExpr production.
	ExitPkgExpr(c *PkgExprContext)

	// ExitFuncExpr is called when exiting the funcExpr production.
	ExitFuncExpr(c *FuncExprContext)

	// ExitMultDivExpr is called when exiting the multDivExpr production.
	ExitMultDivExpr(c *MultDivExprContext)

	// ExitAddSubExpr is called when exiting the addSubExpr production.
	ExitAddSubExpr(c *AddSubExprContext)

	// ExitShiftExpr is called when exiting the shiftExpr production.
	ExitShiftExpr(c *ShiftExprContext)

	// ExitRelationalExpr is called when exiting the relationalExpr production.
	ExitRelationalExpr(c *RelationalExprContext)

	// ExitBitwiseExpr is called when exiting the bitwiseExpr production.
	ExitBitwiseExpr(c *BitwiseExprContext)

	// ExitArrayLiteral is called when exiting the arrayLiteral production.
	ExitArrayLiteral(c *ArrayLiteralContext)

	// ExitArrayAccess is called when exiting the arrayAccess production.
	ExitArrayAccess(c *ArrayAccessContext)
}
