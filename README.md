# Lexical-Analyzer

This project contains the implementation of a Lexical Analyzer for C and C++.

At the base of the functionality stands a Finite Deterministic Automata that consumes characters until one changes it's state.

The analyzer can identify the following types of tokens:
    - Identifiers
    - Integer Constant Values
    - Floating Points Constant Values
    - Keywords
    - Strings
    - Operators

It can also return errors in the following instances:
    - Unterminated String