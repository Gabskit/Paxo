// Generated from Axolang.g4 by ANTLR 4.13.1
// jshint ignore: start
import antlr4 from 'antlr4';
import AxolangListener from './AxolangListener.js';
const serializedATN = [4,1,46,75,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,
2,5,7,5,2,6,7,6,2,7,7,7,1,0,5,0,18,8,0,10,0,12,0,21,9,0,1,0,1,0,1,1,1,1,
3,1,27,8,1,1,2,1,2,3,2,31,8,2,1,2,1,2,1,2,1,2,1,3,1,3,1,4,1,4,1,4,1,4,1,
4,1,4,4,4,45,8,4,11,4,12,4,46,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,67,8,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,0,0,
8,0,2,4,6,8,10,12,14,0,2,1,0,3,31,1,0,40,45,72,0,19,1,0,0,0,2,26,1,0,0,0,
4,30,1,0,0,0,6,36,1,0,0,0,8,38,1,0,0,0,10,66,1,0,0,0,12,68,1,0,0,0,14,72,
1,0,0,0,16,18,3,2,1,0,17,16,1,0,0,0,18,21,1,0,0,0,19,17,1,0,0,0,19,20,1,
0,0,0,20,22,1,0,0,0,21,19,1,0,0,0,22,23,5,0,0,1,23,1,1,0,0,0,24,27,3,4,2,
0,25,27,3,8,4,0,26,24,1,0,0,0,26,25,1,0,0,0,27,3,1,0,0,0,28,31,5,1,0,0,29,
31,3,6,3,0,30,28,1,0,0,0,30,29,1,0,0,0,31,32,1,0,0,0,32,33,5,40,0,0,33,34,
5,2,0,0,34,35,3,14,7,0,35,5,1,0,0,0,36,37,7,0,0,0,37,7,1,0,0,0,38,39,5,32,
0,0,39,40,5,33,0,0,40,41,5,40,0,0,41,42,5,34,0,0,42,44,5,35,0,0,43,45,3,
10,5,0,44,43,1,0,0,0,45,46,1,0,0,0,46,44,1,0,0,0,46,47,1,0,0,0,47,48,1,0,
0,0,48,49,5,36,0,0,49,9,1,0,0,0,50,51,3,14,7,0,51,52,5,37,0,0,52,53,3,12,
6,0,53,54,5,38,0,0,54,67,1,0,0,0,55,56,3,14,7,0,56,57,5,37,0,0,57,58,5,35,
0,0,58,59,3,12,6,0,59,60,5,36,0,0,60,67,1,0,0,0,61,62,5,39,0,0,62,63,5,37,
0,0,63,64,3,12,6,0,64,65,5,38,0,0,65,67,1,0,0,0,66,50,1,0,0,0,66,55,1,0,
0,0,66,61,1,0,0,0,67,11,1,0,0,0,68,69,5,40,0,0,69,70,5,2,0,0,70,71,3,14,
7,0,71,13,1,0,0,0,72,73,7,1,0,0,73,15,1,0,0,0,5,19,26,30,46,66];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class AxolangParser extends antlr4.Parser {

    static grammarFileName = "Axolang.g4";
    static literalNames = [ null, "'auto'", "'='", "'xsany'", "'sany'", 
                            "'any'", "'lany'", "'xlany'", "'xxlany'", "'xxsint'", 
                            "'xsint'", "'sint'", "'int'", "'lint'", "'xlint'", 
                            "'xsflt'", "'sflt'", "'flt'", "'lflt'", "'xlflt'", 
                            "'sdec'", "'dec'", "'ldec'", "'xscom'", "'scom'", 
                            "'com'", "'lcom'", "'xlcom'", "'boo'", "'pkg'", 
                            "'chara'", "'fun'", "'match'", "'('", "')'", 
                            "'{'", "'}'", "'->'", "';'", "'_'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             "IDENTIFIER", "CHAR_LITERAL", "INT_LITERAL", 
                             "FLOAT_LITERAL", "DECIMAL_LITERAL", "COMPLEX_LITERAL", 
                             "WS" ];
    static ruleNames = [ "program", "statement", "varDeclaration", "type", 
                         "matchStatement", "matchCase", "declaration", "expression" ];

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
	        this.state = 19;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while(((((_la - 1)) & ~0x1f) === 0 && ((1 << (_la - 1)) & 4294967293) !== 0)) {
	            this.state = 16;
	            this.statement();
	            this.state = 21;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 22;
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
	        this.state = 26;
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
	        case 11:
	        case 12:
	        case 13:
	        case 14:
	        case 15:
	        case 16:
	        case 17:
	        case 18:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 27:
	        case 28:
	        case 29:
	        case 30:
	        case 31:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 24;
	            this.varDeclaration();
	            break;
	        case 32:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 25;
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
	        this.state = 30;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	            this.state = 28;
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
	        case 11:
	        case 12:
	        case 13:
	        case 14:
	        case 15:
	        case 16:
	        case 17:
	        case 18:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 27:
	        case 28:
	        case 29:
	        case 30:
	        case 31:
	            this.state = 29;
	            this.type();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 32;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 33;
	        this.match(AxolangParser.T__1);
	        this.state = 34;
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
	        this.state = 36;
	        _la = this._input.LA(1);
	        if(!((((_la) & ~0x1f) === 0 && ((1 << _la) & 4294967288) !== 0))) {
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
	        this.state = 38;
	        this.match(AxolangParser.T__31);
	        this.state = 39;
	        this.match(AxolangParser.T__32);
	        this.state = 40;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 41;
	        this.match(AxolangParser.T__33);
	        this.state = 42;
	        this.match(AxolangParser.T__34);
	        this.state = 44; 
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        do {
	            this.state = 43;
	            this.matchCase();
	            this.state = 46; 
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        } while(((((_la - 39)) & ~0x1f) === 0 && ((1 << (_la - 39)) & 127) !== 0));
	        this.state = 48;
	        this.match(AxolangParser.T__35);
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
	    try {
	        this.state = 66;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,4,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 50;
	            this.expression();
	            this.state = 51;
	            this.match(AxolangParser.T__36);
	            this.state = 52;
	            this.declaration();
	            this.state = 53;
	            this.match(AxolangParser.T__37);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 55;
	            this.expression();
	            this.state = 56;
	            this.match(AxolangParser.T__36);
	            this.state = 57;
	            this.match(AxolangParser.T__34);
	            this.state = 58;
	            this.declaration();
	            this.state = 59;
	            this.match(AxolangParser.T__35);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 61;
	            this.match(AxolangParser.T__38);
	            this.state = 62;
	            this.match(AxolangParser.T__36);
	            this.state = 63;
	            this.declaration();
	            this.state = 64;
	            this.match(AxolangParser.T__37);
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
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 68;
	        this.match(AxolangParser.IDENTIFIER);
	        this.state = 69;
	        this.match(AxolangParser.T__1);
	        this.state = 70;
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



	expression() {
	    let localctx = new ExpressionContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 14, AxolangParser.RULE_expression);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 72;
	        _la = this._input.LA(1);
	        if(!(((((_la - 40)) & ~0x1f) === 0 && ((1 << (_la - 40)) & 63) !== 0))) {
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
AxolangParser.T__18 = 19;
AxolangParser.T__19 = 20;
AxolangParser.T__20 = 21;
AxolangParser.T__21 = 22;
AxolangParser.T__22 = 23;
AxolangParser.T__23 = 24;
AxolangParser.T__24 = 25;
AxolangParser.T__25 = 26;
AxolangParser.T__26 = 27;
AxolangParser.T__27 = 28;
AxolangParser.T__28 = 29;
AxolangParser.T__29 = 30;
AxolangParser.T__30 = 31;
AxolangParser.T__31 = 32;
AxolangParser.T__32 = 33;
AxolangParser.T__33 = 34;
AxolangParser.T__34 = 35;
AxolangParser.T__35 = 36;
AxolangParser.T__36 = 37;
AxolangParser.T__37 = 38;
AxolangParser.T__38 = 39;
AxolangParser.IDENTIFIER = 40;
AxolangParser.CHAR_LITERAL = 41;
AxolangParser.INT_LITERAL = 42;
AxolangParser.FLOAT_LITERAL = 43;
AxolangParser.DECIMAL_LITERAL = 44;
AxolangParser.COMPLEX_LITERAL = 45;
AxolangParser.WS = 46;

AxolangParser.RULE_program = 0;
AxolangParser.RULE_statement = 1;
AxolangParser.RULE_varDeclaration = 2;
AxolangParser.RULE_type = 3;
AxolangParser.RULE_matchStatement = 4;
AxolangParser.RULE_matchCase = 5;
AxolangParser.RULE_declaration = 6;
AxolangParser.RULE_expression = 7;

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

	declaration() {
	    return this.getTypedRuleContext(DeclarationContext,0);
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

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
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
AxolangParser.ExpressionContext = ExpressionContext; 
