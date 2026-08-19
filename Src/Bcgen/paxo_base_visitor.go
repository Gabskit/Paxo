// Code generated from Paxo.g4 by ANTLR 4.13.1. DO NOT EDIT.

package parser // Paxo

import "github.com/antlr4-go/antlr/v4"

type BasePaxoVisitor struct {
	*antlr.BaseParseTreeVisitor
}

func (v *BasePaxoVisitor) VisitProgram(ctx *ProgramContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitStatement(ctx *StatementContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitVarDeclaration(ctx *VarDeclarationContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitType(ctx *TypeContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitScope(ctx *ScopeContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitAssignment(ctx *AssignmentContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitCondStatement(ctx *CondStatementContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitMatchCase(ctx *MatchCaseContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitLoopStatement(ctx *LoopStatementContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitLoopMode(ctx *LoopModeContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitLoopDelimiter(ctx *LoopDelimiterContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitLoopEndDelimiter(ctx *LoopEndDelimiterContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitTryCatchStatement(ctx *TryCatchStatementContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitFunctionDeclaration(ctx *FunctionDeclarationContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitPkgDeclaration(ctx *PkgDeclarationContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitBlock(ctx *BlockContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitParameterList(ctx *ParameterListContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitArgumentList(ctx *ArgumentListContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitBoolBitExpr(ctx *BoolBitExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitFuncExpr(ctx *FuncExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitAddSubExpr(ctx *AddSubExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitNotgateExpr(ctx *NotgateExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitIntLitExpr(ctx *IntLitExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitDecLitExpr(ctx *DecLitExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitStringLitExpr(ctx *StringLitExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitPtrLitExpr(ctx *PtrLitExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitRelationalExpr(ctx *RelationalExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitArrayAccExpr(ctx *ArrayAccExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitShiftExpr(ctx *ShiftExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitIdentExpr(ctx *IdentExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitBitwiseExpr(ctx *BitwiseExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitArrayLitExpr(ctx *ArrayLitExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitArrayAccessExpr(ctx *ArrayAccessExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitCharLitExpr(ctx *CharLitExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitBoolTritExpr(ctx *BoolTritExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitMultDivExpr(ctx *MultDivExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitCallExpr(ctx *CallExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitPkgExpr(ctx *PkgExprContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitArrayLiteral(ctx *ArrayLiteralContext) interface{} {
	return v.VisitChildren(ctx)
}

func (v *BasePaxoVisitor) VisitArrayAccess(ctx *ArrayAccessContext) interface{} {
	return v.VisitChildren(ctx)
}
