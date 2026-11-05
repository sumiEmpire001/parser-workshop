import unittest
from parser_workshop import evaluate, ParseError, tokenize

class ParserTests(unittest.TestCase):
    def test_precedence(self):
        self.assertEqual(evaluate("2 + 3 * 4"), 14)
        self.assertEqual(evaluate("(2 + 3) * 4"), 20)
        self.assertEqual(evaluate("-2 * (3 + 1)"), -8)
        self.assertEqual(evaluate("8 / 4 / 2"), 1)

    def test_errors(self):
        for expression in ("", "2 +", "(2 + 3", "1 / 0", "1 + hello", "2 3", "2 ** 3"):
            with self.subTest(expression=expression):
                with self.assertRaises(ParseError):
                    evaluate(expression)

    def test_tokens(self):
        self.assertEqual(tokenize(" 12.5 + 2 "), ["12.5", "+", "2"])
        with self.assertRaises(TypeError):
            evaluate(None)

if __name__ == "__main__":
    unittest.main()
