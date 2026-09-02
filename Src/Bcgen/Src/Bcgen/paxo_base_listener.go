// Code generated from ./Src/Bcgen/Paxo.g4 by ANTLR 4.13.1. DO NOT EDIT.

package parser // Paxo

import "github.com/antlr4-go/antlr/v4"

// BasePaxoListener is a complete listener for a parse tree produced by PaxoParser.
type BasePaxoListener struct{}

var _ PaxoListener = &BasePaxoListener{}

// VisitTerminal is called when a terminal node is visited.
func (s *BasePaxoListener) VisitTerminal(node antlr.TerminalNode) {}

// VisitErrorNode is called when an error node is visited.
func (s *BasePaxoListener) VisitErrorNode(node antlr.ErrorNode) {}

// EnterEveryRule is called when any rule is entered.
func (s *BasePaxoListener) EnterEveryRule(ctx antlr.ParserRuleContext) {}

// ExitEveryRule is called when any rule is exited.
func (s *BasePaxoListener) ExitEveryRule(ctx antlr.ParserRuleContext) {}

// EnterProgram is called when production program is entered.
func (s *BasePaxoListener) EnterProgram(ctx *ProgramContext) {}

// ExitProgram is called when production program is exited.
func (s *BasePaxoListener) ExitProgram(ctx *ProgramContext) {}

// EnterStatement is called when production statement is entered.
func (s *BasePaxoListener) EnterStatement(ctx *StatementContext) {}

// ExitStatement is called when production statement is exited.
func (s *BasePaxoListener) ExitStatement(ctx *StatementContext) {}

// EnterVarDeclaration is called when production varDeclaration is entered.
func (s *BasePaxoListener) EnterVarDeclaration(ctx *VarDeclarationContext) {}

// ExitVarDeclaration is called when production varDeclaration is exited.
func (s *BasePaxoListener) ExitVarDeclaration(ctx *VarDeclarationContext) {}

// EnterType is called when production type is entered.
func (s *BasePaxoListener) EnterType(ctx *TypeContext) {}

// ExitType is called when production type is exited.
func (s *BasePaxoListener) ExitType(ctx *TypeContext) {}

// EnterScope is called when production scope is entered.
func (s *BasePaxoListener) EnterScope(ctx *ScopeContext) {}

// ExitScope is called when production scope is exited.
func (s *BasePaxoListener) ExitScope(ctx *ScopeContext) {}

// EnterAssignment is called when production assignment is entered.
func (s *BasePaxoListener) EnterAssignment(ctx *AssignmentContext) {}

// ExitAssignment is called when production assignment is exited.
func (s *BasePaxoListener) ExitAssignment(ctx *AssignmentContext) {}

// EnterCondStatement is called when production condStatement is entered.
func (s *BasePaxoListener) EnterCondStatement(ctx *CondStatementContext) {}

// ExitCondStatement is called when production condStatement is exited.
func (s *BasePaxoListener) ExitCondStatement(ctx *CondStatementContext) {}

// EnterMatchCase is called when production matchCase is entered.
func (s *BasePaxoListener) EnterMatchCase(ctx *MatchCaseContext) {}

// ExitMatchCase is called when production matchCase is exited.
func (s *BasePaxoListener) ExitMatchCase(ctx *MatchCaseContext) {}

// EnterLoopStatement is called when production loopStatement is entered.
func (s *BasePaxoListener) EnterLoopStatement(ctx *LoopStatementContext) {}

// ExitLoopStatement is called when production loopStatement is exited.
func (s *BasePaxoListener) ExitLoopStatement(ctx *LoopStatementContext) {}

// EnterLoopMode is called when production loopMode is entered.
func (s *BasePaxoListener) EnterLoopMode(ctx *LoopModeContext) {}

// ExitLoopMode is called when production loopMode is exited.
func (s *BasePaxoListener) ExitLoopMode(ctx *LoopModeContext) {}

// EnterLoopDelimiter is called when production loopDelimiter is entered.
func (s *BasePaxoListener) EnterLoopDelimiter(ctx *LoopDelimiterContext) {}

// ExitLoopDelimiter is called when production loopDelimiter is exited.
func (s *BasePaxoListener) ExitLoopDelimiter(ctx *LoopDelimiterContext) {}

// EnterLoopEndDelimiter is called when production loopEndDelimiter is entered.
func (s *BasePaxoListener) EnterLoopEndDelimiter(ctx *LoopEndDelimiterContext) {}

// ExitLoopEndDelimiter is called when production loopEndDelimiter is exited.
func (s *BasePaxoListener) ExitLoopEndDelimiter(ctx *LoopEndDelimiterContext) {}

// EnterTryCatchStatement is called when production tryCatchStatement is entered.
func (s *BasePaxoListener) EnterTryCatchStatement(ctx *TryCatchStatementContext) {}

// ExitTryCatchStatement is called when production tryCatchStatement is exited.
func (s *BasePaxoListener) ExitTryCatchStatement(ctx *TryCatchStatementContext) {}

// EnterFunctionDeclaration is called when production functionDeclaration is entered.
func (s *BasePaxoListener) EnterFunctionDeclaration(ctx *FunctionDeclarationContext) {}

// ExitFunctionDeclaration is called when production functionDeclaration is exited.
func (s *BasePaxoListener) ExitFunctionDeclaration(ctx *FunctionDeclarationContext) {}

// EnterPkgDeclaration is called when production pkgDeclaration is entered.
func (s *BasePaxoListener) EnterPkgDeclaration(ctx *PkgDeclarationContext) {}

// ExitPkgDeclaration is called when production pkgDeclaration is exited.
func (s *BasePaxoListener) ExitPkgDeclaration(ctx *PkgDeclarationContext) {}

// EnterBlock is called when production block is entered.
func (s *BasePaxoListener) EnterBlock(ctx *BlockContext) {}

// ExitBlock is called when production block is exited.
func (s *BasePaxoListener) ExitBlock(ctx *BlockContext) {}

// EnterParameterList is called when production parameterList is entered.
func (s *BasePaxoListener) EnterParameterList(ctx *ParameterListContext) {}

// ExitParameterList is called when production parameterList is exited.
func (s *BasePaxoListener) ExitParameterList(ctx *ParameterListContext) {}

// EnterReturnStatement is called when production returnStatement is entered.
func (s *BasePaxoListener) EnterReturnStatement(ctx *ReturnStatementContext) {}

// ExitReturnStatement is called when production returnStatement is exited.
func (s *BasePaxoListener) ExitReturnStatement(ctx *ReturnStatementContext) {}

// EnterThrowStatement is called when production throwStatement is entered.
func (s *BasePaxoListener) EnterThrowStatement(ctx *ThrowStatementContext) {}

// ExitThrowStatement is called when production throwStatement is exited.
func (s *BasePaxoListener) ExitThrowStatement(ctx *ThrowStatementContext) {}

// EnterArgumentList is called when production argumentList is entered.
func (s *BasePaxoListener) EnterArgumentList(ctx *ArgumentListContext) {}

// ExitArgumentList is called when production argumentList is exited.
func (s *BasePaxoListener) ExitArgumentList(ctx *ArgumentListContext) {}

// EnterBoolBitExpr is called when production boolBitExpr is entered.
func (s *BasePaxoListener) EnterBoolBitExpr(ctx *BoolBitExprContext) {}

// ExitBoolBitExpr is called when production boolBitExpr is exited.
func (s *BasePaxoListener) ExitBoolBitExpr(ctx *BoolBitExprContext) {}

// EnterFuncExpr is called when production funcExpr is entered.
func (s *BasePaxoListener) EnterFuncExpr(ctx *FuncExprContext) {}

// ExitFuncExpr is called when production funcExpr is exited.
func (s *BasePaxoListener) ExitFuncExpr(ctx *FuncExprContext) {}

// EnterAddSubExpr is called when production addSubExpr is entered.
func (s *BasePaxoListener) EnterAddSubExpr(ctx *AddSubExprContext) {}

// ExitAddSubExpr is called when production addSubExpr is exited.
func (s *BasePaxoListener) ExitAddSubExpr(ctx *AddSubExprContext) {}

// EnterNotgateExpr is called when production notgateExpr is entered.
func (s *BasePaxoListener) EnterNotgateExpr(ctx *NotgateExprContext) {}

// ExitNotgateExpr is called when production notgateExpr is exited.
func (s *BasePaxoListener) ExitNotgateExpr(ctx *NotgateExprContext) {}

// EnterIntLitExpr is called when production intLitExpr is entered.
func (s *BasePaxoListener) EnterIntLitExpr(ctx *IntLitExprContext) {}

// ExitIntLitExpr is called when production intLitExpr is exited.
func (s *BasePaxoListener) ExitIntLitExpr(ctx *IntLitExprContext) {}

// EnterDecLitExpr is called when production decLitExpr is entered.
func (s *BasePaxoListener) EnterDecLitExpr(ctx *DecLitExprContext) {}

// ExitDecLitExpr is called when production decLitExpr is exited.
func (s *BasePaxoListener) ExitDecLitExpr(ctx *DecLitExprContext) {}

// EnterStringLitExpr is called when production stringLitExpr is entered.
func (s *BasePaxoListener) EnterStringLitExpr(ctx *StringLitExprContext) {}

// ExitStringLitExpr is called when production stringLitExpr is exited.
func (s *BasePaxoListener) ExitStringLitExpr(ctx *StringLitExprContext) {}

// EnterPtrLitExpr is called when production ptrLitExpr is entered.
func (s *BasePaxoListener) EnterPtrLitExpr(ctx *PtrLitExprContext) {}

// ExitPtrLitExpr is called when production ptrLitExpr is exited.
func (s *BasePaxoListener) ExitPtrLitExpr(ctx *PtrLitExprContext) {}

// EnterRelationalExpr is called when production relationalExpr is entered.
func (s *BasePaxoListener) EnterRelationalExpr(ctx *RelationalExprContext) {}

// ExitRelationalExpr is called when production relationalExpr is exited.
func (s *BasePaxoListener) ExitRelationalExpr(ctx *RelationalExprContext) {}

// EnterDotAccessExpr is called when production dotAccessExpr is entered.
func (s *BasePaxoListener) EnterDotAccessExpr(ctx *DotAccessExprContext) {}

// ExitDotAccessExpr is called when production dotAccessExpr is exited.
func (s *BasePaxoListener) ExitDotAccessExpr(ctx *DotAccessExprContext) {}

// EnterShiftExpr is called when production shiftExpr is entered.
func (s *BasePaxoListener) EnterShiftExpr(ctx *ShiftExprContext) {}

// ExitShiftExpr is called when production shiftExpr is exited.
func (s *BasePaxoListener) ExitShiftExpr(ctx *ShiftExprContext) {}

// EnterColLitExpr is called when production colLitExpr is entered.
func (s *BasePaxoListener) EnterColLitExpr(ctx *ColLitExprContext) {}

// ExitColLitExpr is called when production colLitExpr is exited.
func (s *BasePaxoListener) ExitColLitExpr(ctx *ColLitExprContext) {}

// EnterIdentExpr is called when production identExpr is entered.
func (s *BasePaxoListener) EnterIdentExpr(ctx *IdentExprContext) {}

// ExitIdentExpr is called when production identExpr is exited.
func (s *BasePaxoListener) ExitIdentExpr(ctx *IdentExprContext) {}

// EnterBitwiseExpr is called when production bitwiseExpr is entered.
func (s *BasePaxoListener) EnterBitwiseExpr(ctx *BitwiseExprContext) {}

// ExitBitwiseExpr is called when production bitwiseExpr is exited.
func (s *BasePaxoListener) ExitBitwiseExpr(ctx *BitwiseExprContext) {}

// EnterArrayLitExpr is called when production arrayLitExpr is entered.
func (s *BasePaxoListener) EnterArrayLitExpr(ctx *ArrayLitExprContext) {}

// ExitArrayLitExpr is called when production arrayLitExpr is exited.
func (s *BasePaxoListener) ExitArrayLitExpr(ctx *ArrayLitExprContext) {}

// EnterCharLitExpr is called when production charLitExpr is entered.
func (s *BasePaxoListener) EnterCharLitExpr(ctx *CharLitExprContext) {}

// ExitCharLitExpr is called when production charLitExpr is exited.
func (s *BasePaxoListener) ExitCharLitExpr(ctx *CharLitExprContext) {}

// EnterBoolTritExpr is called when production boolTritExpr is entered.
func (s *BasePaxoListener) EnterBoolTritExpr(ctx *BoolTritExprContext) {}

// ExitBoolTritExpr is called when production boolTritExpr is exited.
func (s *BasePaxoListener) ExitBoolTritExpr(ctx *BoolTritExprContext) {}

// EnterIndexedAccessExpr is called when production indexedAccessExpr is entered.
func (s *BasePaxoListener) EnterIndexedAccessExpr(ctx *IndexedAccessExprContext) {}

// ExitIndexedAccessExpr is called when production indexedAccessExpr is exited.
func (s *BasePaxoListener) ExitIndexedAccessExpr(ctx *IndexedAccessExprContext) {}

// EnterComLitExpr is called when production comLitExpr is entered.
func (s *BasePaxoListener) EnterComLitExpr(ctx *ComLitExprContext) {}

// ExitComLitExpr is called when production comLitExpr is exited.
func (s *BasePaxoListener) ExitComLitExpr(ctx *ComLitExprContext) {}

// EnterThisScopeExpr is called when production thisScopeExpr is entered.
func (s *BasePaxoListener) EnterThisScopeExpr(ctx *ThisScopeExprContext) {}

// ExitThisScopeExpr is called when production thisScopeExpr is exited.
func (s *BasePaxoListener) ExitThisScopeExpr(ctx *ThisScopeExprContext) {}

// EnterMultDivExpr is called when production multDivExpr is entered.
func (s *BasePaxoListener) EnterMultDivExpr(ctx *MultDivExprContext) {}

// ExitMultDivExpr is called when production multDivExpr is exited.
func (s *BasePaxoListener) ExitMultDivExpr(ctx *MultDivExprContext) {}

// EnterCallExpr is called when production callExpr is entered.
func (s *BasePaxoListener) EnterCallExpr(ctx *CallExprContext) {}

// ExitCallExpr is called when production callExpr is exited.
func (s *BasePaxoListener) ExitCallExpr(ctx *CallExprContext) {}

// EnterPkgExpr is called when production pkgExpr is entered.
func (s *BasePaxoListener) EnterPkgExpr(ctx *PkgExprContext) {}

// ExitPkgExpr is called when production pkgExpr is exited.
func (s *BasePaxoListener) ExitPkgExpr(ctx *PkgExprContext) {}

// EnterArrayLiteral is called when production arrayLiteral is entered.
func (s *BasePaxoListener) EnterArrayLiteral(ctx *ArrayLiteralContext) {}

// ExitArrayLiteral is called when production arrayLiteral is exited.
func (s *BasePaxoListener) ExitArrayLiteral(ctx *ArrayLiteralContext) {}
