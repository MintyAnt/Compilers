#!/usr/bin/env python2

import time

class Printer(object):
    def visit(self, node):
        if isinstance(node, EmptySet): 
            return "0"
        if isinstance(node, EmptyString): 
            return "e"
        if isinstance(node, Symbol):
            if (node != None):
                return node.symbol
            return ""
        if isinstance(node, Star):
            if (node.child != None):
                return node.child.accept(self) + "*"
            return ""
        if isinstance(node, Sequence):
            returning = None
            if (node.a != None):
                returning = node.a.accept(self)
            if (node.b != None):
                returning = returning + node.b.accept(self)
            return returning
        if isinstance(node, Or):
            isAValid = (not isinstance(node.a, EmptySet) and not isinstance(node.a, EmptyString))
            isBValid = (not isinstance(node.b, EmptySet) and not isinstance(node.b, EmptyString))
            if (isAValid and isBValid):
                return (node.a.accept(self) + "|" + node.b.accept(self))
            elif (isAValid):
                return node.a.accept(self)
            elif (isBValid):
                return node.b.accept(self)
            return ""
		
#boiler plate code for the Regex lab by mcgeep
class Nullable(object):
    def visit(self, node):
        if (node == None):
            return False
        if isinstance(node, EmptySet): 
            return False
        if isinstance(node, EmptyString): 
            return True
        if isinstance(node, Symbol): 
            return False
        if isinstance(node, Star): 
            return True
        if isinstance(node, Sequence): 
            if (node.a != None and node.b != None):
                return (node.a.accept(self) and node.b.accept(self))
            elif (node.a != None):
                return node.a.accept(self)
            elif (node.b != None):
                return node.b.accept(self)
            else:
                return False
        if isinstance(node, Or): 
            if (node.a != None and node.b != None):
                return (node.a.accept(self) or node.b.accept(self))
            elif (node.a != None):
                return node.a.accept(self)
            elif (node.b != None):
                return node.b.accept(self)
            else:
                return False
		
class Derivative(object):
    def __init__ (self):
        self.nullable = Nullable()
        self.c = ''
		
    def visit(self, node):
        if isinstance(node, EmptySet):
            return node

        if isinstance(node, EmptyString): 
            return EmptySet.GetInstance()

        if isinstance(node, Symbol):
            if self.c == node.symbol:
                return EmptyString.GetInstance()
            else: 
                return EmptySet.GetInstance()

        if isinstance(node, Star):
            if (node.child != None):
                args = (node.child.accept(self), node)
                return Factory.GetInstanceFromMap("Sequence", args)
                #return Sequence(node.child.accept(self), node)
            return None
			
        if isinstance(node, Sequence):
            args = (node.a.accept(self), node.b)
            result = Factory.GetInstanceFromMap("Sequence", args)
            #result = Sequence(node.a.accept(self), node.b)
            if not node.a.accept(self.nullable):
                return result
            else:
                args = (result, node.b.accept(self))
                return Factory.GetInstanceFromMap("Or", args)
                #return Or(result,node.b.accept(self))
				
        if isinstance(node, Or):
            args = (node.a.accept(self), node.b.accept(self))
            return Factory.GetInstanceFromMap("Or", args)
            #return Or(node.a.accept(self), node.b.accept(self))
		
class Node(object):
    def accept(self, visitor):
        return visitor.visit(self)
		
gEmptySetSingleton = None
class EmptySet(Node):
    def GetInstance():
        global gEmptySetSingleton
        if (gEmptySetSingleton == None):
            gEmptySetSingleton = EmptySet()
        return gEmptySetSingleton
	
gEmptyStringSingleton = None
class EmptyString(Node):
    def GetInstance():
        global gEmptyStringSingleton
        if (gEmptyStringSingleton == None):
            gEmptyStringSingleton = EmptyString()
        return gEmptyStringSingleton
	
class Symbol(Node):
    symbol = None
    def __init__(self,symbol):
        self.symbol = symbol

class Star(Node):
    def __init__(self,child):
        self.child = child
		
class Sequence(Node):
    def __init__(self,a,b):
        self.a = a
        self.b = b
		
class Or(Node):
    def __init__(self,a,b):
        self.a = a
        self.b = b

_NodeMap = {}
class Factory():
    def GetInstanceFromMap(inType, inNodeArgs):
        global _NodeMap;
        if (not inType in _NodeMap):
            _NodeMap[inType] = {}
        if (not inNodeArgs in _NodeMap[inType]):
            _NodeMap[inType][inNodeArgs] = Factory.Instantiate(inType, inNodeArgs)

        return _NodeMap[inType][inNodeArgs]

    def Instantiate(inType, inNodeArgs):
        if (inType == "Symbol"):
            return Symbol(inNodeArgs)
        elif (inType == "Star"):
            return Star(inNodeArgs)
        elif (inType == "Sequence"):
            return Sequence(inNodeArgs[0], inNodeArgs[1])
        elif (inType == "Or"):
            return Or(inNodeArgs[0], inNodeArgs[1])


def match(regex, string):
    printer = Printer()
    d = Derivative()
    nullable = Nullable()
    for c in list(string):
        #print ("currentChar %s" % c)
        d.c = c
        regex = regex.accept(d)
        print(printer.visit(regex))
    return regex.accept(nullable)

if __name__ == '__main__':
    beginTime = time.clock()
    testRegex = Or(Symbol('a'),Symbol('b'))
    print (match(testRegex,'c'))
    print ("Total Time: ", time.clock() - beginTime)
	
    beginTime = time.clock()
    testRegex = Star(Or(Symbol('a'),Symbol('b')))
    print (match(testRegex,'a'))
    print ("Total Time: ", time.clock() - beginTime)