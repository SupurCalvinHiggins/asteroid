import re

class Token:
    def __init__(self,type,value):
        self.type = type
        self.value = value

    def __str__(self):
        return 'Token({},{})'.format(self.type,self.value)

class DebuggerLexer:
    def __init__(self, input_string):
        self.token_specs = [
        #   type:          value:
            ('COMMAND',     r'`([^`])*`'),
            
            ('STEP',        r'\bstep\b|\bs\b'),
            ('CONTINUE',    r'\bcontinue\b|\bcont\b|\bc\b'),
            ('NEXT',        r'\bnext\b|\bn\b'),
            ('BREAK',       r'\bbreak\b|\bb\b'),
            ('DELETE',      r'\bdelete\b|\bdel\b|\bd\b'),
            ('BANG',        r'!'),
            ('MACRO',       r'\bmacro\b'),
            ('LIST',        r'\blist\b|\bl\b'),
            ('LONGLIST',    r'\blonglist\b|\bll\b'),
            ('QUIT',        r'\bquit\b|\bq\b'),
            ('EXPLICIT',    r'\bexplicit\b|\be\b'),
            ('UNEXPLICIT',  r'\bunexplicit\b|\bu\b'),
            ('HELP',        r'\bh\b|\bhelp\b'),

            ('NUM',        r'[+-]?([0-9]*[.])?[0-9]+'),
            ('EQUAL',      r'='),
            ('SEMI',       r';'),
            
            ('NAME',       r'[a-zA-Z_\$][a-zA-Z0-9_\$]*'),
            ('WHITESPACE', r'[ \t\n]+'),
            ('UNKNOWN',    r'.')
        ]

        # used for sanity checking in lexer.
        self.token_types = set(type for (type,_) in self.token_specs)
        self.tokens = self.tokenize(input_string)
        # the following is always valid because we will always have
        # at least the EOF token on the tokens list.
        self.curr_token_ix = 0

    def pointer(self):
        return self.tokens[self.curr_token_ix]

    def next(self):
        if not self.end_of_file():
            self.curr_token_ix += 1
        return self.pointer()

    def match(self, token_type):
        if token_type == self.pointer().type:
            tk = self.pointer()
            self.next()
            return tk
        elif token_type not in self.token_types:
            raise ValueError("unknown token type '{}'".format(token_type))
        else:
            raise ValueError('unexpected token {} while parsing, expected {}'
                              .format(self.pointer().type, token_type))

    def end_of_file(self):
        if self.pointer().type == 'EOF':
            return True
        else:
            return False

    def tokenize(self, code):
        tokens = []
        re_list = ['(?P<{}>{})'.format(type,re) for (type,re) in self.token_specs]
        combined_re = '|'.join(re_list)
        match_object_list = list(re.finditer(combined_re, code))
        for mo in match_object_list:
            type = mo.lastgroup
            value = mo.group()
            if type == 'WHITESPACE':
                continue #ignore
            elif type == 'COMMAND':
                tokens.append(Token('COMMAND', value[1:-1]))
            elif type == 'UNKNOWN':
                raise ValueError("unexpected character '{}'".format(value))
            else: 
                tokens.append(Token(type, value))
        tokens.append(Token('EOF', '\eof'))
        return tokens

class DebuggerParser:
    def __init__(self):
        self.dlx = None

    def parse(self, input_string):
        self.dlx = DebuggerLexer(input_string)
        return self.line()

    def line(self):
        if self.dlx.pointer().type == 'MACRO':
            return self.macro()
        else:
            cmds = [self.command()]
            while self.dlx.pointer().type == 'SEMI':
                self.dlx.match('SEMI')
                if self.dlx.pointer().type != 'EOF':
                    cmds += [self.command()]
                else:
                    break
            return ('LINE', cmds)
    
    def macro(self):
        self.dlx.match('MACRO')
        name = self.dlx.match('NAME')
        self.dlx.match('EQUAL')

        l = self.line()

        return ('LINE', [('MACRO', name.value, l[1])] )

    def command(self):
        match(self.dlx.pointer().type):
            case 'COMMAND':
                cmd = self.dlx.match('COMMAND')
                return ('COMMAND', cmd.value)

            case 'BREAK':
                self.dlx.match('BREAK')
                nums = []
                conds = []

                while self.dlx.pointer().type == 'NUM':
                    nums.append(self.dlx.match('NUM').value)
                    if self.dlx.pointer().type == 'COMMAND':
                        conds.append(self.dlx.match('COMMAND').value)
                    else:
                        conds.append(None)

                return ('BREAK', list(map(int, nums)), conds)

            case 'DELETE':
                self.dlx.match('DELETE')
                nums = [self.dlx.match('NUM').value]

                while self.dlx.pointer().type == 'NUM':
                    nums.append(self.dlx.match('NUM').value)

                return ('DELETE', list(map(int, nums)))

            case 'BANG' | 'LONGLIST' | 'LIST' | 'QUIT' | 'EXPLICIT' | 'UNEXPLICIT' | 'STEP' | 'CONTINUE' | 'NEXT':
                t = self.dlx.pointer().type
                self.dlx.match(t)
                return (t,)

            case 'HELP':
                self.dlx.match('HELP')
                
                n = None
                if self.dlx.pointer().type != 'EOF':
                    n = self.dlx.pointer().value
                    self.dlx.next()
                
                return ('HELP', n)

            case 'NAME':
                n = self.dlx.match('NAME').value
                return ('NAME', n)

            case 'EOF':
                return []

            case _:
                raise ValueError("Unknown command: {}".format(
                    str(self.dlx.pointer().value)
                ))

# if __name__ == "__main__":
#     while True:
#         dbgp = DebuggerParser()
#         l = input("> ")
#         print(dbgp.parse(l))