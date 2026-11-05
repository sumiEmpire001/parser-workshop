import math
import re

class ParseError(ValueError):
    pass

_TOKEN = re.compile(r"\s*(?:(\d+(?:\.\d+)?)|([()+*/-])|(\S))")

def tokenize(expression):
    if not isinstance(expression, str):
        raise TypeError("expression must be a string")
    tokens = []
    position = 0
    while position < len(expression):
        if expression[position:].isspace():
            break
        match = _TOKEN.match(expression, position)
        if not match or match.group(3):
            raise ParseError("unexpected character at offset %d" % position)
        tokens.append(match.group(1) or match.group(2))
        position = match.end()
    return tokens

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0

    def take(self, expected=None):
        if self.pos >= len(self.tokens):
            raise ParseError("unexpected end of expression")
        token = self.tokens[self.pos]
        if expected is not None and token != expected:
            raise ParseError("expected %s" % expected)
        self.pos += 1
        return token

    def expression(self):
        value = self.term()
        while self.pos < len(self.tokens) and self.tokens[self.pos] in ("+", "-"):
            op = self.take()
            rhs = self.term()
            value = value + rhs if op == "+" else value - rhs
        return value

    def term(self):
        value = self.factor()
        while self.pos < len(self.tokens) and self.tokens[self.pos] in ("*", "/"):
            op = self.take()
            rhs = self.factor()
            if op == "/" and rhs == 0:
                raise ParseError("division by zero")
            value = value * rhs if op == "*" else value / rhs
        return value

    def factor(self):
        token = self.take()
        if token == "-":
            return -self.factor()
        if token == "+":
            return self.factor()
        if token == "(":
            value = self.expression()
            self.take(")")
            return value
        if token[0].isdigit():
            try:
                value = float(token)
            except (ValueError, OverflowError) as exc:
                raise ParseError("invalid number") from exc
            if not math.isfinite(value):
                raise ParseError("number outside supported range")
            return value
        raise ParseError("expected number or parenthesized expression")

def evaluate(expression):
    tokens = tokenize(expression)
    parser = Parser(tokens)
    if not tokens:
        raise ParseError("empty expression")
    result = parser.expression()
    if parser.pos != len(tokens):
        raise ParseError("trailing tokens")
    return result
