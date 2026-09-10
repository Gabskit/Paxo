// jshint ignore: start
import antlr4 from 'antlr4';
import PaxoListener from './PaxoListener.js';
const serializedATN = [4,1,81,402,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,
4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,
2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,
20,7,20,2,21,7,21,1,0,5,0,46,8,0,10,0,12,0,49,9,0,1,0,1,0,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,63,8,1,1,1,1,1,1,1,1,1,1,1,3,1,70,8,1,1,1,
3,1,73,8,1,1,2,3,2,76,8,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,84,8,2,1,2,1,2,1,2,
1,2,3,2,90,8,2,1,2,1,2,1,2,1,2,1,2,3,2,97,8,2,1,2,1,2,1,2,3,2,102,8,2,1,
3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,3,5,112,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,
5,121,8,5,1,5,1,5,1,5,3,5,126,8,5,1,5,1,5,1,5,3,5,131,8,5,1,5,1,5,1,5,1,
5,1,5,1,5,3,5,139,8,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,147,8,5,3,5,149,8,5,1,
6,1,6,1,6,1,6,1,6,1,6,1,6,5,6,158,8,6,10,6,12,6,161,9,6,1,6,3,6,164,8,6,
1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,173,8,7,1,8,1,8,1,8,1,8,1,8,1,8,3,8,181,
8,8,1,8,1,8,3,8,185,8,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,12,
1,12,1,12,1,12,3,12,200,8,12,1,12,1,12,1,12,1,13,1,13,3,13,207,8,13,1,13,
1,13,1,13,3,13,212,8,13,1,13,1,13,1,14,1,14,3,14,218,8,14,1,14,5,14,221,
8,14,10,14,12,14,224,9,14,1,14,3,14,227,8,14,1,14,1,14,1,15,1,15,5,15,233,
8,15,10,15,12,15,236,9,15,1,15,1,15,1,15,5,15,241,8,15,10,15,12,15,244,9,
15,1,15,1,15,5,15,248,8,15,10,15,12,15,251,9,15,1,15,1,15,1,15,5,15,256,
8,15,10,15,12,15,259,9,15,1,15,3,15,262,8,15,1,16,1,16,1,16,1,16,1,16,1,
16,5,16,270,8,16,10,16,12,16,273,9,16,1,17,1,17,3,17,277,8,17,1,17,3,17,
280,8,17,1,18,1,18,1,18,3,18,285,8,18,1,19,1,19,1,19,5,19,290,8,19,10,19,
12,19,293,9,19,3,19,295,8,19,1,20,1,20,1,20,1,20,3,20,301,8,20,1,20,1,20,
1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,
20,1,20,1,20,3,20,322,8,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,
20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
5,20,362,8,20,10,20,12,20,365,9,20,1,21,1,21,1,21,1,21,5,21,371,8,21,10,
21,12,21,374,9,21,1,21,1,21,1,21,1,21,1,21,1,21,5,21,382,8,21,10,21,12,21,
385,9,21,1,21,1,21,1,21,1,21,1,21,1,21,5,21,393,8,21,10,21,12,21,396,9,21,
1,21,1,21,3,21,400,8,21,1,21,1,159,1,40,22,0,2,4,6,8,10,12,14,16,18,20,22,
24,26,28,30,32,34,36,38,40,42,0,11,1,0,46,57,1,0,58,59,1,0,66,67,1,0,16,
17,1,0,18,19,1,0,42,43,1,0,25,26,1,0,27,28,1,0,29,30,3,0,2,2,4,4,31,37,1,
0,38,41,462,0,47,1,0,0,0,2,72,1,0,0,0,4,101,1,0,0,0,6,103,1,0,0,0,8,105,
1,0,0,0,10,148,1,0,0,0,12,150,1,0,0,0,14,172,1,0,0,0,16,174,1,0,0,0,18,186,
1,0,0,0,20,188,1,0,0,0,22,190,1,0,0,0,24,192,1,0,0,0,26,204,1,0,0,0,28,215,
1,0,0,0,30,261,1,0,0,0,32,263,1,0,0,0,34,274,1,0,0,0,36,281,1,0,0,0,38,294,
1,0,0,0,40,321,1,0,0,0,42,399,1,0,0,0,44,46,3,2,1,0,45,44,1,0,0,0,46,49,
1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,50,1,0,0,0,49,47,1,0,0,0,50,51,5,
0,0,1,51,1,1,0,0,0,52,73,5,1,0,0,53,73,3,4,2,0,54,73,3,10,5,0,55,73,3,12,
6,0,56,73,3,16,8,0,57,73,3,24,12,0,58,73,3,36,18,0,59,73,3,34,17,0,60,62,
3,40,20,0,61,63,5,1,0,0,62,61,1,0,0,0,62,63,1,0,0,0,63,73,1,0,0,0,64,65,
5,63,0,0,65,66,5,2,0,0,66,69,5,76,0,0,67,68,5,3,0,0,68,70,5,76,0,0,69,67,
1,0,0,0,69,70,1,0,0,0,70,71,1,0,0,0,71,73,5,4,0,0,72,52,1,0,0,0,72,53,1,
0,0,0,72,54,1,0,0,0,72,55,1,0,0,0,72,56,1,0,0,0,72,57,1,0,0,0,72,58,1,0,
0,0,72,59,1,0,0,0,72,60,1,0,0,0,72,64,1,0,0,0,73,3,1,0,0,0,74,76,3,8,4,0,
75,74,1,0,0,0,75,76,1,0,0,0,76,77,1,0,0,0,77,78,3,6,3,0,78,79,5,76,0,0,79,
80,5,5,0,0,80,81,3,40,20,0,81,102,1,0,0,0,82,84,3,8,4,0,83,82,1,0,0,0,83,
84,1,0,0,0,84,85,1,0,0,0,85,86,3,6,3,0,86,87,5,76,0,0,87,89,5,6,0,0,88,90,
5,68,0,0,89,88,1,0,0,0,89,90,1,0,0,0,90,91,1,0,0,0,91,92,5,7,0,0,92,93,5,
5,0,0,93,94,3,42,21,0,94,102,1,0,0,0,95,97,3,8,4,0,96,95,1,0,0,0,96,97,1,
0,0,0,97,98,1,0,0,0,98,99,3,6,3,0,99,100,5,76,0,0,100,102,1,0,0,0,101,75,
1,0,0,0,101,83,1,0,0,0,101,96,1,0,0,0,102,5,1,0,0,0,103,104,7,0,0,0,104,
7,1,0,0,0,105,106,7,1,0,0,106,9,1,0,0,0,107,108,5,76,0,0,108,109,5,5,0,0,
109,111,3,40,20,0,110,112,5,1,0,0,111,110,1,0,0,0,111,112,1,0,0,0,112,149,
1,0,0,0,113,114,5,76,0,0,114,115,5,6,0,0,115,116,3,40,20,0,116,117,5,7,0,
0,117,118,5,5,0,0,118,120,3,40,20,0,119,121,5,1,0,0,120,119,1,0,0,0,120,
121,1,0,0,0,121,149,1,0,0,0,122,123,5,76,0,0,123,125,5,8,0,0,124,126,5,1,
0,0,125,124,1,0,0,0,125,126,1,0,0,0,126,149,1,0,0,0,127,128,5,76,0,0,128,
130,5,9,0,0,129,131,5,1,0,0,130,129,1,0,0,0,130,131,1,0,0,0,131,149,1,0,
0,0,132,133,3,40,20,0,133,134,5,3,0,0,134,135,5,76,0,0,135,136,5,5,0,0,136,
138,3,40,20,0,137,139,5,1,0,0,138,137,1,0,0,0,138,139,1,0,0,0,139,149,1,
0,0,0,140,141,5,75,0,0,141,142,5,3,0,0,142,143,5,76,0,0,143,144,5,5,0,0,
144,146,3,40,20,0,145,147,5,1,0,0,146,145,1,0,0,0,146,147,1,0,0,0,147,149,
1,0,0,0,148,107,1,0,0,0,148,113,1,0,0,0,148,122,1,0,0,0,148,127,1,0,0,0,
148,132,1,0,0,0,148,140,1,0,0,0,149,11,1,0,0,0,150,151,5,10,0,0,151,152,
3,40,20,0,152,153,5,11,0,0,153,154,5,12,0,0,154,159,3,14,7,0,155,156,5,13,
0,0,156,158,3,14,7,0,157,155,1,0,0,0,158,161,1,0,0,0,159,160,1,0,0,0,159,
157,1,0,0,0,160,163,1,0,0,0,161,159,1,0,0,0,162,164,5,1,0,0,163,162,1,0,
0,0,163,164,1,0,0,0,164,13,1,0,0,0,165,166,3,40,20,0,166,167,5,14,0,0,167,
168,3,30,15,0,168,173,1,0,0,0,169,170,5,15,0,0,170,171,5,14,0,0,171,173,
3,30,15,0,172,165,1,0,0,0,172,169,1,0,0,0,173,15,1,0,0,0,174,175,5,10,0,
0,175,176,3,40,20,0,176,177,5,11,0,0,177,178,5,13,0,0,178,180,3,18,9,0,179,
181,3,20,10,0,180,179,1,0,0,0,180,181,1,0,0,0,181,182,1,0,0,0,182,184,3,
30,15,0,183,185,3,22,11,0,184,183,1,0,0,0,184,185,1,0,0,0,185,17,1,0,0,0,
186,187,7,2,0,0,187,19,1,0,0,0,188,189,7,3,0,0,189,21,1,0,0,0,190,191,7,
4,0,0,191,23,1,0,0,0,192,193,5,60,0,0,193,194,3,30,15,0,194,195,5,61,0,0,
195,196,5,10,0,0,196,199,5,76,0,0,197,198,5,3,0,0,198,200,5,76,0,0,199,197,
1,0,0,0,199,200,1,0,0,0,200,201,1,0,0,0,201,202,5,11,0,0,202,203,3,30,15,
0,203,25,1,0,0,0,204,206,5,10,0,0,205,207,3,32,16,0,206,205,1,0,0,0,206,
207,1,0,0,0,207,208,1,0,0,0,208,211,5,11,0,0,209,210,5,13,0,0,210,212,3,
6,3,0,211,209,1,0,0,0,211,212,1,0,0,0,212,213,1,0,0,0,213,214,3,30,15,0,
214,27,1,0,0,0,215,222,5,20,0,0,216,218,5,21,0,0,217,216,1,0,0,0,217,218,
1,0,0,0,218,219,1,0,0,0,219,221,3,4,2,0,220,217,1,0,0,0,221,224,1,0,0,0,
222,220,1,0,0,0,222,223,1,0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,225,227,
5,21,0,0,226,225,1,0,0,0,226,227,1,0,0,0,227,228,1,0,0,0,228,229,5,22,0,
0,229,29,1,0,0,0,230,234,5,20,0,0,231,233,3,2,1,0,232,231,1,0,0,0,233,236,
1,0,0,0,234,232,1,0,0,0,234,235,1,0,0,0,235,237,1,0,0,0,236,234,1,0,0,0,
237,262,5,22,0,0,238,242,5,13,0,0,239,241,3,2,1,0,240,239,1,0,0,0,241,244,
1,0,0,0,242,240,1,0,0,0,242,243,1,0,0,0,243,245,1,0,0,0,244,242,1,0,0,0,
245,262,5,23,0,0,246,248,3,2,1,0,247,246,1,0,0,0,248,251,1,0,0,0,249,247,
1,0,0,0,249,250,1,0,0,0,250,252,1,0,0,0,251,249,1,0,0,0,252,262,5,24,0,0,
253,257,5,13,0,0,254,256,3,2,1,0,255,254,1,0,0,0,256,259,1,0,0,0,257,255,
1,0,0,0,257,258,1,0,0,0,258,260,1,0,0,0,259,257,1,0,0,0,260,262,5,1,0,0,
261,230,1,0,0,0,261,238,1,0,0,0,261,249,1,0,0,0,261,253,1,0,0,0,262,31,1,
0,0,0,263,264,3,6,3,0,264,271,5,76,0,0,265,266,5,21,0,0,266,267,3,6,3,0,
267,268,5,76,0,0,268,270,1,0,0,0,269,265,1,0,0,0,270,273,1,0,0,0,271,269,
1,0,0,0,271,272,1,0,0,0,272,33,1,0,0,0,273,271,1,0,0,0,274,276,5,64,0,0,
275,277,3,40,20,0,276,275,1,0,0,0,276,277,1,0,0,0,277,279,1,0,0,0,278,280,
5,1,0,0,279,278,1,0,0,0,279,280,1,0,0,0,280,35,1,0,0,0,281,282,5,65,0,0,
282,284,3,40,20,0,283,285,5,1,0,0,284,283,1,0,0,0,284,285,1,0,0,0,285,37,
1,0,0,0,286,291,3,40,20,0,287,288,5,21,0,0,288,290,3,40,20,0,289,287,1,0,
0,0,290,293,1,0,0,0,291,289,1,0,0,0,291,292,1,0,0,0,292,295,1,0,0,0,293,
291,1,0,0,0,294,286,1,0,0,0,294,295,1,0,0,0,295,39,1,0,0,0,296,297,6,20,
-1,0,297,298,5,76,0,0,298,300,5,10,0,0,299,301,3,38,19,0,300,299,1,0,0,0,
300,301,1,0,0,0,301,302,1,0,0,0,302,322,5,11,0,0,303,304,7,5,0,0,304,322,
3,40,20,15,305,306,5,75,0,0,306,307,5,3,0,0,307,322,5,76,0,0,308,322,5,68,
0,0,309,322,5,69,0,0,310,322,5,78,0,0,311,322,5,77,0,0,312,322,5,71,0,0,
313,322,5,72,0,0,314,322,5,73,0,0,315,322,5,74,0,0,316,322,5,70,0,0,317,
322,3,42,21,0,318,322,5,76,0,0,319,322,3,28,14,0,320,322,3,26,13,0,321,296,
1,0,0,0,321,303,1,0,0,0,321,305,1,0,0,0,321,308,1,0,0,0,321,309,1,0,0,0,
321,310,1,0,0,0,321,311,1,0,0,0,321,312,1,0,0,0,321,313,1,0,0,0,321,314,
1,0,0,0,321,315,1,0,0,0,321,316,1,0,0,0,321,317,1,0,0,0,321,318,1,0,0,0,
321,319,1,0,0,0,321,320,1,0,0,0,322,363,1,0,0,0,323,324,10,20,0,0,324,325,
7,6,0,0,325,362,3,40,20,21,326,327,10,19,0,0,327,328,7,7,0,0,328,362,3,40,
20,20,329,330,10,18,0,0,330,331,7,8,0,0,331,362,3,40,20,19,332,333,10,17,
0,0,333,334,7,9,0,0,334,362,3,40,20,18,335,336,10,16,0,0,336,337,7,10,0,
0,337,362,3,40,20,17,338,339,10,24,0,0,339,340,5,6,0,0,340,341,3,40,20,0,
341,342,5,7,0,0,342,343,5,10,0,0,343,344,3,38,19,0,344,345,5,11,0,0,345,
362,1,0,0,0,346,347,10,23,0,0,347,348,5,6,0,0,348,349,3,40,20,0,349,350,
5,7,0,0,350,362,1,0,0,0,351,352,10,22,0,0,352,353,5,3,0,0,353,354,5,76,0,
0,354,355,5,10,0,0,355,356,3,38,19,0,356,357,5,11,0,0,357,362,1,0,0,0,358,
359,10,21,0,0,359,360,5,3,0,0,360,362,5,76,0,0,361,323,1,0,0,0,361,326,1,
0,0,0,361,329,1,0,0,0,361,332,1,0,0,0,361,335,1,0,0,0,361,338,1,0,0,0,361,
346,1,0,0,0,361,351,1,0,0,0,361,358,1,0,0,0,362,365,1,0,0,0,363,361,1,0,
0,0,363,364,1,0,0,0,364,41,1,0,0,0,365,363,1,0,0,0,366,367,5,44,0,0,367,
372,3,40,20,0,368,369,5,21,0,0,369,371,3,40,20,0,370,368,1,0,0,0,371,374,
1,0,0,0,372,370,1,0,0,0,372,373,1,0,0,0,373,375,1,0,0,0,374,372,1,0,0,0,
375,376,5,45,0,0,376,400,1,0,0,0,377,378,5,20,0,0,378,383,3,40,20,0,379,
380,5,21,0,0,380,382,3,40,20,0,381,379,1,0,0,0,382,385,1,0,0,0,383,381,1,
0,0,0,383,384,1,0,0,0,384,386,1,0,0,0,385,383,1,0,0,0,386,387,5,22,0,0,387,
400,1,0,0,0,388,389,5,6,0,0,389,394,3,40,20,0,390,391,5,21,0,0,391,393,3,
40,20,0,392,390,1,0,0,0,393,396,1,0,0,0,394,392,1,0,0,0,394,395,1,0,0,0,
395,397,1,0,0,0,396,394,1,0,0,0,397,398,5,7,0,0,398,400,1,0,0,0,399,366,
1,0,0,0,399,377,1,0,0,0,399,388,1,0,0,0,400,43,1,0,0,0,46,47,62,69,72,75,
83,89,96,101,111,120,125,130,138,146,148,159,163,172,180,184,199,206,211,
217,222,226,234,242,249,257,261,271,276,279,284,291,294,300,321,361,363,
372,383,394,399];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class PaxoParser extends antlr4.Parser {

    static grammarFileName = "Paxo.g4";
    static literalNames = [ null, "';'", "'<'", "'.'", "'>'", "'='", "'['", 
                            "']'", "'++'", "'--'", "'('", "')'", "'?'", 
                            "':'", "'->'", "'_'", "'|:'", "'\\uD834\uDD06'", 
                            "':|'", "'\\uD834\uDD07'", "'{'", "','", "'}'", 
                            "'\\uD83C\uDFC1'", "'end'", "'\\u00F7'", "'\\u00D7'", 
                            "'+'", "'-'", "'\\u2022\\u00AB'", "'\\u00BB\\u2022'", 
                            "'\\u2264'", "'<='", "'\\u2265'", "'>='", "'=='", 
                            "'!='", "'\\u2260'", "'&'", "'|'", "'.&'", "'.|'", 
                            "'!'", "'.!'", "'\\u00AB'", "'\\u00BB'", null, 
                            null, null, "'abc'", "'trit'", "'bool'", "'pin'", 
                            "'fx'", null, "'int'", "'pdec'", "'col'", null, 
                            "'local'", null, null, null, null, "'return'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, "VAR_TYPE", 
                             "NUM_TYPE", "COMPLEX_TYPE", "CHARA_TYPE", "TRIT_TYPE", 
                             "BOOLEAN_TYPE", "POINTER_TYPE", "FUNC_TYPE", 
                             "PKG_TYPE", "INT_TYPE", "PKDEC_TYPE", "COLOR_TYPE", 
                             "GLOBAL", "LOCAL", "TRY", "CATCH", "ARROW", 
                             "INCLUDE", "RETURN", "THROW", "PAUSE_MODE", 
                             "PLAY_MODE", "INT_LITERAL", "DECIMAL_LITERAL", 
                             "COMPLEX_LITERAL", "BOOLEAN_BIT", "BOOLEAN_TRIT", 
                             "POINTER_LITERAL", "COLOR_LITERAL", "THIS_SCOPE", 
                             "IDENTIFIER", "STRING_LITERAL", "CHAR_LITERAL", 
                             "LINE_COMMENT", "BLOCK_COMMENT", "WS" ];
    static ruleNames = [ "program", "statement", "varDeclaration", "type", 
                         "scope", "assignment", "condStatement", "matchCase", 
                         "loopStatement", "loopMode", "loopDelimiter", "loopEndDelimiter", 
                         "tryCatchStatement", "functionDeclaration", "pkgDeclaration", 
                         "block", "parameterList", "returnStatement", "throwStatement", 
                         "argumentList", "expression", "arrayLiteral" ];

    constructor(input) {
        super(input);
        this._interp = new antlr4.atn.ParserATNSimulator(this, atn, decisionsToDFA, sharedContextCache);
        this.ruleNames = PaxoParser.ruleNames;
        this.literalNames = PaxoParser.literalNames;
        this.symbolicNames = PaxoParser.symbolicNames;
    }

    sempred(localctx, ruleIndex, predIndex) {
    	switch(ruleIndex) {
    	case 20:
    	    		return this.expression_sempred(localctx, predIndex);
        default:
            throw "No predicate with index:" + ruleIndex;
       }
    }

    expression_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 0:
    			return this.precpred(this._ctx, 20);
    		case 1:
    			return this.precpred(this._ctx, 19);
    		case 2:
    			return this.precpred(this._ctx, 18);
    		case 3:
    			return this.precpred(this._ctx, 17);
    		case 4:
    			return this.precpred(this._ctx, 16);
    		case 5:
    			return this.precpred(this._ctx, 24);
    		case 6:
    			return this.precpred(this._ctx, 23);
    		case 7:
    			return this.precpred(this._ctx, 22);
    		case 8:
    			return this.precpred(this._ctx, 21);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };




	program() {
	    let localctx = new ProgramContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 0, PaxoParser.RULE_program);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 47;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 1049666) !== 0) || ((((_la - 42)) & ~0x1f) === 0 && ((1 << (_la - 42)) & 4243062775) !== 0) || ((((_la - 74)) & ~0x1f) === 0 && ((1 << (_la - 74)) & 31) !== 0)) {
	            this.state = 44;
	            this.statement();
	            this.state = 49;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	        this.state = 50;
	        this.match(PaxoParser.EOF);
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
	    this.enterRule(localctx, 2, PaxoParser.RULE_statement);
	    var _la = 0;
	    try {
	        this.state = 72;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,3,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 52;
	            this.match(PaxoParser.T__0);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 53;
	            this.varDeclaration();
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 54;
	            this.assignment();
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 55;
	            this.condStatement();
	            break;

	        case 5:
	            this.enterOuterAlt(localctx, 5);
	            this.state = 56;
	            this.loopStatement();
	            break;

	        case 6:
	            this.enterOuterAlt(localctx, 6);
	            this.state = 57;
	            this.tryCatchStatement();
	            break;

	        case 7:
	            this.enterOuterAlt(localctx, 7);
	            this.state = 58;
	            this.throwStatement();
	            break;

	        case 8:
	            this.enterOuterAlt(localctx, 8);
	            this.state = 59;
	            this.returnStatement();
	            break;

	        case 9:
	            this.enterOuterAlt(localctx, 9);
	            this.state = 60;
	            this.expression(0);
	            this.state = 62;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,1,this._ctx);
	            if(la_===1) {
	                this.state = 61;
	                this.match(PaxoParser.T__0);

	            }
	            break;

	        case 10:
	            this.enterOuterAlt(localctx, 10);
	            this.state = 64;
	            this.match(PaxoParser.INCLUDE);
	            this.state = 65;
	            this.match(PaxoParser.T__1);
	            this.state = 66;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 69;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===3) {
	                this.state = 67;
	                this.match(PaxoParser.T__2);
	                this.state = 68;
	                this.match(PaxoParser.IDENTIFIER);
	            }

	            this.state = 71;
	            this.match(PaxoParser.T__3);
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



	varDeclaration() {
	    let localctx = new VarDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 4, PaxoParser.RULE_varDeclaration);
	    var _la = 0;
	    try {
	        this.state = 101;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,8,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 75;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===58 || _la===59) {
	                this.state = 74;
	                this.scope();
	            }

	            this.state = 77;
	            this.type();
	            this.state = 78;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 79;
	            this.match(PaxoParser.T__4);
	            this.state = 80;
	            this.expression(0);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 83;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===58 || _la===59) {
	                this.state = 82;
	                this.scope();
	            }

	            this.state = 85;
	            this.type();
	            this.state = 86;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 87;
	            this.match(PaxoParser.T__5);
	            this.state = 89;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===68) {
	                this.state = 88;
	                this.match(PaxoParser.INT_LITERAL);
	            }

	            this.state = 91;
	            this.match(PaxoParser.T__6);
	            this.state = 92;
	            this.match(PaxoParser.T__4);
	            this.state = 93;
	            this.arrayLiteral();
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 96;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            if(_la===58 || _la===59) {
	                this.state = 95;
	                this.scope();
	            }

	            this.state = 98;
	            this.type();
	            this.state = 99;
	            this.match(PaxoParser.IDENTIFIER);
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



	type() {
	    let localctx = new TypeContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 6, PaxoParser.RULE_type);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 103;
	        _la = this._input.LA(1);
	        if(!(((((_la - 46)) & ~0x1f) === 0 && ((1 << (_la - 46)) & 4095) !== 0))) {
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



	scope() {
	    let localctx = new ScopeContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 8, PaxoParser.RULE_scope);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 105;
	        _la = this._input.LA(1);
	        if(!(_la===58 || _la===59)) {
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



	assignment() {
	    let localctx = new AssignmentContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 10, PaxoParser.RULE_assignment);
	    try {
	        this.state = 148;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,15,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 107;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 108;
	            this.match(PaxoParser.T__4);
	            this.state = 109;
	            this.expression(0);
	            this.state = 111;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,9,this._ctx);
	            if(la_===1) {
	                this.state = 110;
	                this.match(PaxoParser.T__0);

	            }
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 113;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 114;
	            this.match(PaxoParser.T__5);
	            this.state = 115;
	            this.expression(0);
	            this.state = 116;
	            this.match(PaxoParser.T__6);
	            this.state = 117;
	            this.match(PaxoParser.T__4);
	            this.state = 118;
	            this.expression(0);
	            this.state = 120;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,10,this._ctx);
	            if(la_===1) {
	                this.state = 119;
	                this.match(PaxoParser.T__0);

	            }
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 122;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 123;
	            this.match(PaxoParser.T__7);
	            this.state = 125;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,11,this._ctx);
	            if(la_===1) {
	                this.state = 124;
	                this.match(PaxoParser.T__0);

	            }
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 127;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 128;
	            this.match(PaxoParser.T__8);
	            this.state = 130;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,12,this._ctx);
	            if(la_===1) {
	                this.state = 129;
	                this.match(PaxoParser.T__0);

	            }
	            break;

	        case 5:
	            this.enterOuterAlt(localctx, 5);
	            this.state = 132;
	            this.expression(0);
	            this.state = 133;
	            this.match(PaxoParser.T__2);
	            this.state = 134;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 135;
	            this.match(PaxoParser.T__4);
	            this.state = 136;
	            this.expression(0);
	            this.state = 138;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,13,this._ctx);
	            if(la_===1) {
	                this.state = 137;
	                this.match(PaxoParser.T__0);

	            }
	            break;

	        case 6:
	            this.enterOuterAlt(localctx, 6);
	            this.state = 140;
	            this.match(PaxoParser.THIS_SCOPE);
	            this.state = 141;
	            this.match(PaxoParser.T__2);
	            this.state = 142;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 143;
	            this.match(PaxoParser.T__4);
	            this.state = 144;
	            this.expression(0);
	            this.state = 146;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,14,this._ctx);
	            if(la_===1) {
	                this.state = 145;
	                this.match(PaxoParser.T__0);

	            }
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



	condStatement() {
	    let localctx = new CondStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 12, PaxoParser.RULE_condStatement);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 150;
	        this.match(PaxoParser.T__9);
	        this.state = 151;
	        this.expression(0);
	        this.state = 152;
	        this.match(PaxoParser.T__10);
	        this.state = 153;
	        this.match(PaxoParser.T__11);
	        this.state = 154;
	        this.matchCase();
	        this.state = 159;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,16,this._ctx)
	        while(_alt!=1 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1+1) {
	                this.state = 155;
	                this.match(PaxoParser.T__12);
	                this.state = 156;
	                this.matchCase(); 
	            }
	            this.state = 161;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,16,this._ctx);
	        }

	        this.state = 163;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,17,this._ctx);
	        if(la_===1) {
	            this.state = 162;
	            this.match(PaxoParser.T__0);

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



	matchCase() {
	    let localctx = new MatchCaseContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 14, PaxoParser.RULE_matchCase);
	    try {
	        this.state = 172;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 6:
	        case 10:
	        case 20:
	        case 42:
	        case 43:
	        case 44:
	        case 68:
	        case 69:
	        case 70:
	        case 71:
	        case 72:
	        case 73:
	        case 74:
	        case 75:
	        case 76:
	        case 77:
	        case 78:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 165;
	            this.expression(0);
	            this.state = 166;
	            this.match(PaxoParser.T__13);
	            this.state = 167;
	            this.block();
	            break;
	        case 15:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 169;
	            this.match(PaxoParser.T__14);
	            this.state = 170;
	            this.match(PaxoParser.T__13);
	            this.state = 171;
	            this.block();
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



	loopStatement() {
	    let localctx = new LoopStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 16, PaxoParser.RULE_loopStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 174;
	        this.match(PaxoParser.T__9);
	        this.state = 175;
	        this.expression(0);
	        this.state = 176;
	        this.match(PaxoParser.T__10);
	        this.state = 177;
	        this.match(PaxoParser.T__12);
	        this.state = 178;
	        this.loopMode();
	        this.state = 180;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if(_la===16 || _la===17) {
	            this.state = 179;
	            this.loopDelimiter();
	        }

	        this.state = 182;
	        this.block();
	        this.state = 184;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if(_la===18 || _la===19) {
	            this.state = 183;
	            this.loopEndDelimiter();
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



	loopMode() {
	    let localctx = new LoopModeContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 18, PaxoParser.RULE_loopMode);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 186;
	        _la = this._input.LA(1);
	        if(!(_la===66 || _la===67)) {
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



	loopDelimiter() {
	    let localctx = new LoopDelimiterContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 20, PaxoParser.RULE_loopDelimiter);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 188;
	        _la = this._input.LA(1);
	        if(!(_la===16 || _la===17)) {
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



	loopEndDelimiter() {
	    let localctx = new LoopEndDelimiterContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 22, PaxoParser.RULE_loopEndDelimiter);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 190;
	        _la = this._input.LA(1);
	        if(!(_la===18 || _la===19)) {
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



	tryCatchStatement() {
	    let localctx = new TryCatchStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 24, PaxoParser.RULE_tryCatchStatement);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 192;
	        this.match(PaxoParser.TRY);
	        this.state = 193;
	        this.block();
	        this.state = 194;
	        this.match(PaxoParser.CATCH);
	        this.state = 195;
	        this.match(PaxoParser.T__9);
	        this.state = 196;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 199;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if(_la===3) {
	            this.state = 197;
	            this.match(PaxoParser.T__2);
	            this.state = 198;
	            this.match(PaxoParser.IDENTIFIER);
	        }

	        this.state = 201;
	        this.match(PaxoParser.T__10);
	        this.state = 202;
	        this.block();
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



	functionDeclaration() {
	    let localctx = new FunctionDeclarationContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 26, PaxoParser.RULE_functionDeclaration);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 204;
	        this.match(PaxoParser.T__9);
	        this.state = 206;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if(((((_la - 46)) & ~0x1f) === 0 && ((1 << (_la - 46)) & 4095) !== 0)) {
	            this.state = 205;
	            this.parameterList();
	        }

	        this.state = 208;
	        this.match(PaxoParser.T__10);
	        this.state = 211;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,23,this._ctx);
	        if(la_===1) {
	            this.state = 209;
	            this.match(PaxoParser.T__12);
	            this.state = 210;
	            this.type();

	        }
	        this.state = 213;
	        this.block();
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
	    this.enterRule(localctx, 28, PaxoParser.RULE_pkgDeclaration);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 215;
	        this.match(PaxoParser.T__19);
	        this.state = 222;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,25,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                this.state = 217;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	                if(_la===21) {
	                    this.state = 216;
	                    this.match(PaxoParser.T__20);
	                }

	                this.state = 219;
	                this.varDeclaration(); 
	            }
	            this.state = 224;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,25,this._ctx);
	        }

	        this.state = 226;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if(_la===21) {
	            this.state = 225;
	            this.match(PaxoParser.T__20);
	        }

	        this.state = 228;
	        this.match(PaxoParser.T__21);
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



	block() {
	    let localctx = new BlockContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 30, PaxoParser.RULE_block);
	    var _la = 0;
	    try {
	        this.state = 261;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,31,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 230;
	            this.match(PaxoParser.T__19);
	            this.state = 234;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while((((_la) & ~0x1f) === 0 && ((1 << _la) & 1049666) !== 0) || ((((_la - 42)) & ~0x1f) === 0 && ((1 << (_la - 42)) & 4243062775) !== 0) || ((((_la - 74)) & ~0x1f) === 0 && ((1 << (_la - 74)) & 31) !== 0)) {
	                this.state = 231;
	                this.statement();
	                this.state = 236;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 237;
	            this.match(PaxoParser.T__21);
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 238;
	            this.match(PaxoParser.T__12);
	            this.state = 242;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while((((_la) & ~0x1f) === 0 && ((1 << _la) & 1049666) !== 0) || ((((_la - 42)) & ~0x1f) === 0 && ((1 << (_la - 42)) & 4243062775) !== 0) || ((((_la - 74)) & ~0x1f) === 0 && ((1 << (_la - 74)) & 31) !== 0)) {
	                this.state = 239;
	                this.statement();
	                this.state = 244;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 245;
	            this.match(PaxoParser.T__22);
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 249;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while((((_la) & ~0x1f) === 0 && ((1 << _la) & 1049666) !== 0) || ((((_la - 42)) & ~0x1f) === 0 && ((1 << (_la - 42)) & 4243062775) !== 0) || ((((_la - 74)) & ~0x1f) === 0 && ((1 << (_la - 74)) & 31) !== 0)) {
	                this.state = 246;
	                this.statement();
	                this.state = 251;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 252;
	            this.match(PaxoParser.T__23);
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 253;
	            this.match(PaxoParser.T__12);
	            this.state = 257;
	            this._errHandler.sync(this);
	            var _alt = this._interp.adaptivePredict(this._input,30,this._ctx)
	            while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	                if(_alt===1) {
	                    this.state = 254;
	                    this.statement(); 
	                }
	                this.state = 259;
	                this._errHandler.sync(this);
	                _alt = this._interp.adaptivePredict(this._input,30,this._ctx);
	            }

	            this.state = 260;
	            this.match(PaxoParser.T__0);
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



	parameterList() {
	    let localctx = new ParameterListContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 32, PaxoParser.RULE_parameterList);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 263;
	        this.type();
	        this.state = 264;
	        this.match(PaxoParser.IDENTIFIER);
	        this.state = 271;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while(_la===21) {
	            this.state = 265;
	            this.match(PaxoParser.T__20);
	            this.state = 266;
	            this.type();
	            this.state = 267;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 273;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
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



	returnStatement() {
	    let localctx = new ReturnStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 34, PaxoParser.RULE_returnStatement);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 274;
	        this.match(PaxoParser.RETURN);
	        this.state = 276;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,33,this._ctx);
	        if(la_===1) {
	            this.state = 275;
	            this.expression(0);

	        }
	        this.state = 279;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,34,this._ctx);
	        if(la_===1) {
	            this.state = 278;
	            this.match(PaxoParser.T__0);

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



	throwStatement() {
	    let localctx = new ThrowStatementContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 36, PaxoParser.RULE_throwStatement);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 281;
	        this.match(PaxoParser.THROW);
	        this.state = 282;
	        this.expression(0);
	        this.state = 284;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,35,this._ctx);
	        if(la_===1) {
	            this.state = 283;
	            this.match(PaxoParser.T__0);

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



	argumentList() {
	    let localctx = new ArgumentListContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 38, PaxoParser.RULE_argumentList);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 294;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        if((((_la) & ~0x1f) === 0 && ((1 << _la) & 1049664) !== 0) || ((((_la - 42)) & ~0x1f) === 0 && ((1 << (_la - 42)) & 4227858439) !== 0) || ((((_la - 74)) & ~0x1f) === 0 && ((1 << (_la - 74)) & 31) !== 0)) {
	            this.state = 286;
	            this.expression(0);
	            this.state = 291;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while(_la===21) {
	                this.state = 287;
	                this.match(PaxoParser.T__20);
	                this.state = 288;
	                this.expression(0);
	                this.state = 293;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
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


	expression(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new ExpressionContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 40;
	    this.enterRecursionRule(localctx, 40, PaxoParser.RULE_expression, _p);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 321;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,39,this._ctx);
	        switch(la_) {
	        case 1:
	            localctx = new CallExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;

	            this.state = 297;
	            this.match(PaxoParser.IDENTIFIER);
	            this.state = 298;
	            this.match(PaxoParser.T__9);
	            this.state = 300;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,38,this._ctx);
	            if(la_===1) {
	                this.state = 299;
	                this.argumentList();

	            }
	            this.state = 302;
	            this.match(PaxoParser.T__10);
	            break;

	        case 2:
	            localctx = new NotgateExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 303;
	            _la = this._input.LA(1);
	            if(!(_la===42 || _la===43)) {
	            this._errHandler.recoverInline(this);
	            }
	            else {
	            	this._errHandler.reportMatch(this);
	                this.consume();
	            }
	            this.state = 304;
	            this.expression(15);
	            break;

	        case 3:
	            localctx = new ThisScopeExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 305;
	            this.match(PaxoParser.THIS_SCOPE);
	            this.state = 306;
	            this.match(PaxoParser.T__2);
	            this.state = 307;
	            this.match(PaxoParser.IDENTIFIER);
	            break;

	        case 4:
	            localctx = new IntLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 308;
	            this.match(PaxoParser.INT_LITERAL);
	            break;

	        case 5:
	            localctx = new DecLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 309;
	            this.match(PaxoParser.DECIMAL_LITERAL);
	            break;

	        case 6:
	            localctx = new CharLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 310;
	            this.match(PaxoParser.CHAR_LITERAL);
	            break;

	        case 7:
	            localctx = new StringLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 311;
	            this.match(PaxoParser.STRING_LITERAL);
	            break;

	        case 8:
	            localctx = new BoolBitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 312;
	            this.match(PaxoParser.BOOLEAN_BIT);
	            break;

	        case 9:
	            localctx = new BoolTritExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 313;
	            this.match(PaxoParser.BOOLEAN_TRIT);
	            break;

	        case 10:
	            localctx = new PtrLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 314;
	            this.match(PaxoParser.POINTER_LITERAL);
	            break;

	        case 11:
	            localctx = new ColLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 315;
	            this.match(PaxoParser.COLOR_LITERAL);
	            break;

	        case 12:
	            localctx = new ComLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 316;
	            this.match(PaxoParser.COMPLEX_LITERAL);
	            break;

	        case 13:
	            localctx = new ArrayLitExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 317;
	            this.arrayLiteral();
	            break;

	        case 14:
	            localctx = new IdentExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 318;
	            this.match(PaxoParser.IDENTIFIER);
	            break;

	        case 15:
	            localctx = new PkgExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 319;
	            this.pkgDeclaration();
	            break;

	        case 16:
	            localctx = new FuncExprContext(this, localctx);
	            this._ctx = localctx;
	            _prevctx = localctx;
	            this.state = 320;
	            this.functionDeclaration();
	            break;

	        }
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 363;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,41,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                this.state = 361;
	                this._errHandler.sync(this);
	                var la_ = this._interp.adaptivePredict(this._input,40,this._ctx);
	                switch(la_) {
	                case 1:
	                    localctx = new MultDivExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 323;
	                    if (!( this.precpred(this._ctx, 20))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 20)");
	                    }
	                    this.state = 324;
	                    _la = this._input.LA(1);
	                    if(!(_la===25 || _la===26)) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 325;
	                    this.expression(21);
	                    break;

	                case 2:
	                    localctx = new AddSubExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 326;
	                    if (!( this.precpred(this._ctx, 19))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 19)");
	                    }
	                    this.state = 327;
	                    _la = this._input.LA(1);
	                    if(!(_la===27 || _la===28)) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 328;
	                    this.expression(20);
	                    break;

	                case 3:
	                    localctx = new ShiftExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 329;
	                    if (!( this.precpred(this._ctx, 18))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 18)");
	                    }
	                    this.state = 330;
	                    _la = this._input.LA(1);
	                    if(!(_la===29 || _la===30)) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 331;
	                    this.expression(19);
	                    break;

	                case 4:
	                    localctx = new RelationalExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 332;
	                    if (!( this.precpred(this._ctx, 17))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 17)");
	                    }
	                    this.state = 333;
	                    _la = this._input.LA(1);
	                    if(!((((_la) & ~0x1f) === 0 && ((1 << _la) & 2147483668) !== 0) || ((((_la - 32)) & ~0x1f) === 0 && ((1 << (_la - 32)) & 63) !== 0))) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 334;
	                    this.expression(18);
	                    break;

	                case 5:
	                    localctx = new BitwiseExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 335;
	                    if (!( this.precpred(this._ctx, 16))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 16)");
	                    }
	                    this.state = 336;
	                    _la = this._input.LA(1);
	                    if(!(((((_la - 38)) & ~0x1f) === 0 && ((1 << (_la - 38)) & 15) !== 0))) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 337;
	                    this.expression(17);
	                    break;

	                case 6:
	                    localctx = new IndexedCallExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 338;
	                    if (!( this.precpred(this._ctx, 24))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 24)");
	                    }
	                    this.state = 339;
	                    this.match(PaxoParser.T__5);
	                    this.state = 340;
	                    this.expression(0);
	                    this.state = 341;
	                    this.match(PaxoParser.T__6);
	                    this.state = 342;
	                    this.match(PaxoParser.T__9);
	                    this.state = 343;
	                    this.argumentList();
	                    this.state = 344;
	                    this.match(PaxoParser.T__10);
	                    break;

	                case 7:
	                    localctx = new IndexedAccessExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 346;
	                    if (!( this.precpred(this._ctx, 23))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 23)");
	                    }
	                    this.state = 347;
	                    this.match(PaxoParser.T__5);
	                    this.state = 348;
	                    this.expression(0);
	                    this.state = 349;
	                    this.match(PaxoParser.T__6);
	                    break;

	                case 8:
	                    localctx = new MethodCallExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 351;
	                    if (!( this.precpred(this._ctx, 22))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 22)");
	                    }
	                    this.state = 352;
	                    this.match(PaxoParser.T__2);
	                    this.state = 353;
	                    this.match(PaxoParser.IDENTIFIER);
	                    this.state = 354;
	                    this.match(PaxoParser.T__9);
	                    this.state = 355;
	                    this.argumentList();
	                    this.state = 356;
	                    this.match(PaxoParser.T__10);
	                    break;

	                case 9:
	                    localctx = new DotAccessExprContext(this, new ExpressionContext(this, _parentctx, _parentState));
	                    this.pushNewRecursionContext(localctx, _startState, PaxoParser.RULE_expression);
	                    this.state = 358;
	                    if (!( this.precpred(this._ctx, 21))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 21)");
	                    }
	                    this.state = 359;
	                    this.match(PaxoParser.T__2);
	                    this.state = 360;
	                    this.match(PaxoParser.IDENTIFIER);
	                    break;

	                } 
	            }
	            this.state = 365;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,41,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}



	arrayLiteral() {
	    let localctx = new ArrayLiteralContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 42, PaxoParser.RULE_arrayLiteral);
	    var _la = 0;
	    try {
	        this.state = 399;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 44:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 366;
	            this.match(PaxoParser.T__43);
	            this.state = 367;
	            this.expression(0);
	            this.state = 372;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while(_la===21) {
	                this.state = 368;
	                this.match(PaxoParser.T__20);
	                this.state = 369;
	                this.expression(0);
	                this.state = 374;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 375;
	            this.match(PaxoParser.T__44);
	            break;
	        case 20:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 377;
	            this.match(PaxoParser.T__19);
	            this.state = 378;
	            this.expression(0);
	            this.state = 383;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while(_la===21) {
	                this.state = 379;
	                this.match(PaxoParser.T__20);
	                this.state = 380;
	                this.expression(0);
	                this.state = 385;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 386;
	            this.match(PaxoParser.T__21);
	            break;
	        case 6:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 388;
	            this.match(PaxoParser.T__5);
	            this.state = 389;
	            this.expression(0);
	            this.state = 394;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	            while(_la===21) {
	                this.state = 390;
	                this.match(PaxoParser.T__20);
	                this.state = 391;
	                this.expression(0);
	                this.state = 396;
	                this._errHandler.sync(this);
	                _la = this._input.LA(1);
	            }
	            this.state = 397;
	            this.match(PaxoParser.T__6);
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

PaxoParser.EOF = antlr4.Token.EOF;
PaxoParser.T__0 = 1;
PaxoParser.T__1 = 2;
PaxoParser.T__2 = 3;
PaxoParser.T__3 = 4;
PaxoParser.T__4 = 5;
PaxoParser.T__5 = 6;
PaxoParser.T__6 = 7;
PaxoParser.T__7 = 8;
PaxoParser.T__8 = 9;
PaxoParser.T__9 = 10;
PaxoParser.T__10 = 11;
PaxoParser.T__11 = 12;
PaxoParser.T__12 = 13;
PaxoParser.T__13 = 14;
PaxoParser.T__14 = 15;
PaxoParser.T__15 = 16;
PaxoParser.T__16 = 17;
PaxoParser.T__17 = 18;
PaxoParser.T__18 = 19;
PaxoParser.T__19 = 20;
PaxoParser.T__20 = 21;
PaxoParser.T__21 = 22;
PaxoParser.T__22 = 23;
PaxoParser.T__23 = 24;
PaxoParser.T__24 = 25;
PaxoParser.T__25 = 26;
PaxoParser.T__26 = 27;
PaxoParser.T__27 = 28;
PaxoParser.T__28 = 29;
PaxoParser.T__29 = 30;
PaxoParser.T__30 = 31;
PaxoParser.T__31 = 32;
PaxoParser.T__32 = 33;
PaxoParser.T__33 = 34;
PaxoParser.T__34 = 35;
PaxoParser.T__35 = 36;
PaxoParser.T__36 = 37;
PaxoParser.T__37 = 38;
PaxoParser.T__38 = 39;
PaxoParser.T__39 = 40;
PaxoParser.T__40 = 41;
PaxoParser.T__41 = 42;
PaxoParser.T__42 = 43;
PaxoParser.T__43 = 44;
PaxoParser.T__44 = 45;
PaxoParser.VAR_TYPE = 46;
PaxoParser.NUM_TYPE = 47;
PaxoParser.COMPLEX_TYPE = 48;
PaxoParser.CHARA_TYPE = 49;
PaxoParser.TRIT_TYPE = 50;
PaxoParser.BOOLEAN_TYPE = 51;
PaxoParser.POINTER_TYPE = 52;
PaxoParser.FUNC_TYPE = 53;
PaxoParser.PKG_TYPE = 54;
PaxoParser.INT_TYPE = 55;
PaxoParser.PKDEC_TYPE = 56;
PaxoParser.COLOR_TYPE = 57;
PaxoParser.GLOBAL = 58;
PaxoParser.LOCAL = 59;
PaxoParser.TRY = 60;
PaxoParser.CATCH = 61;
PaxoParser.ARROW = 62;
PaxoParser.INCLUDE = 63;
PaxoParser.RETURN = 64;
PaxoParser.THROW = 65;
PaxoParser.PAUSE_MODE = 66;
PaxoParser.PLAY_MODE = 67;
PaxoParser.INT_LITERAL = 68;
PaxoParser.DECIMAL_LITERAL = 69;
PaxoParser.COMPLEX_LITERAL = 70;
PaxoParser.BOOLEAN_BIT = 71;
PaxoParser.BOOLEAN_TRIT = 72;
PaxoParser.POINTER_LITERAL = 73;
PaxoParser.COLOR_LITERAL = 74;
PaxoParser.THIS_SCOPE = 75;
PaxoParser.IDENTIFIER = 76;
PaxoParser.STRING_LITERAL = 77;
PaxoParser.CHAR_LITERAL = 78;
PaxoParser.LINE_COMMENT = 79;
PaxoParser.BLOCK_COMMENT = 80;
PaxoParser.WS = 81;

PaxoParser.RULE_program = 0;
PaxoParser.RULE_statement = 1;
PaxoParser.RULE_varDeclaration = 2;
PaxoParser.RULE_type = 3;
PaxoParser.RULE_scope = 4;
PaxoParser.RULE_assignment = 5;
PaxoParser.RULE_condStatement = 6;
PaxoParser.RULE_matchCase = 7;
PaxoParser.RULE_loopStatement = 8;
PaxoParser.RULE_loopMode = 9;
PaxoParser.RULE_loopDelimiter = 10;
PaxoParser.RULE_loopEndDelimiter = 11;
PaxoParser.RULE_tryCatchStatement = 12;
PaxoParser.RULE_functionDeclaration = 13;
PaxoParser.RULE_pkgDeclaration = 14;
PaxoParser.RULE_block = 15;
PaxoParser.RULE_parameterList = 16;
PaxoParser.RULE_returnStatement = 17;
PaxoParser.RULE_throwStatement = 18;
PaxoParser.RULE_argumentList = 19;
PaxoParser.RULE_expression = 20;
PaxoParser.RULE_arrayLiteral = 21;

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
        this.ruleIndex = PaxoParser.RULE_program;
    }

	EOF() {
	    return this.getToken(PaxoParser.EOF, 0);
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
	    if(listener instanceof PaxoListener ) {
	        listener.enterProgram(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_statement;
    }

	varDeclaration() {
	    return this.getTypedRuleContext(VarDeclarationContext,0);
	};

	assignment() {
	    return this.getTypedRuleContext(AssignmentContext,0);
	};

	condStatement() {
	    return this.getTypedRuleContext(CondStatementContext,0);
	};

	loopStatement() {
	    return this.getTypedRuleContext(LoopStatementContext,0);
	};

	tryCatchStatement() {
	    return this.getTypedRuleContext(TryCatchStatementContext,0);
	};

	throwStatement() {
	    return this.getTypedRuleContext(ThrowStatementContext,0);
	};

	returnStatement() {
	    return this.getTypedRuleContext(ReturnStatementContext,0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	INCLUDE() {
	    return this.getToken(PaxoParser.INCLUDE, 0);
	};

	IDENTIFIER = function(i) {
		if(i===undefined) {
			i = null;
		}
	    if(i===null) {
	        return this.getTokens(PaxoParser.IDENTIFIER);
	    } else {
	        return this.getToken(PaxoParser.IDENTIFIER, i);
	    }
	};


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_varDeclaration;
    }

	type() {
	    return this.getTypedRuleContext(TypeContext,0);
	};

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	scope() {
	    return this.getTypedRuleContext(ScopeContext,0);
	};

	arrayLiteral() {
	    return this.getTypedRuleContext(ArrayLiteralContext,0);
	};

	INT_LITERAL() {
	    return this.getToken(PaxoParser.INT_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterVarDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
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
        this.ruleIndex = PaxoParser.RULE_type;
    }

	VAR_TYPE() {
	    return this.getToken(PaxoParser.VAR_TYPE, 0);
	};

	NUM_TYPE() {
	    return this.getToken(PaxoParser.NUM_TYPE, 0);
	};

	CHARA_TYPE() {
	    return this.getToken(PaxoParser.CHARA_TYPE, 0);
	};

	POINTER_TYPE() {
	    return this.getToken(PaxoParser.POINTER_TYPE, 0);
	};

	TRIT_TYPE() {
	    return this.getToken(PaxoParser.TRIT_TYPE, 0);
	};

	BOOLEAN_TYPE() {
	    return this.getToken(PaxoParser.BOOLEAN_TYPE, 0);
	};

	FUNC_TYPE() {
	    return this.getToken(PaxoParser.FUNC_TYPE, 0);
	};

	PKG_TYPE() {
	    return this.getToken(PaxoParser.PKG_TYPE, 0);
	};

	INT_TYPE() {
	    return this.getToken(PaxoParser.INT_TYPE, 0);
	};

	PKDEC_TYPE() {
	    return this.getToken(PaxoParser.PKDEC_TYPE, 0);
	};

	COLOR_TYPE() {
	    return this.getToken(PaxoParser.COLOR_TYPE, 0);
	};

	COMPLEX_TYPE() {
	    return this.getToken(PaxoParser.COMPLEX_TYPE, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterType(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitType(this);
		}
	}


}



class ScopeContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_scope;
    }

	GLOBAL() {
	    return this.getToken(PaxoParser.GLOBAL, 0);
	};

	LOCAL() {
	    return this.getToken(PaxoParser.LOCAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterScope(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitScope(this);
		}
	}


}



class AssignmentContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_assignment;
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
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

	THIS_SCOPE() {
	    return this.getToken(PaxoParser.THIS_SCOPE, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterAssignment(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitAssignment(this);
		}
	}


}



class CondStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_condStatement;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
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
	    if(listener instanceof PaxoListener ) {
	        listener.enterCondStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitCondStatement(this);
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
        this.ruleIndex = PaxoParser.RULE_matchCase;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	block() {
	    return this.getTypedRuleContext(BlockContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterMatchCase(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitMatchCase(this);
		}
	}


}



class LoopStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_loopStatement;
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	loopMode() {
	    return this.getTypedRuleContext(LoopModeContext,0);
	};

	block() {
	    return this.getTypedRuleContext(BlockContext,0);
	};

	loopDelimiter() {
	    return this.getTypedRuleContext(LoopDelimiterContext,0);
	};

	loopEndDelimiter() {
	    return this.getTypedRuleContext(LoopEndDelimiterContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterLoopStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitLoopStatement(this);
		}
	}


}



class LoopModeContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_loopMode;
    }

	PAUSE_MODE() {
	    return this.getToken(PaxoParser.PAUSE_MODE, 0);
	};

	PLAY_MODE() {
	    return this.getToken(PaxoParser.PLAY_MODE, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterLoopMode(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitLoopMode(this);
		}
	}


}



class LoopDelimiterContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_loopDelimiter;
    }


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterLoopDelimiter(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitLoopDelimiter(this);
		}
	}


}



class LoopEndDelimiterContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_loopEndDelimiter;
    }


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterLoopEndDelimiter(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitLoopEndDelimiter(this);
		}
	}


}



class TryCatchStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_tryCatchStatement;
    }

	TRY() {
	    return this.getToken(PaxoParser.TRY, 0);
	};

	block = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(BlockContext);
	    } else {
	        return this.getTypedRuleContext(BlockContext,i);
	    }
	};

	CATCH() {
	    return this.getToken(PaxoParser.CATCH, 0);
	};

	IDENTIFIER = function(i) {
		if(i===undefined) {
			i = null;
		}
	    if(i===null) {
	        return this.getTokens(PaxoParser.IDENTIFIER);
	    } else {
	        return this.getToken(PaxoParser.IDENTIFIER, i);
	    }
	};


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterTryCatchStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitTryCatchStatement(this);
		}
	}


}



class FunctionDeclarationContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_functionDeclaration;
    }

	block() {
	    return this.getTypedRuleContext(BlockContext,0);
	};

	parameterList() {
	    return this.getTypedRuleContext(ParameterListContext,0);
	};

	type() {
	    return this.getTypedRuleContext(TypeContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterFunctionDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitFunctionDeclaration(this);
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
        this.ruleIndex = PaxoParser.RULE_pkgDeclaration;
    }

	varDeclaration = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(VarDeclarationContext);
	    } else {
	        return this.getTypedRuleContext(VarDeclarationContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterPkgDeclaration(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitPkgDeclaration(this);
		}
	}


}



class BlockContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_block;
    }

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
	    if(listener instanceof PaxoListener ) {
	        listener.enterBlock(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitBlock(this);
		}
	}


}



class ParameterListContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_parameterList;
    }

	type = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(TypeContext);
	    } else {
	        return this.getTypedRuleContext(TypeContext,i);
	    }
	};

	IDENTIFIER = function(i) {
		if(i===undefined) {
			i = null;
		}
	    if(i===null) {
	        return this.getTokens(PaxoParser.IDENTIFIER);
	    } else {
	        return this.getToken(PaxoParser.IDENTIFIER, i);
	    }
	};


	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterParameterList(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitParameterList(this);
		}
	}


}



class ReturnStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_returnStatement;
    }

	RETURN() {
	    return this.getToken(PaxoParser.RETURN, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterReturnStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitReturnStatement(this);
		}
	}


}



class ThrowStatementContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_throwStatement;
    }

	THROW() {
	    return this.getToken(PaxoParser.THROW, 0);
	};

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterThrowStatement(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitThrowStatement(this);
		}
	}


}



class ArgumentListContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_argumentList;
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterArgumentList(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitArgumentList(this);
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
        this.ruleIndex = PaxoParser.RULE_expression;
    }


	 
		copyFrom(ctx) {
			super.copyFrom(ctx);
		}

}


class CallExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	argumentList() {
	    return this.getTypedRuleContext(ArgumentListContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterCallExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitCallExpr(this);
		}
	}


}

PaxoParser.CallExprContext = CallExprContext;

class NotgateExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterNotgateExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitNotgateExpr(this);
		}
	}


}

PaxoParser.NotgateExprContext = NotgateExprContext;

class ThisScopeExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	THIS_SCOPE() {
	    return this.getToken(PaxoParser.THIS_SCOPE, 0);
	};

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterThisScopeExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitThisScopeExpr(this);
		}
	}


}

PaxoParser.ThisScopeExprContext = ThisScopeExprContext;

class IntLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	INT_LITERAL() {
	    return this.getToken(PaxoParser.INT_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterIntLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitIntLitExpr(this);
		}
	}


}

PaxoParser.IntLitExprContext = IntLitExprContext;

class DecLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	DECIMAL_LITERAL() {
	    return this.getToken(PaxoParser.DECIMAL_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterDecLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitDecLitExpr(this);
		}
	}


}

PaxoParser.DecLitExprContext = DecLitExprContext;

class CharLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	CHAR_LITERAL() {
	    return this.getToken(PaxoParser.CHAR_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterCharLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitCharLitExpr(this);
		}
	}


}

PaxoParser.CharLitExprContext = CharLitExprContext;

class StringLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	STRING_LITERAL() {
	    return this.getToken(PaxoParser.STRING_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterStringLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitStringLitExpr(this);
		}
	}


}

PaxoParser.StringLitExprContext = StringLitExprContext;

class BoolBitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	BOOLEAN_BIT() {
	    return this.getToken(PaxoParser.BOOLEAN_BIT, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterBoolBitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitBoolBitExpr(this);
		}
	}


}

PaxoParser.BoolBitExprContext = BoolBitExprContext;

class BoolTritExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	BOOLEAN_TRIT() {
	    return this.getToken(PaxoParser.BOOLEAN_TRIT, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterBoolTritExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitBoolTritExpr(this);
		}
	}


}

PaxoParser.BoolTritExprContext = BoolTritExprContext;

class PtrLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	POINTER_LITERAL() {
	    return this.getToken(PaxoParser.POINTER_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterPtrLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitPtrLitExpr(this);
		}
	}


}

PaxoParser.PtrLitExprContext = PtrLitExprContext;

class ColLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	COLOR_LITERAL() {
	    return this.getToken(PaxoParser.COLOR_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterColLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitColLitExpr(this);
		}
	}


}

PaxoParser.ColLitExprContext = ColLitExprContext;

class ComLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	COMPLEX_LITERAL() {
	    return this.getToken(PaxoParser.COMPLEX_LITERAL, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterComLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitComLitExpr(this);
		}
	}


}

PaxoParser.ComLitExprContext = ComLitExprContext;

class ArrayLitExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	arrayLiteral() {
	    return this.getTypedRuleContext(ArrayLiteralContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterArrayLitExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitArrayLitExpr(this);
		}
	}


}

PaxoParser.ArrayLitExprContext = ArrayLitExprContext;

class IdentExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterIdentExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitIdentExpr(this);
		}
	}


}

PaxoParser.IdentExprContext = IdentExprContext;

class PkgExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	pkgDeclaration() {
	    return this.getTypedRuleContext(PkgDeclarationContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterPkgExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitPkgExpr(this);
		}
	}


}

PaxoParser.PkgExprContext = PkgExprContext;

class FuncExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	functionDeclaration() {
	    return this.getTypedRuleContext(FunctionDeclarationContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterFuncExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitFuncExpr(this);
		}
	}


}

PaxoParser.FuncExprContext = FuncExprContext;

class MultDivExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterMultDivExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitMultDivExpr(this);
		}
	}


}

PaxoParser.MultDivExprContext = MultDivExprContext;

class AddSubExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterAddSubExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitAddSubExpr(this);
		}
	}


}

PaxoParser.AddSubExprContext = AddSubExprContext;

class ShiftExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterShiftExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitShiftExpr(this);
		}
	}


}

PaxoParser.ShiftExprContext = ShiftExprContext;

class RelationalExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterRelationalExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitRelationalExpr(this);
		}
	}


}

PaxoParser.RelationalExprContext = RelationalExprContext;

class BitwiseExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterBitwiseExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitBitwiseExpr(this);
		}
	}


}

PaxoParser.BitwiseExprContext = BitwiseExprContext;

class IndexedCallExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

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

	argumentList() {
	    return this.getTypedRuleContext(ArgumentListContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterIndexedCallExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitIndexedCallExpr(this);
		}
	}


}

PaxoParser.IndexedCallExprContext = IndexedCallExprContext;

class IndexedAccessExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterIndexedAccessExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitIndexedAccessExpr(this);
		}
	}


}

PaxoParser.IndexedAccessExprContext = IndexedAccessExprContext;

class MethodCallExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	argumentList() {
	    return this.getTypedRuleContext(ArgumentListContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterMethodCallExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitMethodCallExpr(this);
		}
	}


}

PaxoParser.MethodCallExprContext = MethodCallExprContext;

class DotAccessExprContext extends ExpressionContext {

    constructor(parser, ctx) {
        super(parser);
        super.copyFrom(ctx);
    }

	expression() {
	    return this.getTypedRuleContext(ExpressionContext,0);
	};

	IDENTIFIER() {
	    return this.getToken(PaxoParser.IDENTIFIER, 0);
	};

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterDotAccessExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitDotAccessExpr(this);
		}
	}


}

PaxoParser.DotAccessExprContext = DotAccessExprContext;

class ArrayLiteralContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = PaxoParser.RULE_arrayLiteral;
    }

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

	enterRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.enterArrayLiteral(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof PaxoListener ) {
	        listener.exitArrayLiteral(this);
		}
	}


}




PaxoParser.ProgramContext = ProgramContext; 
PaxoParser.StatementContext = StatementContext; 
PaxoParser.VarDeclarationContext = VarDeclarationContext; 
PaxoParser.TypeContext = TypeContext; 
PaxoParser.ScopeContext = ScopeContext; 
PaxoParser.AssignmentContext = AssignmentContext; 
PaxoParser.CondStatementContext = CondStatementContext; 
PaxoParser.MatchCaseContext = MatchCaseContext; 
PaxoParser.LoopStatementContext = LoopStatementContext; 
PaxoParser.LoopModeContext = LoopModeContext; 
PaxoParser.LoopDelimiterContext = LoopDelimiterContext; 
PaxoParser.LoopEndDelimiterContext = LoopEndDelimiterContext; 
PaxoParser.TryCatchStatementContext = TryCatchStatementContext; 
PaxoParser.FunctionDeclarationContext = FunctionDeclarationContext; 
PaxoParser.PkgDeclarationContext = PkgDeclarationContext; 
PaxoParser.BlockContext = BlockContext; 
PaxoParser.ParameterListContext = ParameterListContext; 
PaxoParser.ReturnStatementContext = ReturnStatementContext; 
PaxoParser.ThrowStatementContext = ThrowStatementContext; 
PaxoParser.ArgumentListContext = ArgumentListContext; 
PaxoParser.ExpressionContext = ExpressionContext; 
PaxoParser.ArrayLiteralContext = ArrayLiteralContext; 
