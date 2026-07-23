
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

	// EnterSizePrefix is called when entering the sizePrefix production.
	EnterSizePrefix(c *SizePrefixContext)

	// EnterAssignment is called when entering the assignment production.
	EnterAssignment(c *AssignmentContext)

	// EnterIfElseStatement is called when entering the ifElseStatement production.
	EnterIfElseStatement(c *IfElseStatementContext)

	// EnterMatchStatement is called when entering the matchStatement production.
	EnterMatchStatement(c *MatchStatementContext)

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

	// EnterArrayAccessExpr is called when entering the arrayAccessExpr production.
	EnterArrayAccessExpr(c *ArrayAccessExprContext)

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

	// ExitSizePrefix is called when exiting the sizePrefix production.
	ExitSizePrefix(c *SizePrefixContext)

	// ExitAssignment is called when exiting the assignment production.
	ExitAssignment(c *AssignmentContext)

	// ExitIfElseStatement is called when exiting the ifElseStatement production.
	ExitIfElseStatement(c *IfElseStatementContext)

	// ExitMatchStatement is called when exiting the matchStatement production.
	ExitMatchStatement(c *MatchStatementContext)

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

	// ExitArrayAccessExpr is called when exiting the arrayAccessExpr production.
	ExitArrayAccessExpr(c *ArrayAccessExprContext)

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
