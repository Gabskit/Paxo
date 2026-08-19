// Code generated from Paxo.g4 by ANTLR 4.13.1. DO NOT EDIT.

package parser // Paxo

import "github.com/antlr4-go/antlr/v4"

// A complete Visitor for a parse tree produced by PaxoParser.
type PaxoVisitor interface {
	antlr.ParseTreeVisitor

	// Visit a parse tree produced by PaxoParser#program.
	VisitProgram(ctx *ProgramContext) interface{}

	// Visit a parse tree produced by PaxoParser#statement.
	VisitStatement(ctx *StatementContext) interface{}

	// Visit a parse tree produced by PaxoParser#varDeclaration.
	VisitVarDeclaration(ctx *VarDeclarationContext) interface{}

	// Visit a parse tree produced by PaxoParser#type.
	VisitType(ctx *TypeContext) interface{}

	// Visit a parse tree produced by PaxoParser#scope.
	VisitScope(ctx *ScopeContext) interface{}

	// Visit a parse tree produced by PaxoParser#assignment.
	VisitAssignment(ctx *AssignmentContext) interface{}

	// Visit a parse tree produced by PaxoParser#condStatement.
	VisitCondStatement(ctx *CondStatementContext) interface{}

	// Visit a parse tree produced by PaxoParser#matchCase.
	VisitMatchCase(ctx *MatchCaseContext) interface{}

	// Visit a parse tree produced by PaxoParser#loopStatement.
	VisitLoopStatement(ctx *LoopStatementContext) interface{}

	// Visit a parse tree produced by PaxoParser#loopMode.
	VisitLoopMode(ctx *LoopModeContext) interface{}

	// Visit a parse tree produced by PaxoParser#loopDelimiter.
	VisitLoopDelimiter(ctx *LoopDelimiterContext) interface{}

	// Visit a parse tree produced by PaxoParser#loopEndDelimiter.
	VisitLoopEndDelimiter(ctx *LoopEndDelimiterContext) interface{}

	// Visit a parse tree produced by PaxoParser#tryCatchStatement.
	VisitTryCatchStatement(ctx *TryCatchStatementContext) interface{}

	// Visit a parse tree produced by PaxoParser#functionDeclaration.
	VisitFunctionDeclaration(ctx *FunctionDeclarationContext) interface{}

	// Visit a parse tree produced by PaxoParser#pkgDeclaration.
	VisitPkgDeclaration(ctx *PkgDeclarationContext) interface{}

	// Visit a parse tree produced by PaxoParser#block.
	VisitBlock(ctx *BlockContext) interface{}

	// Visit a parse tree produced by PaxoParser#parameterList.
	VisitParameterList(ctx *ParameterListContext) interface{}

	// Visit a parse tree produced by PaxoParser#argumentList.
	VisitArgumentList(ctx *ArgumentListContext) interface{}

	// Visit a parse tree produced by PaxoParser#boolBitExpr.
	VisitBoolBitExpr(ctx *BoolBitExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#funcExpr.
	VisitFuncExpr(ctx *FuncExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#addSubExpr.
	VisitAddSubExpr(ctx *AddSubExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#notgateExpr.
	VisitNotgateExpr(ctx *NotgateExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#intLitExpr.
	VisitIntLitExpr(ctx *IntLitExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#decLitExpr.
	VisitDecLitExpr(ctx *DecLitExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#stringLitExpr.
	VisitStringLitExpr(ctx *StringLitExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#ptrLitExpr.
	VisitPtrLitExpr(ctx *PtrLitExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#relationalExpr.
	VisitRelationalExpr(ctx *RelationalExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#arrayAccExpr.
	VisitArrayAccExpr(ctx *ArrayAccExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#shiftExpr.
	VisitShiftExpr(ctx *ShiftExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#identExpr.
	VisitIdentExpr(ctx *IdentExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#bitwiseExpr.
	VisitBitwiseExpr(ctx *BitwiseExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#arrayLitExpr.
	VisitArrayLitExpr(ctx *ArrayLitExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#arrayAccessExpr.
	VisitArrayAccessExpr(ctx *ArrayAccessExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#charLitExpr.
	VisitCharLitExpr(ctx *CharLitExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#boolTritExpr.
	VisitBoolTritExpr(ctx *BoolTritExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#multDivExpr.
	VisitMultDivExpr(ctx *MultDivExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#callExpr.
	VisitCallExpr(ctx *CallExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#pkgExpr.
	VisitPkgExpr(ctx *PkgExprContext) interface{}

	// Visit a parse tree produced by PaxoParser#arrayLiteral.
	VisitArrayLiteral(ctx *ArrayLiteralContext) interface{}

	// Visit a parse tree produced by PaxoParser#arrayAccess.
	VisitArrayAccess(ctx *ArrayAccessContext) interface{}
}
