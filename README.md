# Parser Workshop

A recursive-descent arithmetic expression parser supporting precedence, parentheses, unary operators, and clear syntax errors. Python 3.10+; standard library only.

## Run tests
```bash
python -m unittest discover -s tests -v
```

## Example
```python
from parser_workshop import evaluate
print(evaluate("2 + 3 * (4 - 1)"))
```

Only decimal numbers, +, -, *, /, and parentheses are supported. The evaluator does not call eval or execute Python code. Floating-point arithmetic is not appropriate for financial calculations. No variables, exponents, or implicit multiplication. Untrusted inputs should be subject to external size and time limits.

GitHub Actions is configured for Python 3.10, 3.12 and 3.13. Verify CI status before treating the project as validated.

MIT license; see LICENSE.
