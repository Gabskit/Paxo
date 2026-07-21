
import * as antlr from "antlr4ng";
import { Token } from "antlr4ng";

import { PaxoListener } from "./PaxoListener.js";
// for running tests with parameters, TODO: discuss strategy for typed parameters in CI
// eslint-disable-next-line no-unused-vars
type int = number;


export class PaxoParser extends antlr.Parser {
    public static readonly T__0 = 1;
    public static readonly T__1 = 2;
    public static readonly T__2 = 3;
    public static readonly T__3 = 4;
    public static readonly T__4 = 5;
    public static readonly T__5 = 6;
    public static readonly T__6 = 7;
    public static readonly T__7 = 8;
    public static readonly T__8 = 9;
    public static readonly T__9 = 10;
    public static readonly T__10 = 11;
    public static readonly T__11 = 12;
    public static readonly T__12 = 13;
    public static readonly T__13 = 14;
    public static readonly T__14 = 15;
    public static readonly T__15 = 16;
    public static readonly T__16 = 17;
    public static readonly T__17 = 18;
    public static readonly T__18 = 19;
    public static readonly T__19 = 20;
    public static readonly T__20 = 21;
    public static readonly T__21 = 22;
    public static readonly T__22 = 23;
    public static readonly T__23 = 24;
    public static readonly T__24 = 25;
    public static readonly T__25 = 26;
    public static readonly T__26 = 27;
    public static readonly T__27 = 28;
    public static readonly T__28 = 29;
    public static readonly T__29 = 30;
    public static readonly T__30 = 31;
    public static readonly T__31 = 32;
    public static readonly VAR_DECL = 33;
    public static readonly PKG = 34;
    public static readonly TRY = 35;
    public static readonly CATCH = 36;
    public static readonly ARROW = 37;
    public static readonly INCLUDE = 38;
    public static readonly PAUSE_MODE = 39;
    public static readonly PLAY_MODE = 40;
    public static readonly INT_LITERAL = 41;
    public static readonly UINT_LITERAL = 42;
    public static readonly DECIMAL_LITERAL = 43;
    public static readonly BOOLEAN = 44;
    public static readonly COMPLEX_LITERAL = 45;
    public static readonly IDENTIFIER = 46;
    public static readonly STRING_LITERAL = 47;
    public static readonly CHAR_LITERAL = 48;
    public static readonly EMSTRING_LITERAL = 49;
    public static readonly VECTOR = 50;
    public static readonly NANOTIME_LITERAL = 51;
    public static readonly SLICE_LITERAL = 52;
    public static readonly POINTER_LITERAL = 53;
    public static readonly IPV4_LITERAL = 54;
    public static readonly IPV6_LITERAL = 55;
    public static readonly LINE_COMMENT = 56;
    public static readonly BLOCK_COMMENT = 57;
    public static readonly WS = 58;
    public static readonly RULE_program = 0;
    public static readonly RULE_statement = 1;
    public static readonly RULE_varDeclaration = 2;
    public static readonly RULE_sizePrefix = 3;
    public static readonly RULE_assignment = 4;
    public static readonly RULE_ifElseStatement = 5;
    public static readonly RULE_matchStatement = 6;
    public static readonly RULE_matchCase = 7;
    public static readonly RULE_loopStatement = 8;
    public static readonly RULE_loopMode = 9;
    public static readonly RULE_loopDelimiter = 10;
    public static readonly RULE_loopEndDelimiter = 11;
    public static readonly RULE_tryCatchStatement = 12;
    public static readonly RULE_functionDeclaration = 13;
    public static readonly RULE_pkgDeclaration = 14;
    public static readonly RULE_block = 15;
    public static readonly RULE_parameterList = 16;
    public static readonly RULE_argumentList = 17;
    public static readonly RULE_expression = 18;
    public static readonly RULE_arrayLiteral = 19;
    public static readonly RULE_arrayAccess = 20;

    public static readonly literalNames = [
        null, "';'", "'<'", "'.'", "'>'", "'='", "'['", "']'", "'xxs'", 
        "'xs'", "'s'", "'l'", "'xl'", "'++'", "'--'", "'('", "')'", "'{'", 
        "'}'", "'->'", "'_'", "':'", "'|:'", "'\\uD834\uDD06'", "':|'", 
        "'\\uD834\uDD07'", "','", "'\\u2264'", "'\\u2265'", "'=='", "'\\u2260'", 
        "'\\u00AB'", "'\\u00BB'"
    ];

    public static readonly symbolicNames = [
        null, null, null, null, null, null, null, null, null, null, null, 
        null, null, null, null, null, null, null, null, null, null, null, 
        null, null, null, null, null, null, null, null, null, null, null, 
        "VAR_DECL", "PKG", "TRY", "CATCH", "ARROW", "INCLUDE", "PAUSE_MODE", 
        "PLAY_MODE", "INT_LITERAL", "UINT_LITERAL", "DECIMAL_LITERAL", "BOOLEAN", 
        "COMPLEX_LITERAL", "IDENTIFIER", "STRING_LITERAL", "CHAR_LITERAL", 
        "EMSTRING_LITERAL", "VECTOR", "NANOTIME_LITERAL", "SLICE_LITERAL", 
        "POINTER_LITERAL", "IPV4_LITERAL", "IPV6_LITERAL", "LINE_COMMENT", 
        "BLOCK_COMMENT", "WS"
    ];
    public static readonly ruleNames = [
        "program", "statement", "varDeclaration", "sizePrefix", "assignment", 
        "ifElseStatement", "matchStatement", "matchCase", "loopStatement", 
        "loopMode", "loopDelimiter", "loopEndDelimiter", "tryCatchStatement", 
        "functionDeclaration", "pkgDeclaration", "block", "parameterList", 
        "argumentList", "expression", "arrayLiteral", "arrayAccess",
    ];

    public get grammarFileName(): string { return "Paxo.g4"; }
    public get literalNames(): (string | null)[] { return PaxoParser.literalNames; }
    public get symbolicNames(): (string | null)[] { return PaxoParser.symbolicNames; }
    public get ruleNames(): string[] { return PaxoParser.ruleNames; }
    public get serializedATN(): number[] { return PaxoParser._serializedATN; }

    protected createFailedPredicateException(predicate?: string, message?: string): antlr.FailedPredicateException {
        return new antlr.FailedPredicateException(this, predicate, message);
    }

    public constructor(input: antlr.TokenStream) {
        super(input);
        this.interpreter = new antlr.ParserATNSimulator(this, PaxoParser._ATN, PaxoParser.decisionsToDFA, new antlr.PredictionContextCache());
    }
    public program(): ProgramContext {
        let localContext = new ProgramContext(this.context, this.state);
        this.enterRule(localContext, 0, PaxoParser.RULE_program);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 45;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            while ((((_la) & ~0x1F) === 0 && ((1 << _la) & 2147524352) !== 0) || ((((_la - 33)) & ~0x1F) === 0 && ((1 << (_la - 33)) & 8388391) !== 0)) {
                {
                {
                this.state = 42;
                this.statement();
                }
                }
                this.state = 47;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
            }
            this.state = 48;
            this.match(PaxoParser.EOF);
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public statement(): StatementContext {
        let localContext = new StatementContext(this.context, this.state);
        this.enterRule(localContext, 2, PaxoParser.RULE_statement);
        let _la: number;
        try {
            this.state = 69;
            this.errorHandler.sync(this);
            switch (this.interpreter.adaptivePredict(this.tokenStream, 2, this.context) ) {
            case 1:
                this.enterOuterAlt(localContext, 1);
                {
                this.state = 50;
                this.varDeclaration();
                }
                break;
            case 2:
                this.enterOuterAlt(localContext, 2);
                {
                this.state = 51;
                this.assignment();
                }
                break;
            case 3:
                this.enterOuterAlt(localContext, 3);
                {
                this.state = 52;
                this.matchStatement();
                }
                break;
            case 4:
                this.enterOuterAlt(localContext, 4);
                {
                this.state = 53;
                this.ifElseStatement();
                }
                break;
            case 5:
                this.enterOuterAlt(localContext, 5);
                {
                this.state = 54;
                this.loopStatement();
                }
                break;
            case 6:
                this.enterOuterAlt(localContext, 6);
                {
                this.state = 55;
                this.tryCatchStatement();
                }
                break;
            case 7:
                this.enterOuterAlt(localContext, 7);
                {
                this.state = 56;
                this.functionDeclaration();
                }
                break;
            case 8:
                this.enterOuterAlt(localContext, 8);
                {
                this.state = 57;
                this.pkgDeclaration();
                }
                break;
            case 9:
                this.enterOuterAlt(localContext, 9);
                {
                this.state = 58;
                this.expression(0);
                this.state = 59;
                this.match(PaxoParser.T__0);
                }
                break;
            case 10:
                this.enterOuterAlt(localContext, 10);
                {
                this.state = 61;
                this.match(PaxoParser.INCLUDE);
                this.state = 62;
                this.match(PaxoParser.T__1);
                this.state = 63;
                this.match(PaxoParser.IDENTIFIER);
                this.state = 66;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
                if (_la === 3) {
                    {
                    this.state = 64;
                    this.match(PaxoParser.T__2);
                    this.state = 65;
                    this.match(PaxoParser.IDENTIFIER);
                    }
                }

                this.state = 68;
                this.match(PaxoParser.T__3);
                }
                break;
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public varDeclaration(): VarDeclarationContext {
        let localContext = new VarDeclarationContext(this.context, this.state);
        this.enterRule(localContext, 4, PaxoParser.RULE_varDeclaration);
        let _la: number;
        try {
            this.state = 95;
            this.errorHandler.sync(this);
            switch (this.interpreter.adaptivePredict(this.tokenStream, 7, this.context) ) {
            case 1:
                this.enterOuterAlt(localContext, 1);
                {
                this.state = 72;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
                if ((((_la) & ~0x1F) === 0 && ((1 << _la) & 7936) !== 0)) {
                    {
                    this.state = 71;
                    this.sizePrefix();
                    }
                }

                this.state = 74;
                this.match(PaxoParser.VAR_DECL);
                this.state = 75;
                this.match(PaxoParser.IDENTIFIER);
                this.state = 76;
                this.match(PaxoParser.T__4);
                this.state = 77;
                this.expression(0);
                }
                break;
            case 2:
                this.enterOuterAlt(localContext, 2);
                {
                this.state = 79;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
                if ((((_la) & ~0x1F) === 0 && ((1 << _la) & 7936) !== 0)) {
                    {
                    this.state = 78;
                    this.sizePrefix();
                    }
                }

                this.state = 81;
                this.match(PaxoParser.VAR_DECL);
                this.state = 82;
                this.match(PaxoParser.IDENTIFIER);
                this.state = 83;
                this.match(PaxoParser.T__5);
                this.state = 85;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
                if (_la === 41) {
                    {
                    this.state = 84;
                    this.match(PaxoParser.INT_LITERAL);
                    }
                }

                this.state = 87;
                this.match(PaxoParser.T__6);
                this.state = 88;
                this.match(PaxoParser.T__4);
                this.state = 89;
                this.arrayLiteral();
                }
                break;
            case 3:
                this.enterOuterAlt(localContext, 3);
                {
                this.state = 91;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
                if ((((_la) & ~0x1F) === 0 && ((1 << _la) & 7936) !== 0)) {
                    {
                    this.state = 90;
                    this.sizePrefix();
                    }
                }

                this.state = 93;
                this.match(PaxoParser.VAR_DECL);
                this.state = 94;
                this.match(PaxoParser.IDENTIFIER);
                }
                break;
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public sizePrefix(): SizePrefixContext {
        let localContext = new SizePrefixContext(this.context, this.state);
        this.enterRule(localContext, 6, PaxoParser.RULE_sizePrefix);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 97;
            _la = this.tokenStream.LA(1);
            if(!((((_la) & ~0x1F) === 0 && ((1 << _la) & 7936) !== 0))) {
            this.errorHandler.recoverInline(this);
            }
            else {
                this.errorHandler.reportMatch(this);
                this.consume();
            }
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public assignment(): AssignmentContext {
        let localContext = new AssignmentContext(this.context, this.state);
        this.enterRule(localContext, 8, PaxoParser.RULE_assignment);
        try {
            this.state = 106;
            this.errorHandler.sync(this);
            switch (this.interpreter.adaptivePredict(this.tokenStream, 8, this.context) ) {
            case 1:
                this.enterOuterAlt(localContext, 1);
                {
                this.state = 99;
                this.match(PaxoParser.IDENTIFIER);
                this.state = 100;
                this.match(PaxoParser.T__4);
                this.state = 101;
                this.expression(0);
                }
                break;
            case 2:
                this.enterOuterAlt(localContext, 2);
                {
                this.state = 102;
                this.match(PaxoParser.IDENTIFIER);
                this.state = 103;
                this.match(PaxoParser.T__12);
                }
                break;
            case 3:
                this.enterOuterAlt(localContext, 3);
                {
                this.state = 104;
                this.match(PaxoParser.IDENTIFIER);
                this.state = 105;
                this.match(PaxoParser.T__13);
                }
                break;
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public ifElseStatement(): IfElseStatementContext {
        let localContext = new IfElseStatementContext(this.context, this.state);
        this.enterRule(localContext, 10, PaxoParser.RULE_ifElseStatement);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 108;
            this.match(PaxoParser.T__14);
            this.state = 109;
            this.expression(0);
            this.state = 110;
            this.match(PaxoParser.T__15);
            this.state = 111;
            this.block();
            this.state = 114;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            if (_la === 37) {
                {
                this.state = 112;
                this.match(PaxoParser.ARROW);
                this.state = 113;
                this.block();
                }
            }

            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public matchStatement(): MatchStatementContext {
        let localContext = new MatchStatementContext(this.context, this.state);
        this.enterRule(localContext, 12, PaxoParser.RULE_matchStatement);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 116;
            this.match(PaxoParser.T__14);
            this.state = 117;
            this.match(PaxoParser.IDENTIFIER);
            this.state = 118;
            this.match(PaxoParser.T__15);
            this.state = 119;
            this.match(PaxoParser.T__16);
            this.state = 121;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            do {
                {
                {
                this.state = 120;
                this.matchCase();
                }
                }
                this.state = 123;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
            } while (_la === 20 || _la === 31 || ((((_la - 41)) & ~0x1F) === 0 && ((1 << (_la - 41)) & 32767) !== 0));
            this.state = 125;
            this.match(PaxoParser.T__17);
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public matchCase(): MatchCaseContext {
        let localContext = new MatchCaseContext(this.context, this.state);
        this.enterRule(localContext, 14, PaxoParser.RULE_matchCase);
        try {
            this.state = 134;
            this.errorHandler.sync(this);
            switch (this.tokenStream.LA(1)) {
            case PaxoParser.T__30:
            case PaxoParser.INT_LITERAL:
            case PaxoParser.UINT_LITERAL:
            case PaxoParser.DECIMAL_LITERAL:
            case PaxoParser.BOOLEAN:
            case PaxoParser.COMPLEX_LITERAL:
            case PaxoParser.IDENTIFIER:
            case PaxoParser.STRING_LITERAL:
            case PaxoParser.CHAR_LITERAL:
            case PaxoParser.EMSTRING_LITERAL:
            case PaxoParser.VECTOR:
            case PaxoParser.NANOTIME_LITERAL:
            case PaxoParser.SLICE_LITERAL:
            case PaxoParser.POINTER_LITERAL:
            case PaxoParser.IPV4_LITERAL:
            case PaxoParser.IPV6_LITERAL:
                this.enterOuterAlt(localContext, 1);
                {
                this.state = 127;
                this.expression(0);
                this.state = 128;
                this.match(PaxoParser.T__18);
                this.state = 129;
                this.block();
                }
                break;
            case PaxoParser.T__19:
                this.enterOuterAlt(localContext, 2);
                {
                this.state = 131;
                this.match(PaxoParser.T__19);
                this.state = 132;
                this.match(PaxoParser.T__18);
                this.state = 133;
                this.block();
                }
                break;
            default:
                throw new antlr.NoViableAltException(this);
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public loopStatement(): LoopStatementContext {
        let localContext = new LoopStatementContext(this.context, this.state);
        this.enterRule(localContext, 16, PaxoParser.RULE_loopStatement);
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 136;
            this.match(PaxoParser.T__14);
            this.state = 137;
            this.expression(0);
            this.state = 138;
            this.match(PaxoParser.T__15);
            this.state = 139;
            this.match(PaxoParser.T__20);
            this.state = 140;
            this.loopMode();
            this.state = 141;
            this.loopDelimiter();
            this.state = 142;
            this.block();
            this.state = 143;
            this.loopEndDelimiter();
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public loopMode(): LoopModeContext {
        let localContext = new LoopModeContext(this.context, this.state);
        this.enterRule(localContext, 18, PaxoParser.RULE_loopMode);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 145;
            _la = this.tokenStream.LA(1);
            if(!(_la === 39 || _la === 40)) {
            this.errorHandler.recoverInline(this);
            }
            else {
                this.errorHandler.reportMatch(this);
                this.consume();
            }
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public loopDelimiter(): LoopDelimiterContext {
        let localContext = new LoopDelimiterContext(this.context, this.state);
        this.enterRule(localContext, 20, PaxoParser.RULE_loopDelimiter);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 147;
            _la = this.tokenStream.LA(1);
            if(!(_la === 22 || _la === 23)) {
            this.errorHandler.recoverInline(this);
            }
            else {
                this.errorHandler.reportMatch(this);
                this.consume();
            }
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public loopEndDelimiter(): LoopEndDelimiterContext {
        let localContext = new LoopEndDelimiterContext(this.context, this.state);
        this.enterRule(localContext, 22, PaxoParser.RULE_loopEndDelimiter);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 149;
            _la = this.tokenStream.LA(1);
            if(!(_la === 24 || _la === 25)) {
            this.errorHandler.recoverInline(this);
            }
            else {
                this.errorHandler.reportMatch(this);
                this.consume();
            }
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public tryCatchStatement(): TryCatchStatementContext {
        let localContext = new TryCatchStatementContext(this.context, this.state);
        this.enterRule(localContext, 24, PaxoParser.RULE_tryCatchStatement);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 151;
            this.match(PaxoParser.TRY);
            this.state = 152;
            this.block();
            this.state = 153;
            this.match(PaxoParser.CATCH);
            this.state = 154;
            this.match(PaxoParser.T__14);
            this.state = 155;
            this.match(PaxoParser.IDENTIFIER);
            this.state = 158;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            if (_la === 3) {
                {
                this.state = 156;
                this.match(PaxoParser.T__2);
                this.state = 157;
                this.match(PaxoParser.IDENTIFIER);
                }
            }

            this.state = 160;
            this.match(PaxoParser.T__15);
            this.state = 161;
            this.block();
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public functionDeclaration(): FunctionDeclarationContext {
        let localContext = new FunctionDeclarationContext(this.context, this.state);
        this.enterRule(localContext, 26, PaxoParser.RULE_functionDeclaration);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 163;
            this.match(PaxoParser.VAR_DECL);
            this.state = 164;
            this.match(PaxoParser.IDENTIFIER);
            this.state = 165;
            this.match(PaxoParser.T__4);
            this.state = 166;
            this.match(PaxoParser.T__14);
            this.state = 168;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            if (((((_la - 8)) & ~0x1F) === 0 && ((1 << (_la - 8)) & 33554463) !== 0)) {
                {
                this.state = 167;
                this.parameterList();
                }
            }

            this.state = 170;
            this.match(PaxoParser.T__15);
            this.state = 171;
            this.block();
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public pkgDeclaration(): PkgDeclarationContext {
        let localContext = new PkgDeclarationContext(this.context, this.state);
        this.enterRule(localContext, 28, PaxoParser.RULE_pkgDeclaration);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 173;
            this.match(PaxoParser.PKG);
            this.state = 174;
            this.match(PaxoParser.IDENTIFIER);
            this.state = 175;
            this.match(PaxoParser.T__4);
            this.state = 176;
            this.match(PaxoParser.T__16);
            this.state = 181;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            while (((((_la - 8)) & ~0x1F) === 0 && ((1 << (_la - 8)) & 33554463) !== 0)) {
                {
                this.state = 179;
                this.errorHandler.sync(this);
                switch (this.interpreter.adaptivePredict(this.tokenStream, 14, this.context) ) {
                case 1:
                    {
                    this.state = 177;
                    this.varDeclaration();
                    }
                    break;
                case 2:
                    {
                    this.state = 178;
                    this.functionDeclaration();
                    }
                    break;
                }
                }
                this.state = 183;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
            }
            this.state = 184;
            this.match(PaxoParser.T__17);
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public block(): BlockContext {
        let localContext = new BlockContext(this.context, this.state);
        this.enterRule(localContext, 30, PaxoParser.RULE_block);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 186;
            this.match(PaxoParser.T__16);
            this.state = 190;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            while ((((_la) & ~0x1F) === 0 && ((1 << _la) & 2147524352) !== 0) || ((((_la - 33)) & ~0x1F) === 0 && ((1 << (_la - 33)) & 8388391) !== 0)) {
                {
                {
                this.state = 187;
                this.statement();
                }
                }
                this.state = 192;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
            }
            this.state = 193;
            this.match(PaxoParser.T__17);
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public parameterList(): ParameterListContext {
        let localContext = new ParameterListContext(this.context, this.state);
        this.enterRule(localContext, 32, PaxoParser.RULE_parameterList);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 196;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            if ((((_la) & ~0x1F) === 0 && ((1 << _la) & 7936) !== 0)) {
                {
                this.state = 195;
                this.sizePrefix();
                }
            }

            this.state = 198;
            this.match(PaxoParser.VAR_DECL);
            this.state = 199;
            this.match(PaxoParser.IDENTIFIER);
            this.state = 208;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            while (_la === 26) {
                {
                {
                this.state = 200;
                this.match(PaxoParser.T__25);
                this.state = 202;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
                if ((((_la) & ~0x1F) === 0 && ((1 << _la) & 7936) !== 0)) {
                    {
                    this.state = 201;
                    this.sizePrefix();
                    }
                }

                this.state = 204;
                this.match(PaxoParser.VAR_DECL);
                this.state = 205;
                this.match(PaxoParser.IDENTIFIER);
                }
                }
                this.state = 210;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
            }
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public argumentList(): ArgumentListContext {
        let localContext = new ArgumentListContext(this.context, this.state);
        this.enterRule(localContext, 34, PaxoParser.RULE_argumentList);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 211;
            this.expression(0);
            this.state = 216;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            while (_la === 26) {
                {
                {
                this.state = 212;
                this.match(PaxoParser.T__25);
                this.state = 213;
                this.expression(0);
                }
                }
                this.state = 218;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
            }
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }

    public expression(): ExpressionContext;
    public expression(_p: number): ExpressionContext;
    public expression(_p?: number): ExpressionContext {
        if (_p === undefined) {
            _p = 0;
        }

        let parentContext = this.context;
        let parentState = this.state;
        let localContext = new ExpressionContext(this.context, parentState);
        let previousContext = localContext;
        let _startState = 36;
        this.enterRecursionRule(localContext, 36, PaxoParser.RULE_expression, _p);
        let _la: number;
        try {
            let alternative: number;
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 243;
            this.errorHandler.sync(this);
            switch (this.interpreter.adaptivePredict(this.tokenStream, 22, this.context) ) {
            case 1:
                {
                this.state = 220;
                this.match(PaxoParser.IDENTIFIER);
                this.state = 221;
                this.match(PaxoParser.T__14);
                this.state = 223;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
                if (((((_la - 31)) & ~0x1F) === 0 && ((1 << (_la - 31)) & 33553409) !== 0)) {
                    {
                    this.state = 222;
                    this.argumentList();
                    }
                }

                this.state = 225;
                this.match(PaxoParser.T__15);
                }
                break;
            case 2:
                {
                this.state = 226;
                this.match(PaxoParser.INT_LITERAL);
                }
                break;
            case 3:
                {
                this.state = 227;
                this.match(PaxoParser.UINT_LITERAL);
                }
                break;
            case 4:
                {
                this.state = 228;
                this.match(PaxoParser.DECIMAL_LITERAL);
                }
                break;
            case 5:
                {
                this.state = 229;
                this.match(PaxoParser.COMPLEX_LITERAL);
                }
                break;
            case 6:
                {
                this.state = 230;
                this.match(PaxoParser.CHAR_LITERAL);
                }
                break;
            case 7:
                {
                this.state = 231;
                this.match(PaxoParser.STRING_LITERAL);
                }
                break;
            case 8:
                {
                this.state = 232;
                this.match(PaxoParser.EMSTRING_LITERAL);
                }
                break;
            case 9:
                {
                this.state = 233;
                this.match(PaxoParser.BOOLEAN);
                }
                break;
            case 10:
                {
                this.state = 234;
                this.match(PaxoParser.VECTOR);
                }
                break;
            case 11:
                {
                this.state = 235;
                this.match(PaxoParser.NANOTIME_LITERAL);
                }
                break;
            case 12:
                {
                this.state = 236;
                this.match(PaxoParser.SLICE_LITERAL);
                }
                break;
            case 13:
                {
                this.state = 237;
                this.match(PaxoParser.POINTER_LITERAL);
                }
                break;
            case 14:
                {
                this.state = 238;
                this.match(PaxoParser.IPV4_LITERAL);
                }
                break;
            case 15:
                {
                this.state = 239;
                this.match(PaxoParser.IPV6_LITERAL);
                }
                break;
            case 16:
                {
                this.state = 240;
                this.arrayLiteral();
                }
                break;
            case 17:
                {
                this.state = 241;
                this.arrayAccess();
                }
                break;
            case 18:
                {
                this.state = 242;
                this.match(PaxoParser.IDENTIFIER);
                }
                break;
            }
            this.context!.stop = this.tokenStream.LT(-1);
            this.state = 250;
            this.errorHandler.sync(this);
            alternative = this.interpreter.adaptivePredict(this.tokenStream, 23, this.context);
            while (alternative !== 2 && alternative !== antlr.ATN.INVALID_ALT_NUMBER) {
                if (alternative === 1) {
                    if (this.parseListeners != null) {
                        this.triggerExitRuleEvent();
                    }
                    previousContext = localContext;
                    {
                    {
                    localContext = new ExpressionContext(parentContext, parentState);
                    this.pushNewRecursionContext(localContext, _startState, PaxoParser.RULE_expression);
                    this.state = 245;
                    if (!(this.precpred(this.context, 19))) {
                        throw this.createFailedPredicateException("this.precpred(this.context, 19)");
                    }
                    this.state = 246;
                    _la = this.tokenStream.LA(1);
                    if(!((((_la) & ~0x1F) === 0 && ((1 << _la) & 2013265940) !== 0))) {
                    this.errorHandler.recoverInline(this);
                    }
                    else {
                        this.errorHandler.reportMatch(this);
                        this.consume();
                    }
                    this.state = 247;
                    this.expression(20);
                    }
                    }
                }
                this.state = 252;
                this.errorHandler.sync(this);
                alternative = this.interpreter.adaptivePredict(this.tokenStream, 23, this.context);
            }
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.unrollRecursionContexts(parentContext);
        }
        return localContext;
    }
    public arrayLiteral(): ArrayLiteralContext {
        let localContext = new ArrayLiteralContext(this.context, this.state);
        this.enterRule(localContext, 38, PaxoParser.RULE_arrayLiteral);
        let _la: number;
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 253;
            this.match(PaxoParser.T__30);
            this.state = 254;
            this.expression(0);
            this.state = 259;
            this.errorHandler.sync(this);
            _la = this.tokenStream.LA(1);
            while (_la === 26) {
                {
                {
                this.state = 255;
                this.match(PaxoParser.T__25);
                this.state = 256;
                this.expression(0);
                }
                }
                this.state = 261;
                this.errorHandler.sync(this);
                _la = this.tokenStream.LA(1);
            }
            this.state = 262;
            this.match(PaxoParser.T__31);
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }
    public arrayAccess(): ArrayAccessContext {
        let localContext = new ArrayAccessContext(this.context, this.state);
        this.enterRule(localContext, 40, PaxoParser.RULE_arrayAccess);
        try {
            this.enterOuterAlt(localContext, 1);
            {
            this.state = 264;
            this.match(PaxoParser.IDENTIFIER);
            this.state = 265;
            this.match(PaxoParser.T__5);
            this.state = 266;
            this.expression(0);
            this.state = 267;
            this.match(PaxoParser.T__6);
            }
        }
        catch (re) {
            if (re instanceof antlr.RecognitionException) {
                this.errorHandler.reportError(this, re);
                this.errorHandler.recover(this, re);
            } else {
                throw re;
            }
        }
        finally {
            this.exitRule();
        }
        return localContext;
    }

    public override sempred(localContext: antlr.ParserRuleContext | null, ruleIndex: number, predIndex: number): boolean {
        switch (ruleIndex) {
        case 18:
            return this.expression_sempred(localContext as ExpressionContext, predIndex);
        }
        return true;
    }
    private expression_sempred(localContext: ExpressionContext | null, predIndex: number): boolean {
        switch (predIndex) {
        case 0:
            return this.precpred(this.context, 19);
        }
        return true;
    }

    public static readonly _serializedATN: number[] = [
        4,1,58,270,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
        6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,
        2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,
        7,20,1,0,5,0,44,8,0,10,0,12,0,47,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,67,8,1,1,1,3,1,70,
        8,1,1,2,3,2,73,8,2,1,2,1,2,1,2,1,2,1,2,3,2,80,8,2,1,2,1,2,1,2,1,
        2,3,2,86,8,2,1,2,1,2,1,2,1,2,3,2,92,8,2,1,2,1,2,3,2,96,8,2,1,3,1,
        3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,107,8,4,1,5,1,5,1,5,1,5,1,5,1,
        5,3,5,115,8,5,1,6,1,6,1,6,1,6,1,6,4,6,122,8,6,11,6,12,6,123,1,6,
        1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,135,8,7,1,8,1,8,1,8,1,8,1,8,
        1,8,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,12,
        1,12,1,12,1,12,3,12,159,8,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,
        1,13,3,13,169,8,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,
        5,14,180,8,14,10,14,12,14,183,9,14,1,14,1,14,1,15,1,15,5,15,189,
        8,15,10,15,12,15,192,9,15,1,15,1,15,1,16,3,16,197,8,16,1,16,1,16,
        1,16,1,16,3,16,203,8,16,1,16,1,16,5,16,207,8,16,10,16,12,16,210,
        9,16,1,17,1,17,1,17,5,17,215,8,17,10,17,12,17,218,9,17,1,18,1,18,
        1,18,1,18,3,18,224,8,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
        1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,244,8,18,
        1,18,1,18,1,18,5,18,249,8,18,10,18,12,18,252,9,18,1,19,1,19,1,19,
        1,19,5,19,258,8,19,10,19,12,19,261,9,19,1,19,1,19,1,20,1,20,1,20,
        1,20,1,20,1,20,0,1,36,21,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
        30,32,34,36,38,40,0,5,1,0,8,12,1,0,39,40,1,0,22,23,1,0,24,25,3,0,
        2,2,4,4,27,30,299,0,45,1,0,0,0,2,69,1,0,0,0,4,95,1,0,0,0,6,97,1,
        0,0,0,8,106,1,0,0,0,10,108,1,0,0,0,12,116,1,0,0,0,14,134,1,0,0,0,
        16,136,1,0,0,0,18,145,1,0,0,0,20,147,1,0,0,0,22,149,1,0,0,0,24,151,
        1,0,0,0,26,163,1,0,0,0,28,173,1,0,0,0,30,186,1,0,0,0,32,196,1,0,
        0,0,34,211,1,0,0,0,36,243,1,0,0,0,38,253,1,0,0,0,40,264,1,0,0,0,
        42,44,3,2,1,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,0,0,45,46,1,
        0,0,0,46,48,1,0,0,0,47,45,1,0,0,0,48,49,5,0,0,1,49,1,1,0,0,0,50,
        70,3,4,2,0,51,70,3,8,4,0,52,70,3,12,6,0,53,70,3,10,5,0,54,70,3,16,
        8,0,55,70,3,24,12,0,56,70,3,26,13,0,57,70,3,28,14,0,58,59,3,36,18,
        0,59,60,5,1,0,0,60,70,1,0,0,0,61,62,5,38,0,0,62,63,5,2,0,0,63,66,
        5,46,0,0,64,65,5,3,0,0,65,67,5,46,0,0,66,64,1,0,0,0,66,67,1,0,0,
        0,67,68,1,0,0,0,68,70,5,4,0,0,69,50,1,0,0,0,69,51,1,0,0,0,69,52,
        1,0,0,0,69,53,1,0,0,0,69,54,1,0,0,0,69,55,1,0,0,0,69,56,1,0,0,0,
        69,57,1,0,0,0,69,58,1,0,0,0,69,61,1,0,0,0,70,3,1,0,0,0,71,73,3,6,
        3,0,72,71,1,0,0,0,72,73,1,0,0,0,73,74,1,0,0,0,74,75,5,33,0,0,75,
        76,5,46,0,0,76,77,5,5,0,0,77,96,3,36,18,0,78,80,3,6,3,0,79,78,1,
        0,0,0,79,80,1,0,0,0,80,81,1,0,0,0,81,82,5,33,0,0,82,83,5,46,0,0,
        83,85,5,6,0,0,84,86,5,41,0,0,85,84,1,0,0,0,85,86,1,0,0,0,86,87,1,
        0,0,0,87,88,5,7,0,0,88,89,5,5,0,0,89,96,3,38,19,0,90,92,3,6,3,0,
        91,90,1,0,0,0,91,92,1,0,0,0,92,93,1,0,0,0,93,94,5,33,0,0,94,96,5,
        46,0,0,95,72,1,0,0,0,95,79,1,0,0,0,95,91,1,0,0,0,96,5,1,0,0,0,97,
        98,7,0,0,0,98,7,1,0,0,0,99,100,5,46,0,0,100,101,5,5,0,0,101,107,
        3,36,18,0,102,103,5,46,0,0,103,107,5,13,0,0,104,105,5,46,0,0,105,
        107,5,14,0,0,106,99,1,0,0,0,106,102,1,0,0,0,106,104,1,0,0,0,107,
        9,1,0,0,0,108,109,5,15,0,0,109,110,3,36,18,0,110,111,5,16,0,0,111,
        114,3,30,15,0,112,113,5,37,0,0,113,115,3,30,15,0,114,112,1,0,0,0,
        114,115,1,0,0,0,115,11,1,0,0,0,116,117,5,15,0,0,117,118,5,46,0,0,
        118,119,5,16,0,0,119,121,5,17,0,0,120,122,3,14,7,0,121,120,1,0,0,
        0,122,123,1,0,0,0,123,121,1,0,0,0,123,124,1,0,0,0,124,125,1,0,0,
        0,125,126,5,18,0,0,126,13,1,0,0,0,127,128,3,36,18,0,128,129,5,19,
        0,0,129,130,3,30,15,0,130,135,1,0,0,0,131,132,5,20,0,0,132,133,5,
        19,0,0,133,135,3,30,15,0,134,127,1,0,0,0,134,131,1,0,0,0,135,15,
        1,0,0,0,136,137,5,15,0,0,137,138,3,36,18,0,138,139,5,16,0,0,139,
        140,5,21,0,0,140,141,3,18,9,0,141,142,3,20,10,0,142,143,3,30,15,
        0,143,144,3,22,11,0,144,17,1,0,0,0,145,146,7,1,0,0,146,19,1,0,0,
        0,147,148,7,2,0,0,148,21,1,0,0,0,149,150,7,3,0,0,150,23,1,0,0,0,
        151,152,5,35,0,0,152,153,3,30,15,0,153,154,5,36,0,0,154,155,5,15,
        0,0,155,158,5,46,0,0,156,157,5,3,0,0,157,159,5,46,0,0,158,156,1,
        0,0,0,158,159,1,0,0,0,159,160,1,0,0,0,160,161,5,16,0,0,161,162,3,
        30,15,0,162,25,1,0,0,0,163,164,5,33,0,0,164,165,5,46,0,0,165,166,
        5,5,0,0,166,168,5,15,0,0,167,169,3,32,16,0,168,167,1,0,0,0,168,169,
        1,0,0,0,169,170,1,0,0,0,170,171,5,16,0,0,171,172,3,30,15,0,172,27,
        1,0,0,0,173,174,5,34,0,0,174,175,5,46,0,0,175,176,5,5,0,0,176,181,
        5,17,0,0,177,180,3,4,2,0,178,180,3,26,13,0,179,177,1,0,0,0,179,178,
        1,0,0,0,180,183,1,0,0,0,181,179,1,0,0,0,181,182,1,0,0,0,182,184,
        1,0,0,0,183,181,1,0,0,0,184,185,5,18,0,0,185,29,1,0,0,0,186,190,
        5,17,0,0,187,189,3,2,1,0,188,187,1,0,0,0,189,192,1,0,0,0,190,188,
        1,0,0,0,190,191,1,0,0,0,191,193,1,0,0,0,192,190,1,0,0,0,193,194,
        5,18,0,0,194,31,1,0,0,0,195,197,3,6,3,0,196,195,1,0,0,0,196,197,
        1,0,0,0,197,198,1,0,0,0,198,199,5,33,0,0,199,208,5,46,0,0,200,202,
        5,26,0,0,201,203,3,6,3,0,202,201,1,0,0,0,202,203,1,0,0,0,203,204,
        1,0,0,0,204,205,5,33,0,0,205,207,5,46,0,0,206,200,1,0,0,0,207,210,
        1,0,0,0,208,206,1,0,0,0,208,209,1,0,0,0,209,33,1,0,0,0,210,208,1,
        0,0,0,211,216,3,36,18,0,212,213,5,26,0,0,213,215,3,36,18,0,214,212,
        1,0,0,0,215,218,1,0,0,0,216,214,1,0,0,0,216,217,1,0,0,0,217,35,1,
        0,0,0,218,216,1,0,0,0,219,220,6,18,-1,0,220,221,5,46,0,0,221,223,
        5,15,0,0,222,224,3,34,17,0,223,222,1,0,0,0,223,224,1,0,0,0,224,225,
        1,0,0,0,225,244,5,16,0,0,226,244,5,41,0,0,227,244,5,42,0,0,228,244,
        5,43,0,0,229,244,5,45,0,0,230,244,5,48,0,0,231,244,5,47,0,0,232,
        244,5,49,0,0,233,244,5,44,0,0,234,244,5,50,0,0,235,244,5,51,0,0,
        236,244,5,52,0,0,237,244,5,53,0,0,238,244,5,54,0,0,239,244,5,55,
        0,0,240,244,3,38,19,0,241,244,3,40,20,0,242,244,5,46,0,0,243,219,
        1,0,0,0,243,226,1,0,0,0,243,227,1,0,0,0,243,228,1,0,0,0,243,229,
        1,0,0,0,243,230,1,0,0,0,243,231,1,0,0,0,243,232,1,0,0,0,243,233,
        1,0,0,0,243,234,1,0,0,0,243,235,1,0,0,0,243,236,1,0,0,0,243,237,
        1,0,0,0,243,238,1,0,0,0,243,239,1,0,0,0,243,240,1,0,0,0,243,241,
        1,0,0,0,243,242,1,0,0,0,244,250,1,0,0,0,245,246,10,19,0,0,246,247,
        7,4,0,0,247,249,3,36,18,20,248,245,1,0,0,0,249,252,1,0,0,0,250,248,
        1,0,0,0,250,251,1,0,0,0,251,37,1,0,0,0,252,250,1,0,0,0,253,254,5,
        31,0,0,254,259,3,36,18,0,255,256,5,26,0,0,256,258,3,36,18,0,257,
        255,1,0,0,0,258,261,1,0,0,0,259,257,1,0,0,0,259,260,1,0,0,0,260,
        262,1,0,0,0,261,259,1,0,0,0,262,263,5,32,0,0,263,39,1,0,0,0,264,
        265,5,46,0,0,265,266,5,6,0,0,266,267,3,36,18,0,267,268,5,7,0,0,268,
        41,1,0,0,0,25,45,66,69,72,79,85,91,95,106,114,123,134,158,168,179,
        181,190,196,202,208,216,223,243,250,259
    ];

    private static __ATN: antlr.ATN;
    public static get _ATN(): antlr.ATN {
        if (!PaxoParser.__ATN) {
            PaxoParser.__ATN = new antlr.ATNDeserializer().deserialize(PaxoParser._serializedATN);
        }

        return PaxoParser.__ATN;
    }


    private static readonly vocabulary = new antlr.Vocabulary(PaxoParser.literalNames, PaxoParser.symbolicNames, []);

    public override get vocabulary(): antlr.Vocabulary {
        return PaxoParser.vocabulary;
    }

    private static readonly decisionsToDFA = PaxoParser._ATN.decisionToState.map( (ds: antlr.DecisionState, index: number) => new antlr.DFA(ds, index) );
}

export class ProgramContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public EOF(): antlr.TerminalNode {
        return this.getToken(PaxoParser.EOF, 0)!;
    }
    public statement(): StatementContext[];
    public statement(i: number): StatementContext | null;
    public statement(i?: number): StatementContext[] | StatementContext | null {
        if (i === undefined) {
            return this.getRuleContexts(StatementContext);
        }

        return this.getRuleContext(i, StatementContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_program;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterProgram) {
             listener.enterProgram(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitProgram) {
             listener.exitProgram(this);
        }
    }
}


export class StatementContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public varDeclaration(): VarDeclarationContext | null {
        return this.getRuleContext(0, VarDeclarationContext);
    }
    public assignment(): AssignmentContext | null {
        return this.getRuleContext(0, AssignmentContext);
    }
    public matchStatement(): MatchStatementContext | null {
        return this.getRuleContext(0, MatchStatementContext);
    }
    public ifElseStatement(): IfElseStatementContext | null {
        return this.getRuleContext(0, IfElseStatementContext);
    }
    public loopStatement(): LoopStatementContext | null {
        return this.getRuleContext(0, LoopStatementContext);
    }
    public tryCatchStatement(): TryCatchStatementContext | null {
        return this.getRuleContext(0, TryCatchStatementContext);
    }
    public functionDeclaration(): FunctionDeclarationContext | null {
        return this.getRuleContext(0, FunctionDeclarationContext);
    }
    public pkgDeclaration(): PkgDeclarationContext | null {
        return this.getRuleContext(0, PkgDeclarationContext);
    }
    public expression(): ExpressionContext | null {
        return this.getRuleContext(0, ExpressionContext);
    }
    public INCLUDE(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.INCLUDE, 0);
    }
    public IDENTIFIER(): antlr.TerminalNode[];
    public IDENTIFIER(i: number): antlr.TerminalNode | null;
    public IDENTIFIER(i?: number): antlr.TerminalNode | null | antlr.TerminalNode[] {
    	if (i === undefined) {
    		return this.getTokens(PaxoParser.IDENTIFIER);
    	} else {
    		return this.getToken(PaxoParser.IDENTIFIER, i);
    	}
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_statement;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterStatement) {
             listener.enterStatement(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitStatement) {
             listener.exitStatement(this);
        }
    }
}


export class VarDeclarationContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public VAR_DECL(): antlr.TerminalNode {
        return this.getToken(PaxoParser.VAR_DECL, 0)!;
    }
    public IDENTIFIER(): antlr.TerminalNode {
        return this.getToken(PaxoParser.IDENTIFIER, 0)!;
    }
    public expression(): ExpressionContext | null {
        return this.getRuleContext(0, ExpressionContext);
    }
    public sizePrefix(): SizePrefixContext | null {
        return this.getRuleContext(0, SizePrefixContext);
    }
    public arrayLiteral(): ArrayLiteralContext | null {
        return this.getRuleContext(0, ArrayLiteralContext);
    }
    public INT_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.INT_LITERAL, 0);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_varDeclaration;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterVarDeclaration) {
             listener.enterVarDeclaration(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitVarDeclaration) {
             listener.exitVarDeclaration(this);
        }
    }
}


export class SizePrefixContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_sizePrefix;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterSizePrefix) {
             listener.enterSizePrefix(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitSizePrefix) {
             listener.exitSizePrefix(this);
        }
    }
}


export class AssignmentContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public IDENTIFIER(): antlr.TerminalNode {
        return this.getToken(PaxoParser.IDENTIFIER, 0)!;
    }
    public expression(): ExpressionContext | null {
        return this.getRuleContext(0, ExpressionContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_assignment;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterAssignment) {
             listener.enterAssignment(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitAssignment) {
             listener.exitAssignment(this);
        }
    }
}


export class IfElseStatementContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public expression(): ExpressionContext {
        return this.getRuleContext(0, ExpressionContext)!;
    }
    public block(): BlockContext[];
    public block(i: number): BlockContext | null;
    public block(i?: number): BlockContext[] | BlockContext | null {
        if (i === undefined) {
            return this.getRuleContexts(BlockContext);
        }

        return this.getRuleContext(i, BlockContext);
    }
    public ARROW(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.ARROW, 0);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_ifElseStatement;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterIfElseStatement) {
             listener.enterIfElseStatement(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitIfElseStatement) {
             listener.exitIfElseStatement(this);
        }
    }
}


export class MatchStatementContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public IDENTIFIER(): antlr.TerminalNode {
        return this.getToken(PaxoParser.IDENTIFIER, 0)!;
    }
    public matchCase(): MatchCaseContext[];
    public matchCase(i: number): MatchCaseContext | null;
    public matchCase(i?: number): MatchCaseContext[] | MatchCaseContext | null {
        if (i === undefined) {
            return this.getRuleContexts(MatchCaseContext);
        }

        return this.getRuleContext(i, MatchCaseContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_matchStatement;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterMatchStatement) {
             listener.enterMatchStatement(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitMatchStatement) {
             listener.exitMatchStatement(this);
        }
    }
}


export class MatchCaseContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public expression(): ExpressionContext | null {
        return this.getRuleContext(0, ExpressionContext);
    }
    public block(): BlockContext {
        return this.getRuleContext(0, BlockContext)!;
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_matchCase;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterMatchCase) {
             listener.enterMatchCase(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitMatchCase) {
             listener.exitMatchCase(this);
        }
    }
}


export class LoopStatementContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public expression(): ExpressionContext {
        return this.getRuleContext(0, ExpressionContext)!;
    }
    public loopMode(): LoopModeContext {
        return this.getRuleContext(0, LoopModeContext)!;
    }
    public loopDelimiter(): LoopDelimiterContext {
        return this.getRuleContext(0, LoopDelimiterContext)!;
    }
    public block(): BlockContext {
        return this.getRuleContext(0, BlockContext)!;
    }
    public loopEndDelimiter(): LoopEndDelimiterContext {
        return this.getRuleContext(0, LoopEndDelimiterContext)!;
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_loopStatement;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterLoopStatement) {
             listener.enterLoopStatement(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitLoopStatement) {
             listener.exitLoopStatement(this);
        }
    }
}


export class LoopModeContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public PAUSE_MODE(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.PAUSE_MODE, 0);
    }
    public PLAY_MODE(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.PLAY_MODE, 0);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_loopMode;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterLoopMode) {
             listener.enterLoopMode(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitLoopMode) {
             listener.exitLoopMode(this);
        }
    }
}


export class LoopDelimiterContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_loopDelimiter;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterLoopDelimiter) {
             listener.enterLoopDelimiter(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitLoopDelimiter) {
             listener.exitLoopDelimiter(this);
        }
    }
}


export class LoopEndDelimiterContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_loopEndDelimiter;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterLoopEndDelimiter) {
             listener.enterLoopEndDelimiter(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitLoopEndDelimiter) {
             listener.exitLoopEndDelimiter(this);
        }
    }
}


export class TryCatchStatementContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public TRY(): antlr.TerminalNode {
        return this.getToken(PaxoParser.TRY, 0)!;
    }
    public block(): BlockContext[];
    public block(i: number): BlockContext | null;
    public block(i?: number): BlockContext[] | BlockContext | null {
        if (i === undefined) {
            return this.getRuleContexts(BlockContext);
        }

        return this.getRuleContext(i, BlockContext);
    }
    public CATCH(): antlr.TerminalNode {
        return this.getToken(PaxoParser.CATCH, 0)!;
    }
    public IDENTIFIER(): antlr.TerminalNode[];
    public IDENTIFIER(i: number): antlr.TerminalNode | null;
    public IDENTIFIER(i?: number): antlr.TerminalNode | null | antlr.TerminalNode[] {
    	if (i === undefined) {
    		return this.getTokens(PaxoParser.IDENTIFIER);
    	} else {
    		return this.getToken(PaxoParser.IDENTIFIER, i);
    	}
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_tryCatchStatement;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterTryCatchStatement) {
             listener.enterTryCatchStatement(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitTryCatchStatement) {
             listener.exitTryCatchStatement(this);
        }
    }
}


export class FunctionDeclarationContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public VAR_DECL(): antlr.TerminalNode {
        return this.getToken(PaxoParser.VAR_DECL, 0)!;
    }
    public IDENTIFIER(): antlr.TerminalNode {
        return this.getToken(PaxoParser.IDENTIFIER, 0)!;
    }
    public block(): BlockContext {
        return this.getRuleContext(0, BlockContext)!;
    }
    public parameterList(): ParameterListContext | null {
        return this.getRuleContext(0, ParameterListContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_functionDeclaration;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterFunctionDeclaration) {
             listener.enterFunctionDeclaration(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitFunctionDeclaration) {
             listener.exitFunctionDeclaration(this);
        }
    }
}


export class PkgDeclarationContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public PKG(): antlr.TerminalNode {
        return this.getToken(PaxoParser.PKG, 0)!;
    }
    public IDENTIFIER(): antlr.TerminalNode {
        return this.getToken(PaxoParser.IDENTIFIER, 0)!;
    }
    public varDeclaration(): VarDeclarationContext[];
    public varDeclaration(i: number): VarDeclarationContext | null;
    public varDeclaration(i?: number): VarDeclarationContext[] | VarDeclarationContext | null {
        if (i === undefined) {
            return this.getRuleContexts(VarDeclarationContext);
        }

        return this.getRuleContext(i, VarDeclarationContext);
    }
    public functionDeclaration(): FunctionDeclarationContext[];
    public functionDeclaration(i: number): FunctionDeclarationContext | null;
    public functionDeclaration(i?: number): FunctionDeclarationContext[] | FunctionDeclarationContext | null {
        if (i === undefined) {
            return this.getRuleContexts(FunctionDeclarationContext);
        }

        return this.getRuleContext(i, FunctionDeclarationContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_pkgDeclaration;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterPkgDeclaration) {
             listener.enterPkgDeclaration(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitPkgDeclaration) {
             listener.exitPkgDeclaration(this);
        }
    }
}


export class BlockContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public statement(): StatementContext[];
    public statement(i: number): StatementContext | null;
    public statement(i?: number): StatementContext[] | StatementContext | null {
        if (i === undefined) {
            return this.getRuleContexts(StatementContext);
        }

        return this.getRuleContext(i, StatementContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_block;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterBlock) {
             listener.enterBlock(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitBlock) {
             listener.exitBlock(this);
        }
    }
}


export class ParameterListContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public VAR_DECL(): antlr.TerminalNode[];
    public VAR_DECL(i: number): antlr.TerminalNode | null;
    public VAR_DECL(i?: number): antlr.TerminalNode | null | antlr.TerminalNode[] {
    	if (i === undefined) {
    		return this.getTokens(PaxoParser.VAR_DECL);
    	} else {
    		return this.getToken(PaxoParser.VAR_DECL, i);
    	}
    }
    public IDENTIFIER(): antlr.TerminalNode[];
    public IDENTIFIER(i: number): antlr.TerminalNode | null;
    public IDENTIFIER(i?: number): antlr.TerminalNode | null | antlr.TerminalNode[] {
    	if (i === undefined) {
    		return this.getTokens(PaxoParser.IDENTIFIER);
    	} else {
    		return this.getToken(PaxoParser.IDENTIFIER, i);
    	}
    }
    public sizePrefix(): SizePrefixContext[];
    public sizePrefix(i: number): SizePrefixContext | null;
    public sizePrefix(i?: number): SizePrefixContext[] | SizePrefixContext | null {
        if (i === undefined) {
            return this.getRuleContexts(SizePrefixContext);
        }

        return this.getRuleContext(i, SizePrefixContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_parameterList;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterParameterList) {
             listener.enterParameterList(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitParameterList) {
             listener.exitParameterList(this);
        }
    }
}


export class ArgumentListContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public expression(): ExpressionContext[];
    public expression(i: number): ExpressionContext | null;
    public expression(i?: number): ExpressionContext[] | ExpressionContext | null {
        if (i === undefined) {
            return this.getRuleContexts(ExpressionContext);
        }

        return this.getRuleContext(i, ExpressionContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_argumentList;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterArgumentList) {
             listener.enterArgumentList(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitArgumentList) {
             listener.exitArgumentList(this);
        }
    }
}


export class ExpressionContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public IDENTIFIER(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.IDENTIFIER, 0);
    }
    public argumentList(): ArgumentListContext | null {
        return this.getRuleContext(0, ArgumentListContext);
    }
    public INT_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.INT_LITERAL, 0);
    }
    public UINT_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.UINT_LITERAL, 0);
    }
    public DECIMAL_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.DECIMAL_LITERAL, 0);
    }
    public COMPLEX_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.COMPLEX_LITERAL, 0);
    }
    public CHAR_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.CHAR_LITERAL, 0);
    }
    public STRING_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.STRING_LITERAL, 0);
    }
    public EMSTRING_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.EMSTRING_LITERAL, 0);
    }
    public BOOLEAN(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.BOOLEAN, 0);
    }
    public VECTOR(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.VECTOR, 0);
    }
    public NANOTIME_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.NANOTIME_LITERAL, 0);
    }
    public SLICE_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.SLICE_LITERAL, 0);
    }
    public POINTER_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.POINTER_LITERAL, 0);
    }
    public IPV4_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.IPV4_LITERAL, 0);
    }
    public IPV6_LITERAL(): antlr.TerminalNode | null {
        return this.getToken(PaxoParser.IPV6_LITERAL, 0);
    }
    public arrayLiteral(): ArrayLiteralContext | null {
        return this.getRuleContext(0, ArrayLiteralContext);
    }
    public arrayAccess(): ArrayAccessContext | null {
        return this.getRuleContext(0, ArrayAccessContext);
    }
    public expression(): ExpressionContext[];
    public expression(i: number): ExpressionContext | null;
    public expression(i?: number): ExpressionContext[] | ExpressionContext | null {
        if (i === undefined) {
            return this.getRuleContexts(ExpressionContext);
        }

        return this.getRuleContext(i, ExpressionContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_expression;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterExpression) {
             listener.enterExpression(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitExpression) {
             listener.exitExpression(this);
        }
    }
}


export class ArrayLiteralContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public expression(): ExpressionContext[];
    public expression(i: number): ExpressionContext | null;
    public expression(i?: number): ExpressionContext[] | ExpressionContext | null {
        if (i === undefined) {
            return this.getRuleContexts(ExpressionContext);
        }

        return this.getRuleContext(i, ExpressionContext);
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_arrayLiteral;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterArrayLiteral) {
             listener.enterArrayLiteral(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitArrayLiteral) {
             listener.exitArrayLiteral(this);
        }
    }
}


export class ArrayAccessContext extends antlr.ParserRuleContext {
    public constructor(parent: antlr.ParserRuleContext | null, invokingState: number) {
        super(parent, invokingState);
    }
    public IDENTIFIER(): antlr.TerminalNode {
        return this.getToken(PaxoParser.IDENTIFIER, 0)!;
    }
    public expression(): ExpressionContext {
        return this.getRuleContext(0, ExpressionContext)!;
    }
    public override get ruleIndex(): number {
        return PaxoParser.RULE_arrayAccess;
    }
    public override enterRule(listener: PaxoListener): void {
        if(listener.enterArrayAccess) {
             listener.enterArrayAccess(this);
        }
    }
    public override exitRule(listener: PaxoListener): void {
        if(listener.exitArrayAccess) {
             listener.exitArrayAccess(this);
        }
    }
}
