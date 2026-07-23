
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

// EnterSizePrefix is called when production sizePrefix is entered.
func (s *BasePaxoListener) EnterSizePrefix(ctx *SizePrefixContext) {}

// ExitSizePrefix is called when production sizePrefix is exited.
func (s *BasePaxoListener) ExitSizePrefix(ctx *SizePrefixContext) {}

// EnterAssignment is called when production assignment is entered.
func (s *BasePaxoListener) EnterAssignment(ctx *AssignmentContext) {}

// ExitAssignment is called when production assignment is exited.
func (s *BasePaxoListener) ExitAssignment(ctx *AssignmentContext) {}

// EnterIfElseStatement is called when production ifElseStatement is entered.
func (s *BasePaxoListener) EnterIfElseStatement(ctx *IfElseStatementContext) {}

// ExitIfElseStatement is called when production ifElseStatement is exited.
func (s *BasePaxoListener) ExitIfElseStatement(ctx *IfElseStatementContext) {}

// EnterMatchStatement is called when production matchStatement is entered.
func (s *BasePaxoListener) EnterMatchStatement(ctx *MatchStatementContext) {}

// ExitMatchStatement is called when production matchStatement is exited.
func (s *BasePaxoListener) ExitMatchStatement(ctx *MatchStatementContext) {}

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

// EnterArgumentList is called when production argumentList is entered.
func (s *BasePaxoListener) EnterArgumentList(ctx *ArgumentListContext) {}

// ExitArgumentList is called when production argumentList is exited.
func (s *BasePaxoListener) ExitArgumentList(ctx *ArgumentListContext) {}

// EnterArrayAccessExpr is called when production arrayAccessExpr is entered.
func (s *BasePaxoListener) EnterArrayAccessExpr(ctx *ArrayAccessExprContext) {}

// ExitArrayAccessExpr is called when production arrayAccessExpr is exited.
func (s *BasePaxoListener) ExitArrayAccessExpr(ctx *ArrayAccessExprContext) {}

// EnterMultDivExpr is called when production multDivExpr is entered.
func (s *BasePaxoListener) EnterMultDivExpr(ctx *MultDivExprContext) {}

// ExitMultDivExpr is called when production multDivExpr is exited.
func (s *BasePaxoListener) ExitMultDivExpr(ctx *MultDivExprContext) {}

// EnterAddSubExpr is called when production addSubExpr is entered.
func (s *BasePaxoListener) EnterAddSubExpr(ctx *AddSubExprContext) {}

// ExitAddSubExpr is called when production addSubExpr is exited.
func (s *BasePaxoListener) ExitAddSubExpr(ctx *AddSubExprContext) {}

// EnterShiftExpr is called when production shiftExpr is entered.
func (s *BasePaxoListener) EnterShiftExpr(ctx *ShiftExprContext) {}

// ExitShiftExpr is called when production shiftExpr is exited.
func (s *BasePaxoListener) ExitShiftExpr(ctx *ShiftExprContext) {}

// EnterRelationalExpr is called when production relationalExpr is entered.
func (s *BasePaxoListener) EnterRelationalExpr(ctx *RelationalExprContext) {}

// ExitRelationalExpr is called when production relationalExpr is exited.
func (s *BasePaxoListener) ExitRelationalExpr(ctx *RelationalExprContext) {}

// EnterBitwiseExpr is called when production bitwiseExpr is entered.
func (s *BasePaxoListener) EnterBitwiseExpr(ctx *BitwiseExprContext) {}

// ExitBitwiseExpr is called when production bitwiseExpr is exited.
func (s *BasePaxoListener) ExitBitwiseExpr(ctx *BitwiseExprContext) {}

// EnterArrayLiteral is called when production arrayLiteral is entered.
func (s *BasePaxoListener) EnterArrayLiteral(ctx *ArrayLiteralContext) {}

// ExitArrayLiteral is called when production arrayLiteral is exited.
func (s *BasePaxoListener) ExitArrayLiteral(ctx *ArrayLiteralContext) {}

// EnterArrayAccess is called when production arrayAccess is entered.
func (s *BasePaxoListener) EnterArrayAccess(ctx *ArrayAccessContext) {}

// ExitArrayAccess is called when production arrayAccess is exited.
func (s *BasePaxoListener) ExitArrayAccess(ctx *ArrayAccessContext) {}
