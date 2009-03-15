# encoding: utf-8
import unittest, sys, os

def suite():
  suites = []
  #import ${PROJECT_MODULE}.test.something
  #suites.append(${PROJECT_MODULE}.test.something.suite())
  return unittest.TestSuite(suites)

def test(*va, **kw):
  runner = unittest.TextTestRunner(*va, **kw)
  return runner.run(suite())

if __name__ == "__main__":
  test()
