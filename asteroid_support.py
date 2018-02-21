###########################################################################################
# Asteroid support code
#
# (c) 2018 - Lutz Hamel, University of Rhode Island
###########################################################################################

from asteroid_state import state

#########################################################################
def len_seq(seq_list):

    if seq_list[0] == 'nil':
        return 0

    elif seq_list[0] == 'seq':
        # unpack the seq node
        (SEQ, p1, p2) = seq_list

        return 1 + len_seq(p2)

    else:
            raise ValueError("unknown node type: {}".format(seq_list[0]))

###########################################################################################
def reverse_node_list(node_type, node_list):
    ''' 
    shallow reversal of a nil terminated node_type list
    assumes the structure of node_type node: (node_type, element, next)
    NOTE: the list needs to be ('nil',) terminated
    '''
    
    new_list = ('nil',)

    e = node_list
    while(e[0] != 'nil'):
        new_list = (node_type, e[1], new_list)
        e = e[2]

    return new_list

###########################################################################################
def append_node_list(node_type, list1, list2):
    '''
    append list2 to list1.  assume 'nil' terminated lists of node_type
    NOTE: there is a more efficient way of doing this by iterating...
    '''
    
    if list1[0] == 'nil':
        return list2

    else:
        return (node_type, 
                list1[1], 
                append_node_list(node_type,
                                 list1[2],
                                 list2))

###########################################################################################
def dump_AST(node):
    '''
    this function will print any AST that follows the
    
         (TYPE [, child1, child2,...])
    
    tuple format for tree nodes.
    '''
    _dump_AST(node)
    print('')

def _dump_AST(node, level=0):
    
    if isinstance(node, tuple):
        _indent(level)
        nchildren = len(node) - 1

        print("(%s" % node[0], end='')
        
        if nchildren > 0:
            print(" ", end='')
        
        for c in range(nchildren):
            _dump_AST(node[c+1], level+1)
            if c != nchildren-1:
                print(' ', end='')
        
        print(")", end='')

    elif isinstance(node, list):
        _indent(level)
        print("[", end='')

        nchildren = len(node)

        if nchildren > 0:
            print(" ", end='')
        
        for c in range(nchildren):
            _dump_AST(node[c], level+1)
            if c != nchildren-1:
                print(' ', end='')
        
        print("]", end='')

    else:
        print("%s" % str(node), end='')

def _indent(level):
    print('')
    for i in range(level):
        print('  |',end='')


###########################################################################################
def assert_match(input, expected):
    if input != expected:
        raise ValueError(
            "Pattern match failed: expected '{}' but got '{}'".format(
                expected, input))

###########################################################################################
def unify(term, pattern):
    '''
    unify term and pattern recursively and return the unifier.
    this unification allows for the same variable to appear
    multiple times in the unifier.  the user of this
    function must take appropriate actions if this happens.

    we assume that both the term and the pattern are made up of tuple
    nodes:

             (<type>, children*)

    leaf nodes must be nullary constructors.

    NOTE: if the pattern looks like an lval then it is treated like an lval, e.g. 
            let a@[0] = 'a@[0].
          stores the pattern 'a@[0] into lval a@[0].
    '''
    #lhh
    #print("unifying:\nterm {}\npattern {}\n\n".format(term, pattern))

    if isinstance(term, list) or isinstance(pattern, list):
        if not(isinstance(term, list) and isinstance(pattern, list)):
            raise ValueError("Pattern match failed: term and pattern do not agree on list constructor")

        elif len(term) != len(pattern):
            raise ValueError("Pattern match failed: term and pattern lists are not the same length")

        else:
            unifier = []
            for i in range(len(term)):
                unifier += unify(term[i], pattern[i])
            return unifier

    elif pattern[0] == 'deref':  # ('deref', id)
        sym = pattern[1]
        p = state.symtab.lookup_sym(sym)
        return unify(term,p)

    elif pattern[0] == 'id': # variable in pattern add to unifier
        sym = pattern[1]
        if sym == '_': # anonymous variable - ignore unifier
            return []
        else:
            unifier = (pattern, term)
            return [unifier]

    elif pattern[0] == 'structure-ix': # list/constructor lval access
        unifier = (pattern, term)
        return [unifier]

    elif pattern[0] == 'juxta': # constructor/function composition
        # we are looking at something like this:
        #       (0:'juxta', 
        #        1:(0:'id', 
        #           1:sym), 
        #        2:next))

        # check if we are looking at juxta nodes in both the term and the pattern
        if term[0] != pattern[0]:
            raise ValueError("pattern match failed: term and pattern disagree on 'juxta' node")
            # NOTE: list lval binding is now handled by 'structure-ix' node
            # this still could be legal if the pattern is a unification into a list location
            #if pattern[1][0] == 'id':
            #    (type, val) = state.symbol_table.lookup_sym(pattern[1][1])
            #    if type == 'list':
            #        return [(pattern, term)]
            #    else:
            #        raise ValueError("pattern match failed: term and pattern disagree on 'juxta' node")

        # get the types of the juxta args
        type_p1 = pattern[1][0]
        type_t1 = term[1][0]

        # if the types disagree then the juxta nodes describe something different from
        # constructor or function calls -- just keep unifying
        if type_t1 != type_p1:
            unifier = []
            unifier += unify(term[1], pattern[1])
            unifier += unify(term[2], pattern[2])
            return unifier

        # the arg node to juxta is not an id so just unify the rest of the juxta node and return
        assert type_t1 == type_p1
        if type_t1 != 'id':
            unifier = []
            unifier += unify(term[1], pattern[1])
            unifier += unify(term[2], pattern[2])
            return unifier

        # the juxta arg is an id - figure out the semantics of the id and then act accordingly
        assert type_t1 == 'id', type_p1 == 'id'
        sym_p1 = pattern[1][1]
        sym_t1 = term[1][1]

        # if term and pattern disagree on symbol name then error
        if sym_t1 != sym_p1:
            raise ValueError(
                "pattern match failed: name {} does not match name {}".format(
                    sym_t1, sym_p1))

        # at this point we know we are looking at a symbol in both the term and the pattern
        assert sym_t1 == sym_p1
        sym = sym_t1
        sym_val = state.symbol_table.lookup_sym(sym)

        # if the symbol is a list then return the pattern and the term as a unifier
        # NOTE: list lval binding is now handled by the 'structure-ix' node
        #if sym_val[0] == 'list':
        #    unifier = [(pattern, term)]
        #    return unifier

        # if the symbol is a constructor or function keep on unifying
        if sym_val[0] in ['constructor', 'function']:
            return unify(term[2], pattern[2])

        # we have a declared symbol not a list or constructor -- illegal?
        else:
            raise ValueError("pattern match failed: illega juxta context for symbol {}".format(sym))

    elif term[0] == 'id': # variable in term not allowed
        raise ValueError(
            "Pattern match failed: variable {} in term not allowed".format(
                term[1]))

    elif len(term) != len(pattern): # nodes are not of same the arity
        raise ValueError(
            "Pattern match failed: nodes {} and {} are not of the same arity".format(
                term[0], pattern[0]))

    elif term[0] != pattern[0]:  # nodes are not the same
        raise ValueError(
            "Pattern match failed: nodes {} and {} are not the same".format(
                term[0], pattern[0]))

    else:
        #lhh
        #print("unifying {}".format(pattern[0]))
        unifier = []
        for i in range(1,len(term)):
            unifier += unify(term[i], pattern[i])
        #lhh
        #print("returning unifier: {}".format(unifier))
        return unifier
    
###########################################################################################
def promote(type1, type2, strict=True):
    '''
    type promotion table for builtin primitive types
    '''
    
    if type1 == 'string' and type2 in['string', 'real', 'integer']:
        return 'string'
    if type2 == 'string' and type1 in['string', 'real', 'integer']:
        return 'string'
    elif type1 == 'real' and type2 in ['real', 'integer']:
        return 'real'
    elif type2 == 'real' and type1 in ['real', 'integer']:
        return 'real'
    elif type1 == 'integer' and type2 == 'integer':
        return 'integer'
    elif type1 == 'list' and type2 == 'list':
        return 'list'
    else:
        if strict:
            raise ValueError("type {} and type {} are incompatible".format(type1, type2))
        else:
            return ('none',)

###########################################################################################


