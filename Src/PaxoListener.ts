
import { ErrorNode, ParseTreeListener, ParserRuleContext, TerminalNode } from "antlr4ng";


import { ProgramContext } from "./PaxoParser.js";
import { StatementContext } from "./PaxoParser.js";
import { VarDeclarationContext } from "./PaxoParser.js";
import { SizePrefixContext } from "./PaxoParser.js";
import { AssignmentContext } from "./PaxoParser.js";
import { IfElseStatementContext } from "./PaxoParser.js";
import { MatchStatementContext } from "./PaxoParser.js";
import { MatchCaseContext } from "./PaxoParser.js";
import { LoopStatementContext } from "./PaxoParser.js";
import { LoopModeContext } from "./PaxoParser.js";
import { LoopDelimiterContext } from "./PaxoParser.js";
import { LoopEndDelimiterContext } from "./PaxoParser.js";
import { TryCatchStatementContext } from "./PaxoParser.js";
import { FunctionDeclarationContext } from "./PaxoParser.js";
import { PkgDeclarationContext } from "./PaxoParser.js";
import { BlockContext } from "./PaxoParser.js";
import { ParameterListContext } from "./PaxoParser.js";
import { ArgumentListContext } from "./PaxoParser.js";
import { ExpressionContext } from "./PaxoParser.js";
import { ArrayLiteralContext } from "./PaxoParser.js";
import { ArrayAccessContext } from "./PaxoParser.js";


/**
 * This interface defines a complete listener for a parse tree produced by
 * `PaxoParser`.
 */
export class PaxoListener implements ParseTreeListener {
    /**
     * Enter a parse tree produced by `PaxoParser.program`.
     * @param ctx the parse tree
     */
    enterProgram?: (ctx: ProgramContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.program`.
     * @param ctx the parse tree
     */
    exitProgram?: (ctx: ProgramContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.statement`.
     * @param ctx the parse tree
     */
    enterStatement?: (ctx: StatementContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.statement`.
     * @param ctx the parse tree
     */
    exitStatement?: (ctx: StatementContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.varDeclaration`.
     * @param ctx the parse tree
     */
    enterVarDeclaration?: (ctx: VarDeclarationContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.varDeclaration`.
     * @param ctx the parse tree
     */
    exitVarDeclaration?: (ctx: VarDeclarationContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.sizePrefix`.
     * @param ctx the parse tree
     */
    enterSizePrefix?: (ctx: SizePrefixContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.sizePrefix`.
     * @param ctx the parse tree
     */
    exitSizePrefix?: (ctx: SizePrefixContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.assignment`.
     * @param ctx the parse tree
     */
    enterAssignment?: (ctx: AssignmentContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.assignment`.
     * @param ctx the parse tree
     */
    exitAssignment?: (ctx: AssignmentContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.ifElseStatement`.
     * @param ctx the parse tree
     */
    enterIfElseStatement?: (ctx: IfElseStatementContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.ifElseStatement`.
     * @param ctx the parse tree
     */
    exitIfElseStatement?: (ctx: IfElseStatementContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.matchStatement`.
     * @param ctx the parse tree
     */
    enterMatchStatement?: (ctx: MatchStatementContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.matchStatement`.
     * @param ctx the parse tree
     */
    exitMatchStatement?: (ctx: MatchStatementContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.matchCase`.
     * @param ctx the parse tree
     */
    enterMatchCase?: (ctx: MatchCaseContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.matchCase`.
     * @param ctx the parse tree
     */
    exitMatchCase?: (ctx: MatchCaseContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.loopStatement`.
     * @param ctx the parse tree
     */
    enterLoopStatement?: (ctx: LoopStatementContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.loopStatement`.
     * @param ctx the parse tree
     */
    exitLoopStatement?: (ctx: LoopStatementContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.loopMode`.
     * @param ctx the parse tree
     */
    enterLoopMode?: (ctx: LoopModeContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.loopMode`.
     * @param ctx the parse tree
     */
    exitLoopMode?: (ctx: LoopModeContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.loopDelimiter`.
     * @param ctx the parse tree
     */
    enterLoopDelimiter?: (ctx: LoopDelimiterContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.loopDelimiter`.
     * @param ctx the parse tree
     */
    exitLoopDelimiter?: (ctx: LoopDelimiterContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.loopEndDelimiter`.
     * @param ctx the parse tree
     */
    enterLoopEndDelimiter?: (ctx: LoopEndDelimiterContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.loopEndDelimiter`.
     * @param ctx the parse tree
     */
    exitLoopEndDelimiter?: (ctx: LoopEndDelimiterContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.tryCatchStatement`.
     * @param ctx the parse tree
     */
    enterTryCatchStatement?: (ctx: TryCatchStatementContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.tryCatchStatement`.
     * @param ctx the parse tree
     */
    exitTryCatchStatement?: (ctx: TryCatchStatementContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.functionDeclaration`.
     * @param ctx the parse tree
     */
    enterFunctionDeclaration?: (ctx: FunctionDeclarationContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.functionDeclaration`.
     * @param ctx the parse tree
     */
    exitFunctionDeclaration?: (ctx: FunctionDeclarationContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.pkgDeclaration`.
     * @param ctx the parse tree
     */
    enterPkgDeclaration?: (ctx: PkgDeclarationContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.pkgDeclaration`.
     * @param ctx the parse tree
     */
    exitPkgDeclaration?: (ctx: PkgDeclarationContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.block`.
     * @param ctx the parse tree
     */
    enterBlock?: (ctx: BlockContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.block`.
     * @param ctx the parse tree
     */
    exitBlock?: (ctx: BlockContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.parameterList`.
     * @param ctx the parse tree
     */
    enterParameterList?: (ctx: ParameterListContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.parameterList`.
     * @param ctx the parse tree
     */
    exitParameterList?: (ctx: ParameterListContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.argumentList`.
     * @param ctx the parse tree
     */
    enterArgumentList?: (ctx: ArgumentListContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.argumentList`.
     * @param ctx the parse tree
     */
    exitArgumentList?: (ctx: ArgumentListContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.expression`.
     * @param ctx the parse tree
     */
    enterExpression?: (ctx: ExpressionContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.expression`.
     * @param ctx the parse tree
     */
    exitExpression?: (ctx: ExpressionContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.arrayLiteral`.
     * @param ctx the parse tree
     */
    enterArrayLiteral?: (ctx: ArrayLiteralContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.arrayLiteral`.
     * @param ctx the parse tree
     */
    exitArrayLiteral?: (ctx: ArrayLiteralContext) => void;
    /**
     * Enter a parse tree produced by `PaxoParser.arrayAccess`.
     * @param ctx the parse tree
     */
    enterArrayAccess?: (ctx: ArrayAccessContext) => void;
    /**
     * Exit a parse tree produced by `PaxoParser.arrayAccess`.
     * @param ctx the parse tree
     */
    exitArrayAccess?: (ctx: ArrayAccessContext) => void;

    visitTerminal(node: TerminalNode): void {}
    visitErrorNode(node: ErrorNode): void {}
    enterEveryRule(node: ParserRuleContext): void {}
    exitEveryRule(node: ParserRuleContext): void {}
}

