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

## C++11 recursive-descent parser (additional implementation)

The existing Python code and tests remain unchanged. The portable C++11 core is at `cpp/include/parser.hpp`, with tests under `cpp/tests`.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
python -m unittest discover -s tests -v
```

GitHub Actions separately compiles the C++ host tests with GCC and Clang. Same arithmetic operators and precedence as Python. The C++ parser caps input at 4096 bytes and nesting at 64, rejects nonfinite results, and throws exceptions instead of Python errors. It does not support variables or firmware-specific memory guarantees.

**Embedded integration:** The C++ implementation is a host-tested reusable algorithm, not a verified Arduino/ESP32 sketch. Exceptions, STL allocations and memory limits require adaptation for small microcontrollers. Do not connect physical actuators based on this library without independent fail-safe controls and on-device testing.
