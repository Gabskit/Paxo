// Generated from Axolang.g4 by ANTLR 4.13.1
// jshint ignore: start
import antlr4 from 'antlr4';
import AxolangListener from './AxolangListener.js';
const serializedATN = [4,1,28,120,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,
4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,1,0,5,0,22,8,0,10,0,12,0,25,9,
0,1,0,1,0,1,1,1,1,3,1,31,8,1,1,2,1,2,3,2,35,8,2,1,2,1,2,1,2,1,2,1,3,1,3,
1,4,1,4,1,4,1,4,1,4,1,4,4,4,49,8,4,11,4,12,4,50,1,4,1,4,1,5,1,5,1,5,1,5,
1,5,1,5,1,5,1,5,1,5,5,5,64,8,5,10,5,12,5,67,9,5,1,5,1,5,1,5,1,5,1,5,1,5,
1,5,3,5,76,8,5,1,6,1,6,1,6,1,6,1,6,1,6,5,6,84,8,6,10,6,12,6,87,9,6,1,6,1,
6,3,6,91,8,6,1,7,1,7,3,7,95,8,7,1,7,1,7,1,7,1,8,1,8,5,8,102,8,8,10,8,12,
8,105,9,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,118,8,9,1,9,0,
0,10,0,2,4,6,8,10,12,14,16,18,0,1,1,0,3,10,129,0,23,1,0,0,0,2,30,1,0,0,0,
4,34,1,0,0,0,6,40,1,0,0,0,8,42,1,0,0,0,10,75,1,0,0,0,12,90,1,0,0,0,14,94,
1,0,0,0,16,99,1,0,0,0,18,117,1,0,0,0,20,22,3,2,1,0,21,20,1,0,0,0,22,25,1,
0,0,0,23,21,1,0,0,0,23,24,1,0,0,0,24,26,1,0,0,0,25,23,1,0,0,0,26,27,5,0,
0,1,27,1,1,0,0,0,28,31,3,4,2,0,29,31,3,8,4,0,30,28,1,0,0,0,30,29,1,0,0,0,
31,3,1,0,0,0,32,35,5,1,0,0,33,35,3,6,3,0,34,32,1,0,0,0,34,33,1,0,0,0,35,
36,1,0,0,0,36,37,5,19,0,0,37,38,5,2,0,0,38,39,3,18,9,0,39,5,1,0,0,0,40,41,
7,0,0,0,41,7,1,0,0,0,42,43,5,11,0,0,43,44,5,12,0,0,44,45,5,19,0,0,45,46,
5,13,0,0,46,48,5,14,0,0,47,49,3,10,5,0,48,47,1,0,0,0,49,50,1,0,0,0,50,48,
1,0,0,0,50,51,1,0,0,0,51,52,1,0,0,0,52,53,5,15,0,0,53,9,1,0,0,0,54,55,3,
18,9,0,55,56,5,16,0,0,56,57,3,12,6,0,57,58,5,17,0,0,58,76,1,0,0,0,59,60,
3,18,9,0,60,61,5,16,0,0,61,65,5,14,0,0,62,64,3,12,6,0,63,62,1,0,0,0,64,67,
1,0,0,0,65,63,1,0,0,0,65,66,1,0,0,0,66,68,1,0,0,0,67,65,1,0,0,0,68,69,5,
15,0,0,69,76,1,0,0,0,70,71,5,18,0,0,71,72,5,16,0,0,72,73,3,12,6,0,73,74,
5,17,0,0,74,76,1,0,0,0,75,54,1,0,0,0,75,59,1,0,0,0,75,70,1,0,0,0,76,11,1,
0,0,0,77,78,5,19,0,0,78,79,5,2,0,0,79,91,3,18,9,0,80,81,5,19,0,0,81,85,5,
12,0,0,82,84,3,18,9,0,83,82,1,0,0,0,84,87,1,0,0,0,85,83,1,0,0,0,85,86,1,
0,0,0,86,88,1,0,0,0,87,85,1,0,0,0,88,91,5,13,0,0,89,91,3,2,1,0,90,77,1,0,
0,0,90,80,1,0,0,0,90,89,1,0,0,0,91,13,1,0,0,0,92,95,5,1,0,0,93,95,3,6,3,
0,94,92,1,0,0,0,94,93,1,0,0,0,95,96,1,0,0,0,96,97,5,19,0,0,97,98,5,28,0,
0,98,15,1,0,0,0,99,103,5,14,0,0,100,102,3,14,7,0,101,100,1,0,0,0,102,105,
1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,0,105,103,1,0,0,0,
106,107,5,15,0,0,107,17,1,0,0,0,108,118,5,21,0,0,109,118,5,22,0,0,110,118,
5,23,0,0,111,118,5,19,0,0,112,118,5,25,0,0,113,118,5,20,0,0,114,118,5,24,
0,0,115,118,5,26,0,0,116,118,3,16,8,0,117,108,1,0,0,0,117,109,1,0,0,0,117,
110,1,0,0,0,117,111,1,0,0,0,117,112,1,0,0,0,117,113,1,0,0,0,117,114,1,0,
0,0,117,115,1,0,0,0,117,116,1,0,0,0,118,19,1,0,0,0,11,23,30,34,50,65,75,
85,90,94,103,117];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class AxolangParser extends antlr4.Parser {

    static grammarFileName = "Axolang.g4";
    static literalNames = [ null, "'auto'", "'='", "'xxsvar'", "'xsvar'", 
                            "'svar'", "'var'", "'lvar'", "'xlvar'", "'xxlvar'", 
                            "'fun'", "'match'", "'('", "')'", "'{'", "'}'", 
                            "'->'", "';'", "'_'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, "IDENTIFIER", "CHAR_LITERAL", 
                             "INT_LITERAL", "UINT_LITERAL", "FLOAT_LITERAL", 
                             "DECIMAL_LITERAL", "COMPLEX_LITERAL", "BOOLEAN", 
                             "WS", "NL" ];
    static ruleNames = [ "program", "statement", "varDeclaration", "type", 
                         "matchStatement", "matchCase", "declaration", "pkgVar", 
                         "pkgDeclaration", "expression" ];

    constructor(input) {
        super(input);
        this._interp = new antlr4.atn.ParserATNSimulator(this, atn, decisionsToDFA, sharedContextCache);
        this.ruleNames = AxolangParser.ruleNames;
        this.literalNames = AxolangParser.literalNames;
        this.symbolicNames = AxolangParser.symbolicNames;
    }



	program() {
	    let localctx = new ProgramContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 0, AxolangParser.RULE_program);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 23;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 4090) !== 0)) {
	            this.state = 20;
	            this.statement();
	            this.state = 25;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 26;
	        this.match(AxolangParser.EOF);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	statement() {
	    let localctx = new StatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 2, AxolangParser.RULE_statement);
	    try {
	        this.state = 30;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 3:
	        case 4:
	        case 5:
	        case 6:
	        case 7:
	        case 8:
	        case 9:
	        case 10:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 28;
	            this.varDeclaration();
	            break;
	        case 11:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 29;
	            this.matchStatement();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	varDeclaration() {
	    let localctx = new VarDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 4, AxolangParser.RULE_varDeclaration);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 34;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	            this.state = 32;
	            this.match(AxolangParser.T__0);
	            break;
	        case 3:
	        case 4:
	        case 5:
	        case 6:
	        case 7:
	        case 8:
	        case 9:
	        case 10:
	            this.state = 33;
	            this.type();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 36;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 37;
	        this.match(AxolangParser.T__1);
	        this.state = 38;
	        this.expression();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	type() {
	    let localctx = new TypeContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 6, AxolangParser.RULE_type);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 40;
	        _la = this._input.LA(1);
	        if(!((((_la) & ~0x1f) === 0 && ((1 << _la) & 2040) !== 0))) {
	        this._errHandler.recoverInline(this);
	        }
	        else {
	        	this._errHandler.reportMatch(this);
	            this.consume();
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	matchStatement() {
	    let localctx = new MatchStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 8, AxolangParser.RULE_matchStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 42;
	        this.match(AxolangParser.T__10);
	        this.state = 43;
	        this.match(AxolangParser.T__11);
	        this.state = 44;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 45;
	        this.match(AxolangParser.T__12);
	        this.state = 46;
	        this.match(AxolangParser.T__13);
	        this.state = 48; 
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        do {
	            this.state = 47;
	            this.matchCase();
	            this.state = 50; 
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        } while((((_la) & ~0x1f) === 0 && ((1 << _la) & 133971968) !== 0));
	        this.state = 52;
	        this.match(AxolangParser.T__14);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	matchCase() {
	    let localctx = new MatchCaseContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 10, AxolangParser.RULE_matchCase);
	    var _la = 0;
	    try {
	        this.state = 75;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,5,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 54;
	            this.expression();
	            this.state = 55;
	            this.match(AxolangParser.T__15);
	            this.state = 56;
	            this.declaration();
	            this.state = 57;
	            this.match(AxolangParser.T__16);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 59;
	            this.expression();
	            this.state = 60;
	            this.match(AxolangParser.T__15);
	            this.state = 61;
	            this.match(AxolangParser.T__13);
	            this.state = 65;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while((((_la) & ~0x1f) === 0 && ((1 << _la) & 528378) !== 0)) {
	                this.state = 62;
	                this.declaration();
	                this.state = 67;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 68;
	            this.match(AxolangParser.T__14);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 70;
	            this.match(AxolangParser.T__17);
	            this.state = 71;
	            this.match(AxolangParser.T__15);
	            this.state = 72;
	            this.declaration();
	            this.state = 73;
	            this.match(AxolangParser.T__16);
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	declaration() {
	    let localctx = new DeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 12, AxolangParser.RULE_declaration);
	    var _la = 0;
	    try {
	        this.state = 90;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,7,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 77;
	            this.match(AxolangParser.IDENTIFIER);
	            this.state = 78;
	            this.match(AxolangParser.T__1);
	            this.state = 79;
	            this.expression();
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 80;
	            this.match(AxolangParser.IDENTIFIER);
	            this.state = 81;
	            this.match(AxolangParser.T__11);
	            this.state = 85;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while((((_la) & ~0x1f) === 0 && ((1 << _la) & 133709824) !== 0)) {
	                this.state = 82;
	                this.expression();
	                this.state = 87;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 88;
	            this.match(AxolangParser.T__12);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 89;
	            this.statement();
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	pkgVar() {
	    let localctx = new PkgVarContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 14, AxolangParser.RULE_pkgVar);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 94;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	            this.state = 92;
	            this.match(AxolangParser.T__0);
	            break;
	        case 3:
	        case 4:
	        case 5:
	        case 6:
	        case 7:
	        case 8:
	        case 9:
	        case 10:
	            this.state = 93;
	            this.type();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 96;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 97;
	        this.match(AxolangParser.NL);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	pkgDeclaration() {
	    let localctx = new PkgDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 16, AxolangParser.RULE_pkgDeclaration);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 99;
	        this.match(AxolangParser.T__13);
	        this.state = 103;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 2042) !== 0)) {
	            this.state = 100;
	            this.pkgVar();
	            this.state = 105;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 106;
	        this.match(AxolangParser.T__14);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	expression() {
	    let localctx = new ExpressionContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 18, AxolangParser.RULE_expression);
	    try {
	        this.state = 117;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 21:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 108;
	            this.match(AxolangParser.INT_LITERAL);
	            break;
	        case 22:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 109;
	            this.match(AxolangParser.UINT_LITERAL);
	            break;
	        case 23:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 110;
	            this.match(AxolangParser.FLOAT_LITERAL);
	            break;
	        case 19:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 111;
	            this.match(AxolangParser.IDENTIFIER);
	            break;
	        case 25:
	            this.enterOuterAlt(localctx, 5);
	            this.state = 112;
	            this.match(AxolangParser.COMPLEX_LITERAL);
	            break;
	        case 20:
	            this.enterOuterAlt(localctx, 6);
	            this.state = 113;
	            this.match(AxolangParser.CHAR_LITERAL);
	            break;
	        case 24:
	            this.enterOuterAlt(localctx, 7);
	            this.state = 114;
	            this.match(AxolangParser.DECIMAL_LITERAL);
	            break;
	        case 26:
	            this.enterOuterAlt(localctx, 8);
	            this.state = 115;
	            this.match(AxolangParser.BOOLEAN);
	            break;
	        case 14:
	            this.enterOuterAlt(localctx, 9);
	            this.state = 116;
	            this.pkgDeclaration();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


}

AxolangParser.EOF = antlr4.Token.EOF;
AxolangParser.T__0 = 1;
AxolangParser.T__1 = 2;
AxolangParser.T__2 = 3;
AxolangParser.T__3 = 4;
AxolangParser.T__4 = 5;
AxolangParser.T__5 = 6;
AxolangParser.T__6 = 7;
AxolangParser.T__7 = 8;
AxolangParser.T__8 = 9;
AxolangParser.T__9 = 10;
AxolangParser.T__10 = 11;
AxolangParser.T__11 = 12;
AxolangParser.T__12 = 13;
AxolangParser.T__13 = 14;
AxolangParser.T__14 = 15;
AxolangParser.T__15 = 16;
AxolangParser.T__16 = 17;
AxolangParser.T__17 = 18;
AxolangParser.IDENTIFIER = 19;
AxolangParser.CHAR_LITERAL = 20;
AxolangParser.INT_LITERAL = 21;
AxolangParser.UINT_LITERAL = 22;
AxolangParser.FLOAT_LITERAL = 23;
AxolangParser.DECIMAL_LITERAL = 24;
AxolangParser.COMPLEX_LITERAL = 25;
AxolangParser.BOOLEAN = 26;
AxolangParser.WS = 27;
AxolangParser.NL = 28;

AxolangParser.RULE_program = 0;
AxolangParser.RULE_statement = 1;
AxolangParser.RULE_varDeclaration = 2;
AxolangParser.RULE_type = 3;
AxolangParser.RULE_matchStatement = 4;
AxolangParser.RULE_matchCase = 5;
AxolangParser.RULE_declaration = 6;
AxolangParser.RULE_pkgVar = 7;
AxolangParser.RULE_pkgDeclaration = 8;
AxolangParser.RULE_expression = 9;

class ProgramContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_program;
    }

	EOF() {
	    return this.getToken(AxolangParser.EOF, 0);
	};

	statement = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(StatementContext);
	    } else {
	        return this.getTypedRuleContext(StatementContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterProgram(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitProgram(this);
		}
	}


}



class StatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_statement;
    }

	varDeclaration() {
	    return this.getTypedRuleContext(VarDeclarationContext,0);
	};

	matchStatement() {
	    return this.getTypedRuleContext(MatchStatementContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitStatement(this);
		}
	}


}



class VarDeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_varDeclaration;
    }

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	type() {
	    return this.getTypedRuleContext(TypeContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterVarDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitVarDeclaration(this);
		}
	}


}



class TypeContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_type;
    }


	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterType(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitType(this);
		}
	}


}



class MatchStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_matchStatement;
    }

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	matchCase = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(MatchCaseContext);
	    } else {
	        return this.getTypedRuleContext(MatchCaseContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterMatchStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitMatchStatement(this);
		}
	}


}



class MatchCaseContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_matchCase;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	declaration = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(DeclarationContext);
	    } else {
	        return this.getTypedRuleContext(DeclarationContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterMatchCase(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitMatchCase(this);
		}
	}


}



class DeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_declaration;
    }

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	expression = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(ExpressionContext);
	    } else {
	        return this.getTypedRuleContext(ExpressionContext,i);
	    }
	};

	statement() {
	    return this.getTypedRuleContext(StatementContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitDeclaration(this);
		}
	}


}



class PkgVarContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_pkgVar;
    }

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	NL() {
	    return this.getToken(AxolangParser.NL, 0);
	};

	type() {
	    return this.getTypedRuleContext(TypeContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterPkgVar(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitPkgVar(this);
		}
	}


}



class PkgDeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_pkgDeclaration;
    }

	pkgVar = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(PkgVarContext);
	    } else {
	        return this.getTypedRuleContext(PkgVarContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterPkgDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitPkgDeclaration(this);
		}
	}


}



class ExpressionContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = AxolangParser.RULE_expression;
    }

	INT_LITERAL() {
	    return this.getToken(AxolangParser.INT_LITERAL, 0);
	};

	UINT_LITERAL() {
	    return this.getToken(AxolangParser.UINT_LITERAL, 0);
	};

	FLOAT_LITERAL() {
	    return this.getToken(AxolangParser.FLOAT_LITERAL, 0);
	};

	IDENTIFIER() {
	    return this.getToken(AxolangParser.IDENTIFIER, 0);
	};

	COMPLEX_LITERAL() {
	    return this.getToken(AxolangParser.COMPLEX_LITERAL, 0);
	};

	CHAR_LITERAL() {
	    return this.getToken(AxolangParser.CHAR_LITERAL, 0);
	};

	DECIMAL_LITERAL() {
	    return this.getToken(AxolangParser.DECIMAL_LITERAL, 0);
	};

	BOOLEAN() {
	    return this.getToken(AxolangParser.BOOLEAN, 0);
	};

	pkgDeclaration() {
	    return this.getTypedRuleContext(PkgDeclarationContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.enterExpression(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof AxolangListener ) {
	        listener.exitExpression(this);
		}
	}


}




AxolangParser.ProgramContext = ProgramContext; 
AxolangParser.StatementContext = StatementContext; 
AxolangParser.VarDeclarationContext = VarDeclarationContext; 
AxolangParser.TypeContext = TypeContext; 
AxolangParser.MatchStatementContext = MatchStatementContext; 
AxolangParser.MatchCaseContext = MatchCaseContext; 
AxolangParser.DeclarationContext = DeclarationContext; 
AxolangParser.PkgVarContext = PkgVarContext; 
AxolangParser.PkgDeclarationContext = PkgDeclarationContext; 
AxolangParser.ExpressionContext = ExpressionContext; 
